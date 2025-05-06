/**********************************文件头部注释************************************/
//
//
//                      Copyright (C), 2005-2010, AV Frontier Tech. Co., Ltd.
//
//
// 文件名：        ywvfs.c
//
// 创建者：        chenj
//
// 创建时间：    2008.09.19
//
// 文件描述：    完成对文件系统的封装
//
// 修改记录：   日       期      作      者       版本      修定
//                       ---------            -----------           -----           -----
//                             2008.09.19        chenj       0.01           新建
//
/*****************************************************************************************/

#ifndef _LARGEFILE64_SOURCE
/* For 64 */
#define _LARGEFILE64_SOURCE
#endif
#include <stdio.h>
#include <linux/magic.h>
#include <sys/statfs.h>
#include <stdarg.h>

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#include <errno.h>
#include "ywdefs.h"
#include "ywos.h"
#include "ywlib.h"
#include "ywvfs.h"


/* Private Macros ----------------------------------------------------- */

#define YWVFS_MAX_DISK                              2


//#define YWVFS_MAX_DEVICEINFO                      10 /*一个硬盘最多10个分区*/


/*以下是文件系统的类型定义*/
#define YWVFS_FAT16_FS_TYPE						    0x04
#define YWVFS_FAT32_FS_TYPE							0x0B
#define YWVFS_E2FS_FS_TYPE							0x83
/*以上是文件系统的类型定义*/
#if defined(ST_OSLINUX) && defined(DEBUG_TRACE)
//for errors
#include <stdlib.h>
#include <stdio.h>
#define YWHAL_ERROR(x) perror(x)
#else
#define YWHAL_ERROR(x)
#endif

#ifndef NTFS_SUPER_MAGIC
#define NTFS_SUPER_MAGIC 0x5346544e
#endif

#define CIFS_MAGIC_NUMBER 0xFF534D42
/* Private Constants -------------------------------------------------- */


typedef struct  YWVFS_HandleParams_s
{
    YW_DeviceName_t         DiskName;
    YWHDD_Handle_T          HddHandle;
    //YWOsplusHandle_T        OsplusHandle;
    BOOL                    IsOpen;
    //U32                   index;             /*按照先后顺序进行排序*/
    U32                     VolumeNum;
    YWVFS_VolumeInfo_T      VolumeInfo[YWVFS_MAX_VOLUME_NUM];

}YWVFS_HandleParams_T;


/* Private Variables -------------------------------------------------- */
/* Global Variables ------------------------------------------------------- */

static BOOL                 YWVFSi_ISInitialized = FALSE;


static U32                  YWVFSi_MonutVolumeIndex = 0;
static YW_DeviceName_t      YWVFSi_DiskName[YWVFS_MAX_DISK] = {"HDD0","HDD1"};
static YWVFS_HandleParams_T YWVFSi_HandleParam[YWVFS_MAX_DISK];


/* Private Function prototypes ---------------------------------------- */
static char *YWVFSi_GetErrorText(U32 errorNo);

#if 0

/***********************************************************************
	函数说明:	查HDD handle索引
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
static YW_ErrorType_T  YWVFSi_GetHddDiskIndex(YWHDD_Handle_T HddHandle,U32 *index)
{
    U32 i;

    if(index == NULL)
    {
        return YWHAL_ERROR_BAD_PARAMETER;
    }

    for(i=0;i<YWVFS_MAX_DISK;i++)
    {
        if(YWVFSi_HandleParam[i].HddHandle == HddHandle)
        {
            *index = i;
            break;
        }
    }

    if(i>= YWVFS_MAX_DISK)
    {
        *index = YWVFS_MAX_DISK;
    }

    return YW_NO_ERROR;
}


/***********************************************************************
	函数说明:	VFS初始化
	参数说明:

       修改记录:	日       期      作      者       修定
 				       ---------         ---------         -----
               		        2008.09.25         chenj              新建
************************************************************************/
YW_ErrorType_T YWVFS_Init(void)
{
    U32                     i;

    for(i=0;i<YWVFS_MAX_DISK;i++)
    {
        YWLIB_Memset(YWVFSi_HandleParam[i].DiskName, 0, sizeof(YW_DeviceName_t));
        YWLIB_Memset(YWVFSi_HandleParam[i].VolumeInfo, 0, sizeof(YWVFS_VolumeInfo_T)*YWVFS_MAX_VOLUME_NUM);
        //YWVFSi_HandleParam[i].OsplusHandle          = (YWOsplusHandle_T)NULL;
        YWVFSi_HandleParam[i].VolumeNum             = 0;
        YWVFSi_HandleParam[i].IsOpen                = FALSE;
    }

    YWVFSi_MonutVolumeIndex = 0;
    YWVFSi_ISInitialized = TRUE;

    return YW_NO_ERROR;
}


/***********************************************************************
	函数说明:	term vfs
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
YW_ErrorType_T YWVFS_Term( void)
{
    U32         i;

    YWVFS_UnMountAll();

    for(i=0;i<YWVFS_MAX_DISK;i++)
    {
        YWLIB_Memset(YWVFSi_HandleParam[i].DiskName, 0, sizeof(YW_DeviceName_t));
        YWLIB_Memset(YWVFSi_HandleParam[i].VolumeInfo, 0, sizeof(YWVFS_VolumeInfo_T)*YWVFS_MAX_VOLUME_NUM);
        YWVFSi_HandleParam[i].HddHandle         = (YWHDD_Handle_T)NULL;
        //YWVFSi_HandleParam[i].OsplusHandle      = (YWOsplusHandle_T)NULL;
        YWVFSi_HandleParam[i].VolumeNum         = 0;
        YWVFSi_HandleParam[i].IsOpen            = FALSE;
    }
    YWVFSi_MonutVolumeIndex = 0;
    YWVFSi_ISInitialized    = FALSE;
    return YW_NO_ERROR;
}




#define YWVFS_VOLUME_OPERATION
/***********************************************************************
	函数说明:	取分区信息
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
static YW_ErrorType_T YWVFSi_GetVolum(YWVFS_HandleParams_T *HandleParam)
{
    U32                         i,index = 0;
    U32                         ii,jj;
    char                        VolumeName[DISK_DEVNAME_LENGTH];
    YWVFS_HandleParams_T        TempParam;


    if(HandleParam == NULL)
    {
        return YWHAL_ERROR_FEATURE_NOT_SUPPORTED;
    }

    YWLIB_Memset(&TempParam, 0, sizeof(YWVFS_HandleParams_T));
    YWLIB_Memcpy(&TempParam, HandleParam, sizeof(YWVFS_HandleParams_T));
    TempParam.VolumeNum = 0;
    YWLIB_Memset(&(TempParam.VolumeInfo), 0, sizeof(YWVFS_VolumeInfo_T)*YWVFS_MAX_VOLUME_NUM);

    //----check which disk is needed operating
    for(i=0; i<diskNum; i++)
    {
        if(strcmp(diskName[i],TempParam.DiskName) == 0)
        {
            index = i;
            break;
        }
    }
    if (i == diskNum)// can't find disk
    {
        return YWHAL_ERROR_INVALID_HANDLE;
    }
    for(i=0; i<pDiskInfo[index]->partitions; i++)
    {
        switch(pDiskInfo[index]->ptes[i].part_table->sys_ind)
        {
            case 0x1: /*fat12*/
            case 0x11:
            {
                TempParam.VolumeInfo[i].type= YWVFS_FS_TYPE_FAT12;
                break;
            }

            case 0x06 : /*fat 16*/
            case 0x0E :
            case 0x14 :
            case 0x16 :
            case 0x1E :
            case YWVFS_FAT16_FS_TYPE:
            {
                TempParam.VolumeInfo[i].type = YWVFS_FS_TYPE_FAT16;
                break;
            }

            case 0x0C : /*fat 32*/
            case 0x1B :
            case 0x1C :
            case YWVFS_FAT32_FS_TYPE:
            {
                TempParam.VolumeInfo[i].type = YWVFS_FS_TYPE_FAT32;
                break;
            }

            case YWVFS_E2FS_FS_TYPE: /*e2fs*/
            {
                TempParam.VolumeInfo[i].type = YWVFS_FS_TYPE_EXT2;
                break;
            }

            case 0x05: /*msdos*/
            case 0x0f: /*windows95*//*ntfs*/
            case 0x85: /*linux*/ /*e3fs*/
            default:
            {
                TempParam.VolumeInfo[i].type = YWVFS_FS_TYPE_UNKNOW;
            }
        }//swtich
        //get_sectorsize(pDiskInfo[index]);
        TempParam.VolumeInfo[i].VolumeTotalSize = pDiskInfo[index]->sector_size*get_nr_sects(pDiskInfo[index]->ptes[i].part_table);
        YWLIB_Sprintf(VolumeName, "%s%d",diskName[index],i+1); //name sypt sda1 or hda2
        YWLIB_Strcpy((S8 *)TempParam.VolumeInfo[i].volumeName, (S8 *)VolumeName);
        for(ii=0; ii<YWVFS_MAX_DISK;ii++)
        {
            if(!(YWVFSi_HandleParam[ii].IsOpen ))
                continue;

            for(jj=0;jj<YWVFSi_HandleParam[ii].VolumeNum;jj++)
            {
                if(YWLIB_Strcmp(TempParam.VolumeInfo[i].volumeName,
                    YWVFSi_HandleParam[ii].VolumeInfo[jj].volumeName)==0)
                {
                    YWLIB_Strcpy(TempParam.VolumeInfo[i].mountName,
                        YWVFSi_HandleParam[ii].VolumeInfo[jj].mountName);
                    TempParam.VolumeInfo[i].type = YWVFSi_HandleParam[ii].VolumeInfo[jj].type;
                }
            }
        }
    }
    TempParam.VolumeNum = pDiskInfo[index]->partitions;


    YWLIB_Memset(HandleParam, 0, sizeof(YWVFS_HandleParams_T));
    YWLIB_Memcpy(HandleParam, &TempParam, sizeof(YWVFS_HandleParams_T));

    return YW_NO_ERROR;
}

