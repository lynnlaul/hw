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
void Uart0_Init(U16 baud,U16 ctrl,U8 ust);	//打开通讯口    ，UST=0关闭，UST=1打开
void Uart0_putbyte(unsigned char data);		//发送一个字节
unsigned  char Uart0_getbyte(void);         //接收一个字节
unsigned char Uart0_getrxstate(void);		//接受缓冲区状态
unsigned  char Uart0_getrxbuf(void);        //接受缓冲区数据
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
//毫秒延时
void delayms( unsigned int); 
//延时us
void delayus(unsigned int us);
//获取进入应用后的时间，单位为10毫秒
unsigned long get_now_clk(void);
//获取一个定时器，定时器编号从4-31
int req_timer(void);
//设置一个定时器时间,单位为毫秒
void set_timer(int tm,unsigned long ms);
//检查定时器是否到了
int is_timer_over(int tm);
//释放一个定时器
void free_timer(int tm);
//获取当前的系统时间时钟,系统时钟循环使用 单位微秒
unsigned long get_now_usclk(void);

//扩展脚功能函数
#define SET_PIN_IN 		100
#define SET_PIN_OUT		101
/*
	扩展脚对应编号, 
	0--5脚
	1--6脚
	2--7脚
	3--3脚
	4--4脚
例如	把7脚设置高电平 Port_Set(2,1)
	把7脚设置低电平 Port_Set(2,0)
	
	3-7脚默认都为输出口，除了第7脚外，
	   其他4个脚可以设置为输入
		具体设置格式为
		Port_Set(100,1<<编号);
例如把第六脚设置成输入 	Port_Set(100,1<<1);
 	  第三脚设置成输入   Port_Set(100,1<<3);
	
*/
void Port_Set(unsigned long portbit,unsigned long bal);

//获取扩展脚的状态
//例如获取6脚状态 Port_Get(1); 返回0表示低电平，非0表示高电平
unsigned long Port_Get(unsigned long portbit);

/*
4舍5入函数
	fin 	输入的浮点数
	dnum	设定的小数点位数
	so		四舍五入后的字符串

返回：
	四舍五入后的值	 
*/
extern double f4s5r(double fin,unsigned char dnum,char *so);
//获取GBK字库点阵
/* 返回
	-1	没有GBKFONT.BIN字库,需要下载字库
	0 	表示不在GBK字符集里面
	2   表示获取字库成功

	
24点阵的点阵长度是72字节
16点阵的长度是32字节	
*/
	
extern int get_gbkfont(unsigned char gbkch[2],unsigned char *OutDot,int dotsize);
//获取asc字符点阵
/* 返回
	0 不是asc字符 ch>=0x80
	1 表示获取字库成功 0-0x19为控制字符，没有点阵输出

	24点阵的点阵长度是48字节
	点阵宽度是12×24
	 
*/
extern int get_ascdot(unsigned char ch,unsigned char *OutDot);
/*

获取机器编号，编号是否合法由应用自己检查
返回0
 */
unsigned char get_hpos_sn(unsigned char sn[8]);
/*
获取库版本 
*/
int get_lib_version(void);


#endif