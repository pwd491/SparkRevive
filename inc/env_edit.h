



#ifndef ___ENV_EDIT__H___
#define ___ENV_EDIT__H___


typedef enum Pdk_type_e
{
    PDK_TYPE_7111 = 0,
    PDK_TYPE_7162,
}PDK_TYPE_E;



#define XSTR(s) STR(s)
#define STR(s) #s


#define CFG_FLASH_BASE		0xA0000000	/* FLASH (uncached) via PMB */

#define CFG_SDRAM_BASE		0x80000000      /* LMI    Cached addr via PMB */
#define CFG_LOAD_ADDR		CFG_SDRAM_BASE	/* default load address		*/


#define CONFIG_BAUDRATE		115200

#define CONFIG_BOOTDELAY	3//10		/* default delay before executing bootcmd */

#define BOARD mb618

//YWDRIVER_MODI d48zm 2010/3/23 modify
#define CFG_MONITOR_LEN		0x00080000	/* Reserve 512 KiB for Monitor */
#define CFG_MONITOR_BASE        CFG_FLASH_BASE

#if CFG_MONITOR_LEN == 0x00008000		/* 32 KiB */
#	define MONITOR_SECTORS	"0xa0000000    0xa0007fff"
#elif CFG_MONITOR_LEN == 0x00010000		/* 64 KiB */
#	define MONITOR_SECTORS	"0xa0000000    0xa000ffff"
#elif CFG_MONITOR_LEN == 0x00018000		/* 96 KiB */
#	define MONITOR_SECTORS	"0xa0000000    0xa0017fff"
#elif CFG_MONITOR_LEN == 0x00020000		/* 128 KiB */
#	define MONITOR_SECTORS	"0xa0000000    0xa001ffff"
#elif CFG_MONITOR_LEN == 0x00040000		/* 256 KiB */
#	define MONITOR_SECTORS	"0xa0000000    0xa003ffff"
#elif CFG_MONITOR_LEN == 0x00060000		/* 384 KiB */
#	define MONITOR_SECTORS	"0xa0000000    0xa005ffff"
#elif CFG_MONITOR_LEN == 0x00080000		/* 512 KiB */
#	define MONITOR_SECTORS	"0xa0000000    0xa007ffff"
#else						/* unknown */
#	error "Unable to determine sectors for monitor"
#endif
//YWDRIVER_MODI d48zm 2010/3/23 modify end

#define CFG_YW_KERNEL_LENGTH_HEX    0x00700000
#define CFG_YW_KERNEL_BASE_HEX	    0xa0080000

#define CFG_YW_KERNEL_SEC		" a0080000 a077ffff "
#define CFG_YW_KERNEL_LEN		" "XSTR(CFG_YW_KERNEL_LENGTH_HEX)" "
#define CFG_YW_KERNEL_BASE		" "XSTR(CFG_YW_KERNEL_BASE_HEX)" "

#define CFG_YW_ROOTFS_BASE      0xa0800000
#define CFG_YW_ROOTFS_SEC       "a0800000 a1ffffff"

#define CFG_YW_BOOTCMD 			"bootm " CFG_YW_KERNEL_BASE
#define	MAGIC_VERSION			"1.7"	// must change when upgrade u-boot

#define CFG_YW_UPDATE_KERNEL \
		"protect off " CFG_YW_KERNEL_SEC ";" \
		"erase " CFG_YW_KERNEL_SEC ";" \
		"cp.b " XSTR(CFG_LOAD_ADDR) CFG_YW_KERNEL_BASE CFG_YW_KERNEL_LEN ";" \
		"protect on " CFG_YW_KERNEL_SEC

#define CFG_SPARK_PATH              "spark"
#define CFG_SPARK_KERNEL_NAME       "mImage"
#define CFG_SPARK_USERFS_NAME       "userfsub.img"

#define CFG_SPARK_KERNEL_FULLNAME   CFG_SPARK_PATH"/"CFG_SPARK_KERNEL_NAME
#define CFG_SPARK_USERFS_FULLNAME   CFG_SPARK_PATH"/"CFG_SPARK_USERFS_NAME

#define CFG_ENIGMA2_PATH            "enigma2"
#define CFG_ENIGMA2_KERNEL_NAME     "uImage"
#define CFG_ENIGMA2_USERFS_NAME     "e2jffs2.img"

#define CFG_ENIGMA2_KERNEL_FULLNAME CFG_ENIGMA2_PATH"/"CFG_ENIGMA2_KERNEL_NAME
#define CFG_ENIGMA2_USERFS_FULLNAME CFG_ENIGMA2_PATH"/"CFG_ENIGMA2_USERFS_NAME



