#include "typedef.h"
#include "fifo_com.h"

int mesg_send(int fd, mesg_T *mptr)
{
    int n = 0;
    n = write(fd, mptr, FIFO_MSG_HEAD + mptr->mesg_len);
    if(n != FIFO_MSG_HEAD + mptr->mesg_len)
    {
        printf("fifo full or write faile.\n");
        perror("send error!\n");
    }
    return n;
}

int mesg_recv(int fd, mesg_T *mptr)
{
    int len = 0;
    int n = 0;

    if((n = read(fd, mptr, FIFO_MSG_HEAD)) == 0)
    {
        /*read file end*/
        return 0;
    }
    else if(n != FIFO_MSG_HEAD)
    {
        //printf("recv msg head error.\n");
        return -1;
    }

    if((len = mptr->mesg_len) > 0)
    {
        if((n = read(fd, mptr->mesg_data, len)) != len)
        {
            printf("recv msg error.\n");
            return -1;
        }
    }

    return len;
}


