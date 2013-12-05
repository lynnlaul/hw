//*******************RC531��ַ����********************
#define	REG_PageSel		0x00		//ҳд�Ĵ���
#define	REG_Command			0x01   	        //����Ĵ���
#define	REG_FIFO			0x02		//FIFO����
#define	REG_PrimaryStatus	        0x03		//״̬�Ĵ���1
#define	REG_FIFO_Length		0x04		//FIFO���ȼĴ���
#define	REG_SecondaryStatus         0x05		//״̬�Ĵ���2
#define REG_InterruptEn		0x06		//�ж�����Ĵ���
#define	REG_Int_Req			0x07		//�ж������ǼĴ���
#define	REG_Control			0x09		//���ƼĴ���
#define	REG_ErrorFlag		0x0A		//����״̬�Ĵ���
#define REG_CollPos			0x0B		//��ͻ���Ĵ���
#define REG_TimerValue		0x0C		//��ʱ����ǰֵ
#define REG_CRCResultLSB            0x0D
#define REG_CRCResultMSB            0x0E
#define	REG_Bit_Frame		0x0F		//λ֡�����Ĵ���
#define	REG_BitFraming		0x0F		//λ֡�����Ĵ���
#define	REG_TxControl		0x11		//���Ϳ��ƼĴ���
#define	REG_CwConductance           0x12            //
#define	REG_ModConductance          0x13            //
#define	REG_CoderControl            0x14            //�����������ѡ��Ĵ���
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
#define	REG_ChannelRedundancy	0x22		//RFͨ������ģʽ���üĴ���
#define REG_CRCPresetLSB            0x23
#define REG_CRCPresetMSB            0x24
#define REG_MFOUTSelect             0x26
#define REG_TimerClock		0x2A		//��ʱ���������üĴ���
#define REG_TimerControl	        0x2B		//��ʱ�����ƼĴ���
#define REG_TimerReload		0x2C		//��ʱ����ֵ�Ĵ���
#define REG_IRQPinConfig            0x2D
#define REG_TestAnaSelect           0x3A
#define REG_TestDigiSelect          0x3D		//���Թܽ����üĴ���

//*******************RC531����Ĵ��������� *******************
#define	CMD_Idle                    0x00
#define	CMD_Transmit                0x1A
#define	CMD_Receive                 0x16
#define	CMD_Transceive		0x1E		//���ͽ�������
#define CMD_ReadE2			0x03		//��rc531 e2����
#define CMD_WriteE2			0x01		//дrc531 e2����
#define CMD_Authent1		0x0C		//
#define CMD_Authent2		0x14
#define CMD_LoadKeyE2		0x0B
#define CMD_LoadKey			0x19
#define CMD_LoadConfig              0x07
#define CMD_CalcCRC                 0x12

//*******************ISO/IEC FDIS 14443 ��ض��� *******************
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
rc531 �򵥲���
1�� ��Դ                ʵ�ʽӽ�
2�� ��
3��---RC531_SCK  ���    3��
4��---RC531_MOSI ���    4��
5��---RC531_NSS  ���    6��
6��---RC531_MISO ����    GPE5 cpu70�� GPE5 ��ӦIO���5
7��---�ϵ����Ч  ���    5��
8�� 
*/
//�����Դ
#define RC531_POWER_ON 	Port_Set(0,1)
#define RC531_POWER_OFF Port_Set(0,0)
//����ѡ��SPI
#define SPI_SELECT 		Port_Set(1,0)
//#define SPI_UNSELECT 		Port_Set(1,0)
#define SPI_UNSELECT	Port_Set(1,1)
//����SPIʱ��
#define SPI_CLK_L Port_Set(3,0)
#define SPI_CLK_H Port_Set(3,1)
//����MOSI
#define SPI_MOSI_L Port_Set(4,0)
#define SPI_MOSI_H Port_Set(4,1)
//����MISO 
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