#define CONFIG_EXTRA_ENV_SETTINGS \
		"board=" XSTR(BOARD) "\0" \
		"monitor_base=" XSTR(CFG_MONITOR_BASE) "\0" \
		"monitor_len=" XSTR(CFG_MONITOR_LEN) "\0" \
		"monitor_sec=" MONITOR_SECTORS "\0" \
		"load_addr=" XSTR(CFG_LOAD_ADDR) "\0" \
		"unprot=" \
        "protect off $monitor_sec\0" \
        "update=" \
        "protect off $monitor_sec;erase $monitor_sec;" \
        "cp.b $load_addr $monitor_base $monitor_len;" \
        "protect on $monitor_sec\0" \
        "HOSTNAME=LINUX7109\0" \
		"ethaddr=00:80:E1:12:06:38\0" \
		"ipaddr=192.168.40.63\0" \
		"netmask=255.255.255.0\0" \
		"gatewayip=192.168.3.1\0" \
		"serverip=192.168.40.19\0" \
		"bootcmd=" CFG_YW_BOOTCMD "\0" \
        "kernel_base=" CFG_YW_KERNEL_BASE "\0" \
		"kernel_base_spark=" CFG_YW_KERNEL_BASE "\0" \
		"kernel_base_enigma2=0x18000000\0" \
        "kernel_sec=" CFG_YW_KERNEL_SEC "\0" \
        "kernel_len=" CFG_YW_KERNEL_LEN "\0" \
        "update_kernel=" CFG_YW_UPDATE_KERNEL "\0" \
        "rootfs_base=" XSTR(CFG_YW_ROOTFS_BASE) "\0" \
        "rootfs_sec=" CFG_YW_ROOTFS_SEC "\0" \
		"menucmd=update\0" \
		"tftp_kernel_name="CFG_SPARK_KERNEL_NAME"\0" \
		"tftp_kernel_name_spark="CFG_SPARK_KERNEL_NAME"\0" \
		"tftp_kernel_name_enigma2="CFG_ENIGMA2_KERNEL_NAME"\0" \
		"tftp_userfs_name="CFG_SPARK_USERFS_NAME"\0" \
		"tftp_userfs_name_spark="CFG_SPARK_USERFS_NAME"\0" \
		"tftp_userfs_name_enigma2="CFG_ENIGMA2_USERFS_NAME"\0" \
		"kernel_name="CFG_SPARK_KERNEL_FULLNAME"\0" \
		"kernel_name_spark="CFG_SPARK_KERNEL_FULLNAME"\0" \
		"kernel_name_enigma2="CFG_ENIGMA2_KERNEL_FULLNAME"\0" \
		"userfs_name="CFG_SPARK_USERFS_FULLNAME"\0" \
		"userfs_name_spark="CFG_SPARK_USERFS_FULLNAME"\0" \
		"userfs_name_enigma2="CFG_ENIGMA2_USERFS_FULLNAME"\0" \
		"userfs_base=800000\0" \
		"userfs_base_spark=800000\0" \
		"userfs_base_enigma2=18800000\0" \
		"userfs_len=17800000\0" \
		"userfs_len_spark=17800000\0" \
		"userfs_len_enigma2=7700000\0" \
		"kernelnfspath=192.168.40.19:/opt/target\0" \
		"rootfs_name=UserFS\0" \
		"rootfsnfspath=192.168.40.19:/home/d22cj/workspace/target\0" \
		"uboot_name=u-boot.bin\0" \
		"ubootnfspath=192.168.40.19:/home/d22cj/workspace/target\0" \
		"bootfromnfs=nfs a4000000 $kernelnfspath/$kernel_name;bootm a4000000\0" \
		"bootargs_nfs=console=ttyAS1,115200 nwhwconf=device:eth0,hwaddr:00:80:E1:12:40:61 " \
		"stmmaceth=msglvl:0,phyaddr:1:watchdog:5000 root=/dev/nfs nfsroot=" \
		"192.168.40.19:/opt/target,nfsvers=2,rsize=4096," \
		"wsize=8192,tcp rw ip=192.168.40.61:192.168.40.19:192.168.3.1:255.255.0.0:" \
		"LINUX7109:eth0:off bigphysarea=4000\0" \
		"bootargs_flash=console=ttyAS1,115200 rw ramdisk_size=6144 init=/linuxrc " \
		"root=/dev/ram0 nwhwconf=device:eth0,hwaddr:00:80:E1:12:40:69 ip=192.168.0.69" \
		":192.168.3.119:192.168.3.1:255.255.0.0:lh:eth0:off stmmaceth=msglvl:0,phyaddr:1," \
		"watchdog:5000 bigphysarea=4000\0" \
		"bootargs=console=ttyAS1,115200 rw ramdisk_size=6144 init=/linuxrc " \
		"root=/dev/ram0 nwhwconf=device:eth0,hwaddr:00:80:E1:12:40:69 ip=192.168.0.69" \
		":192.168.0.119:192.168.0.1:255.255.255.0:lh:eth0:off stmmaceth=msglvl:0,phyaddr:1," \
		"watchdog:5000 bigphysarea=4000\0" \
		"bootargs_spark=console=ttyAS1,115200 rw ramdisk_size=6144 init=/linuxrc " \
		"root=/dev/ram0 nwhwconf=device:eth0,hwaddr:00:80:E1:12:40:69 ip=192.168.0.69" \
		":192.168.3.119:192.168.3.1:255.255.0.0:lh:eth0:off stmmaceth=msglvl:0,phyaddr:1," \
		"watchdog:5000 bigphysarea=4000\0" \
		"bootargs_enigma2=console=ttyAS1,115200 root=/dev/mtdblock6 rootfstype=jffs2 " \
		"rw init=/bin/devinit coprocessor_mem=4m@0x40000000,4m@0x40400000 printk=1 " \
		"nwhwconf=device:eth0,hwaddr:00:80:E1:12:40:61 rw ip=172.100.100.249:172.100.100.174:" \
		"172.100.100.174:255.255.0.0:LINUX7109:eth0:off bigphysarea=6000 stmmaceth=msglvl:0,phyaddr:2,watchdog:5000\0" \
		"boot_system=spark\0"	\
		"magic_version=" MAGIC_VERSION "\0"
