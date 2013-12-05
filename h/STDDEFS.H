#ifndef _STDDEFS_H
#define _STDDEFS_H

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;
typedef volatile unsigned char vuchar;
typedef volatile unsigned short vushort;
typedef volatile unsigned long vulong;
typedef volatile unsigned int vuint;
typedef volatile int vint;


typedef	unsigned char U8;
typedef unsigned short U16;
typedef unsigned int U32;
typedef	signed char S8;
typedef signed short S16;
typedef signed int S32;

typedef volatile U8  REG8;
typedef volatile U16  REG16;
typedef volatile U32  REG32;

typedef unsigned char BYTE;

 
typedef	U8 *	P_U8;		/*  unsigned 8 bit data  */
typedef	U16 *	P_U16;		/*  unsigned 16 bit data */
typedef	U32 *	P_U32;		/*  unsigned 32 bit data */
typedef	S8 *	P_S8;		/*  signed 8 bit data  */
typedef	S16 *	P_S16;		/*  signed 16 bit data */
typedef	S32 *	P_S32;		/*  signed 32 bit data */

#ifndef NULL
#define NULL	0
#endif

typedef struct{
	U16 year;
	U8 month;
	U8 day;
	U8 weekday;
	U8 hour;
	U8 min;
	U8 sec;
}TIME_STRUC;

#ifndef TRUE
#define TRUE	0
#endif

#ifndef FALSE   
#define FALSE	1
#endif

#endif