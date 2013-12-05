
//==================
//	For LIB Driver

#ifndef __LIB_H__
#define __LIB_H__

#include "def.h"
#include "44b.h"


unsigned char libuse( unsigned char *filename,unsigned char nn);
unsigned char libopen( unsigned char n);
unsigned int libsumr(void);
unsigned char libsumf(void);
unsigned int libgetr(void);
unsigned char libgetf(void);
//unsigned char libset( int n, unsigned char n);
int libset(unsigned long rec,unsigned short field);
unsigned char libread(unsigned char *s);
int libwrite(unsigned char *cnt);
char libdel(void);
int libapp(void);


#endif