/***********************************************************************
	函数说明:	根据分区名查询硬盘的句柄
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
YW_ErrorType_T YWVFS_GetHddHandleByVolumeName(S8 *VolumeName,YWHDD_Handle_T *HddHandle)
{
    YW_ErrorType_T              YW_ErrorCode = YW_NO_ERROR;
    U32                         i,j;
    U32                         uiVolumeIndex = 0;

    if((VolumeName == NULL)||(HddHandle == NULL))
    {
        return YWHAL_ERROR_BAD_PARAMETER;
    }

    for(i=0; i<YWVFS_MAX_DISK;i++)
    {
        if(!(YWVFSi_HandleParam[i].IsOpen))
            continue;

        for(j=0;j<YWVFSi_HandleParam[i].VolumeNum;j++)
        {
            if(YWLIB_Strcmp(VolumeName , (S8 *)YWVFSi_HandleParam[i].VolumeInfo[j].volumeName))
            {
                *HddHandle = YWVFSi_HandleParam[i].HddHandle;
                return YW_NO_ERROR;
            }
        }
    }

    return YWHAL_ERROR_UNKNOWN_DEVICE;

}
/***********************************************************************
	函数说明:	取分区信息
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
YW_ErrorType_T YWVFS_GetVolumInfo(YWVFS_VolumesInfo_T * volumesInfo)
{
    YW_ErrorType_T          YW_ErrorCode = YW_NO_ERROR;
    U32                             i,j;
    U32                             uiVolumeIndex = 0;

    if(volumesInfo == NULL)
    {
        YWOSTRACE((YWOS_TRACE_ERROR,"[error][YWVFS_GetVolumInfo] bad param \n"));
        return YWHAL_ERROR_BAD_PARAMETER;
    }

    for(i=0; i<YWVFS_MAX_DISK;i++)
    {
        if(!(YWVFSi_HandleParam[i].IsOpen))
            continue;

        YW_ErrorCode = YWVFSi_GetVolum(&YWVFSi_HandleParam[i]);
        if(YW_ErrorCode != YW_NO_ERROR)
        {
            return YWHAL_ERROR_DEVICE_BUSY;
        }

        for(j=0;j<YWVFSi_HandleParam[i].VolumeNum;j++)
        {
            volumesInfo->info[uiVolumeIndex].VolumeTotalSize    = YWVFSi_HandleParam[i].VolumeInfo[j].VolumeTotalSize;
            volumesInfo->info[uiVolumeIndex].type               = YWVFSi_HandleParam[i].VolumeInfo[j].type;
            YWLIB_Strcpy((S8 *)volumesInfo->info[uiVolumeIndex].volumeName , (S8 *)YWVFSi_HandleParam[i].VolumeInfo[j].volumeName);
            YWLIB_Strcpy((S8 *)volumesInfo->info[uiVolumeIndex].mountName, (S8 *)YWVFSi_HandleParam[i].VolumeInfo[j].mountName);

            uiVolumeIndex++;
        }
    }

    volumesInfo->volumeNum = uiVolumeIndex;

    return YW_ErrorCode;
}

/***********************************************************************
	函数说明:	在硬盘上建立分区
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
YW_ErrorType_T YWVFS_CreateVolume(YWHDD_Handle_T HddHandle,YWVFS_Partition_T * partition)
{
    YW_ErrorType_T          YW_ErrorCode = YW_NO_ERROR;
    U32                     index;
    S32                     ReturnValue;
    BOOL                    ret;

    YW_ErrorCode = YWVFSi_GetHddDiskIndex(HddHandle, &index);
    if((YW_ErrorCode != YW_NO_ERROR)&&(index< YWVFS_MAX_DISK))
    {
        YW_ErrorCode = YWHAL_ERROR_INVALID_HANDLE;
        return YW_ErrorCode;
    }

   if(add_partition(pDiskInfo[index], pDiskInfo[index]->typeSel[partition->type - 1],//need match echo other
               partition->startBlock, partition->startBlock+partition->BlockNum, partition->raw_type))
    {
        YWVFSi_GetVolum(&YWVFSi_HandleParam[index]);
    }
    else
    {
        YW_ErrorCode = YWVFS_ERROR_CREATE_VOLUME;
    }


    return YW_ErrorCode;
}

/***********************************************************************
	函数说明:	删除分区
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
YW_ErrorType_T YWVFS_DeleteVolume(S8 *volumeName)
{
    YW_ErrorType_T      YW_ErrorCode = YW_NO_ERROR;
    U32                 index,i;

    for(index = 0 ;index < YWVFS_MAX_DISK ; index++)
        for (i = 0; i < pDiskInfo[index]->partitions; i++)
            if (YWLIB_Strcmp(YWVFSi_HandleParam[index].VolumeInfo[i].volumeName,volumeName) == 0)
                break;

    if((index == YWVFS_MAX_DISK) && (i == pDiskInfo[index]->partitions ))
    {
        return YWVFS_ERROR_DELETE_PARTITION;
    }
    delete_partition(pDiskInfo[index],i);

    for(index=0; index<YWVFS_MAX_DISK; index++) //删除分区后重新取一下分区信息
        YWVFSi_GetVolum(&YWVFSi_HandleParam[index]);

    return YW_ErrorCode;
}

/***********************************************************************
	函数说明:	挂分区到VFS上
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
                2009.02.17         chenj              modify
************************************************************************/
YW_ErrorType_T YWVFS_Mount( S8 *volumeName,const S8    *Dir,YWVFS_FsType_T type)
{
    YW_ErrorType_T      YW_ErrorCode = YW_NO_ERROR;
    U32                 index,i;

    for(index = 0 ;index < YWVFS_MAX_DISK ; index++)
        for (i = 0; i < pDiskInfo[index]->partitions; i++)
            if (YWLIB_Strcmp(YWVFSi_HandleParam[index].VolumeInfo[i].volumeName,volumeName) == 0)
                break;

    if((index == YWVFS_MAX_DISK) && (i == pDiskInfo[index]->partitions ))
    {
        return YWVFS_ERROR_DELETE_PARTITION;
    }

    if(PART_Mount((int)((index << 8) | i)))
    {
        YWLIB_Strcpy(YWVFSi_HandleParam[index].VolumeInfo[i].mountName, volumeName);//dir is not used ,we made it
        YWVFSi_HandleParam[index].VolumeInfo[i].type = type;
    }
    else
    {
        YWOSTRACE((YWOS_TRACE_ERROR,"[error]Error string =%s\n",YWVFSi_GetErrorText(errno)));
        YWOS_Trace(YWOS_TRACE_INFO, "[YWVFS_Mount]mount volume[%s] Failed\n",volumeName);
        return YWVFS_ERROR_MOUNT_VOLUME;
    }

    return YW_ErrorCode;
}


