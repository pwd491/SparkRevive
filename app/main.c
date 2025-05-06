/*
 * File: main.c    
 * Author:  
 * Brief: main file, the entrance of the application.
 * 
 */

/*
 * History:
 * ================================================================
 * 
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include <signal.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <errno.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <execinfo.h>
#include "ywdefs.h"

#include "ywos.h"

#include "ywtimer_ext.h"

#include "fifo_com.h"
#include "fifo_client.h"

#include"ywgui_ext.h"
#include "ywstring.h"


static int readfd = 0;
static int writefd = 0;
static unsigned int screen_width = 0;
static unsigned int screen_height = 0;
/*7->111, indicate plug-in can use all the three tuners*/
/*3->011 tuner0 and tuner1 is allowed*/
/*4->100 tuner2 is allowed*/
static unsigned int tuner_info = 7;
/*GUI show with the App start, do not need press red key */
static BOOL bGuiDirectShow = FALSE;
/*if GUI is destroyed, the App close immediately*/
static BOOL bAppCloseWithGui = FALSE;
static char prog_name[256] = {0};
static char client_path[256] = {0};


/*the predefined functions*/
extern void YWPLUGIN_Init(void);
extern void YWPLUGIN_Term(void);
extern S8* YWPLUGIN_GetVersion(void);

/*the  GUI functions*/
extern void APP_MsgProc(void * para);
extern void APP_GuiInit(void);
extern void APP_GuiTerm(void);

/*the event functions*/
extern YW_ErrorType_T YWEVT_Init(void);
extern YW_ErrorType_T YWEVT_Term(void);
extern S8* YWPLUGIN_GetVersion(void);

void set_gui_diretc_show(BOOL bShow)
{
    bGuiDirectShow = bShow;
}

void set_app_close_with_gui(BOOL bSync)
{
    bAppCloseWithGui = bSync;
}

int get_tuner_info(void)
{
    return tuner_info;
}