//YWDRIVER_MODI D02SH 2009/07/20 add end


/************************************************************************
 * Default settings to be used when no valid environment is found
 */
#define XMK_STR(x)	#x
#define MK_STR(x)	XMK_STR(x)


/*******************************************************/
//for nand flash (7167) default env data
#define PDK7162_BOARD pdk7105

#define CFG_BOOT_FROM_SPI

#define PDK7162_CFG_MONITOR_LEN		0x00100000	/* 1M for Monitor :uboot+env param*/

#define PDK7162_CFG_SDRAM_BASE		0x8C000000      /* SDRAM in P1 region */

#define PDK7162_CFG_LOAD_ADDR		PDK7162_CFG_SDRAM_BASE	/* default load address		*/

#ifdef YW_GIT_VERSION
#define PDK7162_CONFIG_YW_VERSION_ON_ARG YW_GIT_VERSION
#else
#define PDK7162_CONFIG_YW_VERSION_ON_ARG ""
#endif


//YWDRIVER_MODI lwj add begin
#define PDK7162_CFG_YW_SPARK_KERNEL_LEN		" 0x00a00000 "
#define PDK7162_CFG_YW_SPARK_KERNEL_BASE	" 0x00100000 "
#define PDK7162_CFG_YW_SPARK_USERFS_LEN		" 0x16c00000 "
#define PDK7162_CFG_YW_SPARK_USERFS_BASE	" 0x01400000 "

#define PDK7162_CFG_YW_ENIGMA2_KERNEL_LEN	" 0x00800000 "
#define PDK7162_CFG_YW_ENIGMA2_KERNEL_BASE	" 0x18000000 "
#define PDK7162_CFG_YW_ENIGMA2_USERFS_LEN	" 0x07700000 "
#define PDK7162_CFG_YW_ENIGMA2_USERFS_BASE	" 0x18800000 "

#define PDK7162_CFG_UBOOT					"u-boot.bin"

#define PDK7162_CFG_SPARK_PATH              "spark"
#define PDK7162_CFG_SPARK_KERNEL_NAME       "mImage"
#define PDK7162_CFG_SPARK_USERFS_NAME       "userfsub.img"

#define PDK7162_CFG_ENIGMA2_PATH            "enigma2"
#define PDK7162_CFG_ENIGMA2_KERNEL_NAME     "uImage"
#define PDK7162_CFG_ENIGMA2_USERFS_NAME     "e2jffs2.img"



#define PDK7162_CFG_YW_LOADU_UBOOT			"fatload usb 0 $load_addr "PDK7162_CFG_UBOOT
#define PDK7162_CFG_YW_TFTP_UBOOT			"tftp $load_addr "PDK7162_CFG_UBOOT

#define PDK7162_CFG_YW_LOADU_KERNEL			"fatload usb 0 $load_addr $kernel_name"
#define PDK7162_CFG_YW_LOADU_KERNEL_SPARK	"fatload usb 0 $load_addr "PDK7162_CFG_SPARK_KERNEL_NAME
#define PDK7162_CFG_YW_LOADU_KERNEL_ENIGMA2	"fatload usb 0 $load_addr "PDK7162_CFG_ENIGMA2_KERNEL_NAME

#define PDK7162_CFG_YW_TFTP_KERNEL			"tftp $load_addr $tftp_kernel_name"
#define PDK7162_CFG_YW_TFTP_KERNEL_SPARK	"tftp $load_addr "PDK7162_CFG_SPARK_KERNEL_NAME
#define PDK7162_CFG_YW_TFTP_KERNEL_ENIGMA2	"tftp $load_addr "PDK7162_CFG_ENIGMA2_KERNEL_NAME

#define PDK7162_CFG_YW_LOADU_USERFS			"fatload usb 0 $load_addr $userfs_name"
#define PDK7162_CFG_YW_LOADU_USERFS_SPARK	"fatload usb 0 $load_addr "PDK7162_CFG_SPARK_USERFS_NAME
#define PDK7162_CFG_YW_LOADU_USERFS_ENIGMA2	"fatload usb 0 $load_addr "PDK7162_CFG_ENIGMA2_USERFS_NAME