/***********************************************************************
	函数说明:	卸载分区
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
                2009.02.17         chenj              modify
************************************************************************/
YW_ErrorType_T  YWVFS_UnMount(const S8  *monutName)
{
    U32                 index,i;

    for(index = 0 ;index < YWVFS_MAX_DISK ; index++)
        for (i = 0; i < pDiskInfo[index]->partitions; i++)
            if (YWLIB_Strcmp(YWVFSi_HandleParam[index].VolumeInfo[i].volumeName,monutName) == 0)
                break;

    if((index == YWVFS_MAX_DISK) && (i == pDiskInfo[index]->partitions ))
    {
        return YWVFS_ERROR_DELETE_PARTITION;
    }

    if(monutName == NULL || YWLIB_Strcmp((S8 *)monutName , (S8 *)"")==0)
    {
        return YWHAL_ERROR_BAD_PARAMETER;
    }

    if(PART_UnMount((int)((index << 8) | i)))
    {
        YWLIB_Memset(YWVFSi_HandleParam[index].VolumeInfo[i].mountName, 0, sizeof(YWVFS_MAX_NAME_LENGTH));
        YWVFSi_HandleParam[index].VolumeInfo[i].type = YWVFS_FS_TYPE_UNKNOW;
    }
    else
    {
        YWOSTRACE((YWOS_TRACE_ERROR,"[error]Error string =%s\n",YWVFSi_GetErrorText(errno)));
        YWOS_Trace(YWOS_TRACE_INFO, "[YWVFS_UnMount]unmount volume[%s] Failed\n",monutName);
        return YWVFS_ERROR_UNMOUNT_VOLUME;
    }

    return YW_NO_ERROR;
}

/***********************************************************************
	函数说明:	卸载所有分区
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
                2009.02.17         chenj              modify
************************************************************************/
YW_ErrorType_T YWVFS_UnMountAll(void)
{
    U32                 index,i;

    for(index = 0 ;index < YWVFS_MAX_DISK ; index++)
        for (i = 0; i < pDiskInfo[index]->partitions; i++)
        {
            if(PART_UnMount((int)((index << 8) | i)))
            {
                YWLIB_Memset(YWVFSi_HandleParam[index].VolumeInfo[i].mountName, 0, sizeof(YWVFS_MAX_NAME_LENGTH));
                YWVFSi_HandleParam[index].VolumeInfo[i].type = YWVFS_FS_TYPE_UNKNOW;
            }
            else
            {
                YWOSTRACE((YWOS_TRACE_ERROR,"[error]Error string =%s\n",YWVFSi_GetErrorText(errno)));
                return YWVFS_ERROR_UNMOUNT_VOLUME;
            }
        }
    return YW_NO_ERROR;
}


