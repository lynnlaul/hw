#ifndef _MIFARE_H
#define _MIFARE_H

#define ALL                   0x01
#define IDLE                  0x00

#define MI_OK                           0
#define MI_CHK_OK                       0
#define MI_CRC_ZERO                     0

#define MI_CRC_NOTZERO                  1

#define MI_NOTAGERR                     (-1)
#define MI_CHK_FAILED                   (-1)
#define MI_CRCERR                       (-2)
#define MI_CHK_COMPERR                  (-2)
#define MI_EMPTY                        (-3)
#define MI_AUTHERR                      (-4)
#define MI_PARITYERR                    (-5)
#define MI_CODEERR                      (-6)

#define MI_SERNRERR                     (-8)
#define MI_KEYERR                       (-9)
#define MI_NOTAUTHERR                   (-10)
#define MI_BITCOUNTERR                  (-11)
#define MI_BYTECOUNTERR                 (-12)
#define MI_IDLE                         (-13)
#define MI_TRANSERR                     (-14)
#define MI_WRITEERR                     (-15)
#define MI_INCRERR                      (-16)
#define MI_DECRERR                      (-17)
#define MI_READERR                      (-18)
#define MI_OVFLERR                      (-19)
#define MI_POLLING                      (-20)
#define MI_FRAMINGERR                   (-21)
#define MI_ACCESSERR                    (-22)
#define MI_UNKNOWN_COMMAND              (-23)
#define MI_COLLERR                      (-24)
#define MI_RESETERR                     (-25)
#define MI_INITERR                      (-25)
#define MI_INTERFACEERR                 (-26)
#define MI_ACCESSTIMEOUT                (-27)
#define MI_NOBITWISEANTICOLL            (-28)
#define MI_QUIT                         (-30)

#define MI_RECBUF_OVERFLOW              (-50) 
#define MI_SENDBYTENR                   (-51)
	
#define MI_SENDBUF_OVERFLOW             (-53)
#define MI_BAUDRATE_NOT_SUPPORTED       (-54)
#define MI_SAME_BAUDRATE_REQUIRED       (-55)

#define MI_WRONG_PARAMETER_VALUE        (-60)

#define MI_BREAK                        (-99)
#define MI_NY_IMPLEMENTED               (-100)
#define MI_NO_MFRC                      (-101)
#define MI_MFRC_NOTAUTH                 (-102)
#define MI_WRONG_DES_MODE               (-103)
#define MI_HOST_AUTH_FAILED             (-104)

#define MI_WRONG_LOAD_MODE              (-106)
#define MI_WRONG_DESKEY                 (-107)
#define MI_MKLOAD_FAILED                (-108)
#define MI_FIFOERR                      (-109)
#define MI_WRONG_ADDR                   (-110)
#define MI_DESKEYLOAD_FAILED            (-111)

#define MI_WRONG_SEL_CNT                (-114)

#define MI_WRONG_TEST_MODE              (-117)
#define MI_TEST_FAILED                  (-118)
#define MI_TOC_ERROR                    (-119)
#define MI_COMM_ABORT                   (-120)
#define MI_INVALID_BASE                 (-121)
#define MI_MFRC_RESET                   (-122)
#define MI_WRONG_VALUE                  (-123)
#define MI_VALERR                       (-124)
 
 
int mif_open(void);	//
int mif_close(void);//

int mif_request(unsigned char mode,unsigned char *atq);
int mif_anticoll(unsigned char bcnt,unsigned char  *cardsnr);
int mif_select(unsigned char  *serial);
int mif_authentication( unsigned char auth_mode,unsigned char sactor,unsigned char *snr);
int mif_write( unsigned char blockaddr,unsigned char *W_data);
int mif_read(unsigned char blockaddr,unsigned char *mif_data);
int mif_load_key(unsigned char  *uncodekey);
int mif_increment(unsigned char block_addr, unsigned long value);
int mif_decrement(unsigned char block_addr, unsigned long value);
int mif_transfer(unsigned char block_addr);
int mif_restore(unsigned char block_addr);
int mif_halt(void);
int mif_readrom(unsigned short addr, unsigned char len,unsigned char  *e2data);
int mif_writerom(unsigned short addr, unsigned char len,unsigned char  *e2data);
          
#endif