#define PDK7162_CFG_YW_TFTP_USERFS			"tftp $load_addr $tftp_userfs_name"
#define PDK7162_CFG_YW_TFTP_USERFS_SPARK	"tftp $load_addr "PDK7162_CFG_SPARK_USERFS_NAME
#define PDK7162_CFG_YW_TFTP_USERFS_ENIGMA2	"tftp $load_addr "PDK7162_CFG_ENIGMA2_USERFS_NAME


#if defined(CFG_BOOT_FROM_NAND) || defined(CFG_BOOT_FROM_SPI)
#define PDK7162_CFG_YW_BOOTCMD_SPARK \
		"nboot.i " XSTR(PDK7162_CFG_LOAD_ADDR) " 0 " PDK7162_CFG_YW_SPARK_KERNEL_BASE ";" \
		"bootm " XSTR(PDK7162_CFG_LOAD_ADDR)
#else
#define PDK7162_CFG_YW_BOOTCMD_SPARK "bootm " PDK7162_CFG_YW_SPARK_KERNEL_BASE
#endif

#define PDK7162_CFG_YW_BOOTCMD_ENIGMA2												\
		"nboot.i " XSTR(PDK7162_CFG_LOAD_ADDR) " 0 " PDK7162_CFG_YW_ENIGMA2_KERNEL_BASE ";"	\
		"bootm " XSTR(PDK7162_CFG_LOAD_ADDR)

#define PDK7162_CFG_YW_BOOTCMD		PDK7162_CFG_YW_BOOTCMD_SPARK


#if defined(CFG_BOOT_FROM_NAND)
#define PDK7162_CFG_YW_UPDATE_UBOOT "nand erase $monitor_base $monitor_len"			\
							"nand write.i $load_addr $monitor_base $monitor_len"
#elif defined(CFG_BOOT_FROM_SPI)
#define PDK7162_CFG_YW_UPDATE_UBOOT "eeprom write $load_addr $monitor_base $monitor_len"
#define PDK7162_CFG_YW_ERASE_UBOOT_ENV "mw.b $load_addr 0 " XSTR(CFG_ENV_SIZE) ";"	\
					"eeprom write $load_addr 0x000a0000 "XSTR(CFG_ENV_SIZE)
#else
#define PDK7162_CFG_YW_UPDATE_UBOOT "protect off $monitor_sec;"						\
							"erase $monitor_sec;"							\
							"cp.b $load_addr $monitor_base $monitor_len;"	\
							"protect on $monitor_sec"
#endif


#define PDK7162_CFG_YW_ERASE_CMD				"nand erase"
#define PDK7162_CFG_YW_WRITE_CMD				"nand write.i"
#define PDK7162_CFG_YW_WRITE_USERFS_SPARK_CMD	"nand write.yaffs2"
#define PDK7162_CFG_YW_WRITE_USERFS_ENIGMA2_CMD	"nand write.jffs2"


/*
#define PDK7162_CFG_YW_UPDATE_KERNEL "nand erase " PDK7162_CFG_YW_SPARK_KERNEL_BASE PDK7162_CFG_YW_SPARK_KERNEL_LEN ";" \
		"nand write.i " XSTR(PDK7162_CFG_LOAD_ADDR) PDK7162_CFG_YW_SPARK_KERNEL_BASE "$filesize"

#define PDK7162_CFG_YW_UPDATE_USERFS "nand erase " PDK7162_CFG_YW_SPARK_USERFS_BASE PDK7162_CFG_YW_SPARK_USERFS_LEN ";" \
		"nand write.yaffs2 " XSTR(PDK7162_CFG_LOAD_ADDR) PDK7162_CFG_YW_SPARK_USERFS_BASE "$filesize"
*/

#define PDK7162_CFG_YW_ERASE_KERNEL_SPARK 		PDK7162_CFG_YW_ERASE_CMD " "			\
											PDK7162_CFG_YW_SPARK_KERNEL_BASE	\
											PDK7162_CFG_YW_SPARK_KERNEL_LEN
#define PDK7162_CFG_YW_WRITE_KERNEL_SPARK 		PDK7162_CFG_YW_WRITE_CMD " "			\
											XSTR(PDK7162_CFG_LOAD_ADDR) 		\
											PDK7162_CFG_YW_SPARK_KERNEL_BASE 	\
											"$filesize"
#define PDK7162_CFG_YW_UPDATE_KERNEL_SPARK		PDK7162_CFG_YW_ERASE_KERNEL_SPARK ";"	\
											PDK7162_CFG_YW_WRITE_KERNEL_SPARK
#define PDK7162_CFG_YW_ERASE_KERNEL_ENIGMA2		PDK7162_CFG_YW_ERASE_CMD " "			\
											PDK7162_CFG_YW_ENIGMA2_KERNEL_BASE	\
											PDK7162_CFG_YW_ENIGMA2_KERNEL_LEN
#define PDK7162_CFG_YW_WRITE_KERNEL_ENIGMA2		PDK7162_CFG_YW_WRITE_CMD " "			\
											XSTR(PDK7162_CFG_LOAD_ADDR) 		\
											PDK7162_CFG_YW_ENIGMA2_KERNEL_BASE 	\
											"$filesize"