/***********************************************************************
	函数说明:	Write all unwritten data (and metadata) for a volume
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32  YWVFS_Sync( const S8 *Root)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_sync((char *)Root);
#else
    int ret ;
    ret = fsync((int)Root);
    if(ret < 0)
    {
        YWHAL_ERROR("fsync:");
    }
    return ret;
#endif
// D02SH 2009/09/14 modify end
}

/***********************************************************************
	函数说明:	Write all unwritten data (and metadata) for all volume
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32  YWVFS_SyncAll( void)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_sync_all();
#else
    sync();
    return 0;
#endif
// D02SH 2009/09/14 modify end
}


/***********************************************************************
	函数说明:	format a volume
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
YW_ErrorType_T  YWVFS_Format( const S8 * volumeName,YWVFS_FsType_T type,void *Param)
{

    S8                  FsName[16];
    YW_ErrorType_T      YW_ErrorCode = YW_NO_ERROR;

// D02SH 2009/09/16 add begin
//Description:2linux
    char CmdLine[255];
// D02SH 2009/09/16 add end


    YWLIB_Memset(FsName, 0, 16);
    switch(type)
    {
        case YWVFS_FS_TYPE_EXT2:
        {
            YWLIB_Strcpy((S8 *)FsName, (S8 *)"ext2");
            //YWLIB_Memcpy(&E2FS_Format, Param, sizeof(e2fs_format_t));
        }
        break;
        case YWVFS_FS_TYPE_FAT32:
        {
            YWLIB_Strcpy((S8 *)FsName, (S8 *)"vfat");
            //YWLIB_Memcpy(&FAT_Format, Param, sizeof(fat_format_t));
        }
        break;
        default:
        {
            YWOS_Trace(YWOS_TRACE_INFO, "[YWVFS_Format]mount volume[%s] OK\n",volumeName);
            return YWHAL_ERROR_FEATURE_NOT_SUPPORTED;
        }

    }
// D02SH 2009/09/16 modify begin
//Description:2linux
#if 0

    if(vfs_format((char *)volumeName, (char *)FsName, Param)!= OSPLUS_SUCCESS)
    {
        YW_ErrorCode  = YWVFS_ERROR_FORMAT;
        YWOSTRACE((YWOS_TRACE_ERROR,"[error]Error string =%s\n",YWVFSi_GetErrorText(errno)));

    }
#else
    sprintf(CmdLine,"mkfs %s -t %s %s",Param,FsName,volumeName);
    YW_ErrorCode =  YWOS_SystemCmd(CmdLine);
#endif
// D02SH 2009/09/16 modify end

    return YW_ErrorCode;
}

#define YWVFS_FILE_OPERATION

/***********************************************************************
	函数说明:	Open a file after converting the mode to the equivalent flags
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
YWVFS_FileHandle_T YWVFS_Open( const S8  *FileName,const S32  Flags)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return (YWVFS_FileHandle_T )vfs_open((char *)FileName, Flags);
#else
    YWVFS_FileHandle_T hDir ;
    int     iflag = 0;

    switch (Flags & YWVFS_O_RDWR)
    {
        case YWVFS_O_RDONLY:
            iflag |= O_RDONLY;
            break;
        case YWVFS_O_WRONLY:
            iflag |= O_WRONLY;
            break;
        case YWVFS_O_RDWR:
            iflag |= O_RDWR;
            break;
        default:

            break;
    }
    if (Flags & YWVFS_O_APPEND)
    {
        iflag |= O_APPEND;
    }
    if (Flags & YWVFS_O_CREAT)
    {
        iflag |= O_CREAT;
    }
    if (Flags & YWVFS_O_EXCL)
    {
        iflag |= O_EXCL;
    }
    if (Flags & YWVFS_O_TRUNC)
    {
        iflag |= O_TRUNC;
    }
    hDir = (YWVFS_FileHandle_T )open((char *)FileName, iflag);
    if(hDir == 0)
    {
        YWHAL_ERROR("open:");
    }

    return hDir;
#endif
// D02SH 2009/09/14 modify end
}


/***********************************************************************
	函数说明:	Create a file
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
YWVFS_FileHandle_T YWVFS_Creat(const S8   *FileName)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return (YWVFS_FileHandle_T )vfs_creat((char *)FileName);
#else
    return (YWVFS_FileHandle_T )open((char *)FileName,O_CREAT | O_TRUNC | O_WRONLY);
#endif
// D02SH 2009/09/14 modify end
}

/***********************************************************************
	函数说明:	Close a file
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32 YWVFS_Close( YWVFS_FileHandle_T FileHandle)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_fclose((vfs_file_t *)FileHandle);
#else
    int ret ;
    ret = close((int)FileHandle);
    if(ret < 0)
    {
        YWHAL_ERROR("close:");
    }
    return ret;
#endif
// D02SH 2009/09/14 modify end
}


/***********************************************************************
	函数说明:	Close a file
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32 YWVFS_FClose( YWVFS_FileHandle_T FileHandle)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_close((vfs_file_t *)FileHandle);
#else
    int ret ;
    ret = fclose((FILE *)FileHandle);
    if(ret < 0)
    {
        YWHAL_ERROR("fclose:");
    }
    return ret;
#endif
// D02SH 2009/09/14 modify end
}


/***********************************************************************
	函数说明:	Read x bytes from a file
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32 YWVFS_Read( YWVFS_FileHandle_T FileHandle,void  *Buffer,const U32     Size)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_read((vfs_file_t *)FileHandle, Buffer, Size);
#else
    int ret ;
    ret = read((int)FileHandle, Buffer, Size);
    if(ret < 0)
    {
        YWHAL_ERROR("read:");
    }
    return ret;

#endif
// D02SH 2009/09/14 modify end
}

/***********************************************************************
	函数说明:	write x bytes to a file
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32 YWVFS_Write( YWVFS_FileHandle_T FileHandle, void  *Buffer, const  U32     Size )
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_write((vfs_file_t *) FileHandle,   Buffer, Size);
#else
    int ret ;
    ret = write((int) FileHandle,   Buffer, Size);
    if(ret < 0)
    {
        YWHAL_ERROR("write:");
    }
    return ret;

#endif
// D02SH 2009/09/14 modify end
}


/***********************************************************************
	函数说明:	seek to a new position in a file
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32 YWVFS_LSeek( YWVFS_FileHandle_T FileHandle,const S32 Offset,const S32 Whence)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_lseek((vfs_file_t * )FileHandle, Offset, Whence);
#else
    int ret ;
    ret = lseek((int )FileHandle, Offset, Whence);
    if(ret < 0)
    {
        YWHAL_ERROR("lseek:");
    }
    return ret;

#endif
// D02SH 2009/09/14 modify end
}


/***********************************************************************
	函数说明:	seek to a new position in a file
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32 YWVFS_FSeek( YWVFS_FileHandle_T FileHandle,const S32     Offset,const S32     Whence)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_fseek((vfs_file_t * )FileHandle, Offset, Whence);
#else
    int ret ;
    ret = fseek((FILE * )FileHandle, Offset, Whence);
    if(ret < 0)
    {
        YWHAL_ERROR("fseek:");
    }
    return ret;
#endif
// D02SH 2009/09/14 modify end
}


/***********************************************************************
	函数说明:	Seek to a new 64 bit position in a file
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32 YWVFS_FSeek64( YWVFS_FileHandle_T FileHandle,const U64 Offset,const S32     Whence)
{
    long long myOffer;

    myOffer = Offset.MSW;
    myOffer = myOffer << 32;
    myOffer += Offset.LSW;
    //return vfs_fseek64((vfs_file_t * )FileHandle, myOffer, Whence);
}

/***********************************************************************
	函数说明:	rename oldpath to a newpath
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
***********************************************************************/
S32 YWVFS_ReName( const S8 *OldPath,const S8 *NewPath)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_rename((char *)OldPath, (char *)NewPath);
#else
    int ret ;
    ret = rename((char *)OldPath, (char *)NewPath);
    if(ret < 0)
    {
        YWHAL_ERROR("rename:");
    }
    return ret;

#endif
// D02SH 2009/09/14 modify end
}



/***********************************************************************
	函数说明:	Get stats on a file
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32  YWVFS_FStat( YWVFS_FileHandle_T FileHandle,YWVFS_Stat_T   *Buffer)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    vfs_stat_t buf;
#else
    struct stat buf;
#endif
// D02SH 2009/09/14 modify end
    S32        ret;

    YWLIB_Memset(&buf, 0, sizeof(stat));
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    ret = vfs_fstat((vfs_file_t *)FileHandle, &buf);
#else
    ret = fstat((int)FileHandle, &buf); //need fd
    if(ret < 0)
    {
        YWHAL_ERROR("fstat:");
    }
#endif
// D02SH 2009/09/14 modify end

    Buffer->ATime       = buf.st_atime;
    Buffer->BlockSize   = buf.st_blksize;
    Buffer->CTime       = buf.st_ctime;
    Buffer->Mode        = buf.st_mode;
    Buffer->MTime       = buf.st_mtime;
    Buffer->Size        = buf.st_size;

    return ret;
}


/***********************************************************************
	函数说明:	Get stats on a 64 bit file
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32  YWVFS_FStat64( YWVFS_FileHandle_T FileHandle,YWVFS_Stat64_T  *Buffer)
{
    //vfs_stat64_t    buf;
    S32             ret;
/*  2009-09-18@14:57:25 D02SH Remark

    YWLIB_Memset(&buf, 0, sizeof(vfs_stat_t));
    //ret = vfs_fstat64((vfs_file_t *)FileHandle, &buf);

    Buffer->ATime       = buf.st_atime;
    Buffer->BlockSize   = buf.st_blksize;
    Buffer->CTime       = buf.st_ctime;
    Buffer->Mode        = buf.st_mode;
    Buffer->MTime       = buf.st_mtime;
    Buffer->Size.MSW    = (buf.st_size >> 32)&0xffffffff ;
    Buffer->Size.LSW    = buf.st_size&0xffffffff;
*/

    return ret;
}


