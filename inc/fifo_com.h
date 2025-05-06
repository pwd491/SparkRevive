#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>


#define FIFO_MSG_LEN   (512)
#define FIFO_MSG_HEAD  (8)  /*two sizeof(int)*/

#define FIFO_SERVER "/tmp/fifoserver"
#define FIFO_CLIENT  "/tmp/fifo."
#define FILE_MODE  (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define CLIENT_OPEN_FLAG      (6666)


#define SCANCODE_OK                        0x0D
#define SCANCODE_MENU                      0x12
#define SCANCODE_EXIT                      0x1B
#define SCANCODE_HOME                      SCANCODE_MENU
#define SCANCODE_BACK                      SCANCODE_EXIT


#define SCANCODE_PGUP                      0x8E//0xAC//0x21
#define SCANCODE_PGDN                      0x8F//0xAD//0x22

#define SCANCODE_LEFT                      0x25
#define SCANCODE_UP                        0x26
#define SCANCODE_RIGHT                     0x27
#define SCANCODE_DOWN                      0x28


#define SCANCODE_0                         0x30
#define SCANCODE_1                         0x31
#define SCANCODE_2                         0x32
#define SCANCODE_3                         0x33
#define SCANCODE_4                         0x34
#define SCANCODE_5                         0x35
#define SCANCODE_6                         0x36
#define SCANCODE_7                         0x37
#define SCANCODE_8                         0x38
#define SCANCODE_9                         0x39

#define SCANCODE_F1                        0x70 //Red
#define SCANCODE_F2                        0x71 //Green
#define SCANCODE_F3                        0x72 //Yellow
#define SCANCODE_F4                        0x73 //Blue
#define SCANCODE_RED                       SCANCODE_F1
#define SCANCODE_GREEN                     SCANCODE_F2
#define SCANCODE_YELLOW                    SCANCODE_F3
#define SCANCODE_BLUE                      SCANCODE_F4

#define SCANCODE_F1_KEY                       0x80
#define SCANCODE_TIMER                        0x82
#define SCANCODE_TIMESHIFT                    0x83
#define SCANCODE_PIP                          0x84
#define SCANCODE_TVSAT                        0x85
#define SCANCODE_TVRADIO                      0x86
#define SCANCODE_RECALL                       0x87
#define SCANCODE_FIND                         0x88
#define SCANCODE_RECORD                       0x89
#define SCANCODE_FAV                          0x8B
#define SCANCODE_FOLDER                       0x8C
#define SCANCODE_STOP                         0x8D
#define SCANCODE_PLAY                         0x90
#define SCANCODE_PREV                         0x91
#define SCANCODE_NEXT                         0x92
#define SCANCODE_BACK_SLOW                    0x93
#define SCANCODE_FORWARD_SLOW                 0x94
#define SCANCODE_WHITE                        0x95
#define SCANCODE_USB                          0x96

#define SCANCODE_POWER                     0xA0
#define SCANCODE_MUTE                      0xA1
#define SCANCODE_VOL_DOWN                  0xA2
#define SCANCODE_VOL_UP                    0xA3
#define SCANCODE_PROG_DOWN                 0xA4
#define SCANCODE_PROG_UP                   0xA5
#define SCANCODE_GUIDE                     0xA6
#define SCANCODE_VIEW                      0xA7
#define SCANCODE_VIDEO_FORMAT              0xA8
#define SCANCODE_INFO                      0xA9
#define SCANCODE_UHF                       0xAA
#define SCANCODE_PAUSE                     0xAB
#define SCANCODE_RECEDE                    0xAC //快退
#define SCANCODE_FORWARD                   0xAD //快进
#define SCANCODE_SAT                       0xAE
#define SCANCODE_TTX                       0xAF
#define SCANCODE_SUBT                      0xB0

#define PANEL_SCANCODE_POWER                    0xC0
#define PANEL_SCANCODE_MENU                       0xC1
#define PANEL_SCANCODE_ENTER                      0xC2
#define PANEL_SCANCODE_UP                              0xC3
#define PANEL_SCANCODE_DOWN                      0xC4
#define PANEL_SCANCODE_LEFT                         0xC5
#define PANEL_SCANCODE_RIGHT                      0xC6

enum mesg_type_e
{
    /*client msg*/
    CLIENT_OPEN = 1,
    CLIENT_CLOSE,
    CLIENT_DRAW,

    /*server msg*/
    SER_BUF1_MEM,
    SER_BUF2_MEM,
    SER_BUF_XRES,
    SER_BUF_YRES,
    SER_BUF_BITS_PER_PIXEL,
    SER_START_CLIENT,
    SER_STOP_CLIENT,
    SER_KEY_MSG,

    CLIENT_STARTGUI,
    CLIENT_STOPGUI,
    CLIENT_INFO,

    //二进制000~111,为1的那一位表示plugin可以用。最右边为tuner0，从右开始。
    SER_TUNER_INFO,
    
    CLIENT_OPEN_GUI_DIRECT,
    CLIENT_CLOSE_APP_WITH_GUI,

}mesg_type_T;

typedef struct mesg_s
{
    int mesg_len;
    int mesg_type;
    char mesg_data[FIFO_MSG_LEN];
}mesg_T;

enum draw_type_e
{
    TYPE_SET_PIXEL,
    TYPE_DRAW_LINE,
    TYPE_DRAW_RECT,
    TYPE_FILL_RECT,
    TYPE_DRAW_TRIANGLE,
    TYPE_FILL_TRIANGLE,
    TYPE_DRAW_CIRCLE,
    TYPE_FILL_CIRCLE,
    TYPE_DRAW_BITMAP,
    TYPE_DRAW_TEXT,
};
typedef struct draw_info_s
{
    unsigned char type;  /**/
    unsigned char color[4];
    union
    {
        struct
        {
            int x_pos;
            int y_pos;
        }pixel;
        struct
        {
            int x_pos1;
            int y_pos1;
            int x_pos2;
            int y_pos2;
            int line_width;
        }line;
        struct
        {
            int top;
            int left;
            int width;
            int height;
        }draw_rect;
        struct
        {
            int top;
            int left;
            int width;
            int height;
        }fill_rect;
        struct
        {
            int x_pos1;
            int y_pos1;
            int x_pos2;
            int y_pos2;
            int x_pos3;
            int y_pos3;
        }draw_triangle;
        struct
        {
            int x_pos1;
            int y_pos1;
            int x_pos2;
            int y_pos2;
            int x_pos3;
            int y_pos3;
        }fill_triangle;
        struct
        {
            int x_pos;
            int y_pos;
            int radii;
        }draw_circle;
        struct
        {
            int x_pos;
            int y_pos;
            int radii;
        }fill_circle;
        struct
        {
            int top;
            int left;
            int width;
            int height;
            int style; /*0 for left, 1 for center, 2 for right*/
            char num;
            char info[64];
        }text;
    }contents;

}draw_info_T;

int mesg_send(int fd, mesg_T *mptr);
int mesg_recv(int fd, mesg_T *mptr);


