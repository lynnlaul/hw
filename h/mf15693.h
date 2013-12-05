#ifndef _ISO15693_H
#define _ISO15693_H


#define  LB_ACCESSTIMEOUT                (10)
#define  LB_OK                       9
#define  LB_REVDATA_ERR			   	12
#define  LB_BLOCKLOCKED              13
#define  LB_COMMAND_UNSURPORT        14 
#define	 LB_COMMANDFORMAT_ERR	     15
#define	 LB_OPTION_UNSURPORT	     17
#define	 LB_UNKOWN_ERR			     18
#define	 LB_BLOCK_NOTEXIST 		     19
#define  LB_BLOCK_LOCKUNSUCESS       20
 
#define	 LB_NO_ERR		   			 0
#define	 LB_NO_TAG		    		 8
#define	 LB_CRCERR		    		 2
#define	 LB_COLLERR		    		 11
#define	 LB_SNRERR		     		 4 
#define	 LB_COUNTERR		     	 5
#define	 LB_TSOCC		     		 6
#define  LB_FRAMINGERR        		 7

char ISO15693_open(void);
char ISO15693_close(void);
char ISO15693_Transceive (U8  *cmd, U8  cmdlen, U8  *rcv);
char ISO15693_Inventory (U8  flags,U8  AFI,U8  masklengh,U8  *uid,U8  *resp);
char ISO15693_Inventory_16 ( U8  *cmd,U8  cmdlen,U8  *rcv);
char ISO15693_GetInfo(U8  flags,U8  *uid, U8  *resp); 
char ISO15693_Read_sm (U8  flags,U8  *uid,U8  blnr,U8  nbl,U8  *resp);	
char ISO15693_Write_sm (U8  flags,U8  *uid,U8  blnr,U8  nbl,U8  *_data,U8  *resp);
char ISO15693_Lock_Block (U8  flags,U8  *uid,U8  blnr,U8  *resp);
char ISO15693_Select (U8  flags,U8  *uid, U8  *resp);
char ISO15693_Get_MBSec(U8  flags,U8  *uid,U8  blnr, U8  nbl,U8  *resp);
char ISO15693_Lock_AFI (U8  flags,U8  *uid,U8  *resp);
char ISO15693_RTReady (U8  flags,U8  *uid,U8  *resp);
char ISO15693_Write_AFI (U8  flags,U8  *uid,U8  AFI,U8  *resp);
char ISO15693_Stay_Quiet (U8  flags,U8  *uid,U8  *resp);
char ISO15693_Write_DSFID (U8  flags,U8  *uid, U8  DSFID,U8  *resp);
char ISO15693_Lock_DSFID (U8  flags,U8  *uid,U8  *resp);


#endif