void client_term(void)
{
    mesg_T mesg;

    if(bAppCloseWithGui)
    {
        memset(&mesg, 0, sizeof(mesg));
        snprintf(mesg.mesg_data, sizeof(mesg.mesg_data), "%s", prog_name);
        mesg.mesg_len = strlen(mesg.mesg_data);
        mesg.mesg_type = CLIENT_CLOSE_APP_WITH_GUI;
        mesg_send(writefd, &mesg);
    }
    
    memset(&mesg, 0, sizeof(mesg));
    snprintf(mesg.mesg_data, sizeof(mesg.mesg_data), "%s", prog_name);
    mesg.mesg_len = strlen(mesg.mesg_data);
    mesg.mesg_type = CLIENT_CLOSE;
    mesg_send(writefd, &mesg);
    printf("client term.\n");
}
int osd_process_init(int argc, char *argv[])
{
    //int readfd = 0;
    //int writefd = 0;
    mesg_T mesg;
    int n = 0;
    int start_draw = 0;
    int key_num = 0;
    char *p = NULL;
    (void)argc;

    memset(prog_name, 0, sizeof(prog_name));
    /*create client fifo*/
    p = strrchr(argv[0], '/');
    p++;
    strncpy(prog_name, p, sizeof(prog_name) - 1);
    //snprintf(client_path, sizeof(client_path), "%s%ld", FIFO_CLIENT, (long)pid);
    snprintf(client_path, sizeof(client_path), "%s%s", FIFO_CLIENT, p);
    if((mkfifo(client_path, FILE_MODE) < 0) && (errno != EEXIST))
    {
        printf("make fifo faile.\n");
        return 0;
    }
    /*open server fifo to write*/
    writefd = open(FIFO_SERVER, O_WRONLY | O_NONBLOCK, 0);

    /*open client fifo to read*/
    readfd = open(client_path, O_RDONLY | O_NONBLOCK, 0);
    
    /*send open msg to server*/
    memset(&mesg, 0, sizeof(mesg));
    snprintf(mesg.mesg_data, sizeof(mesg.mesg_data), "%s", p);
    mesg.mesg_len = strlen(mesg.mesg_data);
    mesg.mesg_type = CLIENT_OPEN;
    mesg_send(writefd, &mesg);

    /*send cur plugin version to server*/
    memset(&mesg, 0, sizeof(mesg));
    snprintf(mesg.mesg_data, sizeof(mesg.mesg_data), "<name=%s><version=%s>", (char*)p, (char*)YWPLUGIN_GetVersion());
    mesg.mesg_len = strlen(mesg.mesg_data);
    mesg.mesg_type = CLIENT_INFO;
    mesg_send(writefd, &mesg);

    if(bGuiDirectShow)
    {
        memset(&mesg, 0, sizeof(mesg));
        snprintf(mesg.mesg_data, sizeof(mesg.mesg_data), "%s", prog_name);
        mesg.mesg_len = strlen(mesg.mesg_data);
        mesg.mesg_type = CLIENT_OPEN_GUI_DIRECT;
        mesg_send(writefd, &mesg);
    }

    /*init string and set system menu language*/
	YWSTR_InitString();
	YWSTR_SetLanguage(LANGUAGE_ENGLISH);


    /*read msg from server*/
    while(1)
    {
        memset(&mesg, 0, sizeof(mesg));
        n = mesg_recv(readfd, &mesg);
        if(n <= 0)
        {
            usleep(50000);
            continue;
        }
        switch(mesg.mesg_type)
        {
            case SER_BUF1_MEM:
                break;
            case SER_BUF2_MEM:
                break;
            case SER_BUF_XRES:
                screen_width = atol(mesg.mesg_data);
                printf("width: %d\n", screen_width);
                break;
            case SER_BUF_YRES:
                screen_height = atol(mesg.mesg_data);
                printf("height: %d\n", screen_height);
                break;
            case SER_TUNER_INFO:
                tuner_info = atol(mesg.mesg_data);
                printf("tuner_info: %d\n", tuner_info);
                break;
            case SER_START_CLIENT:
            {
				int sparkver = 0;

				sparkver = atol(mesg.mesg_data);
				if (sparkver >=11420)	//只有在spark 1.1.42版本以上才能运行基于ywgui的PLUGIN
				{
	                start_draw = 1;
					APP_GuiInit();
					APP_MsgProc(NULL);
					APP_GuiTerm();
				}
				else
				{
					client_term();
				}
                break;
            }
            case SER_BUF_BITS_PER_PIXEL:
                break;
            case SER_KEY_MSG:
                key_num = atol(mesg.mesg_data);
                if(start_draw > 0)
                {
                    /*do nothing*/
                }
                break;
            default:
                break;
        }
        usleep(50000);
    }


    return 0;
}


int osd_process_term (void)
{
	if (readfd>0)
	{
		printf("osd_process_term----------------->close read fd\n");
		close(readfd);
	}

	if (writefd>0)
	{
		printf("osd_process_term----------------->close write fd\n");

		close(writefd);
	}
	unlink(client_path);

}

void sigterm_handler(int sig)
{
	osd_process_term();

	YWPLUGIN_Term();

    #ifdef YWGUI_ENABLE_TIMER
    YWTIMER_Term();
    YWEVT_Term();
    #endif

	YWOS_Term();
	exit(0);
}

int main(int argc, char *argv[])
{
    YW_ErrorType_T Error = YW_NO_ERROR;
    
	signal(SIGINT, sigterm_handler);
	signal(SIGTERM, sigterm_handler);
	//signal(SIGCHLD, SIG_IGN);

	Error = YWOS_Init();
    if(Error != YW_NO_ERROR)
    {
        printf("YWOS_Init failed.\n");
    }
    #ifdef YWGUI_ENABLE_TIMER
    Error = YWEVT_Init();
    if(Error != YW_NO_ERROR)
    {
        printf("YWEVT_Init failed.\n");
    }
    Error= YWTIMER_Init();
    if(Error != YW_NO_ERROR)
    {
        printf("YWTIMER_Init failed.\n");
    }
    #endif

	YWPLUGIN_Init();

	osd_process_init(argc, argv);

	APP_GuiTerm();

    #ifdef YWGUI_ENABLE_TIMER
    Error = YWTIMER_Term();
    if(Error != YW_NO_ERROR)
    {
        printf("YWTIMER_Term failed.\n");
    }
    Error = YWEVT_Term();
    if(Error != YW_NO_ERROR)
    {
        printf("YWEVT_Term failed.\n");
    }
    #endif
	exit(0);

    return 0;
}