/***********************************************************************
	函数说明:	Get stats on a file
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32  YWVFS_Stat( const S8 * filename,YWVFS_Stat_T   *Buffer)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
        vfs_stat_t buf;
#else
        struct stat buf;
#endif
// D02SH 2009/09/14 modify end

    S32        ret;

    YWLIB_Memset(&buf, 0, sizeof(stat));
// D02SH 2009/09/16 modify begin
//Description:2linux
#if 0
    ret = vfs_stat((char *)filename, &buf);
#else
    ret = stat((char *)filename, &buf);   //need filename
    if(ret < 0)
    {
        YWHAL_ERROR("stat:");
    }
#endif
// D02SH 2009/09/16 modify end

    Buffer->ATime       = buf.st_atime;
    Buffer->BlockSize   = buf.st_blksize;
    Buffer->CTime       = buf.st_ctime;
    Buffer->Mode        = buf.st_mode;
    Buffer->MTime       = buf.st_mtime;
    Buffer->Size        = buf.st_size;

    return ret;

}
#endif
/***********************************************************************
	函数说明:	Get stats on a 64 bit file
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32  YWVFS_Stat64( const S8 * filename,YWVFS_Stat64_T   *Buffer)
{
   // vfs_stat64_t    buf;
    S32             ret;
/*  2009-09-18@14:57:53 D02SH Remark

    YWLIB_Memset(&buf, 0, sizeof(vfs_stat_t));
    ret = vfs_stat64((char *)filename, &buf);

    Buffer->ATime       = buf.st_atime;
    Buffer->BlockSize   = buf.st_blksize;
    Buffer->CTime       = buf.st_ctime;
    Buffer->Mode        = buf.st_mode;
    Buffer->MTime       = buf.st_mtime;
    Buffer->Size.MSW    = (buf.st_size>>32)&0xffffffff ;
    Buffer->Size.LSW    = buf.st_size&0xffffffff;
*/
    struct stat64 buf;
    YWLIB_Memset(&buf, 0, sizeof(stat64));
    ret = stat64(filename, &buf);
    Buffer->ATime       = buf.st_atime;
    Buffer->BlockSize   = buf.st_blksize;
    Buffer->CTime       = buf.st_ctime;
    Buffer->Mode        = buf.st_mode;
    Buffer->MTime       = buf.st_mtime;
    Buffer->Size.LSW    = buf.st_size;
    Buffer->Size.MSW    = buf.st_size >> 32;
    return ret;

}
#if 0
S32 YWVFS_Statfs64( const S8 *filename, YWVFS_Statfs64_T *Buffer)
{
    S32             ret;
    struct statfs64 buf;

    YWLIB_Memset(&buf, 0, sizeof(statfs64));
    ret = statfs64((char *)filename, &buf);
    switch (buf.f_type)
    {
        case EXT3_SUPER_MAGIC:
            Buffer->FsType = YWVFS_FS_TYPE_EXT3;
            break;
        case MSDOS_SUPER_MAGIC:
            Buffer->FsType = YWVFS_FS_TYPE_FAT32;
            break;
        case NTFS_SUPER_MAGIC:
            Buffer->FsType = YWVFS_FS_TYPE_NTFS;
            break;
        case SMB_SUPER_MAGIC:
            Buffer->FsType = YWVFS_FS_TYPE_SMB;
            break;
        case NFS_SUPER_MAGIC:
            Buffer->FsType = YWVFS_FS_TYPE_NFS;
            break;
        case USBDEVICE_SUPER_MAGIC:
            Buffer->FsType = YWVFS_FS_TYPE_USBDEVICE;
            break;
        case JFFS2_SUPER_MAGIC:
            Buffer->FsType = YWVFS_FS_TYPE_JFFS2;
            break;
        case HPFS_SUPER_MAGIC:
            Buffer->FsType = YWVFS_FS_TYPE_HPFS;
            break;
        case ADFS_SUPER_MAGIC:
            Buffer->FsType = YWVFS_FS_TYPE_ADFS;
            break;
        case AFFS_SUPER_MAGIC:
            Buffer->FsType = YWVFS_FS_TYPE_AFFS;
            break;
        case AFS_SUPER_MAGIC:
            Buffer->FsType = YWVFS_FS_TYPE_AFS;
            break;
        case AUTOFS_SUPER_MAGIC:
            Buffer->FsType = YWVFS_FS_TYPE_AUTOFS;
            break;
        case CODA_SUPER_MAGIC:
            Buffer->FsType = YWVFS_FS_TYPE_CODA;
            break;
        case EFS_SUPER_MAGIC:
            Buffer->FsType = YWVFS_FS_TYPE_EFS;
            break;
        case ISOFS_SUPER_MAGIC:
            Buffer->FsType = YWVFS_FS_TYPE_ISOFS;
            break;
        case ANON_INODE_FS_MAGIC:
            Buffer->FsType = YWVFS_FS_TYPE_ANON;
            break;
        case NCP_SUPER_MAGIC:
            Buffer->FsType = YWVFS_FS_TYPE_NCP;
            break;
        case OPENPROM_SUPER_MAGIC:
            Buffer->FsType = YWVFS_FS_TYPE_OPENPROM;
            break;
        case PROC_SUPER_MAGIC:
            Buffer->FsType = YWVFS_FS_TYPE_PROC;
            break;
        case QNX4_SUPER_MAGIC:
            Buffer->FsType = YWVFS_FS_TYPE_QNX4;
            break;
        case REISERFS_SUPER_MAGIC:
            Buffer->FsType = YWVFS_FS_TYPE_REISERFS;
            break;
        case CIFS_MAGIC_NUMBER:
            Buffer->FsType = YWVFS_FS_TYPE_CIFS;
            break;
        default:
            Buffer->FsType = YWVFS_FS_TYPE_UNKNOW;
            break;
    }

    Buffer->blkSize     = buf.f_bsize;

    Buffer->blocks.LSW    = buf.f_blocks;
    Buffer->blocks.MSW    = buf.f_blocks >> 32;

    Buffer->blkfree.LSW    = buf.f_bfree;
    Buffer->blkfree.MSW    = buf.f_bfree >> 32;

    Buffer->blkavail.LSW    = buf.f_bavail;
    Buffer->blkavail.MSW    = buf.f_bavail >> 32;
    return ret;
}

U32  YWVFS_GetfsUsedPercent64(YWVFS_Statfs64_T *statFs)
{
    unsigned long long blocks_blocks;
    unsigned long long blocks_bfree;
    unsigned long long blocks_bavail;
    unsigned long long blocks_used;
    unsigned blocks_percent_used = 0;

    blocks_blocks = (unsigned long long)statFs->blocks.MSW << 32 | statFs->blocks.LSW;
    blocks_bfree = (unsigned long long)statFs->blkfree.MSW << 32 | statFs->blkfree.LSW;
    blocks_bavail = (unsigned long long)statFs->blkavail.MSW << 32 | statFs->blkavail.LSW;

    blocks_percent_used = 0;
	if (blocks_blocks > 0)
    {
        blocks_used = blocks_blocks - blocks_bfree;
		if (blocks_used + blocks_bavail)
        {
			blocks_percent_used =
                (blocks_used * 100ULL + (blocks_used + blocks_bavail) / 2) /
                                        (blocks_used + blocks_bavail);
 //           DEBUG("blocks_percent_used = %d\n", blocks_percent_used);
		}
 //       DEBUG("blocks_percent_used = %3u%%\n", blocks_percent_used);

	}
    return blocks_percent_used;
}
extern U32  YWVFS_GetfsUsedPercent64(YWVFS_Statfs64_T *statFs);

