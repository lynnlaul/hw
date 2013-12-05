//*******************RC531地址定义********************
#define	REG_PageSel		0x00		//页写寄存器
#define	REG_Command			0x01   	        //命令寄存器
#define	REG_FIFO			0x02		//FIFO缓冲
#define	REG_PrimaryStatus	        0x03		//状态寄存器1
#define	REG_FIFO_Length		0x04		//FIFO长度寄存器
#define	REG_SecondaryStatus         0x05		//状态寄存器2
#define REG_InterruptEn		0x06		//中断允许寄存器
#define	REG_Int_Req			0x07		//中断申请标记寄存器
#define	REG_Control			0x09		//控制寄存器
#define	REG_ErrorFlag		0x0A		//错误状态寄存器
#define REG_CollPos			0x0B		//冲突检测寄存器
#define REG_TimerValue		0x0C		//定时器当前值
#define REG_CRCResultLSB            0x0D
#define REG_CRCResultMSB            0x0E
#define	REG_Bit_Frame		0x0F		//位帧调整寄存器
#define	REG_BitFraming		0x0F		//位帧调整寄存器
#define	REG_TxControl		0x11		//发送控制寄存器
#define	REG_CwConductance           0x12            //
#define	REG_ModConductance          0x13            //
#define	REG_CoderControl            0x14            //波特率与编码选择寄存器
#define REG_ModWidth                0x15
#define REG_TypeBFraming            0x17
#define REG_RxControl1              0x19
#define REG_DecoderControl          0x1A
#define REG_BitPhase                0x1B
#define REG_RxThreshold             0x1C
#define REG_BPSKDemControl          0x1D
#define REG_RxControl2              0x1E
#define REG_ClockQControl           0x1F
#define REG_RxWait			0x21		//	
#define	REG_ChannelRedundancy	0x22		//RF通道检验模式设置寄存器
#define REG_CRCPresetLSB            0x23
#define REG_CRCPresetMSB            0x24
#define REG_MFOUTSelect             0x26
#define REG_TimerClock		0x2A		//定时器周期设置寄存器
#define REG_TimerControl	        0x2B		//定时器控制寄存器
#define REG_TimerReload		0x2C		//定时器初值寄存器
#define REG_IRQPinConfig            0x2D
#define REG_TestAnaSelect           0x3A
#define REG_TestDigiSelect          0x3D		//测试管脚配置寄存器

//*******************RC531命令寄存器命令码 *******************
#define	CMD_Idle                    0x00
#define	CMD_Transmit                0x1A
#define	CMD_Receive                 0x16
#define	CMD_Transceive		0x1E		//发送接收命令
#define CMD_ReadE2			0x03		//读rc531 e2命令
#define CMD_WriteE2			0x01		//写rc531 e2命令
#define CMD_Authent1		0x0C		//
#define CMD_Authent2		0x14
#define CMD_LoadKeyE2		0x0B
#define CMD_LoadKey			0x19
#define CMD_LoadConfig              0x07
#define CMD_CalcCRC                 0x12

//*******************ISO/IEC FDIS 14443 相关定义 *******************
   // TYPE A
#define REQA                    0x26
#define WUPA                    0x52
#define ATQA_BYTE0              0x04
#define ATQA_BYTE1              0x00
#define SAK_BYTE0               0x80
#define SAK_BYTE1               0x88
#define HLTA_BYTE0              0x50
#define HLTA_BYTE1              0x00

#define ANTICOLL1               0x93
#define AUTHENT1A               0x60
#define AUTHENT1B               0x61
#define READ                    0x30
#define WRITE                   0xA0
#define DECREMENT               0xC0
#define INCREMENT               0xC1
#define RESTORE                 0xC2
#define TRANSFER                0xB0
#define HALT                    0x50
/********************************************/

/* 
rc531 简单操作
1脚 电源                实际接脚
2脚 地
3脚---RC531_SCK  输出    3脚
4脚---RC531_MOSI 输出    4脚
5脚---RC531_NSS  输出    6脚
6脚---RC531_MISO 输入    GPE5 cpu70脚 GPE5 对应IO编号5
7脚---上电高有效  输出    5脚
8脚 
*/
//定义电源
#define RC531_POWER_ON 	Port_Set(0,1)
#define RC531_POWER_OFF Port_Set(0,0)
//定义选择SPI
#define SPI_SELECT 		Port_Set(1,0)
//#define SPI_UNSELECT 		Port_Set(1,0)
#define SPI_UNSELECT	Port_Set(1,1)
//定义SPI时钟
#define SPI_CLK_L Port_Set(3,0)
#define SPI_CLK_H Port_Set(3,1)
//定义MOSI
#define SPI_MOSI_L Port_Set(4,0)
#define SPI_MOSI_H Port_Set(4,1)
//定义MISO 
#define SPI_MISO_H Port_Get(5)

#define ReadIO rc531_register_read
#define WriteIO rc531_register_write
/********************************************/
unsigned char rc531_spi_rw(unsigned char wd);
void rc531_register_write(char reg_ad,char reg_data);
char rc531_register_read(char reg_ad);
char SetBitMask(unsigned char reg,unsigned char mask);
char ClearBitMask(unsigned char reg,unsigned char mask);
void FlushFIFO(void);
int getErrorDisp(char * function);
int getError(void);
int getErrorNoKEYERR(void);
