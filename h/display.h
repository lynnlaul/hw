
#ifndef _DISPLAY_H
#define _DISPLAY_H

void screen(  unsigned char scmod);
void cls(void);
void clsn(  unsigned char stcol,  unsigned char strow);

void moveto(U8 y,U8 x);
void MoveTo(U8 x,U8 y);

unsigned char getx(void);
unsigned char gety(void);
void putch(  unsigned char dischar);
void putchhex(  unsigned char dishex);
void putn_hex(unsigned char len,unsigned char *s);

void putstr(  unsigned char *disstr);
void putn(  unsigned char strlen,  unsigned char *disstr);
void putch_h(  unsigned char dischar);
void putstr_h(  unsigned char *disstr);
void putn_h(  unsigned char strlen,  unsigned char *disstr);

void put_block(U8 x,U8 y,U8 *s);
void get_block(U8 x,U8 y,U8 *s);
#endif