/***********************************************************************
	函数说明:	Open a file after converting the mode to the equivalent flags
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
YWVFS_FileHandle_T YWVFS_FOpen( const S8   *FileName,const S8    *Mode)
{
    //YWVFS_FileHandle_T FileHandle;

    //FileHandle = vfs_fopen((char *)FileName, (char *)Mode);
    //YWOSTRACE((YWOS_TRACE_ERROR,"[error]Error string =%s\n",YWVFSi_GetErrorText(errno)));
    //return FileHandle;
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return (YWVFS_FileHandle_T)vfs_fopen((char *)FileName, (char *)Mode);
#else
    return (YWVFS_FileHandle_T)fopen((char *)FileName, (char *)Mode);
#endif
// D02SH 2009/09/14 modify end

}


/***********************************************************************
	函数说明:	Get the current file position
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32 YWVFS_FTell( YWVFS_FileHandle_T FileHandle)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_ftell((vfs_file_t * )FileHandle);
#else
    int ret ;
    ret = ftell((FILE * )FileHandle);
    if(ret < 0)
    {
        YWHAL_ERROR("ftell:");
    }
    return ret;

#endif
// D02SH 2009/09/14 modify end
}

/***********************************************************************
	函数说明:	Get the current file position
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S64 YWVFS_FTell64( YWVFS_FileHandle_T FileHandle)
{
    long long pos;
    S64 MyPos;

    //pos = vfs_ftell64((vfs_file_t * )FileHandle);
    MyPos.MSW = (pos >> 32)&0xffffffff;
    MyPos.LSW = pos &0xffffffff;
    return MyPos;
}


/***********************************************************************
	函数说明:	Rewind to the start of the file
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32 YWVFS_ReWind( YWVFS_FileHandle_T FileHandle)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_rewind((vfs_file_t * )FileHandle);
#else
    rewind((FILE * )FileHandle);
    return 0;
#endif
// D02SH 2009/09/14 modify end
}


/***********************************************************************
	函数说明:	Get the file position
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32 YWVFS_FGetPos( YWVFS_FileHandle_T FileHandle,const U32 *Pos)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_fgetpos((vfs_file_t * )FileHandle, (size_t *)Pos);
#else
    int ret ;
    ret = fgetpos((FILE * )FileHandle, (size_t *)Pos);
    if(ret < 0)
    {
        YWHAL_ERROR("fgetpos:");
    }
    return ret;

#endif
// D02SH 2009/09/14 modify end
}


/***********************************************************************
	函数说明:	Set the file position
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32  YWVFS_FSetPos( YWVFS_FileHandle_T FileHandle,const U32  *Pos)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_fsetpos((vfs_file_t *)FileHandle, (size_t *)Pos);
#else
    int ret ;
    ret = fsetpos((FILE *)FileHandle, (size_t *)Pos);
    if(ret < 0)
    {
        YWHAL_ERROR("fsetpos:");
    }
    return ret;

#endif
// D02SH 2009/09/14 modify end
}

/***********************************************************************
	函数说明:	Read size X nMemb bytes from the file
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32  YWVFS_FRead(void *Ptr,const S32   Size,const S32     NMemb,YWVFS_FileHandle_T FileHandle)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
    U8* BuffTmp = Ptr;
    S32 Buffsize = Size * NMemb;
    S32 readLen = 0;
    S32 readsize = 0;
    S32 TotalReadLen = 0;

    if (NMemb*Size >= 2*YW_K)
    {
        readsize = 2*YW_K;
    }
    else
    {
        readsize = Size*NMemb;
    }
#if 0
    return vfs_fread(Ptr, Size, NMemb, (vfs_file_t *)FileHandle);
#else
    /*while(readLen > 0)
	{
        readLen = fread(BuffTmp, (size_t)1, (size_t)readsize, (FILE *)FileHandle);
        if(readLen < 0)
        {
            return readLen;
        }

        if(YWVFS_FEof(FileHandle))
        {
            break;
        }

        Buffsize -=readLen;

		if(readLen <=0 ||Buffsize<=0)
		{
		    break;
		}
		BuffTmp+=readLen;
	}
    return Size *NMemb;//fread(Ptr, (size_t)Size, (size_t)NMemb, (FILE *)FileHandle);
    */
    if(readsize<=0||Buffsize<=0)
        return 0;

    while(TotalReadLen<Buffsize)
    {
        readLen = fread(BuffTmp, (size_t)1, (size_t)readsize, (FILE *)FileHandle);
        if(readLen <= 0)
        {
            break;
        }

        TotalReadLen+=readLen;
        BuffTmp+=readLen;

        if(YWVFS_FEof(FileHandle))
        {
            break;
        }
    }

    return TotalReadLen;
#endif
// D02SH 2009/09/14 modify end
}


/***********************************************************************
	函数说明:	Write size X nMemb bytes to the file
	参数说明:

    修改记录:	日       期      作      者       修定
 				---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32  YWVFS_FWrite(void  *Ptr,const S32  Size,const S32  NMemb,YWVFS_FileHandle_T FileHandle)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
    U8* BuffTmp = Ptr;
    S32 Buffsize = Size * NMemb;
    S32 writeLen = 1;


#if 0
    return vfs_fwrite(Ptr, Size, NMemb, (vfs_file_t *)FileHandle);
#else
    while(writeLen > 0)
	{
        writeLen = fwrite(BuffTmp, (size_t)1, (Buffsize > 2*YW_K)? 2*YW_K: Buffsize, (FILE *)FileHandle);
        if(writeLen < 0)
        {
            return writeLen;
        }

        if(YWVFS_FEof(FileHandle))
        {
            break;
        }

        Buffsize -= writeLen;

		if(writeLen <=0 ||Buffsize<=0)
		{
		    break;
		}
		BuffTmp+=writeLen;
	}
    return Size * NMemb;//fwrite(Ptr, (size_t)Size, (size_t)NMemb, (FILE *)FileHandle);
#endif
// D02SH 2009/09/14 modify end
}


/***********************************************************************
	函数说明:	check if the current position is at the end of the file
	参数说明:

    修改记录:	日       期      作      者       修定
                ---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32 YWVFS_FEof( YWVFS_FileHandle_T FileHandle)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_feof((vfs_file_t *)FileHandle);
#else
    int ret ;
    ret = feof((FILE *)FileHandle);
    if(ret < 0)
    {
        YWHAL_ERROR("feof:");
    }
    return ret;

#endif
// D02SH 2009/09/14 modify end
}


/***********************************************************************
	函数说明:	Get a char from the file
	参数说明:

    修改记录:	日       期      作      者       修定
                ---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32 YWVFS_FGetC( YWVFS_FileHandle_T FileHandle)
{
//YWDRIVER_MODI D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_fgetc((vfs_file_t * )FileHandle);
#else
    int ret ;
    ret = fgetc((FILE * )FileHandle);
    if(ret < 0)
    {
        YWHAL_ERROR("fgetc:");
    }
    return ret;

#endif
//YWDRIVER_MODI D02SH 2009/09/14 modify end
}


/***********************************************************************
	函数说明:	Get a string from the file
	参数说明:

    修改记录:	日       期      作      者       修定
                ---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S8  *YWVFS_FGetS(S8    *Str ,const S32     Size,YWVFS_FileHandle_T FileHandle)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return (S8 *)vfs_fgets((char *)Str, (size_t)Size, (vfs_file_t *)FileHandle);
#else
    return (S8 *)fgets((char *)Str, (size_t)Size, (FILE *)FileHandle);
#endif
// D02SH 2009/09/14 modify end
}


/***********************************************************************
	函数说明:	write a char to the file
	参数说明:

    修改记录:	日       期      作      者       修定
                ---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32 YWVFS_FPutC( const S32   *Ch,YWVFS_FileHandle_T FileHandle)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_fputc((int)Ch, (vfs_file_t * )FileHandle);
#else
    int ret ;
    ret = fputc((int)Ch, (FILE * )FileHandle);
    if(ret < 0)
    {
        YWHAL_ERROR("fputc:");
    }
    return ret;

#endif
// D02SH 2009/09/14 modify end
}


/***********************************************************************
	函数说明:	Write a string to the file
	参数说明:

    修改记录:	日       期      作      者       修定
                ---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32 YWVFS_FPutS( S8 *Str,YWVFS_FileHandle_T FileHandle)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_fputs((char *)Str, (vfs_file_t * )FileHandle);
#else
    int ret ;
    ret = fputs((char *)Str, (FILE * )FileHandle);
    if(ret < 0)
    {
        YWHAL_ERROR("fputs:");
    }
    return ret;

#endif
// D02SH 2009/09/14 modify end
}


/***********************************************************************
	函数说明:	Flush any unwritten data(and metadata) to a file

	参数说明:

    修改记录:	日       期      作      者       修定
                ---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32 YWVFS_FFlush( YWVFS_FileHandle_T FileHandle)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_fflush((vfs_file_t *)FileHandle);
#else
    int ret ;
    ret = fflush((FILE *)FileHandle);
    if(ret < 0)
    {
        YWHAL_ERROR("fflush:");
    }
    return ret;

#endif
// D02SH 2009/09/14 modify end
}


/***********************************************************************
	函数说明:	Remove a file

	参数说明:

    修改记录:	日       期      作      者       修定
                ---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32  YWVFS_UnLink( const S8 *Path)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_unlink((char *)Path);
#else
    int ret ;
    ret = unlink((char *)Path);
    if(ret < 0)
    {
        YWHAL_ERROR("unlink:");
    }
    return ret;

#endif
// D02SH 2009/09/14 modify end
}


/***********************************************************************
	函数说明:	Change the mode of a file/dir

	参数说明:

    修改记录:	日       期      作      者       修定
                ---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32  YWVFS_FChmod( const S8 *path,const U32 Mode)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_chmod((char *)path, Mode);
#else
    int ret ;
    ret = chmod((char *)path, Mode);
    if(ret < 0)
    {
        YWHAL_ERROR("chmod:");
    }
    return ret;

#endif
// D02SH 2009/09/14 modify end
}


/***********************************************************************
	函数说明:	Send a command to a file

	参数说明:

    修改记录:	日       期      作      者       修定
                ---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32 YWVFS_FCntl( YWVFS_FileHandle_T FileHandle,const S32  Request,void  *Param)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_fcntl((vfs_file_t *)FileHandle, Request, Param);
#else
    int ret ;
    ret = fcntl((FILE *)FileHandle, Request, Param);
    if(ret < 0)
    {
        YWHAL_ERROR("fcntl:");
    }
    return ret;

#endif
// D02SH 2009/09/14 modify end
}




/***********************************************************************
	函数说明:	Print data to a file

	参数说明:

    修改记录:	日       期      作      者       修定
                ---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32  YWVFS_VFprintf(YWVFS_FileHandle_T FileHandle,const char * fmt, va_list args)
{

// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_vfprintf((vfs_file_t * )FileHandle, fmt, args);
#else
    int ret ;
    return vfprintf((FILE * )FileHandle, fmt, (va_list)args);
    if(ret < 0)
    {
        YWHAL_ERROR("vfprintf:");
    }
    return ret;

#endif
// D02SH 2009/09/14 modify end
}


/***********************************************************************
	函数说明:	Printf data to a file

	参数说明:

    修改记录:	日       期      作      者       修定
                ---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32  YWVFS_Fprintf(YWVFS_FileHandle_T FileHandle,const char * fmt,...)
{
    char  StringBuffer[512];                    /* Send String Buffer */
    va_list  List;                                            /* Argument Pointer */


    va_start( List, fmt );                                    /* Get Argument Pointer */
    vsprintf( StringBuffer, fmt, List );                        /* Make Display String */
    va_end(List);

// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_fprintf((vfs_file_t * )FileHandle, StringBuffer);
#else
    int ret ;
    ret = fprintf((FILE * )FileHandle, StringBuffer);
    if(ret < 0)
    {
        YWHAL_ERROR("fprintf:");
    }
    return ret;

#endif
// D02SH 2009/09/14 modify end
}



/***********************************************************************
	函数说明:	Resize the file

	参数说明:

    修改记录:	日       期      作      者       修定
                ---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32  YWVFS_Resize(YWVFS_FileHandle_T FileHandle,const U32 size)
{
   //return vfs_resize((vfs_file_t *)FileHandle, size);
   return 0;
}


/***********************************************************************
	函数说明:	Resize the file

	参数说明:

    修改记录:	日       期      作      者       修定
                ---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32  YWVFS_Resize64(YWVFS_FileHandle_T FileHandle,const U64 size)
{
    long long MySize;

    MySize = size.MSW;
    MySize = MySize << 32;
    MySize += size.LSW;
   // return vfs_resize64((vfs_file_t *)FileHandle, MySize);
    return 0;
}


S32  YWVFS_FScntl(const S8*    Root,const S32          Request,void               *Param)
{
    //return vfs_fscntl( (char *)Root, Request, Param);
    return 0;
}

S32  YWVFS_Dcntl( YWVFS_DirHandle_T *DirHandle,const S32  Request,void   *Param)
{
    //return vfs_dcntl((void * )DirHandle, Request, Param);
    return 0;
}

S32  YWVFS_Defrag( const S8 *root, YWVFS_DefragOption_T DOption)
{
   // return vfs_defrag((char *)root,  DOption);
   return 0;
}


S32  YWVFS_Fsck(S8 *VolumeName, YWVFS_FsType_T type)
{
    char    FsName[YWVFS_MAX_NAME_LENGTH];
// D02SH 2009/09/16 add begin
//Description:2linux
    char CmdLine[255];
// D02SH 2009/09/16 add end

// D02SH 2009/09/16 modify begin
//Description:2linux
#if 0
    YWLIB_Memset(FsName, 0, YWVFS_MAX_NAME_LENGTH);
    switch(type)
    {
        case YWVFS_FS_TYPE_EXT2:
        {
            YWLIB_Strcpy((S8 *)FsName, (S8 *)E2FS_NAME);
        }
        break;

        case YWVFS_FS_TYPE_FAT32:
        {
            YWLIB_Strcpy((S8 *)FsName, (S8 *)FAT_NAME);
        }
        break;

        default:
        {
            YWOS_Trace(YWOS_TRACE_INFO, "[YWVFS_Fsck] volume[%s] file system type can not support\n",VolumeName);
            return YWHAL_ERROR_FEATURE_NOT_SUPPORTED;
        }
   }

   return vfs_fsck((char *)VolumeName, FsName);
#else
   sprintf(CmdLine,"fsck -a %s",VolumeName);
   return YWOS_SystemCmd(CmdLine);
#endif
// D02SH 2009/09/16 modify end
}

#if 0
S32  YWVFS_Fsck(S8 *device_name, const S8 *fs_name)
{
    return vfs_fsck((char *)device_name, (char *)fs_name);
}
#endif
#endif
#define YWVFS_DIROPERATION


/***********************************************************************
	函数说明:	Open a dir for reading

	参数说明:

    修改记录:	日       期      作      者       修定
                ---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
YWVFS_DirHandle_T YWVFS_OpenDir(const S8 *DirName)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return (YWVFS_DirHandle_T) vfs_opendir((char *)DirName);
#else
    YWVFS_DirHandle_T hDir ;
    hDir = (YWVFS_DirHandle_T) opendir((char *)DirName);
    if(hDir == 0)
    {
        YWHAL_ERROR("opendir:");
    }

    return hDir;
    //return (YWVFS_DirHandle_T) opendir((char *)DirName);
#endif
// D02SH 2009/09/14 modify end
}

/***********************************************************************
	函数说明:	close the dir

	参数说明:

    修改记录:	日       期      作      者       修定
                ---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32 YWVFS_CloseDir(YWVFS_DirHandle_T DirHandle)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_closedir((vfs_dir_t *) DirHandle);
#else
    int ret ;
    ret = closedir((DIR *) DirHandle);
    if(ret < 0)
    {
        YWHAL_ERROR("closedir:");
    }
    return ret;

#endif
// D02SH 2009/09/14 modify end
}

/***********************************************************************
	函数说明:	Read the next dir entry from a dir

	参数说明:

    修改记录:	日       期      作      者       修定
                ---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32 YWVFS_ReadDir(  YWVFS_DirHandle_T DirHandle,YWVFS_DirEnt_T *Dirent)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_readdir((vfs_dir_t * )DirHandle, (vfs_dirent_t * )Dirent);
#else
    struct dirent *ptr;
    if ((ptr = readdir((DIR *)DirHandle)) == NULL)
    {
        YWHAL_ERROR("readdir");
        return -1;
    }
    YWLIB_Strcpy((S8 *)Dirent->Name, (S8 *) ptr->d_name);
    Dirent->Mode = ptr->d_type;
    return 0;
#endif
// D02SH 2009/09/14 modify end
}

/***********************************************************************
	函数说明:	Read the next dir entry from a dir

	参数说明:

    修改记录:	日       期      作      者       修定
                ---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
YW_ErrorType_T YWVFS_GetDirEntryNum(  YWVFS_DirHandle_T DirHandle,U32 *EntryNum)
{
    YW_ErrorType_T  YW_ErrorCode = YW_NO_ERROR;
    S32             ret =0;
    U32             Num;
// D02SH 2009/09/15 add begin
//Description:2linux
    struct dirent *ptr;
// D02SH 2009/09/15 add end

    if((DirHandle == (YWVFS_DirHandle_T)NULL) ||(EntryNum == NULL))
        return YWHAL_ERROR_BAD_PARAMETER;

// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    ret = vfs_rewinddir((vfs_dir_t * )DirHandle);
#else
    rewinddir((DIR * )DirHandle);
#endif
// D02SH 2009/09/14 modify end
    if(ret != 0)
    {
//        YWOSTRACE((YWOS_TRACE_ERROR,"[error]Error string =%s\n",YWVFSi_GetErrorText(errno)));
        return YWVFS_ERROR_OPENDIR;
    }

    Num = 0;
// D02SH 2009/09/15 modify begin
//Description:2linux
#if 0
    while(1)
    {
        ret = vfs_readdir((vfs_dir_t * )DirHandle, &Dirent);
        if(ret != 0)
        {
            YWOSTRACE((YWOS_TRACE_ERROR,"[error]Error string =%s\n",YWVFSi_GetErrorText(errno)));
            //YW_ErrorCode =  YWVFS_ERROR_OPENDIR;
            break;
        }
        Num++;
    }
#else
    while ((ptr = readdir((DIR *)DirHandle)) != NULL)
    {
        Num++;
    }
#endif
// D02SH 2009/09/15 modify end
    *EntryNum = Num;

    return YW_ErrorCode;
}


/***********************************************************************
	函数说明:	Read the next dir entry from a dir

	参数说明:

    修改记录:	日       期      作      者       修定
                ---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
YW_ErrorType_T YWVFS_GetDirEntry(  YWVFS_DirHandle_T DirHandle,YWVFS_DirEnt_T *Dirent,U32 EntryNum)
{
    YW_ErrorType_T  YW_ErrorCode = YW_NO_ERROR;
    S32             ret =0;
    U32             Num;
// D02SH 2009/09/15 add begin
//Description:2linux
    struct dirent *ptr;
// D02SH 2009/09/15 add end
    if((DirHandle == (YWVFS_DirHandle_T)NULL)
        ||(Dirent == (YWVFS_DirEnt_T *)NULL)
        ||(EntryNum == 0))
        return YWHAL_ERROR_BAD_PARAMETER;

// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    ret = vfs_rewinddir((vfs_dir_t * )DirHandle);
#else
    rewinddir((DIR * )DirHandle);
#endif
// D02SH 2009/09/14 modify end
    if(ret != 0)
    {
//        YWOSTRACE((YWOS_TRACE_ERROR,"[error]Error string =%s\n",YWVFSi_GetErrorText(errno)));
        return YWVFS_ERROR_OPENDIR;
    }

    Num = 0;
// D02SH 2009/09/15 modify begin
//Description:2linux
#if 0
    while(1)
    {
        if(Num >= EntryNum)
        {
           //YW_ErrorCode =  YWVFS_ERROR_NOT_ENOUGH_SPACE;
           break;
        }

        ret = vfs_readdir((vfs_dir_t * )DirHandle, (vfs_dirent_t *)(&(Dirent[Num])));

        if(ret != 0)
        {
            YWOSTRACE((YWOS_TRACE_ERROR,"[error]Error string =%s\n",YWVFSi_GetErrorText(errno)));
           // YW_ErrorCode =  YWVFS_ERROR_OPENDIR;
            break;
        }
        Num++;
    }
#else
    while ((ptr = readdir((DIR *)DirHandle)) != NULL)
    {
        if(Num >= EntryNum)
        {
           //YW_ErrorCode =  YWVFS_ERROR_NOT_ENOUGH_SPACE;
           break;
        }
        YWLIB_Strcpy((S8 *)Dirent->Name, (S8 *) ptr->d_name);
        Num++;
    }
#endif
// D02SH 2009/09/15 modify end

    return YW_ErrorCode;
}


/***********************************************************************
	函数说明:	Rewind to the start of a dir

	参数说明:

    修改记录:	日       期      作      者       修定
                ---------         ---------      -----
                2008.09.25         chenj          新建
************************************************************************/
S32  YWVFS_ReWindDir(  YWVFS_DirHandle_T DirHandle)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_rewinddir((vfs_dir_t * )DirHandle);
#else
    rewinddir((DIR * )DirHandle);
    return 0;