#define PDK7162_CFG_YW_UPDATE_KERNEL_ENIGMA2	PDK7162_CFG_YW_ERASE_KERNEL_ENIGMA2 ";"	\
											PDK7162_CFG_YW_WRITE_KERNEL_ENIGMA2
#define PDK7162_CFG_YW_UPDATE_KERNEL			PDK7162_CFG_YW_UPDATE_KERNEL_SPARK
#define PDK7162_CFG_YW_ERASE_USERFS_SPARK		PDK7162_CFG_YW_ERASE_CMD " "			\
											PDK7162_CFG_YW_SPARK_USERFS_BASE	\
											PDK7162_CFG_YW_SPARK_USERFS_LEN
#define PDK7162_CFG_YW_WRITE_USERFS_SPARK 		PDK7162_CFG_YW_WRITE_USERFS_SPARK_CMD " "	\
											XSTR(PDK7162_CFG_LOAD_ADDR) 		\
											PDK7162_CFG_YW_SPARK_USERFS_BASE 	\
											"$filesize"
#define PDK7162_CFG_YW_UPDATE_USERFS_SPARK		PDK7162_CFG_YW_ERASE_USERFS_SPARK ";"	\
											PDK7162_CFG_YW_WRITE_USERFS_SPARK
#define PDK7162_CFG_YW_ERASE_USERFS_ENIGMA2 	PDK7162_CFG_YW_ERASE_CMD " "			\
											PDK7162_CFG_YW_ENIGMA2_USERFS_BASE	\
											PDK7162_CFG_YW_ENIGMA2_USERFS_LEN
#define PDK7162_CFG_YW_WRITE_USERFS_ENIGMA2 	PDK7162_CFG_YW_WRITE_USERFS_ENIGMA2_CMD " "	\
											XSTR(PDK7162_CFG_LOAD_ADDR) 		\
											PDK7162_CFG_YW_ENIGMA2_USERFS_BASE 	\
											"$filesize"
#define PDK7162_CFG_YW_UPDATE_USERFS_ENIGMA2	PDK7162_CFG_YW_ERASE_USERFS_ENIGMA2 ";"	\
											PDK7162_CFG_YW_WRITE_USERFS_ENIGMA2
#define PDK7162_CFG_YW_UPDATE_USERFS			PDK7162_CFG_YW_UPDATE_USERFS_SPARK



#define PDK7162_CFG_SPARK_KERNEL_FULLNAME   PDK7162_CFG_SPARK_PATH"/"PDK7162_CFG_SPARK_KERNEL_NAME
#define PDK7162_CFG_SPARK_USERFS_FULLNAME   PDK7162_CFG_SPARK_PATH"/"PDK7162_CFG_SPARK_USERFS_NAME

#define PDK7162_CFG_ENIGMA2_KERNEL_FULLNAME PDK7162_CFG_ENIGMA2_PATH"/"PDK7162_CFG_ENIGMA2_KERNEL_NAME
#define PDK7162_CFG_ENIGMA2_USERFS_FULLNAME PDK7162_CFG_ENIGMA2_PATH"/"PDK7162_CFG_ENIGMA2_USERFS_NAME

#define PDK7162_YWCFG_BOOTARGS_SPARK		"console=ttyAS1,115200 "				\
									"rw "									\
									"ramdisk_size=6144 "					\
									"root=/dev/ram0 "						\
									"init=/linuxrc "						\
									"nwhwconf=device:eth0,"					\
											"hwaddr:00:80:E1:12:40:69 "		\
									"ip=192.168.0.69:"						\
											"192.168.3.119:"				\
											"192.168.3.1:"					\
											"255.255.0.0:"					\
											"Spark:"						\
											"eth0:"							\
											"off "							\
									"stmmaceth=msglvl:0,"					\
											"phyaddr:1,"					\
											"watchdog:5000 "				\
									"bigphysarea=7000"

#define PDK7162_YWCFG_BOOTARGS_ENIGMA2		"console=ttyAS1,115200 "				\
									"rw "									\
									"root=/dev/mtdblock6 "					\
									"rootfstype=jffs2 "						\
									"init=/bin/devinit "					\
									"coprocessor_mem=4m@0x40000000,"		\
											"4m@0x40400000 "				\
									"printk=1 "								\
									"nwhwconf=device:eth0,"					\
											"hwaddr:00:80:E1:12:40:61 "		\
									"ip=172.100.100.249:"					\
											"172.100.100.174:"				\
											"172.100.100.174:"				\
											"255.255.0.0:"					\
											"Enigma2:"						\
											"eth0:"							\
											"off "							\
									"stmmaceth=msglvl:0,"					\
											"phyaddr:2,"					\
											"watchdog:5000 "				\
									"bigphysarea=6000"


