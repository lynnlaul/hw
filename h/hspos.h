#ifndef _HSPOS_H
#define _HSPOS_H
 
#include <stdios.h> 
#include <fileapi.h>
#include <dbfio.h>
#include <printer.h>
#include <mfmifare.h>
//-------------------------------------------------------------------------------------------------------
//key
//-------------------------------------------------------------------------------------------------------
#define 	KEY_F1		0x88
#define 	KEY_F2		0x89
#define 	KEY_SW		0x8c
#define 	KEY_ENTER	0x8d
#define 	KEY_CLS		0x82
#define 	KEY_DOWN	0x8f
#define 	KEY_UP		0x8e

char key( unsigned char disb);
char keya(  unsigned char *disb,unsigned char n);
char keygo(void);
char keygos(unsigned long n);
char keys( unsigned char *disb);
char keysn(unsigned char *s,unsigned char n);
//-------------------------------------------------------------------------------------------------------
//lcd display
//-------------------------------------------------------------------------------------------------------
void screen(  U8 scmod);
void cls(void);
void clsn(  U8 stcol,  U8 strow);
void moveto(U8 y,U8 x);
void MoveTo(U8 x,U8 y);
U8 getx(void);
U8 gety(void);
void putch(  U8 dischar);
void putstr(const char *disstr);
#define puts putstr
void putn(  U8 strlen,  U8 *disstr);
void putch_x(  U8 dischar,U8 dis_mode);
void putstr_x(  U8 *disstr,U8 dis_mode);
void putn_x (U8 strlen,  U8 *disstr,U8 dis_mode);
void putch_h(  U8 dischar);
void putstr_h(  U8 *disstr);
void putn_h(  U8 strlen,  U8 *disstr);
void putchhex(  U8 dishex);
void putn_hex(U8 len,U8 *s);
void put_block(U8 x,U8 y,U8 *s);
void get_block(U8 x,U8 y,U8 *s);
void reverse_block(U8 x,U8 y);
void save_video(U8 sx,U8 ex,U8 sy,U8 ey,U8 *buf_ptr);
void restore_video(U8 sx,U8 ex,U8 sy,U8 ey,U8 *buf_ptr);
void setdot( U8 x, U8 y);
void clrdot( U8 x, U8 y);
void drawline(U8 sx,U8 sy,U8 ex,U8 ey);
void drawrect(U8 sx,U8 sy,U8 ex,U8 ey);

//-------------------------------------------------------------------------------------------------------
//rtc
//-------------------------------------------------------------------------------------------------------
void gettime(  unsigned char *rtmbuf);
void getdate(  unsigned char *rdtbuf);
unsigned char getweek(void );
void settime( unsigned char *wtmbuf);
void setdata( unsigned char *wdtbuf);
void setweek( unsigned char);

//-------------------------------------------------------------------------------------------------------
//uart
//-------------------------------------------------------------------------------------------------------
//baund
#define  B1200   	0   
#define  B2400   	1  
#define  B4800   	2
#define  B9600   	3
#define  B19200  	4    
#define  B28800  	5
#define  B38400  	6
#define  B57600  	7    
#define  B76800  	8   
#define  B115200  	9    

#define  B110     20  
#define  B300     21
#define  B600	  22

#define  UART_ON    1
#define  UART_OFF	0



//UART0
void Uart0_Init(U16 baud,U16 ctrl,U8 ust);	//��ͨѶ��    ��UST=0�رգ�UST=1��
void Uart0_putbyte(unsigned char data);		//����һ���ֽ�
unsigned  char Uart0_getbyte(void);         //����һ���ֽ�
unsigned char Uart0_getrxstate(void);		//���ܻ�����״̬
unsigned  char Uart0_getrxbuf(void);        //���ܻ���������
//uart
void cominit(unsigned char baud,unsigned char ctrl,unsigned char ust);
unsigned char comread(unsigned char *rdata);
void comwrite(  unsigned char sdata);
unsigned char combuf(void);
unsigned char comstate(void);

//low ir
void ir_init(unsigned char baud,unsigned char ctrl,unsigned char ust);
unsigned char ir_read(unsigned char *rdata);
void ir_write(  unsigned char sdata);
unsigned char ir_rxbuf(void);
unsigned char ir_rxstate(void);