#endif
// D02SH 2009/09/14 modify end
}


/***********************************************************************
	函数说明:	Get the current position in the dir

	参数说明:

    修改记录:	日       期      作      者       修定
                ---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32  YWVFS_TellDir(  YWVFS_DirHandle_T DirHandle)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_telldir((vfs_dir_t * )DirHandle);
#else
    int ret ;
    ret = telldir((DIR * )DirHandle);
    if(ret < 0)
    {
        YWHAL_ERROR("telldir:");
    }
    return ret;

#endif
// D02SH 2009/09/14 modify end
}

/***********************************************************************
	函数说明:	Seek to a new position in the dir (previously saved from a call to vfs_telldir)

	参数说明:

    修改记录:	日       期      作      者       修定
                ---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32 YWVFS_SeekDir( YWVFS_DirHandle_T DirHandle,const S32     Offset)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_seekdir((vfs_dir_t *) DirHandle, Offset);
#else
    seekdir((DIR *) DirHandle, (off_t)Offset);
    return 0;
#endif
// D02SH 2009/09/14 modify end
}

/***********************************************************************
	函数说明:	Make a new dir

	参数说明:

    修改记录:	日       期      作      者       修定
                ---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32  YWVFS_MkDir( const S8 *PathName)
{
//YWDRIVER_MODI D02SH 2009/09/14 modify begin
//Description:2llinux
#if 0
    return vfs_mkdir((char *)PathName);
#else
    int ret ;
    ret = mkdir((char *)PathName,S_IRWXG|S_IRWXU);
    if(ret < 0)
    {
        YWHAL_ERROR("mkdir:");
    }
    return ret;

#endif
//YWDRIVER_MODI D02SH 2009/09/14 modify end
}

/***********************************************************************
	函数说明:	Remove a dir

	参数说明:

    修改记录:	日       期      作      者       修定
                ---------         ---------         -----
                2008.09.25         chenj              新建
************************************************************************/
S32  YWVFS_RmDir( const S8 *PathName)
{
// D02SH 2009/09/14 modify begin
//Description:2linux
#if 0
    return vfs_rmdir((char *)PathName);
#else
    int ret ;
    ret = rmdir((char *)PathName);
    if(ret < 0)
    {
        YWHAL_ERROR("rmdir:");
    }
    return ret;

#endif
// D02SH 2009/09/14 modify end
}


#define YWVFS_ERRORS

S8  *YWVFS_GetErrorInfo()
{
    return (S8 *)YWVFSi_GetErrorText(errno);
}


static char *YWVFSi_GetErrorText(U32 errorNo)
{
    extern int errno;
    if ((errorNo > 255) || (errorNo < 0)) //unnorm return system record
    {
        return (char *)strerror(errno);
    }
    return (char *)strerror(errorNo);
}