#define PDK7162_YWCFG_BOOTARGS_NFS			"console=ttyAS0,115200 "				\
									"rw "									\
									"root=/dev/nfs "						\
									"nfsroot=192.168.40.19:/opt/target,"	\
											"nfsvers=2,"					\
											"rsize=4096,"					\
											"wsize=8192,tcp "				\
									"nwhwconf=device:eth0,"					\
											"hwaddr:00:80:E1:12:40:61 "		\
									"ip=192.168.40.61:"						\
											"192.168.40.19:"				\
											"192.168.3.1:"					\
											"255.255.0.0:" 					\
											"LINUX7167:"					\
											"eth0:"							\
											"off "							\
									"stmmaceth=msglvl:0,"					\
											"phyaddr:1,"					\
											"watchdog:5000 "				\
									"bigphysarea=7000"
/***** 2011-11-11 D26LF Add end ****/

#define PDK7162_CONFIG_EXTRA_ENV_SETTINGS \
		"yw_version=" PDK7162_CONFIG_YW_VERSION_ON_ARG "\0" \
		"board=" XSTR(PDK7162_BOARD) "\0" \
		"monitor_base=0" "\0" \
		"monitor_len=" XSTR(PDK7162_CFG_MONITOR_LEN) "\0" \
		"load_addr=" XSTR(PDK7162_CFG_LOAD_ADDR) "\0" \
        "HOSTNAME=LINUX7167\0" \
		"ethaddr=00:80:E1:12:06:38\0" \
		"ipaddr=192.168.40.63\0" \
		"netmask=255.255.255.0\0" \
		"gatewayip=192.168.40.1\0" \
		"serverip=192.168.40.19\0" \
		"bootcmd=" PDK7162_CFG_YW_BOOTCMD_SPARK "\0" \
		"bootcmd_spark=" PDK7162_CFG_YW_BOOTCMD_SPARK "\0" \
		"bootcmd_enigma2=" PDK7162_CFG_YW_BOOTCMD_ENIGMA2 "\0" \
        "kernel_base=" PDK7162_CFG_YW_SPARK_KERNEL_BASE "\0" \
		"kernel_base_spark="PDK7162_CFG_YW_SPARK_KERNEL_BASE"\0" \
		"kernel_base_enigma2="PDK7162_CFG_YW_ENIGMA2_KERNEL_BASE"\0" \
		"kernel_len=" PDK7162_CFG_YW_SPARK_KERNEL_LEN "\0" \
		"kernel_len_spark=" PDK7162_CFG_YW_SPARK_KERNEL_LEN "\0" \
		"kernel_len_enigma2=" PDK7162_CFG_YW_ENIGMA2_KERNEL_LEN "\0" \
		"erase_env=" PDK7162_CFG_YW_ERASE_UBOOT_ENV "\0" \
		"loadu_uboot=" PDK7162_CFG_YW_LOADU_UBOOT "\0" \
		"loadu_kernel=" PDK7162_CFG_YW_LOADU_KERNEL "\0" \
		"loadu_kernel_spark=" PDK7162_CFG_YW_LOADU_KERNEL_SPARK "\0" \
		"loadu_kernel_enigma2=" PDK7162_CFG_YW_LOADU_KERNEL_ENIGMA2 "\0" \
		"loadu_userfs=" PDK7162_CFG_YW_LOADU_USERFS "\0" \
		"loadu_userfs_spark=" PDK7162_CFG_YW_LOADU_USERFS_SPARK "\0" \
		"loadu_userfs_enigma2=" PDK7162_CFG_YW_LOADU_USERFS_ENIGMA2 "\0" \
		"tftp_uboot=" PDK7162_CFG_YW_TFTP_UBOOT "\0" \
		"tftp_kernel=" PDK7162_CFG_YW_TFTP_KERNEL "\0" \
		"tftp_kernel_spark=" PDK7162_CFG_YW_TFTP_KERNEL_SPARK "\0" \
		"tftp_kernel_enigma2=" PDK7162_CFG_YW_TFTP_KERNEL_ENIGMA2 "\0" \
		"tftp_userfs=" PDK7162_CFG_YW_TFTP_USERFS "\0" \
		"tftp_userfs_spark=" PDK7162_CFG_YW_TFTP_USERFS_SPARK "\0" \
		"tftp_userfs_enigma2=" PDK7162_CFG_YW_TFTP_USERFS_ENIGMA2 "\0" \
        "erase_kernel=" PDK7162_CFG_YW_ERASE_KERNEL_SPARK"\0" \
        "erase_userfs=" PDK7162_CFG_YW_ERASE_USERFS_SPARK "\0" \
        "erase_kernel_enigma2=" PDK7162_CFG_YW_ERASE_KERNEL_ENIGMA2"\0" \
        "erase_userfs_enigma2=" PDK7162_CFG_YW_ERASE_USERFS_ENIGMA2 "\0" \
        "write_kernel=" PDK7162_CFG_YW_WRITE_KERNEL_SPARK"\0" \
        "write_userfs=" PDK7162_CFG_YW_WRITE_USERFS_SPARK "\0" \
        "write_kernel_enigma2=" PDK7162_CFG_YW_WRITE_KERNEL_ENIGMA2"\0" \
        "write_userfs_enigma2=" PDK7162_CFG_YW_WRITE_USERFS_ENIGMA2 "\0" \
        "update=" PDK7162_CFG_YW_UPDATE_UBOOT "\0" \
        "update_kernel=" PDK7162_CFG_YW_UPDATE_KERNEL "\0" \
        "update_userfs=" PDK7162_CFG_YW_UPDATE_USERFS "\0" \
        "update_kernel_enigma2=" PDK7162_CFG_YW_UPDATE_KERNEL_ENIGMA2"\0" \
        "update_userfs_enigma2=" PDK7162_CFG_YW_UPDATE_USERFS_ENIGMA2 "\0" \
		"tftp_kernel_name="PDK7162_CFG_SPARK_KERNEL_NAME"\0" \
		"tftp_kernel_name_spark="PDK7162_CFG_SPARK_KERNEL_NAME"\0" \
		"tftp_kernel_name_enigma2="PDK7162_CFG_ENIGMA2_KERNEL_NAME"\0" \
		"tftp_userfs_name="PDK7162_CFG_SPARK_USERFS_NAME"\0" \
		"tftp_userfs_name_spark="PDK7162_CFG_SPARK_USERFS_NAME"\0" \
		"tftp_userfs_name_enigma2="PDK7162_CFG_ENIGMA2_USERFS_NAME"\0" \
		"kernel_name="PDK7162_CFG_SPARK_KERNEL_FULLNAME"\0" \
		"kernel_name_spark="PDK7162_CFG_SPARK_KERNEL_FULLNAME"\0" \
		"kernel_name_enigma2="PDK7162_CFG_ENIGMA2_KERNEL_FULLNAME"\0" \
		"userfs_name="PDK7162_CFG_SPARK_USERFS_FULLNAME"\0" \
		"userfs_name_spark="PDK7162_CFG_SPARK_USERFS_FULLNAME"\0" \
		"userfs_name_enigma2="PDK7162_CFG_ENIGMA2_USERFS_FULLNAME"\0" \
		"userfs_base="PDK7162_CFG_YW_SPARK_USERFS_BASE"\0" \
		"userfs_base_spark="PDK7162_CFG_YW_SPARK_USERFS_BASE"\0" \
		"userfs_base_enigma2="PDK7162_CFG_YW_ENIGMA2_USERFS_BASE"\0" \
		"userfs_len="PDK7162_CFG_YW_SPARK_USERFS_LEN"\0" \
		"userfs_len_spark="PDK7162_CFG_YW_SPARK_USERFS_LEN"\0" \
		"userfs_len_enigma2="PDK7162_CFG_YW_ENIGMA2_USERFS_LEN"\0" \
		"uboot_name=u-boot.bin\0" \
		"ubootnfspath=192.168.40.19:/opt/target\0" \
		"kernelnfspath=192.168.40.19:/opt/target\0" \
		"rootfsnfspath=192.168.40.19:/opt/target\0" \
		"bootfromnfs="PDK7162_YWCFG_BOOTARGS_NFS"\0" \
		"bootargs_flash="PDK7162_YWCFG_BOOTARGS_SPARK"\0" \
		"bootargs="PDK7162_YWCFG_BOOTARGS_SPARK"\0" \
		"bootargs_spark="PDK7162_YWCFG_BOOTARGS_SPARK"\0" \
		"bootargs_enigma2="PDK7162_YWCFG_BOOTARGS_ENIGMA2"\0" \
		"boot_system=spark\0"