//beep
void BeepOn(void);
void BeepOff(void);
void BeepSet(U8 x,U32 fun);
void beep(int t);
void bell(unsigned char deltm);
//-------------------------------------------------------------------------------------------------------
//sram MAX512BYTE
//-------------------------------------------------------------------------------------------------------
int sram_write(U16 sadd,U16 len,U8 *dbuf);
int sram_read(U16 sadd,U16 len,U8 *dbuf);
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
char doubletoasc(double  c,char *s);
unsigned char stradd(  unsigned char *str1,  unsigned char *str2,  unsigned char addlen);
unsigned char strsub(  unsigned char *str1,  unsigned char *str2,  unsigned char sublen);
unsigned char strmul(  unsigned char *str1,  unsigned char *str2,  unsigned char mullen);
unsigned char strdiv(  unsigned char *str1,  unsigned char *str2,  unsigned char divlen);
unsigned char itos(  unsigned int,  unsigned char *);
int  stoi(  unsigned char,  unsigned char *);
unsigned char ltoa(  long,  unsigned char *);
void htoa(  unsigned char);
unsigned char atoh(  unsigned char,  unsigned char);
unsigned char atob(  unsigned char,  unsigned char);
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

void exit(unsigned char s);

#define Delayus delayus
void delay(unsigned int cnt);
//������ʱ
void delayms( unsigned int); 
//��ʱus
void delayus(unsigned int us);
//��ȡ����Ӧ�ú��ʱ�䣬��λΪ10����
unsigned long get_now_clk(void);
//��ȡһ����ʱ������ʱ����Ŵ�4-31
int req_timer(void);
//����һ����ʱ��ʱ��,��λΪ����
void set_timer(int tm,unsigned long ms);
//��鶨ʱ���Ƿ���
int is_timer_over(int tm);
//�ͷ�һ����ʱ��
void free_timer(int tm);
//��ȡ��ǰ��ϵͳʱ��ʱ��,ϵͳʱ��ѭ��ʹ�� ��λ΢��
unsigned long get_now_usclk(void);

//��չ�Ź��ܺ���
#define SET_PIN_IN 		100
#define SET_PIN_OUT		101
/*
	��չ�Ŷ�Ӧ���, 
	0--5��
	1--6��
	2--7��
	3--3��
	4--4��
����	��7�����øߵ�ƽ Port_Set(2,1)
	��7�����õ͵�ƽ Port_Set(2,0)
	
	3-7��Ĭ�϶�Ϊ����ڣ����˵�7���⣬
	   ����4���ſ�������Ϊ����
		�������ø�ʽΪ
		Port_Set(100,1<<���);
����ѵ��������ó����� 	Port_Set(100,1<<1);
 	  ���������ó�����   Port_Set(100,1<<3);
	
*/
void Port_Set(unsigned long portbit,unsigned long bal);

//��ȡ��չ�ŵ�״̬
//�����ȡ6��״̬ Port_Get(1); ����0��ʾ�͵�ƽ����0��ʾ�ߵ�ƽ
unsigned long Port_Get(unsigned long portbit);

/*
4��5�뺯��
	fin 	����ĸ�����
	dnum	�趨��С����λ��
	so		�����������ַ���

���أ�
	����������ֵ	 
*/
extern double f4s5r(double fin,unsigned char dnum,char *so);
//��ȡGBK�ֿ����
/* ����
	-1	û��GBKFONT.BIN�ֿ�,��Ҫ�����ֿ�
	0 	��ʾ����GBK�ַ�������
	2   ��ʾ��ȡ�ֿ�ɹ�

	
24����ĵ��󳤶���72�ֽ�
16����ĳ�����32�ֽ�	
*/
	
extern int get_gbkfont(unsigned char gbkch[2],unsigned char *OutDot,int dotsize);
//��ȡasc�ַ�����
/* ����
	0 ����asc�ַ� ch>=0x80
	1 ��ʾ��ȡ�ֿ�ɹ� 0-0x19Ϊ�����ַ���û�е������

	24����ĵ��󳤶���48�ֽ�
	��������12��24
	 
*/
extern int get_ascdot(unsigned char ch,unsigned char *OutDot);
/*

��ȡ������ţ�����Ƿ�Ϸ���Ӧ���Լ����
����0
 */
unsigned char get_hpos_sn(unsigned char sn[8]);
/*
��ȡ��汾 
*/
int get_lib_version(void);


#endif