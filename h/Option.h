#ifndef __OPTION_H__
#define __OPTION_H__

// ************* OPTIONS **************

#define MCLK	32000000

#define WRBUFOPT (0x8)   //write_buf_on

#define SYSCFG_0KB (0x0|WRBUFOPT)
#define SYSCFG_4KB (0x2|WRBUFOPT)
#define SYSCFG_8KB (0x6|WRBUFOPT)

#define DRAM	    1		//In case DRAM is used
#define SDRAM	    2		//In case SDRAM is used
#define BDRAMTYPE   SDRAM	//used in power.c,44blib.c

//BUSWIDTH; 16,32
#define BUSWIDTH    (16)

#define CACHECFG    SYSCFG_8KB

#define _RAM_STARTADDRESS 0x2030000

//#define _ISR_STARTADDRESS 0xc1fff00   //GCS6:16M DRAM
#define _ISR_STARTADDRESS 0x207ff00     //GCS6:64M DRAM/SDRAM

#define Non_Cache_Start	(0x2000000)
#define Non_Cache_End 	(0xc000000)

#define CLCD_240_320	(1)
#define MLCD_320_240	(2)
#define LCD_TYPE	MLCD_320_240
//#define LCD_TYPE	CLCD_240_320

// NOTE: rom.mak,option.a have to be changed
#endif /*__OPTION_H__*/