#if 0
#define NAND_CONFIG_EXTRA_ENV_SETTINGS \
		"board=" XSTR(NAND_BOARD) "\0" \
		"monitor_base=0" "\0" \
		"monitor_len=" XSTR(NAND_CFG_MONITOR_LEN) "\0" \
		"load_addr=" XSTR(NAND_CFG_LOAD_ADDR) "\0" \
        "HOSTNAME=LINUX7167\0" \
		"ethaddr=00:80:E1:12:06:38\0" \
		"ipaddr=192.168.40.63\0" \
		"netmask=255.255.255.0\0" \
		"gatewayip=192.168.40.1\0" \
		"serverip=192.168.40.19\0" \
		"bootcmd=" NAND_CFG_YW_BOOTCMD "\0" \
        "kernel_base=" NAND_CFG_YW_SPARK_KERNEL_BASE "\0" \
		"kernel_base_spark="NAND_CFG_YW_SPARK_KERNEL_BASE"\0" \
		"kernel_base_enigma2="NAND_CFG_YW_ENIGMA2_KERNEL_BASE"\0" \
		"kernel_len=" NAND_CFG_YW_SPARK_KERNEL_LEN "\0" \
		"kernel_len_spark=" NAND_CFG_YW_SPARK_KERNEL_LEN "\0" \
		"kernel_len_enigma2=" NAND_CFG_YW_ENIGMA2_KERNEL_LEN "\0" \
        "update_kernel=" NAND_CFG_YW_UPDATE_KERNEL "\0" \
        "update_rootfs=" NAND_CFG_YW_UPDATE_USERFS "\0" \
		"tftp_kernel_name="NAND_CFG_SPARK_KERNEL_NAME"\0" \
		"tftp_kernel_name_spark="NAND_CFG_SPARK_KERNEL_NAME"\0" \
		"tftp_kernel_name_enigma2="NAND_CFG_ENIGMA2_KERNEL_NAME"\0" \
		"tftp_userfs_name="NAND_CFG_SPARK_USERFS_NAME"\0" \
		"tftp_userfs_name_spark="NAND_CFG_SPARK_USERFS_NAME"\0" \
		"tftp_userfs_name_enigma2="NAND_CFG_ENIGMA2_USERFS_NAME"\0" \
		"kernel_name="NAND_CFG_SPARK_KERNEL_FULLNAME"\0" \
		"kernel_name_spark="NAND_CFG_SPARK_KERNEL_FULLNAME"\0" \
		"kernel_name_enigma2="NAND_CFG_ENIGMA2_KERNEL_FULLNAME"\0" \
		"userfs_name="NAND_CFG_SPARK_USERFS_FULLNAME"\0" \
		"userfs_name_spark="NAND_CFG_SPARK_USERFS_FULLNAME"\0" \
		"userfs_name_enigma2="NAND_CFG_ENIGMA2_USERFS_FULLNAME"\0" \
		"userfs_base="NAND_CFG_YW_SPARK_USERFS_BASE"\0" \
		"userfs_base_spark="NAND_CFG_YW_SPARK_USERFS_BASE"\0" \
		"userfs_base_enigma2="NAND_CFG_YW_ENIGMA2_USERFS_BASE"\0" \
		"userfs_len="NAND_CFG_YW_SPARK_USERFS_LEN"\0" \
		"userfs_len_spark="NAND_CFG_YW_SPARK_USERFS_LEN"\0" \
		"userfs_len_enigma2="NAND_CFG_YW_ENIGMA2_USERFS_LEN"\0" \
		"kernelnfspath=192.168.40.19:/opt/target\0" \
		"rootfsnfspath=192.168.40.19:/opt/target\0" \
		"uboot_name=u-boot.bin\0" \
		"ubootnfspath=192.168.40.19:/opt/target\0" \
		"bootfromnfs=nfs 0x80000000 $kernelnfspath/$kernel_name;bootm 0x80000000\0" \
		"bootargs_nfs=console=ttyAS0,115200 nwhwconf=device:eth0,hwaddr:00:80:E1:12:40:61 " \
		"stmmaceth=msglvl:0,phyaddr:1,watchdog:5000 root=/dev/nfs nfsroot=" \
		"192.168.40.19:/opt/target,nfsvers=2,rsize=4096," \
		"wsize=8192,tcp rw ip=192.168.40.61:192.168.40.19:192.168.3.1:255.255.0.0:" \
		"LINUX7167:eth0:off bigphysarea=7000\0" \
		"bootargs_flash=console=ttyAS1,115200 rw ramdisk_size=6144 init=/linuxrc " \
		"root=/dev/ram0 nwhwconf=device:eth0,hwaddr:00:80:E1:12:40:69 ip=192.168.0.69" \
		":192.168.3.119:192.168.3.1:255.255.0.0:lh:eth0:off stmmaceth=msglvl:0,phyaddr:1," \
		"watchdog:5000 bigphysarea=7000\0" \
		"bootargs=console=ttyAS1,115200 rw ramdisk_size=6144 init=/linuxrc " \
		"root=/dev/ram0 nwhwconf=device:eth0,hwaddr:00:80:E1:12:40:69 ip=192.168.0.69" \
		":192.168.0.119:192.168.0.1:255.255.255.0:lh:eth0:off stmmaceth=msglvl:0,phyaddr:1," \
		"watchdog:5000 bigphysarea=7000\0" \
		"bootargs_spark=console=ttyAS1,115200 rw ramdisk_size=6144 init=/linuxrc " \
		"root=/dev/ram0 nwhwconf=device:eth0,hwaddr:00:80:E1:12:40:69 ip=192.168.0.69" \
		":192.168.3.119:192.168.3.1:255.255.0.0:lh:eth0:off stmmaceth=msglvl:0,phyaddr:1," \
		"watchdog:5000 bigphysarea=7000\0" \
		"bootargs_enigma2=console=ttyAS1,115200 root=/dev/mtdblock4 rootfstype=jffs2 " \
		"rw init=/bin/devinit coprocessor_mem=4m@0x40000000,4m@0x40400000 printk=1 " \
		"nwhwconf=device:eth0,hwaddr:00:80:E1:12:40:61 rw ip=172.100.100.249:172.100.100.174:" \
		"172.100.100.174:255.255.0.0:LINUX7167:eth0:off bigphysarea=6000 stmmaceth=msglvl:0,phyaddr:2,watchdog:5000\0" \
		"boot_system=spark\0"

#endif

unsigned long crc32(unsigned long, const unsigned char *, unsigned long);
void set_pdk_type(PDK_TYPE_E pdktype);
PDK_TYPE_E get_pdk_type(void);
int set_system_enigma2();
int set_e2boot_save();
int set_e2boot_init();
void set_e2boot_release();
int set_openseries();
int set_closeseries();



#endif



