/*===============================================================================
���Ⳮ����Գ���
��д: Cynthia
	
===============================================================================*/
#include <hspos.h>


#define uchar unsigned char

//#define YANSHI 280000  /* ���ڴ����ʱ */
#define RBAK ((int *)0x207FE00)//2050000)  /* ���ڴ������ʾ�ļ�¼�� */
#define DELAY_TIME 8500
#define DELAY_TIME2 1000
#define DELAY_TIME3 200

//MRDATA.DBF
#define DBH       0//����
#define ZDL    1//�й��ܵ���
#define MCCS     2//���峣��
#define KHMC     3//�ͻ�����
#define ADDR     4//��ַ
#define CBDATE     5//��������
#define CBTIME    6//����ʱ��

uchar addr[13],addr1[13],Baddr[10];//���ַ
uchar yssj[99],fxsj[99];//�������ݴ��
uchar com_tsbz=0;//����ͨѶ��־��com_tsbz=0��ʾ�ú�������ͨѶ,com_tsbz=1��ʾ�ô��ڸ����ͨѶ
int ydsx1,sxh_zdl;
int total;//����ܼ�¼��
int yanshi;
uchar YANSHI[5];


int fy(char k,int r);
void hwcb();
int cb(int r);
int cb2(int r);
int cb_1(int r);
int cb_2(int r);
int print(int r);
void read_addr(uchar *resu,int r);
void read_addr1(uchar *resu,int r);
void read_addr2(uchar *resu,int r);
void read_addr3(uchar *resu,int r);
void read_data(uchar *pbsbm,uchar *resu,unsigned int pxh,long int sxh);
void read_data1(uchar *pbsbm,uchar *resu,unsigned int pxh,long int sxh);
void read_data2(uchar *pbsbm,uchar *resu,int r);
void rece(uchar *pbsbm,uchar *cmd,uchar *resu,int psxh);
void rece1(uchar *pbsbm,uchar *cmd,uchar *resu,int psxh);
void rece2(uchar *pbsbm,uchar *cmd,uchar *resu,int psxh);
void rece3(uchar *pbsbm,uchar *cmd,uchar *resu,int psxh);
void rece4(uchar *pbsbm,uchar *cmd,uchar *resu,int psxh);
void disperr(uchar err,uchar *pbsbm,int psxh);
void disperr1(uchar err,uchar *pbsbm,int psxh);
void getdate1(uchar *pdate);
void gettime1(uchar *ptime);
void ito10_2(int achar,uchar *pls);
void ito16(uchar *achar,uchar *pls,unsigned int wz);
void ito16_2(int achar,uchar *pls);
void ito16_4(int achar,uchar *pls);
void send_data(uchar *pbsbm);
void send_data1(uchar *pbsbm);
void send_data_ir(uchar *pbsbm);
void send_data_ir1(uchar *pbsbm);
void crtime(void);
void crtime1(void);
void del0(uchar *dd,unsigned int x);
//void save_sjc(uchar *ptime , uchar *mtime , int i);
void fycb(int r);
int toBCD(char *pSrc,char *pDest,int destLen);
void dleay1(void);
void setrtime(void);
void keyss(unsigned int x,unsigned int y,unsigned int ws,unsigned char *mkey,unsigned int s);
unsigned char ksh(uchar *cdata,  uchar n1,  uchar n2,  uchar reg);

int cbtype = 1;
/*=================================================================================
����:	������
����:
����:
=================================================================================*/
int main(void)
{
	int r,rt;
	uchar k;
	
	screen(1);       		/* �趨Ϊ������ʾ״̬ */
	       rt=libuse("MRDATA.dbf",0);
      if(rt!=0)
      {
      	putstr("�����ݿ����");	
      	bell(50);
      	key(0);
      }
      libopen(0);       	/* �򿪵�һ���ݿ� */
      total=libsumr();   	/* �����һ���ݿ���ܼ�¼�� */
      //if(RBAK[0]>=total||RBAK[0]<0)     /* �Ը���װ�����ݿ�,RBAK�е�ֵ(��¼��)���ܻᳬ���䷶Χ,������,����Ϊ0(����һ��¼) */ 
      //   {RBAK[0]=0;libapp();}
	if (total == 0) libapp();
	RBAK[0]=0;
	while(1)
	{     
	     cls();moveto(15,14);  putstr("   ");
	     moveto(1, 3);        putstr("������Գ���");
	     moveto(3, 1);     putstr("====================");
		 
	     moveto(6, 2);     putstr("����Լ: ");
	     moveto(8, 2);     putstr("[1] DLT645-1997");
	     moveto(10, 2);   putstr("[2] DLT645-2007");
	     
	     moveto(16, 2);   putstr("[F2] �˳�");
		do { k=key(0); }while(k!=0x31&&k!=0x32&&k!=0x89); // �ж�����ļ�ֵ,������Ĳ���'1','2','3','4'��'F2'������ȴ�����
            switch(k) 
		{
			case '1':cbtype=1;break;
			case '2':cbtype=2;break;
			case 0x89:return;
		}
	
		while(1)
		{     
		     cls();moveto(15,14);  putstr("   ");
		     moveto(1, 3);        putstr("������Գ���");
		     moveto(3, 1);     putstr("====================");

		      moveto(6, 2);     putstr("[1] ���ý�����ʱ");
		     moveto(8, 2);     putstr("[2] Уʱ");
		     moveto(10, 2);     putstr("[3] ����");
		     
		     moveto(16, 2);   putstr("[F2] �˳�");
			do { k=key(0); }while(k!=0x31&&k!=0x32&&k!=0x33&&k!=0x89); // �ж�����ļ�ֵ,������Ĳ���'1','2','3','4'��'F2'������ȴ�����
	            switch(k) 
			{
				case '1':setrtime();break;
				case '2':if (cbtype == 1) crtime();else crtime1();break;
				case '3':hwcb();break;
			}
			if (k == 0x89) break;
		}
	}
}


// ����: �������ϼ�,��¼�ż�1,�������¼�,��¼�ż�1 
// ���: kΪ������ֵ,rΪ��ǰ��¼�� 
// ����: ���ش����ļ�¼�� 
int fy(char k,int r)
{
	int f;
	uchar l,kdata[50];
	
	
	if(k==0x8e)
	{
		if(r==0)
		{
			cls();
			moveto(15,14);
			putstr("   ");
			moveto(5,3);
			putstr_h("�ѵ��׼�¼!");
			bell(5);
			for(f = 0;f < 25;f++)
			delay(DELAY_TIME);
		} 
		else {r-=1;}
	}
	else if(k==0x8f)
	{
    if(r==total-1)
		{
			cls();
			moveto(15,14);
			putstr("   ");
			moveto(5,3);
			putstr_h("�ѵ�ĩ��¼!");
			bell(5);
			for(f = 0;f < 25;f++)
			delay(DELAY_TIME);
		}
		else	{r+=1;}
	}
	return(r);
}




//����:���Ⳮ�๦�ܱ�
//���:���ݿ����
//����:��

void hwcb()
{
	uchar k,f,kdata[30];
	int r;
  r=RBAK[0];
	
	do
        {    cls();moveto(15,14);putstr("   "); 
	      moveto(1, 6);        putstr("�����ȡ");
	      moveto(3, 1); putstr("====================");

             moveto(5, 1); putstr("����:");  
             moveto(7,1); libset(r,DBH);libread(kdata);putn_h(18,kdata);
	      moveto(9,1); putstr("�ܵ���:");libset(r,ZDL);libread(kdata);putn_h(12,kdata);
	      //moveto(9, 1); putstr("���峣��:");moveto(9,10);libset(r,MCCS);libread(kdata);putn_h(10,kdata);
	      moveto(11,1);   putstr("[1]:�㲥����");
	      moveto(13,1);   putstr("[2]:�ֶ�����");
	      moveto(15,1);   putstr("[F1]:��ӡ");
	      moveto(17,1);   putstr("[���]:�������");
	      moveto(19,1);   putstr("[F2]:�˳�");
	      if((total=libsumr())==0)
	      {moveto(5,8); putstr("          ");
	       moveto(7,8);putstr("          ");  
	       moveto(9,10);putstr("          ");libapp();}
	      do { k=key(0); }while(k!=0x8e&&k!=0x8f&&k!=0x88&&k!=0x31&&k!=0x89&&k!=0x82&&k!=0x32);
	      switch(k)// ��������İ���������Ӧ�ĺ���
	      {
				case 0x8e:r=fy(k,r);break; 
				case 0x8f:if(total==0){cls();moveto(15,14);putstr("   ");moveto(5,3);putstr_h("�ѵ�ĩ��¼!");bell(5);for(f = 0;f < 25;f++)delay(DELAY_TIME);r=0;} else r=fy(k,r);break;
				case 0x88:print(r);break;
				case 0x31:if (cbtype == 1) cb(r);else cb2(r);break;
				case 0x82:libset(r,DBH);libwrite("            ");libset(r,ZDL);libwrite("          ");libset(r,MCCS);libwrite("          ");break;
				case 0x89:return;
				case 0x32:if (cbtype == 1) cb_1(r);else cb_2(r);break;
	      }
	    }while(1);
	
}

/*=================================================================================
����:	����
����:	
����:
=================================================================================*/
int cb(int r)//2008-04-18
{
	long int j,sxh,z,cbycm,a,b,c,i=0;
	uchar l,k,pbsbm[20],ls[20],kdata2[50],kdata[50],cdata[50],kdata1[50],str[50];
	//int a,b,lx;
       //r=RBAK[0];
  
	//for(i=0;i<50;i++)
	//{kdata[i]=0;ls[i]=0;}
	
	//memset(cdata, 0, 9);
	memset(Baddr, 0x99,sizeof(Baddr));//cls();moveto(15,14);putn_h(10,Baddr);key(0);
	cls();moveto(15,14);putstr("   ");moveto(3,2);putstr("���ڶ�ȡ���ţ����Ժ�...");
	read_addr(ls,r);
	if(ls[0]=='0')	{goto exit;}
	    i++;
		//�����ַ
	//libset(sxh,DBH);libread(kdata);
	//for(i=0;i<8;i++)
		//cdata[i]=kdata[i+2];
	//toBCD(cdata,Baddr,6);
	//��ַ�볤�Ȳ���6 �ֽ�ʱ����ʮ������AAH ����6 �ֽ�
	//for(i=strlen(Baddr);i<6;i++)
		//Baddr[i] = 0xAA;
exit1:	cls();moveto(15,14);putstr("   ");moveto(3,2);putstr("���ڶ�ȡ�й��ܵ��������Ժ�...");	
		//9010�й��ܵ���
		j=0x9010;
              ito16_4(j,pbsbm);
		read_data(pbsbm,ls,1,r);
		if(ls[0]=='0'&&ls[1]==0)	{goto exit;}
		    i++;
		del0(fxsj,14);
		libset(r,ZDL);libwrite(fxsj);
/*		
exi:         cls();moveto(15,14);putstr("   ");moveto(3,2);putstr("���ڶ�ȡ���峣�������Ժ�...");
		//C030���峣��
		j=0xC030;
    ito16_4(j,pbsbm);
		read_data(pbsbm,ls,1,r);
		if(ls[0]=='0'&&ls[1]==0)	{goto exit;}
		    i++;
		del0(fxsj,14);
		libset(r,MCCS);libwrite(fxsj);
*/		
exit:if(i!=0)libapp();
}

/*=================================================================================
����:	����
����:	
����:
=================================================================================*/
int cb_1(int r)//2008-04-18
{
	long int j,sxh,z,cbycm,j1,j2,j3,j4,i=0;
	uchar l,k,f,pbsbm[20],ls[20],kdata2[50],kdata[50],cdata[50],kdata1[50],str[50];
	
	memset(Baddr,0xAA,sizeof(Baddr));
	memset(ls,0,sizeof(ls));
hwcb_1:
    	cls();
	moveto(2,1);putstr("������ַ +����A:");
	moveto(6,3);putstr("__________");
	moveto(19,1);putstr("[F2] �˳�");
	memset(cdata,0,sizeof(cdata));
	moveto(4,3); f=ksh(cdata,0,12,1);   // �ȴ�������
	if(f==0)
	{   // �����벻����ֵ��ȷ�ϼ�
		if(cdata[1]==0) goto hwcb_1;// ����������ֵ���������ܼ�
		else
		{ // ����������һ������Ϊ���ܼ�,�ж�����'��','��','F2','ȷ��'�ͷ���
				if(cdata[1]!=0x89)   goto hwcb_1;
				if(cdata[1]==0x89){return;}
		}
	}
	//for(i=0;i<l;i++)
	//{if(kdata[i]==' ')break;}
	//if(i<l)length=i;
	//else length=l;
	j3=f/2; 
	//j4=length%2;
	//if(j4==0);
	//else j3+=1;
	
	if(j3>4)j3=4;
	//moveto(3,1);printf("%d",length);   
	for(i=0;i<j3;i++)
	{
	    kdata1[0]=cdata[f-i*2-2];kdata1[1]=0;
	    if(kdata1[0]=='A'){kdata1[0]='1',kdata1[1]='0';kdata1[2]=0;}
	    if(kdata1[0]=='B'){kdata1[0]='1',kdata1[1]='1';kdata1[2]=0;}
	    if(kdata1[0]=='C'){kdata1[0]='1',kdata1[1]='2';kdata1[2]=0;}
	    if(kdata1[0]=='D'){kdata1[0]='1',kdata1[1]='3';kdata1[2]=0;}
	    if(kdata1[0]=='E'){kdata1[0]='1',kdata1[1]='4';kdata1[2]=0;}
	    if(kdata1[0]=='F'){kdata1[0]='1',kdata1[1]='5';kdata1[2]=0;}
	    //moveto(5,1);putstr(kdata1);putchhex(kdata1[0]);
	    j1=stoi(2,kdata1);
	    //moveto(7,1);printf("%d",j1);
	    j1=j1*16;
	    //moveto(9,1);printf("%d",j1);
	    
	    kdata1[0]=cdata[f-i*2-1];kdata1[1]=0;
	     if(kdata1[0]=='A'){kdata1[0]='1',kdata1[1]='0';kdata1[2]=0;}
	    if(kdata1[0]=='B'){kdata1[0]='1',kdata1[1]='1';kdata1[2]=0;}
	    if(kdata1[0]=='C'){kdata1[0]='1',kdata1[1]='2';kdata1[2]=0;}
	    if(kdata1[0]=='D'){kdata1[0]='1',kdata1[1]='3';kdata1[2]=0;}
	    if(kdata1[0]=='E'){kdata1[0]='1',kdata1[1]='4';kdata1[2]=0;}
	    if(kdata1[0]=='F'){kdata1[0]='1',kdata1[1]='5';kdata1[2]=0;}
	    j2=stoi(2,kdata1);
	    j1=j1+j2;
	    //moveto(11,1);printf("%d",j1);
	    
	    Baddr[i]=j1;
	    //moveto(13,1);putchhex(Baddr[i]);key(0);
	}
	
	cls();moveto(15,14);putstr("   ");moveto(3,2);putstr("���ڶ�ȡ���ţ����Ժ�...");
	read_addr(ls,r);
	if(ls[0]=='0')	{goto exit;}
	    i++;
		//�����ַ
	//libset(sxh,DBH);libread(kdata);
	//for(i=0;i<8;i++)
		//cdata[i]=kdata[i+2];
	//toBCD(cdata,Baddr,6);
	//��ַ�볤�Ȳ���6 �ֽ�ʱ����ʮ������AAH ����6 �ֽ�
	//for(i=strlen(Baddr);i<6;i++)
		//Baddr[i] = 0xAA;
exit1:	cls();moveto(15,14);putstr("   ");moveto(3,2);putstr("���ڶ�ȡ�й��ܵ��������Ժ�...");	
		//9010�й��ܵ���
		j=0x9010;
              ito16_4(j,pbsbm);
		read_data(pbsbm,ls,1,r);
		if(ls[0]=='0'&&ls[1]==0)	{goto exit;}
		    i++;
		del0(fxsj,14);
		libset(r,ZDL);libwrite(fxsj);
/*		
exi:         cls();moveto(15,14);putstr("   ");moveto(3,2);putstr("���ڶ�ȡ���峣�������Ժ�...");
		//C030���峣��
		j=0xC030;
    ito16_4(j,pbsbm);
		read_data(pbsbm,ls,1,r);
		if(ls[0]=='0'&&ls[1]==0)	{goto exit;}
		    i++;
		del0(fxsj,14);
		libset(r,MCCS);libwrite(fxsj);
*/		
exit:if(i!=0)libapp();
}

/*=================================================================================
����:	����
����:	
����:
=================================================================================*/
int cb_2(int r)
{
	long int j,sxh,z,cbycm,j1,j2,j3,j4,i=0;
	uchar l,k,f,pbsbm[20],ls[20],kdata2[50],kdata[50],cdata[50],kdata1[50],str[50];
	
	memset(Baddr,0xAA,sizeof(Baddr));
	memset(ls,0,sizeof(ls));
hwcb_1:
    	cls();
	moveto(2,1);putstr("��������ı��ַ:");
	moveto(6,3);putstr("__________");
	moveto(19,1);putstr("[F2] �˳�");
	memset(cdata,0,sizeof(cdata));
	moveto(4,3); f=ksh(cdata,0,12,0);   // �ȴ����뱾�µ׶�
	if(f==0)// ������Ϊ��
	{   
		if(cdata[1]==0) goto hwcb_1;// ����������ֵ���������ܼ�
		else
		{ // ����������һ������Ϊ���ܼ�,�ж�����'��','��','F2','ȷ��'�ͷ���
				if(cdata[1]!=0x89)   goto hwcb_1;
				if(cdata[1]==0x89){return;}
		}
	}
	
	j3=f/2; 
	
	if(j3>4)j3=4;
	//moveto(3,1);printf("%d",length);   
	for(i=0;i<j3;i++)
	{
	    kdata1[0]=cdata[f-i*2-2];kdata1[1]=0;
	    if(kdata1[0]=='A'){kdata1[0]='1',kdata1[1]='0';kdata1[2]=0;}
	    if(kdata1[0]=='B'){kdata1[0]='1',kdata1[1]='1';kdata1[2]=0;}
	    if(kdata1[0]=='C'){kdata1[0]='1',kdata1[1]='2';kdata1[2]=0;}
	    if(kdata1[0]=='D'){kdata1[0]='1',kdata1[1]='3';kdata1[2]=0;}
	    if(kdata1[0]=='E'){kdata1[0]='1',kdata1[1]='4';kdata1[2]=0;}
	    if(kdata1[0]=='F'){kdata1[0]='1',kdata1[1]='5';kdata1[2]=0;}
	    //moveto(5,1);putstr(kdata1);putchhex(kdata1[0]);
	    j1=stoi(2,kdata1);
	    //moveto(7,1);printf("%d",j1);
	    j1=j1*16;
	    //moveto(9,1);printf("%d",j1);
	    
	    kdata1[0]=cdata[f-i*2-1];kdata1[1]=0;
	     if(kdata1[0]=='A'){kdata1[0]='1',kdata1[1]='0';kdata1[2]=0;}
	    if(kdata1[0]=='B'){kdata1[0]='1',kdata1[1]='1';kdata1[2]=0;}
	    if(kdata1[0]=='C'){kdata1[0]='1',kdata1[1]='2';kdata1[2]=0;}
	    if(kdata1[0]=='D'){kdata1[0]='1',kdata1[1]='3';kdata1[2]=0;}
	    if(kdata1[0]=='E'){kdata1[0]='1',kdata1[1]='4';kdata1[2]=0;}
	    if(kdata1[0]=='F'){kdata1[0]='1',kdata1[1]='5';kdata1[2]=0;}
	    j2=stoi(2,kdata1);
	    j1=j1+j2;
	    //moveto(11,1);printf("%d",j1);
	    
	    Baddr[i]=j1;
	    //moveto(13,1);putchhex(Baddr[i]);key(0);
	}
	
	//cls();moveto(15,14);putstr("   ");moveto(3,2);putstr("���ڶ�ȡ���ţ����Ժ�...");
	//read_addr3(ls,r);
	//if(ls[0]=='0')	{goto exit;}
	//delay(3000);
       
	for (i=5,j=0; i>=0; i--,j+=2)
	{	
		j1 = Baddr[i];
		ito16_2(j1,ls);
		addr[j]=ls[0];
		addr[j+1]=ls[1];
		addr[j+2]=0;
      
		if(ls[1]==0){addr[j]='0';addr[j+1]=ls[0];addr[j+2]=0;}
	}
	addr[13]=0;//���������ݴ���ȫ�ֱ���
	
	for(i=0;i<12;i++)
	{addr1[i]=addr[12-i];}
 
       libset(r,DBH);libwrite(addr);
		   
	//0x00010000
	pbsbm[0] = 0x00;
	pbsbm[1] = 0x00;
	pbsbm[2] = 0x01;
	pbsbm[3] = 0x00;
	pbsbm[4] = 0;
	cls();moveto(15,14);putstr("   ");moveto(3,2);putstr("���ڶ�ȡ�й��ܵ��������Ժ�...");
	read_data2(pbsbm,ls,r);

	exit:;
}

/*=================================================================================
����:	����
����:	
����:
=================================================================================*/
int cb2(int r)//2008-04-18
{
	long int j,sxh,z,cbycm,a,b,c,i=0;
	uchar l,k,pbsbm[20],ls[20],kdata2[50],kdata[50],cdata[50],kdata1[50],str[50];
	//int a,b,lx;
       //r=RBAK[0];
  
	//for(i=0;i<50;i++)
	//{kdata[i]=0;ls[i]=0;}
	
	//memset(cdata, 0, 9);
	memset(Baddr, 0xAA,sizeof(Baddr));//cls();moveto(15,14);putn_h(10,Baddr);key(0);
	cls();moveto(15,14);putstr("   ");moveto(3,2);putstr("���ڶ�ȡ���ţ����Ժ�...");
	read_addr2(ls,r);
	if(ls[0]=='0')	{goto exit;}

	delayms(2000);
	   
	//0x00010000
	pbsbm[0] = 0x00;
	pbsbm[1] = 0x00;
	pbsbm[2] = 0x01;
	pbsbm[3] = 0x00;
	pbsbm[4] = 0;
	cls();moveto(15,14);putstr("   ");moveto(3,2);putstr("���ڶ�ȡ�й��ܵ��������Ժ�...");
	read_data2(pbsbm,ls,r);
	   // i++;
		//�����ַ
	//libset(sxh,DBH);libread(kdata);
	//for(i=0;i<8;i++)
		//cdata[i]=kdata[i+2];
	//toBCD(cdata,Baddr,6);
	//��ַ�볤�Ȳ���6 �ֽ�ʱ����ʮ������AAH ����6 �ֽ�
	//for(i=strlen(Baddr);i<6;i++)
		//Baddr[i] = 0xAA;
/*		
exi:         cls();moveto(15,14);putstr("   ");moveto(3,2);putstr("���ڶ�ȡ���峣�������Ժ�...");
		//C030���峣��
		j=0xC030;
    ito16_4(j,pbsbm);
		read_data(pbsbm,ls,1,r);
		if(ls[0]=='0'&&ls[1]==0)	{goto exit;}
		    i++;
		del0(fxsj,14);
		libset(r,MCCS);libwrite(fxsj);
*/		
exit:;
}

/*================================================================================
��������ӡ����
������
���أ�
================================================================================*/
int print(int r)
{
	uchar rt,k;
	uchar data[50];
	
	cls();moveto(15,14);putstr("   ");
	moveto(5,1);putstr("�Ƿ�ȷ�ϴ�ӡ?");
	moveto(8,6);putstr("��ȷ����:��");
	moveto(10,6);putstr("�������:��");
	
	do{k=key(0);}while(k!=0x82&&k!=0x8d);
	if(k==0x82) return;
	
	
	rt=Printer_Open();
	
	if (rt!=0) 
	{
		Printer_Close();
		cls(); putstr("��ʼ������"); printf(" %x",rt);
		return;
	}
		Printer_SpaceSet(2,50);  
		Printer_ClrBuf();  
		Printer_Str(" �����ȡ");Printer_Str("\n");
		Printer_Str("====================");Printer_Str("\n");
		Printer_Str("���ţ�");libset(r,DBH);libread(data);Printer_Str(data);Printer_Str("\n");
		Printer_Str("�й��ܵ���:");libset(r,ZDL);libread(data);Printer_Str(data);Printer_Str("\n");
		Printer_Str("���峣��:");libset(r,MCCS);libread(data);Printer_Str(data);Printer_Str("\n");
		
	   if(Printer_Buffer(400)!=0)
		{
			Printer_Close();  cls();   putstr("��ӡ����!");    key(0);return;
		} 
		Printer_ClrBuf();
		
		Printer_Close();
}

/*=================================================================================
����:	��ȡ���ַ
����:	resuΪ����ͨѶ�Ƿ�ɹ���־
����:	��ȡ��ַ����addr[]
=================================================================================*/	
void read_addr(uchar *resu,int r)
{
	uchar  k,k1,i,ls[10],ls2[2],xh,l;
	uchar  cmd[99],pbsbm[4],ls0[2],ls1[2],i0,i1;
	long int j,j1,cs;
  	if (com_tsbz==0)	{ir_init(B1200,0x2B,UART_ON);}
  	else {cominit(B1200,0x2B,UART_ON);}
stat:	
	j=0xC032;
	ito16_4(j,pbsbm);
	
	//Baddr[0]
	
	rece(pbsbm,cmd,ls,1);
	if((ls[0]=='0')||(ls[0]=='2')){resu[0]=ls[0];resu[1]=ls[1];goto exi;}
	resu[0]='9';resu[1]=0;

	i=17;j=0;
	while(i>=12)
	{	if(cmd[i]>=51){j1=cmd[i]-51;}else{j1=cmd[i]+205;}
		ito16_2(j1,ls);
		addr[j]=ls[0];
		addr[j+1]=ls[1];
		addr[j+2]=0;
      
		if(ls[1]==0){addr[j]='0';addr[j+1]=ls[0];addr[j+2]=0;}
		i--;j=j+2;
	}
	addr[13]=0;//���������ݴ���ȫ�ֱ���
	
	for(i=0;i<12;i++)
	{addr1[i]=addr[12-i];}
 
       libset(r,DBH);libwrite(addr);

	exi:i++;
}

/*=================================================================================
����:	��ȡ���ַ
����:	resuΪ����ͨѶ�Ƿ�ɹ���־
����:	��ȡ��ַ����addr[]
=================================================================================*/	
void read_addr1(uchar *resu,int r)
{
	uchar  k,k1,i,rt,err,ls[10],ls2[2],xh;
	uchar  cmd[99],pbsbm[8],ls0[2],ls1[2],i0,i1;
	long int byanshi,l,j,j1,cs;
  	if (com_tsbz==0)	{ir_init(B1200,0x2B,UART_ON);}
  	else {cominit(B1200,0x2B,UART_ON);}
	
stat:   
	memset(cmd,0,sizeof(cmd));
	xh=0;
	i=0;
	rt=0;
	byanshi=1;
	l=50;

	// �����
	send_data_ir(pbsbm);
	//cls();
        while(xh==0)
	{
		if (com_tsbz==0)
		{  
		    if(ir_rxstate()!=0)                                                                                                                        
		   {   
		       cmd[i]=ir_rxbuf();
			//putchhex(cmd[i]);
		   	if(rt<2)
		   	{
		   		if((cmd[i]==0xfe)&&(rt==0))
		   		{rt=1;}
		   		if((cmd[i]==0x68)&&(rt==1))
		   		{rt=2;
		   		i=0;
		   		cmd[i]=0x68;
		   		byanshi=0;
		   		}
		   		if(rt!=0&&i>=15+l)  {xh=1;} //15
		   		 
		   	}
		   	else
		   	{
           			if(i==9){l=cmd[9];if(l>70){l=0;}}
		   		if(i==11+l)//11
		   		{xh=1;}
		   	}
		   	i++; 
		   }else
		   {	byanshi++;
		   	if(byanshi>35000)
		   	{xh=1;}
		   }
		}
		else
		{
		    if(comstate()!=0)                                                                                                                        
		  {   
		        cmd[i]=combuf();
		   	if(rt<2)
		   	{
		   		if((cmd[i]==0xfe)&&(rt==0))
		   		{rt=1;}
		   		if((cmd[i]==0x68)&&(rt==1))
		   		{rt=2;
		   		i=0;
		   		cmd[i]=0x68;
		   		byanshi=0;
		   		}
		   		if(rt!=0&&i>=15+l)  {xh=1;} //15
		   		
		   	}
		   	else
		   	{
           			if(i==9){l=cmd[9];if(l>70){l=0;}}
		   		if(i==11+l)//11
		   		{xh=1;}
		   	}
		   	i++;
		   }else
		   {	byanshi++;
		   	if(byanshi>35000)
		   	{xh=1;}
		   }
		}
	}

	cs=0;
	l=cmd[9];
	if(l>70){l=0;}
	for(j=0;j<=9+l;j++)
	{	cs=cs+cmd[j];
	}
	while(cs>256)
	{cs=cs-256;}
       
	if((cmd[10+l]==cs)&&(cmd[8]==0x93))
	{
		for (i=0;i<6;i++)
			Baddr[i] = cmd[i+1];
		for (i=6,j=0; i>0; i--,j+=2)
		{	
			//if(cmd[i]>=51){j1=cmd[i]-51;}else{j1=cmd[i]+205;}
			j1 = cmd[i];
			ito16_2(j1,ls);
			addr[j]=ls[0];
			addr[j+1]=ls[1];
			addr[j+2]=0;
	      
			if(ls[1]==0){addr[j]='0';addr[j+1]=ls[0];addr[j+2]=0;}
		}
		addr[13]=0;//���������ݴ���ȫ�ֱ���
		
		for(i=0;i<12;i++)
		{addr1[i]=addr[12-i];}
		
		resu[0]='9';resu[1]=0;
	}
}

/*=================================================================================
����:	��ȡ���ַ
����:	resuΪ����ͨѶ�Ƿ�ɹ���־
����:	��ȡ��ַ����addr[]
=================================================================================*/	
void read_addr2(uchar *resu,int r)
{
	uchar  k,k1,i,ls[10],ls2[2],xh,l;
	uchar  cmd[99],pbsbm[8],ls0[2],ls1[2],i0,i1;
	long int j,j1,cs;
  	if (com_tsbz==0)	{ir_init(B1200,0x2B,UART_ON);}
  	else {cominit(B1200,0x2B,UART_ON);}
stat:	
	//j=0xC032;
	//ito16_4(j,pbsbm);
	
	//Baddr[0]
	
	rece2(pbsbm,cmd,ls,r);
	if((ls[0]=='0')||(ls[0]=='2')){resu[0]=ls[0];resu[1]=ls[1];goto exi;}
	resu[0]='9';resu[1]=0;

	for (i=0;i<6;i++)
		Baddr[i] = cmd[i+1];
	for (i=6,j=0; i>0; i--,j+=2)
	{	
		//if(cmd[i]>=51){j1=cmd[i]-51;}else{j1=cmd[i]+205;}
		j1 = cmd[i];
		ito16_2(j1,ls);
		addr[j]=ls[0];
		addr[j+1]=ls[1];
		addr[j+2]=0;
      
		if(ls[1]==0){addr[j]='0';addr[j+1]=ls[0];addr[j+2]=0;}
	}
	addr[13]=0;//���������ݴ���ȫ�ֱ���
	
	for(i=0;i<12;i++)
	{addr1[i]=addr[12-i];}
 
       libset(r,DBH);libwrite(addr);
	exi:;
}

/*=================================================================================
����:	��ȡ���ַ
����:	resuΪ����ͨѶ�Ƿ�ɹ���־
����:	��ȡ��ַ����addr[]
=================================================================================*/	
void read_addr3(uchar *resu,int r)
{
	uchar  k,k1,i,ls[10],ls2[2],xh,l;
	uchar  cmd[99],pbsbm[8],ls0[2],ls1[2],i0,i1;
	long int j,j1,cs;
  	if (com_tsbz==0)	{ir_init(B1200,0x2B,UART_ON);}
  	else {cominit(B1200,0x2B,UART_ON);}
stat:	
	//j=0xC032;
	//ito16_4(j,pbsbm);
	//0x04000401
	pbsbm[0] = 0x01;
	pbsbm[1] = 0x04;
	pbsbm[2] = 0x00;
	pbsbm[3] = 0x04;
	pbsbm[4] = 0;
	
	//Baddr[0]
	
	rece4(pbsbm,cmd,ls,r);
	if((ls[0]=='0')||(ls[0]=='2')){resu[0]=ls[0];resu[1]=ls[1];goto exi;}
	resu[0]='9';resu[1]=0;
	
	for (i=0;i<6;i++)
		Baddr[i] = cmd[i+1];
	for (i=6,j=0; i>0; i--,j+=2)
	{	
		//if(cmd[i]>=51){j1=cmd[i]-51;}else{j1=cmd[i]+205;}
		j1 = cmd[i];
		ito16_2(j1,ls);
		addr[j]=ls[0];
		addr[j+1]=ls[1];
		addr[j+2]=0;
      
		if(ls[1]==0){addr[j]='0';addr[j+1]=ls[0];addr[j+2]=0;}
	}
	addr[13]=0;//���������ݴ���ȫ�ֱ���
	
	for(i=0;i<12;i++)
	{addr1[i]=addr[12-i];}
 
       libset(r,DBH);libwrite(addr);
	exi:i++;
}

void read_data2(uchar *pbsbm,uchar *resu,int r)
{
	uchar  k,k1,i,ls[10],ls2[2],xh,l;
	uchar  cmd[99],ls0[2],ls1[2],i0,i1;
	long int j,j1,cs;
  	if (com_tsbz==0)	{ir_init(B1200,0x2B,UART_ON);}//
  	else {cominit(B1200,0x2B,UART_ON);}
stat:	
	//j=0xC032;
	//ito16_4(j,pbsbm);
	
	//Baddr[0]
	
	rece3(pbsbm,cmd,ls,r);
	if((ls[0]=='0')||(ls[0]=='2')){resu[0]=ls[0];resu[1]=ls[1];goto exi;}
	resu[0]='9';resu[1]=0;
	
	for (i=17,j=0; i>=14; i--,j+=2)
	{	
      		if (i == 14) {fxsj[j++]='.';}
		if (cmd[i]>=51)
			{j1=cmd[i]-51;}
		else
			{j1=cmd[i]+205;}
		ito16_2(j1,ls);
		fxsj[j]=ls[0];
		fxsj[j+1]=ls[1];
		fxsj[j+2]=0;
		if(ls[1]==0)
			{fxsj[j]='0';fxsj[j+1]=ls[0];fxsj[j+2]=0;}
	}
	fxsj[9]=0;//���������ݴ���ȫ�ֱ���
	libset(r,ZDL);libwrite(fxsj);
	exi:;
}

/*=================================================================================
����:	��ȡ����
����:*pbsbmΪ���������ݱ�ʶ(ͨ�Ź�Լ),*resuΪ����ͨѶ�Ƿ�ɹ���־,pxhΪ���ݳ��ȿ���
����:	���ݴ���fxsj[]
=================================================================================*/
void read_data(uchar *pbsbm,uchar *resu,unsigned int pxh,long int sxh)
{
	unsigned char  rbuf[10],k,k1,i,ls[10],ls2[2],xh,l,kdata[50];
	unsigned char  cmd[99];
	long int cs,j,j1;
	int a,b;
	float f;
stat:
	rece(pbsbm,cmd,ls,1);
	if(ls[0]=='0'){resu[0]=ls[0];resu[1]=ls[1];goto exi;}
	if(ls[0]=='2'){resu[0]=ls[0];resu[1]=ls[1];goto exi;}
	resu[0]='9';resu[1]=0;

	if(pxh==1||pxh==7||pxh==8)
	{
		i=12+cmd[9]-3;
		j=0;
		while(i>=12)
		{	
			if(cmd[i]>=51){j1=cmd[i]-51;}else{j1=cmd[i]+205;}
			
			ito16_2(j1,ls);
			//itos(j1,ls);
			fxsj[j]=ls[0];
			fxsj[j+1]=ls[1];
			fxsj[j+2]=0;
			
			if(ls[1]==0){fxsj[j]='0';fxsj[j+1]=ls[0];fxsj[j+2]=0;}
			i--;
			
			if(pxh==1&&i==12){fxsj[j+2]='.';fxsj[j+3]='.';j++;}
			else if(pxh==7&&i==13){fxsj[j+2]='.';fxsj[j+3]='.';j++;}
			else if(pxh==8&&i==13){fxsj[j+2]='.';fxsj[j+3]='.';j++;}
			j=j+2;
		}
		for(i=j;i<=18;i++)  {fxsj[i]=0;}
	}
	else if(pxh==2||pxh==3||pxh==5||pxh==9)
	{
		i=12+cmd[9]-3;
		j=0;
		while(i>=12)
		{	
			if(cmd[i]>=51){j1=cmd[i]-51;}else{j1=cmd[i]+0x100-51;} 
			ito16_2(j1,ls);
			fxsj[j]=ls[0];
			fxsj[j+1]=ls[1]																									;
			fxsj[j+2]=0;
			if(ls[1]==0)   { fxsj[j]='0'; fxsj[j+1]=ls[0]; fxsj[j+2]=0;     }
			i--;j=j+2;
		}
		for(i=j;i<=10;i++)  {fxsj[i]=0;}
	}
	else if(pxh==4||pxh==6)
	{
		j=0;
		i=12+cmd[9]-3;
		while(i>=12)
		{	
			if(cmd[i]>=51){j1=cmd[i]-51;}else{j1=cmd[i]+0x100-51;}
			ito16_2(j1,ls);
			//itos(j1,ls);
			fxsj[j]=ls[0];
			fxsj[j+1]=ls[1];
			fxsj[j+2]=0;
			if(ls[1]==0)   { fxsj[j]='0'; fxsj[j+1]=ls[0]; fxsj[j+2]=0;     }
			i--;j=j+2;
		}
		for(i=j;i<=10;i++)  {fxsj[i]=0;}
	}
exi:	;
}

/*=================================================================================
����:	��ȡ����
����:*pbsbmΪ���������ݱ�ʶ(ͨ�Ź�Լ),*resuΪ����ͨѶ�Ƿ�ɹ���־,pxhΪ���ݳ��ȿ���
����:	���ݴ���fxsj[]
=================================================================================*/
void read_data1(uchar *pbsbm,uchar *resu,unsigned int pxh,long int sxh)
{
	unsigned char  rbuf[10],k,k1,i,ls[10],ls2[2],xh,l,kdata[50];
	unsigned char  cmd[99];
	long int cs,j,j1;
	int a,b;
	float f;
stat:
	rece1(pbsbm,cmd,ls,1);
	if(ls[0]=='0'){resu[0]=ls[0];resu[1]=ls[1];goto exi;}
	if(ls[0]=='2'){resu[0]=ls[0];resu[1]=ls[1];goto exi;}
	resu[0]='9';resu[1]=0;

	if(pxh==1||pxh==7||pxh==8)
	{
		i=9+cmd[9];
		j=0;
		while(i>=14)
		{	
			if(cmd[i]>=51){j1=cmd[i]-51;}else{j1=cmd[i]+205;}
			
			ito16_2(j1,ls);
			//itos(j1,ls);
			fxsj[j]=ls[0];
			fxsj[j+1]=ls[1];
			fxsj[j+2]=0;
			
			if(ls[1]==0){fxsj[j]='0';fxsj[j+1]=ls[0];fxsj[j+2]=0;}
			i--;
			
			if(pxh==1&&i==12){fxsj[j+2]='.';fxsj[j+3]='.';j++;}
			else if(pxh==7&&i==13){fxsj[j+2]='.';fxsj[j+3]='.';j++;}
			else if(pxh==8&&i==13){fxsj[j+2]='.';fxsj[j+3]='.';j++;}
			j=j+2;
		}
		for(i=j;i<=18;i++)  {fxsj[i]=0;}
	}
	else if(pxh==2||pxh==3||pxh==5||pxh==9)
	{
		i=9+cmd[9];
		j=0;
		while(i>=14)
		{	
			if(cmd[i]>=51){j1=cmd[i]-51;}else{j1=cmd[i]+0x100-51;} 
			ito16_2(j1,ls);
			fxsj[j]=ls[0];
			fxsj[j+1]=ls[1]																									;
			fxsj[j+2]=0;
			if(ls[1]==0)   { fxsj[j]='0'; fxsj[j+1]=ls[0]; fxsj[j+2]=0;     }
			i--;j=j+2;
		}
		for(i=j;i<=10;i++)  {fxsj[i]=0;}
	}
	else if(pxh==4||pxh==6)
	{
		i=9+cmd[9];
		j=0;
		while(i>=14)
		{	
			if(cmd[i]>=51){j1=cmd[i]-51;}else{j1=cmd[i]+0x100-51;}
			ito16_2(j1,ls);
			//itos(j1,ls);
			fxsj[j]=ls[0];
			fxsj[j+1]=ls[1];
			fxsj[j+2]=0;
			if(ls[1]==0)   { fxsj[j]='0'; fxsj[j+1]=ls[0]; fxsj[j+2]=0;     }
			i--;j=j+2;
		}
		for(i=j;i<=10;i++)  {fxsj[i]=0;}
	}
exi:	;
}

/*=================================================================================
����:	����ͨѶ
����:	*pbsbmΪ���������ݱ�ʶ(ͨ�Ź�Լ),*cmd��Ŷ�������,*resuΪ����ͨѶ�Ƿ�ɹ���־,psxhΪ�ض����ʱ��ʾ���ڶ�ȡ����Ŀ
����:
=================================================================================*/
void rece(uchar *pbsbm,uchar *cmd,uchar *resu,int psxh)
{	
	uchar  i,j,xh,rt,err,ls[10],k;
 	long int byanshi,l,cs;
 	err=0;
stat:   
	memset(cmd,0,sizeof(cmd));
	xh=0;
	i=0;
	rt=0;
	byanshi=1;
	l=50;
	send_data(pbsbm);
        
        while(xh==0)
	{
		if (com_tsbz==0)
		{  
		    if(ir_rxstate()!=0)                                                                                                                        
		   {   
		        cmd[i]=ir_rxbuf();
		   	if(rt<2)
		   	{
		   		if((cmd[i]==0xfe)&&(rt==0))
		   		{rt=1;}
		   		if((cmd[i]==0x68)&&(rt==1))
		   		{rt=2;
		   		i=0;
		   		cmd[i]=0x68;
		   		byanshi=0;
		   		}
		   		if(rt!=0&&i>=15+l)  {xh=1;} 
		   		 
		   	}
		   	else
		   	{
           			if(i==9){l=cmd[9];if(l>70){l=0;}}
		   		if(i==11+l)
		   		{xh=1;}
		   	}
		   	i++; 
		   }else
		   {	byanshi++;
		   	if(byanshi>35000)
		   	{xh=1;}
		   }
		}
		else
		{
		    if(comstate()!=0)                                                                                                                        
		  {   
		        cmd[i]=combuf();
		   	if(rt<2)
		   	{
		   		if((cmd[i]==0xfe)&&(rt==0))
		   		{rt=1;}
		   		if((cmd[i]==0x68)&&(rt==1))
		   		{rt=2;
		   		i=0;
		   		cmd[i]=0x68;
		   		byanshi=0;
		   		}
		   		if(rt!=0&&i>=15+l)  {xh=1;} 
		   		
		   	}
		   	else
		   	{
           			if(i==9){l=cmd[9];if(l>70){l=0;}}
		   		if(i==11+l)
		   		{xh=1;}
		   	}
		   	i++;
		   }else
		   {	byanshi++;
		   	if(byanshi>35000)
		   	{xh=1;}
		   }
		}
	}
	cs=0;
	l=cmd[9];
	if(l>70){l=0;}
	for(i=0;i<=9+l;i++)
	{	cs=cs+cmd[i];
	}
	while(cs>256)
	{cs=cs-256;}
	i=cs;
       
       //cls();for(i=0;i<25;i++)putchhex(cmd[i]);key(0);
	if((cmd[10+l]==cs||cmd[10+l]==i)&&(cmd[8]==0x81)&&((cmd[10]-51==pbsbm[0])||(cmd[10]+205==pbsbm[0]))&&((cmd[11]-51==pbsbm[1])||(cmd[11]+205==pbsbm[1])))
	{ 	ls[0]='1';ls[1]=0;
		/*j=0;
		for(i=0;i<=20;i++)
		{	ito16(cmd,ls,i);
			yssj[j]=ls[0];
			yssj[j+1]=ls[1];
			yssj[j+2]=0;
			j=j+2;
		}
		//Baddr[0]=cmd[1];Baddr[1]=cmd[2];Baddr[2]=cmd[3];Baddr[3]=cmd[4];Baddr[4]=cmd[5];Baddr[5]=cmd[6];
		while(j<=99){yssj[j]=0;j++;}*/
		resu[0]='9';resu[1]=0;
	}
	
	else
	{	
	    
	    if(err<5) 
		{	
		    	disperr(err,pbsbm,psxh);err++; 
			 goto stat;
		}else
			{cl:	cls();
				putstr("\n���յ����Ϣ����");
				putchhex(pbsbm[1]);
				putchhex(pbsbm[0]);    
				putstr("\n�Ƿ�����");
				putstr("\n1.����");
				putstr("\n2.(�س�)����");
				putstr("\n3.����");
				k=key(0);
    	 
				if(k=='1')
				{resu[0]='0';resu[1]=0; }	
				else if(k=='2'||k==0x8d)
				{resu[0]='1';resu[1]=0;err=0;goto stat; }
				else if(k=='3')
				{resu[0]='2';resu[1]=0; }	
				else
				goto cl;
			}
	}
}

/*=================================================================================
����:	����ͨѶ
����:	*pbsbmΪ���������ݱ�ʶ(ͨ�Ź�Լ),*cmd��Ŷ�������,*resuΪ����ͨѶ�Ƿ�ɹ���־,psxhΪ�ض����ʱ��ʾ���ڶ�ȡ����Ŀ
����:
=================================================================================*/
void rece1(uchar *pbsbm,uchar *cmd,uchar *resu,int psxh)
{	
	uchar  i,j,xh,rt,err,ls[10],k;
 	long int byanshi,l,cs;
 	err=0;
stat:   
	memset(cmd,0,sizeof(cmd));
	xh=0;
	i=0;
	rt=0;
	byanshi=1;
	l=50;
	send_data1(pbsbm);
        
        while(xh==0)
	{
		if (com_tsbz==0)
		{  
		    if(ir_rxstate()!=0)                                                                                                                        
		   {   
		       cmd[i]=ir_rxbuf();
			//putchhex(cmd[i]);
		   	if(rt<2)
		   	{
		   		if((cmd[i]==0xfe)&&(rt==0))
		   		{rt=1;}
		   		if((cmd[i]==0x68)&&(rt==1))
		   		{rt=2;
		   		i=0;
		   		cmd[i]=0x68;
		   		byanshi=0;
		   		}
		   		if(rt!=0&&i>=15+l)  {xh=1;} //15
		   		 
		   	}
		   	else
		   	{
           			if(i==9){l=cmd[9];if(l>70){l=0;}}
		   		if(i==11+l)//11
		   		{xh=1;}
		   	}
		   	i++; 
		   }else
		   {	byanshi++;
		   	if(byanshi>35000)
		   	{xh=1;}
		   }
		}
		else
		{
		    if(comstate()!=0)                                                                                                                        
		  {   
		        cmd[i]=combuf();
		   	if(rt<2)
		   	{
		   		if((cmd[i]==0xfe)&&(rt==0))
		   		{rt=1;}
		   		if((cmd[i]==0x68)&&(rt==1))
		   		{rt=2;
		   		i=0;
		   		cmd[i]=0x68;
		   		byanshi=0;
		   		}
		   		if(rt!=0&&i>=15+l)  {xh=1;} //15
		   		
		   	}
		   	else
		   	{
           			if(i==9){l=cmd[9];if(l>70){l=0;}}
		   		if(i==11+l)//11
		   		{xh=1;}
		   	}
		   	i++;
		   }else
		   {	byanshi++;
		   	if(byanshi>35000)
		   	{xh=1;}
		   }
		}
	}
	cs=0;
	l=cmd[9];
	if(l>70){l=0;}
	for(i=0;i<=9+l;i++)
	{	cs=cs+cmd[i];
	}
	while(cs>256)
	{cs=cs-256;}
	i=cs;
       
       //cls();for(i=0;i<25;i++)putchhex(cmd[i]);key(0);
	if((cmd[10+l]==cs||cmd[10+l]==i)&&(cmd[8]==0x91)&&((cmd[10]-51==pbsbm[0])||(cmd[10]+205==pbsbm[0]))&&((cmd[11]-51==pbsbm[1])||(cmd[11]+205==pbsbm[1]))&&((cmd[12]-51==pbsbm[2])||(cmd[12]+205==pbsbm[2]))&&((cmd[13]-51==pbsbm[3])||(cmd[13]+205==pbsbm[3])))
	{ 	ls[0]='1';ls[1]=0;
		/*j=0;
		for(i=0;i<=20;i++)
		{	ito16(cmd,ls,i);
			yssj[j]=ls[0];
			yssj[j+1]=ls[1];
			yssj[j+2]=0;
			j=j+2;
		}
		//Baddr[0]=cmd[1];Baddr[1]=cmd[2];Baddr[2]=cmd[3];Baddr[3]=cmd[4];Baddr[4]=cmd[5];Baddr[5]=cmd[6];
		while(j<=99){yssj[j]=0;j++;}*/
		resu[0]='9';resu[1]=0;
	}
	
	else
	{	
	    
	    if(err<5) 
		{	
		    	disperr1(err,pbsbm,psxh);err++; 
			 goto stat;
		}else
			{cl:	cls();
				putstr("\n���յ����Ϣ����");
				putchhex(pbsbm[3]);
				putchhex(pbsbm[2]);    
				putchhex(pbsbm[1]);
				putchhex(pbsbm[0]);    
				putstr("\n�Ƿ�����");
				putstr("\n1.����");
				putstr("\n2.(�س�)����");
				putstr("\n3.����");
				k=key(0);
    	 
				if(k=='1')
				{resu[0]='0';resu[1]=0; }	
				else if(k=='2'||k==0x8d)
				{resu[0]='1';resu[1]=0;err=0;goto stat; }
				else if(k=='3')
				{resu[0]='2';resu[1]=0; }	
				else
				goto cl;
			}
	}
}

/*=================================================================================
����:	����ͨѶ
����:	*pbsbmΪ���������ݱ�ʶ(ͨ�Ź�Լ),*cmd��Ŷ�������,*resuΪ����ͨѶ�Ƿ�ɹ���־,psxhΪ�ض����ʱ��ʾ���ڶ�ȡ����Ŀ
����:
=================================================================================*/
void rece2(uchar *pbsbm,uchar *cmd,uchar *resu,int r)
{	
	uchar  i,xh,rt,err,ls[10],k;
 	long int byanshi,l,j,j1,cs;
 	err=0;
stat:   
	memset(cmd,0,sizeof(cmd));
	xh=0;
	i=0;
	rt=0;
	byanshi=1;
	l=50;

	// �����
	send_data_ir(pbsbm);
	//cls();
        while(xh==0)
	{
		if (com_tsbz==0)
		{  
		    if(ir_rxstate()!=0)                                                                                                                        
		   {   
		       cmd[i]=ir_rxbuf();
			//putchhex(cmd[i]);
		   	if(rt<2)
		   	{
		   		if((cmd[i]==0xfe)&&(rt==0))
		   		{rt=1;}
		   		if((cmd[i]==0x68)&&(rt==1))
		   		{rt=2;
		   		i=0;
		   		cmd[i]=0x68;
		   		byanshi=0;
		   		}
		   		if(rt!=0&&i>=15+l)  {xh=1;} //15
		   		 
		   	}
		   	else
		   	{
           			if(i==9){l=cmd[9];if(l>70){l=0;}}
		   		if(i==11+l)//11
		   		{xh=1;}
		   	}
		   	i++; 
		   }else
		   {	byanshi++;
		   	if(byanshi>35000)
		   	{xh=1;}
		   }
		}
		else
		{
		    if(comstate()!=0)                                                                                                                        
		  {   
		        cmd[i]=combuf();
		   	if(rt<2)
		   	{
		   		if((cmd[i]==0xfe)&&(rt==0))
		   		{rt=1;}
		   		if((cmd[i]==0x68)&&(rt==1))
		   		{rt=2;
		   		i=0;
		   		cmd[i]=0x68;
		   		byanshi=0;
		   		}
		   		if(rt!=0&&i>=15+l)  {xh=1;} //15
		   		
		   	}
		   	else
		   	{
           			if(i==9){l=cmd[9];if(l>70){l=0;}}
		   		if(i==11+l)//11
		   		{xh=1;}
		   	}
		   	i++;
		   }else
		   {	byanshi++;
		   	if(byanshi>35000)
		   	{xh=1;}
		   }
		}
	}

	cs=0;
	l=cmd[9];
	if(l>70){l=0;}
	for(j=0;j<=9+l;j++)
	{	cs=cs+cmd[j];
	}
	while(cs>256)
	{cs=cs-256;}
       
	if((cmd[10+l]==cs)&&(cmd[8]==0x93))
		{
		resu[0]='9';resu[1]=0;
		}
	else
		{
		resu[0]='0';resu[1]=0;
		l=i;
		memset(ls, 0, sizeof(ls));
		libset(r,DBH);libwrite(ls);
		libset(r,ZDL);libwrite(ls);
		cls();moveto(15,14);putstr("   ");moveto(3,2);putstr("��ȡ����ʧ��");
		moveto(5,1);for (i=0;i<l;i++){putchhex(cmd[i]);putstr(" ");}
		key(0);
		}
 }

void rece3(uchar *pbsbm,uchar *cmd,uchar *resu,int r)
{	
	uchar  i,xh,rt,err,ls[10],k;
 	long int byanshi,l,j,j1,cs;
 	err=0;
stat:   
	memset(cmd,0,sizeof(cmd));
	xh=0;
	i=0;
	rt=0;
	byanshi=1;
	l=50;

 	// ������
	send_data_ir1(pbsbm);
        
	//cls();
        while(xh==0)
	{
		if (com_tsbz==0)
		{  
		    if(ir_rxstate()!=0)                                                                                                                        
		   {   
		       cmd[i]=ir_rxbuf();
			//putchhex(cmd[i]);
		   	if(rt<2)
		   	{
		   		if((cmd[i]==0xfe)&&(rt==0))
		   		{rt=1;}
		   		if((cmd[i]==0x68)&&(rt==1))
		   		{rt=2;
		   		i=0;
		   		cmd[i]=0x68;
		   		byanshi=0;
		   		}
		   		if(rt!=0&&i>=15+l)  {xh=1;} //15
		   		 
		   	}
		   	else
		   	{
           			if(i==9){l=cmd[9];if(l>70){l=0;}}
		   		if(i==11+l)//11
		   		{xh=1;}
		   	}
		   	i++; 
		   }else
		   {	byanshi++;
		   	if(byanshi>35000)
		   	{xh=1;}
		   }
		}
		else
		{
		    if(comstate()!=0)                                                                                                                        
		  {   
		        cmd[i]=combuf();
		   	if(rt<2)
		   	{
		   		if((cmd[i]==0xfe)&&(rt==0))
		   		{rt=1;}
		   		if((cmd[i]==0x68)&&(rt==1))
		   		{rt=2;
		   		i=0;
		   		cmd[i]=0x68;
		   		byanshi=0;
		   		}
		   		if(rt!=0&&i>=15+l)  {xh=1;} //15
		   		
		   	}
		   	else
		   	{
           			if(i==9){l=cmd[9];if(l>70){l=0;}}
		   		if(i==11+l)//11
		   		{xh=1;}
		   	}
		   	i++;
		   }else
		   {	byanshi++;
		   	if(byanshi>35000)
		   	{xh=1;}
		   }
		}
	}

	cs=0;
	l=cmd[9];
	if(l>70){l=0;}
	for(j=0;j<=9+l;j++)
	{	cs=cs+cmd[j];
	}
	while(cs>256)
	{cs=cs-256;}
       
	if((cmd[10+l]==cs)&&(cmd[8]==0x91))
		{
		resu[0]='9';resu[1]=0;
		}
	else
		{
		resu[0]='0';resu[1]=0;
		l=i;
		memset(ls, 0, sizeof(ls));
		libset(r,ZDL);libwrite(ls);
		cls();moveto(15,14);putstr("   ");moveto(3,2);putstr("��ȡ����ʧ��");
		moveto(5,1);for (i=0;i<l;i++){putchhex(cmd[i]);putstr(" ");}
		key(0);
		}
 }

/*=================================================================================
����:	����ͨѶ
����:	*pbsbmΪ���������ݱ�ʶ(ͨ�Ź�Լ),*cmd��Ŷ�������,*resuΪ����ͨѶ�Ƿ�ɹ���־,psxhΪ�ض����ʱ��ʾ���ڶ�ȡ����Ŀ
����:
=================================================================================*/
void rece4(uchar *pbsbm,uchar *cmd,uchar *resu,int r)
{	
	uchar  i,xh,rt,err,ls[10],k;
 	long int byanshi,l,j,j1,cs;
 	err=0;
stat:   
	memset(cmd,0,sizeof(cmd));
	xh=0;
	i=0;
	rt=0;
	byanshi=1;
	l=50;

	// �����
	send_data_ir1(pbsbm);
	//cls();
        while(xh==0)
	{
		if (com_tsbz==0)
		{  
		    if(ir_rxstate()!=0)                                                                                                                        
		   {   
		       cmd[i]=ir_rxbuf();
			//putchhex(cmd[i]);
		   	if(rt<2)
		   	{
		   		if((cmd[i]==0xfe)&&(rt==0))
		   		{rt=1;}
		   		if((cmd[i]==0x68)&&(rt==1))
		   		{rt=2;
		   		i=0;
		   		cmd[i]=0x68;
		   		byanshi=0;
		   		}
		   		if(rt!=0&&i>=15+l)  {xh=1;} //15
		   		 
		   	}
		   	else
		   	{
           			if(i==9){l=cmd[9];if(l>70){l=0;}}
		   		if(i==11+l)//11
		   		{xh=1;}
		   	}
		   	i++; 
		   }else
		   {	byanshi++;
		   	if(byanshi>35000)
		   	{xh=1;}
		   }
		}
		else
		{
		    if(comstate()!=0)                                                                                                                        
		  {   
		        cmd[i]=combuf();
		   	if(rt<2)
		   	{
		   		if((cmd[i]==0xfe)&&(rt==0))
		   		{rt=1;}
		   		if((cmd[i]==0x68)&&(rt==1))
		   		{rt=2;
		   		i=0;
		   		cmd[i]=0x68;
		   		byanshi=0;
		   		}
		   		if(rt!=0&&i>=15+l)  {xh=1;} //15
		   		
		   	}
		   	else
		   	{
           			if(i==9){l=cmd[9];if(l>70){l=0;}}
		   		if(i==11+l)//11
		   		{xh=1;}
		   	}
		   	i++;
		   }else
		   {	byanshi++;
		   	if(byanshi>35000)
		   	{xh=1;}
		   }
		}
	}

	cs=0;
	l=cmd[9];
	if(l>70){l=0;}
	for(j=0;j<=9+l;j++)
	{	cs=cs+cmd[j];
	}
	while(cs>256)
	{cs=cs-256;}
       
	if((cmd[10+l]==cs)&&(cmd[8]==0x91))
		{
		resu[0]='9';resu[1]=0;
		}
	else
		{
		resu[0]='0';resu[1]=0;
		l=i;
		memset(ls, 0, sizeof(ls));
		libset(r,DBH);libwrite(ls);
		libset(r,ZDL);libwrite(ls);
		cls();moveto(15,14);putstr("   ");moveto(3,2);putstr("��ȡ����ʧ��");
		moveto(5,1);for (i=0;i<l;i++){putchhex(cmd[i]);putstr(" ");}
		key(0);
		}
 }

/*=================================================================================
����:	�ض������ʾ
����:	errΪ�ض�����,*pbsbmΪ���������ݱ�ʶ(ͨ�Ź�Լ),psxhΪ�ض����ʱ��ʾ���ڶ�ȡ����Ŀ
����:
=================================================================================*/
void disperr(uchar err,uchar *pbsbm,int psxh)
{  	
	int i;
	cls();
	moveto(3,1);
	putstr("���ڳ����ض�����\n");
	putstr("����=");printf("%d",err);
	putstr("\n�ض����� ");
	putchhex(pbsbm[1]);
	putchhex(pbsbm[0]);    
	if(!(psxh==0))
	{	putstr("\n�� ");
		printf("%d",psxh);
		putstr(" ��");
	}
}

/*=================================================================================
����:	�ض������ʾ
����:	errΪ�ض�����,*pbsbmΪ���������ݱ�ʶ(ͨ�Ź�Լ),psxhΪ�ض����ʱ��ʾ���ڶ�ȡ����Ŀ
����:
=================================================================================*/
void disperr1(uchar err,uchar *pbsbm,int psxh)
{  	
	int i;
	cls();
	moveto(3,1);
	putstr("���ڳ����ض�����\n");
	putstr("����=");printf("%d",err);
	putstr("\n�ض����� ");
	putchhex(pbsbm[3]);
	putchhex(pbsbm[2]);    
	putchhex(pbsbm[1]);
	putchhex(pbsbm[0]);    
	if(!(psxh==0))
	{	putstr("\n�� ");
		printf("%d",psxh);
		putstr(" ��");
	}
}

/*=================================================================================
����:	��ȡ����
����:	*pdateΪ��ȡ������(YYMMDD)
����:
=================================================================================*/
void getdate1(uchar *pdate)
{	
	uchar adate[10];
	getdate(adate);
	pdate[0]=adate[2];
	pdate[1]=adate[3];
	pdate[2]=adate[5];
	pdate[3]=adate[6];
	pdate[4]=adate[8];
	pdate[5]=adate[9];
	pdate[6]=0;
	pdate[7]=0;
	pdate[8]=0;
	pdate[9]=0;
}

/*=================================================================================
����:	��ȡʱ��
����:	*ptimeΪ��ȡ��ʱ��(HHMMSS)
����:
=================================================================================*/
void gettime1(uchar *ptime)
{	
	uchar atime[10];
	gettime(atime);
	ptime[0]=atime[0];
	ptime[1]=atime[1];
	ptime[2]=atime[3];
	ptime[3]=atime[4];
	ptime[4]=atime[6];
	ptime[5]=atime[7];
	ptime[6]=0;
}

/*=================================================================================
����:	ת��һ�������10������Ϊ16������
����:	*acharΪ10������,*plsΪ16������,wzΪ�������
����:	
=================================================================================*/
void ito16(uchar *achar,uchar *pls,unsigned int wz)
{	
	int i,j;
	i=achar[wz]/16;
	if(i==0){pls[0]='0';} else
	if(i==1){pls[0]='1';} else
	if(i==2){pls[0]='2';} else
	if(i==3){pls[0]='3';} else
	if(i==4){pls[0]='4';} else
	if(i==5){pls[0]='5';} else
	if(i==6){pls[0]='6';} else
	if(i==7){pls[0]='7';} else
	if(i==8){pls[0]='8';} else
	if(i==9){pls[0]='9';} else
	if(i==10){pls[0]='A';} else
	if(i==11){pls[0]='B';} else
	if(i==12){pls[0]='C';} else
	if(i==13){pls[0]='D';} else
	if(i==14){pls[0]='E';} else
	if(i==15){pls[0]='F';}

	i=achar[wz]-i*16;
	if(i==0){pls[1]='0';} else
	if(i==1){pls[1]='1';} else
	if(i==2){pls[1]='2';} else
	if(i==3){pls[1]='3';} else
	if(i==4){pls[1]='4';} else
	if(i==5){pls[1]='5';} else
	if(i==6){pls[1]='6';} else
	if(i==7){pls[1]='7';} else
	if(i==8){pls[1]='8';} else
	if(i==9){pls[1]='9';} else
	if(i==10){pls[1]='A';} else
	if(i==11){pls[1]='B';} else
	if(i==12){pls[1]='C';} else
	if(i==13){pls[1]='D';} else
	if(i==14){pls[1]='E';} else
	if(i==15){pls[1]='F';}
	pls[2]=0;
}

/*=================================================================================
����:	ת��һ��10������Ϊ16������(4λ)
����:	*acharΪ10������,*plsΪ16������
����:
=================================================================================*/
void ito16_4(int achar,uchar *pls)
{	
	int i1,i2,i3,i4,j;
	i1=achar/4096;
	if(i1==0){pls[0]='0';} else
	if(i1==1){pls[0]='1';} else
	if(i1==2){pls[0]='2';} else
	if(i1==3){pls[0]='3';} else
	if(i1==4){pls[0]='4';} else
	if(i1==5){pls[0]='5';} else
	if(i1==6){pls[0]='6';} else
	if(i1==7){pls[0]='7';} else
	if(i1==8){pls[0]='8';} else
	if(i1==9){pls[0]='9';} else
	if(i1==10){pls[0]='A';} else
	if(i1==11){pls[0]='B';} else
	if(i1==12){pls[0]='C';} else
	if(i1==13){pls[0]='D';} else
	if(i1==14){pls[0]='E';} else
	if(i1==15){pls[0]='F';}
   
	i2=(achar-i1*4096)/256;
	if(i2==0){pls[1]='0';} else
	if(i2==1){pls[1]='1';} else
	if(i2==2){pls[1]='2';} else
	if(i2==3){pls[1]='3';} else
	if(i2==4){pls[1]='4';} else
	if(i2==5){pls[1]='5';} else
	if(i2==6){pls[1]='6';} else
	if(i2==7){pls[1]='7';} else
	if(i2==8){pls[1]='8';} else
	if(i2==9){pls[1]='9';} else
	if(i2==10){pls[1]='A';} else
	if(i2==11){pls[1]='B';} else
	if(i2==12){pls[1]='C';} else
	if(i2==13){pls[1]='D';} else
	if(i2==14){pls[1]='E';} else
	if(i2==15){pls[1]='F';}

	i3=(achar-i1*4096-i2*256)/16;
	if(i3==0){pls[2]='0';} else
	if(i3==1){pls[2]='1';} else
	if(i3==2){pls[2]='2';} else
	if(i3==3){pls[2]='3';} else
	if(i3==4){pls[2]='4';} else
	if(i3==5){pls[2]='5';} else
	if(i3==6){pls[2]='6';} else
	if(i3==7){pls[2]='7';} else
	if(i3==8){pls[2]='8';} else
	if(i3==9){pls[2]='9';} else
	if(i3==10){pls[2]='A';} else
	if(i3==11){pls[2]='B';} else
	if(i3==12){pls[2]='C';} else
	if(i3==13){pls[2]='D';} else
	if(i3==14){pls[2]='E';} else
	if(i3==15){pls[2]='F';}

	i4=achar-i1*4096-i2*256-i3*16;
	if(i4==0){pls[3]='0';} else
	if(i4==1){pls[3]='1';} else
	if(i4==2){pls[3]='2';} else
	if(i4==3){pls[3]='3';} else
	if(i4==4){pls[3]='4';} else
	if(i4==5){pls[3]='5';} else
	if(i4==6){pls[3]='6';} else
	if(i4==7){pls[3]='7';} else
	if(i4==8){pls[3]='8';} else
	if(i4==9){pls[3]='9';} else
	if(i4==10){pls[3]='A';} else
	if(i4==11){pls[3]='B';} else
	if(i4==12){pls[3]='C';} else
	if(i4==13){pls[3]='D';} else
	if(i4==14){pls[3]='E';} else
	if(i4==15){pls[3]='F';}
	pls[4]=0;
	pls[0]=i3*16+i4;
	pls[1]=i1*16+i2;
	pls[2]=0;
	pls[3]=0;
}

/*=================================================================================
����:	ת��һ��10������Ϊ16������(2λ)
����:	*acharΪ10������,*plsΪ16������
����:
=================================================================================*/
void ito16_2(int achar,uchar *pls)
{	
	int i1,i2,i3,i4,j;
	i1=achar/16;
	if(i1==0){pls[0]='0';} else
	if(i1==1){pls[0]='1';} else
	if(i1==2){pls[0]='2';} else
	if(i1==3){pls[0]='3';} else
	if(i1==4){pls[0]='4';} else
	if(i1==5){pls[0]='5';} else
	if(i1==6){pls[0]='6';} else
	if(i1==7){pls[0]='7';} else
	if(i1==8){pls[0]='8';} else
	if(i1==9){pls[0]='9';} else
	if(i1==10){pls[0]='A';} else
	if(i1==11){pls[0]='B';} else
	if(i1==12){pls[0]='C';} else
	if(i1==13){pls[0]='D';} else
	if(i1==14){pls[0]='E';} else
	if(i1==15){pls[0]='F';}
   
	i2=achar-i1*16;
	if(i2==0){pls[1]='0';} else
	if(i2==1){pls[1]='1';} else
	if(i2==2){pls[1]='2';} else
	if(i2==3){pls[1]='3';} else
	if(i2==4){pls[1]='4';} else
	if(i2==5){pls[1]='5';} else
	if(i2==6){pls[1]='6';} else
	if(i2==7){pls[1]='7';} else
	if(i2==8){pls[1]='8';} else
	if(i2==9){pls[1]='9';} else
	if(i2==10){pls[1]='A';} else
	if(i2==11){pls[1]='B';} else
	if(i2==12){pls[1]='C';} else
	if(i2==13){pls[1]='D';} else
	if(i2==14){pls[1]='E';} else
	if(i2==15){pls[1]='F';}

	pls[2]=0;
}

/*=================================================================================
����:	��������(��������ͨѶ)
����:	*pbsbmΪ���������ݱ�ʶ(ͨ�Ź�Լ)
����:
=================================================================================*/
void send_data(uchar *pbsbm)
{ 	
	long int cs;
	if (com_tsbz==0)	{ir_init(B1200,0x2B,UART_ON);}
  	else {cominit(B1200,0x2B,UART_ON);}  
	dleay1();
	if (com_tsbz==0)
	{
	  	ir_write(0xFE);delay(DELAY_TIME3);
	  	ir_write(0xFE);delay(DELAY_TIME3);
	  	ir_write(0xFE);delay(DELAY_TIME3);
	  	ir_write(0x68);delay(DELAY_TIME3);
	  	ir_write(Baddr[0]);delay(DELAY_TIME3);
	  	ir_write(Baddr[1]);delay(DELAY_TIME3);
	  	ir_write(Baddr[2]);delay(DELAY_TIME3);
	  	ir_write(Baddr[3]);delay(DELAY_TIME3);
	  	ir_write(Baddr[4]);delay(DELAY_TIME3);
	  	ir_write(Baddr[5]);delay(DELAY_TIME3);
	  	ir_write(0x68);delay(DELAY_TIME3);
	  	ir_write(0x1);delay(DELAY_TIME3);
	  	ir_write(0x2);delay(DELAY_TIME3);
	  	if(pbsbm[0]+0x33>255)
	  	{ir_write(pbsbm[0]+0x33-0x100);delay(DELAY_TIME3);}
	  	else{ir_write(pbsbm[0]+0x33);delay(DELAY_TIME3);}
	  	if(pbsbm[1]+0x33>255)
	  	{ir_write(pbsbm[1]+0x33-0x100);delay(DELAY_TIME3);}
	  	else{ir_write(pbsbm[1]+0x33);delay(DELAY_TIME3);}
	  	cs=0x68+Baddr[0]+Baddr[1]+Baddr[2]+Baddr[3]+Baddr[4]+Baddr[5]+0x68+0x1+0x2+pbsbm[0]+pbsbm[1]+51+51;
	  	while(cs>256)  {cs=cs-256;}
	  	ir_write(cs);delay(DELAY_TIME3);
	  	ir_write(0x16);delay(400);
	}
	else
	{
		comwrite(0xFE);
	  	comwrite(0xFE);
	  	comwrite(0xFE);
	  	comwrite(0x68);
	  	if(pbsbm[0]==0x32&&pbsbm[1]==0xC0)
	  	{
	  		Baddr[0]=0x99;Baddr[1]=0x99;Baddr[2]=0x99;Baddr[3]=0x99;Baddr[4]=0x99;Baddr[5]=0x99;
	  		comwrite(Baddr[0]);
	  		comwrite(Baddr[1]);
	  		comwrite(Baddr[2]);
	  		comwrite(Baddr[3]);
	  		comwrite(Baddr[4]);
	  		comwrite(Baddr[5]);
	  	}else
	  	{
	  		comwrite(Baddr[0]);
	  		comwrite(Baddr[1]);
	  		comwrite(Baddr[2]);
	  		comwrite(Baddr[3]);
	  		comwrite(Baddr[4]);
	  		comwrite(Baddr[5]);
	  	}
	  	comwrite(0x68);
	  	comwrite(0x1);
	  	comwrite(0x2);
	  	if(pbsbm[0]+0x33>255)
	  	{comwrite(pbsbm[0]+0x33-0x100);}
	  	else{comwrite(pbsbm[0]+0x33);}
	  	if(pbsbm[1]+0x33>255)
	  	{comwrite(pbsbm[1]+0x33-0x100);}
	  	else{comwrite(pbsbm[1]+0x33);}
	  	cs=0x68+Baddr[0]+Baddr[1]+Baddr[2]+Baddr[3]+Baddr[4]+Baddr[5]+0x68+0x1+0x2+pbsbm[0]+pbsbm[1]+51+51;
	  	while(cs>256)  {cs=cs-256;}
	  	comwrite(cs);
	  	comwrite(0x16);
	}
}

/*=================================================================================
����:	��������(��������ͨѶ)
����:	*pbsbmΪ���������ݱ�ʶ(ͨ�Ź�Լ)
����:
=================================================================================*/
void send_data1(uchar *pbsbm)
{ 	
	int i;
	long int cs;
	if (com_tsbz==0)	{ir_init(B1200,0x2B,UART_ON);}
  	else {cominit(B1200,0x2B,UART_ON);}  
	dleay1();
	if (com_tsbz==0)
	{
	  	ir_write(0xFE);delay(DELAY_TIME3);
	  	ir_write(0xFE);delay(DELAY_TIME3);
	  	ir_write(0xFE);delay(DELAY_TIME3);
	  	ir_write(0xFE);delay(DELAY_TIME3);
	  	ir_write(0x68);delay(DELAY_TIME3);
	  	ir_write(Baddr[0]);delay(DELAY_TIME3);
	  	ir_write(Baddr[1]);delay(DELAY_TIME3);
	  	ir_write(Baddr[2]);delay(DELAY_TIME3);
	  	ir_write(Baddr[3]);delay(DELAY_TIME3);
	  	ir_write(Baddr[4]);delay(DELAY_TIME3);
	  	ir_write(Baddr[5]);delay(DELAY_TIME3);
	  	ir_write(0x68);delay(DELAY_TIME3);
	  	ir_write(0x11);delay(DELAY_TIME3);
	  	ir_write(0x04);delay(DELAY_TIME3);
		for (i=0; i<4; i++)
		{
		  	if(pbsbm[i]+0x33>255)
		  	{ir_write(pbsbm[i]+0x33-0x100);delay(DELAY_TIME3);}
		  	else{ir_write(pbsbm[i]+0x33);delay(DELAY_TIME3);}
		}
	  	cs=0x68+Baddr[0]+Baddr[1]+Baddr[2]+Baddr[3]+Baddr[4]+Baddr[5]+0x68+0x11+0x04+pbsbm[0]+pbsbm[1]+pbsbm[2]+pbsbm[3]+51+51+51+51;
	  	while(cs>256)  {cs=cs-256;}
	  	ir_write(cs);delay(DELAY_TIME3);
	  	ir_write(0x16);delay(400);
	}
}

/*=================================================================================
����:	��������(��������ͨѶ)
����:	*pbsbmΪ���������ݱ�ʶ(ͨ�Ź�Լ)
����:
=================================================================================*/
void send_data_ir(uchar *pbsbm)
{ 	
	long int cs;
	if (com_tsbz==0)	{ir_init(B1200,0x2B,UART_ON);}
  	else {cominit(B1200,0x2B,UART_ON);}  
	dleay1();
	if (com_tsbz==0)
	{
	  	ir_write(0xFE);delay(DELAY_TIME3);
	  	ir_write(0xFE);delay(DELAY_TIME3);
	  	ir_write(0xFE);delay(DELAY_TIME3);
	  	ir_write(0xFE);delay(DELAY_TIME3);
	  	ir_write(0x68);delay(DELAY_TIME3);
	  	ir_write(Baddr[0]);delay(DELAY_TIME3);
	  	ir_write(Baddr[1]);delay(DELAY_TIME3);
	  	ir_write(Baddr[2]);delay(DELAY_TIME3);
	  	ir_write(Baddr[3]);delay(DELAY_TIME3);
	  	ir_write(Baddr[4]);delay(DELAY_TIME3);
	  	ir_write(Baddr[5]);delay(DELAY_TIME3);
	  	ir_write(0x68);delay(DELAY_TIME3);
	  	ir_write(0x13);delay(DELAY_TIME3);
	  	ir_write(0x00);delay(DELAY_TIME3);
	  	cs=0x68+Baddr[0]+Baddr[1]+Baddr[2]+Baddr[3]+Baddr[4]+Baddr[5]+0x68+0x13+0x00;
	  	while(cs>256)  {cs=cs-256;}
	  	ir_write(cs);delay(DELAY_TIME3);
	  	ir_write(0x16);delay(400);
	}
}

void send_data_ir1(uchar *pbsbm)
{ 	
	int i;
	long int cs;
	if (com_tsbz==0)	{ir_init(B1200,0x2B,UART_ON);}
  	else {cominit(B1200,0x2B,UART_ON);}  
	dleay1();
	if (com_tsbz==0)
	{
	  	ir_write(0xFE);delay(DELAY_TIME3);
	  	ir_write(0xFE);delay(DELAY_TIME3);
	  	ir_write(0xFE);delay(DELAY_TIME3);
	  	ir_write(0xFE);delay(DELAY_TIME3);
	  	ir_write(0x68);delay(DELAY_TIME3);
	  	ir_write(Baddr[0]);delay(DELAY_TIME3);
	  	ir_write(Baddr[1]);delay(DELAY_TIME3);
	  	ir_write(Baddr[2]);delay(DELAY_TIME3);
	  	ir_write(Baddr[3]);delay(DELAY_TIME3);
	  	ir_write(Baddr[4]);delay(DELAY_TIME3);
	  	ir_write(Baddr[5]);delay(DELAY_TIME3);
	  	ir_write(0x68);delay(DELAY_TIME3);
	  	ir_write(0x11);delay(DELAY_TIME3);
	  	ir_write(0x04);delay(DELAY_TIME3);
		for (i=0; i<4; i++)
		{
		  	if(pbsbm[i]+0x33>255)
		  	{ir_write(pbsbm[i]+0x33-0x100);delay(DELAY_TIME3);}
		  	else{ir_write(pbsbm[i]+0x33);delay(DELAY_TIME3);}
		}
	  	cs=0x68+Baddr[0]+Baddr[1]+Baddr[2]+Baddr[3]+Baddr[4]+Baddr[5]+0x68+0x11+0x04+pbsbm[0]+pbsbm[1]+pbsbm[2]+pbsbm[3]+51+51+51+51;
	  	while(cs>256)  {cs=cs-256;}
	  	ir_write(cs);delay(DELAY_TIME3);
	  	ir_write(0x16);delay(400);
	}
}

/*=================================================================================
����:	У������ʱ��
����:	
����:	
=================================================================================*/
void crtime(void)
{ 	
	uchar  addr2[8],rbuf[10],k,k1,i,i0,i1,ls[10],ls2[2],cmd[50],xh,l,f;
  	uchar  rbuf3[10],r,total,mdate[9],mtime[7],pdate[9],ptime[7],pbsbm[4],ls0[2],ls1[2];
  	long int cs,j;
       r=RBAK[0];
	cls();
	putstr("���ڶ�ʱ");
	j=0xC010;
	ito16_4(j,pbsbm);
	read_data(pbsbm,ls,2,0);
	if(ls[0]=='0'||ls[0]=='2')
	{for(j=0;j<=99;j++)
	{fxsj[j]=0;}}
	
	for(i=0;i<=8;i++)
	{mdate[i]=fxsj[i];}
	mdate[6]=0;
	mdate[7]=0;
	mdate[8]=0;
	mdate[9]=0;
	
		
	j=0xc011;
	ito16_4(j,pbsbm);
	read_data(pbsbm,ls,3,0);
	if(ls[0]=='0'||ls[0]=='2')
	{for(j=0;j<=99;j++)
	{fxsj[j]=0;}}
	
	for(i=0;i<=5;i++)
	{mtime[i]=fxsj[i];}
	mtime[6]=0;
	mtime[7]=0;
	
	cls();
	moveto(5,1);
	putstr("�������:");
	putstr(mdate);
	moveto(7,1);
	putstr("���ʱ��:");
	putstr(mtime);
	
  	getdate1(pdate);
	gettime1(ptime);
	
	moveto(9,1);
	putstr("���������:");
	putstr(pdate);
	moveto(11,1);
	putstr("�����ʱ��:");
	putstr(ptime);
	
	libset(r,CBDATE);libwrite(pdate);
	libset(r,CBTIME);libwrite(ptime);
		
	//save_sjc(ptime,mtime,0);
	
		
	if (com_tsbz==0)	{ir_init(B1200,0x2B,UART_ON);}
      	else {cominit(B1200,0x2B,UART_ON);}
	dleay1();
	if (com_tsbz==0)
	{
		ir_write(0xFE);
		ir_write(0xFE);
		ir_write(0xFE);
		ir_write(0x68);
		ir_write(0x99);
		ir_write(0x99);
		ir_write(0x99);
		ir_write(0x99);
		ir_write(0x99);
		ir_write(0x99);
		ir_write(0x68);
		ir_write(0x8);
		ir_write(0x6);
	}
	else
	{
		comwrite(0xFE);
		comwrite(0xFE);
		comwrite(0xFE);
		comwrite(0x68);
		comwrite(0x99);
		comwrite(0x99);
		comwrite(0x99);
		comwrite(0x99);
		comwrite(0x99);
		comwrite(0x99);
		comwrite(0x68);
		comwrite(0x8);
		comwrite(0x6);
	}
	cs=0x68+0x99+0x99+0x99+0x99+0x99+0x99+0x68+0x8+0x6;
	for(j=2;j>=0;j--)
	{
		ls0[0]=ptime[j*2];
		ls0[1]=0;
		ls1[0]=ptime[j*2+1];
		ls1[1]=0;
		i0=stoi(3,ls0);
		i1=stoi(3,ls1);
		i=i0*16+i1+51;
		if (com_tsbz==0)	{	ir_write(i); }
		else {	comwrite(i); }
		ls0[0]=i;
		cs=cs+i;
	}
	for(j=2;j>=0;j--)
	{
		ls0[0]=pdate[j*2];
		ls0[1]=0;
		ls1[0]=pdate[j*2+1];
		ls1[1]=0;
		i0=stoi(3,ls0);
		i1=stoi(3,ls1);
		i=i0*16+i1+51;  
		if (com_tsbz==0)	{	ir_write(i); }
		else {	comwrite(i); } 
		ls0[0]=i;
		cs=cs+i;
	}
	while(cs>256)
	{cs=cs-256;}			
	if (com_tsbz==0)	{	ir_write(cs); ir_write(0x16); }
	else {	comwrite(cs); comwrite(0x16); }
	
	
	for(j=0;j<=9;j++)
	{mdate[j]=0;}
	for(j=0;j<=7;j++)
	{mtime[j]=0;}
	for(j=0;j<=9;j++)
	{pdate[j]=0;}
	for(j=0;j<=7;j++)
	{ptime[j]=0;}
	
	j=0xC010;
	ito16_4(j,pbsbm);
	read_data(pbsbm,ls,2,0);
	if(ls[0]=='0'||ls[0]=='2')
	{for(j=0;j<=99;j++)
	{fxsj[j]=0;}}
	
	for(i=0;i<=7;i++)
	{mdate[i]=fxsj[i];}
	mdate[8]=0;
	mdate[9]=0;
		
	j=0xC011;
	ito16_4(j,pbsbm);
	read_data(pbsbm,ls,3,0);
	if(ls[0]=='0'||ls[0]=='2')
	{for(j=0;j<=99;j++)
	{fxsj[j]=0;}}
	
	for(i=0;i<=5;i++)
	{mtime[i]=fxsj[i];}
	mtime[6]=0;
	mtime[7]=0;
		  	
       //getdate1(pdate);
	//gettime1(ptime);
	
	//save_sjc(ptime,mtime,1);
	key(0);
}

/*=================================================================================
����:	У������ʱ��
����:	
����:	
=================================================================================*/
void crtime1(void)
{ 	
	uchar  addr2[8],rbuf[10],k,k1,i,i0,i1,ls[10],ls2[2],cmd[50],xh,l,f;
  	uchar  rbuf3[10],r,total,mdate[9],mtime[7],pdate[9],ptime[7],pbsbm[8],ls0[2],ls1[2];
  	long int cs,j;
       r=RBAK[0];

	memset(Baddr,0xAA,sizeof(Baddr));
	memset(ls,0,sizeof(ls));
	cls();
	putstr("���ڶ�ȡ����");
	read_addr1(ls, r);
	if((ls[0]=='0')||(ls[0]=='2')) {putstr("��ȡ����ʧ��");key(0);return;}
	
	cls();
	putstr("���ڶ�ʱ");
	//j=0xC010;
	//ito16_4(j,pbsbm);
	//04000101
	pbsbm[0] = 0x01;
	pbsbm[1] = 0x01;
	pbsbm[2] = 0x00;
	pbsbm[3] = 0x04;
	pbsbm[4] = 0;
	read_data1(pbsbm,ls,2,0);
	if(ls[0]=='0'||ls[0]=='2')
	{for(j=0;j<=99;j++)
	{fxsj[j]=0;}}
	
	for(i=0;i<=8;i++)
	{mdate[i]=fxsj[i];}
	mdate[6]=0;
	mdate[7]=0;
	mdate[8]=0;
	mdate[9]=0;
	
		
	//j=0xc011;
	//ito16_4(j,pbsbm);
	//04000102
	pbsbm[0] = 0x02;
	pbsbm[1] = 0x01;
	pbsbm[2] = 0x00;
	pbsbm[3] = 0x04;
	pbsbm[4] = 0;
	read_data1(pbsbm,ls,3,0);
	if(ls[0]=='0'||ls[0]=='2')
	{for(j=0;j<=99;j++)
	{fxsj[j]=0;}}
	
	for(i=0;i<=5;i++)
	{mtime[i]=fxsj[i];}
	mtime[6]=0;
	mtime[7]=0;
	
	cls();
	moveto(5,1);
	putstr("�������:");
	putstr(mdate);
	moveto(7,1);
	putstr("���ʱ��:");
	putstr(mtime);
	
  	getdate1(pdate);
	gettime1(ptime);
	
	moveto(9,1);
	putstr("���������:");
	putstr(pdate);
	moveto(11,1);
	putstr("�����ʱ��:");
	putstr(ptime);
	
	libset(r,CBDATE);libwrite(pdate);
	libset(r,CBTIME);libwrite(ptime);
		
	//save_sjc(ptime,mtime,0);
	
		
	if (com_tsbz==0)	{ir_init(B1200,0x2B,UART_ON);}
      	else {cominit(B1200,0x2B,UART_ON);}
	dleay1();
	if (com_tsbz==0)
	{
		ir_write(0xFE);
		ir_write(0xFE);
		ir_write(0xFE);
		ir_write(0xFE);
		ir_write(0x68);
		ir_write(0x99);
		ir_write(0x99);
		ir_write(0x99);
		ir_write(0x99);
		ir_write(0x99);
		ir_write(0x99);
		ir_write(0x68);
		ir_write(0x8);
		ir_write(0x6);
	}
	else
	{
		comwrite(0xFE);
		comwrite(0xFE);
		comwrite(0xFE);
		comwrite(0xFE);
		comwrite(0x68);
		comwrite(0x99);
		comwrite(0x99);
		comwrite(0x99);
		comwrite(0x99);
		comwrite(0x99);
		comwrite(0x99);
		comwrite(0x68);
		comwrite(0x8);
		comwrite(0x6);
	}
	cs=0x68+0x99+0x99+0x99+0x99+0x99+0x99+0x68+0x8+0x6;
	for(j=2;j>=0;j--)
	{
		ls0[0]=ptime[j*2];
		ls0[1]=0;
		ls1[0]=ptime[j*2+1];
		ls1[1]=0;
		i0=stoi(3,ls0);
		i1=stoi(3,ls1);
		i=i0*16+i1+51;
		if (com_tsbz==0)	{	ir_write(i); }
		else {	comwrite(i); }
		ls0[0]=i;
		cs=cs+i;
	}
	for(j=2;j>=0;j--)
	{
		ls0[0]=pdate[j*2];
		ls0[1]=0;
		ls1[0]=pdate[j*2+1];
		ls1[1]=0;
		i0=stoi(3,ls0);
		i1=stoi(3,ls1);
		i=i0*16+i1+51;  
		if (com_tsbz==0)	{	ir_write(i); }
		else {	comwrite(i); } 
		ls0[0]=i;
		cs=cs+i;
	}
	while(cs>256)
	{cs=cs-256;}			
	if (com_tsbz==0)	{	ir_write(cs); ir_write(0x16); }
	else {	comwrite(cs); comwrite(0x16); }
	
	
	for(j=0;j<=9;j++)
	{mdate[j]=0;}
	for(j=0;j<=7;j++)
	{mtime[j]=0;}
	for(j=0;j<=9;j++)
	{pdate[j]=0;}
	for(j=0;j<=7;j++)
	{ptime[j]=0;}
	
	//j=0xC010;
	//ito16_4(j,pbsbm);
	//04000101
	pbsbm[0] = 0x01;
	pbsbm[1] = 0x01;
	pbsbm[2] = 0x00;
	pbsbm[3] = 0x04;
	pbsbm[4] = 0;
	read_data1(pbsbm,ls,2,0);
	if(ls[0]=='0'||ls[0]=='2')
	{for(j=0;j<=99;j++)
	{fxsj[j]=0;}}
	
	for(i=0;i<=7;i++)
	{mdate[i]=fxsj[i];}
	mdate[8]=0;
	mdate[9]=0;
		
	//j=0xC011;
	//ito16_4(j,pbsbm);
	//04000102
	pbsbm[0] = 0x02;
	pbsbm[1] = 0x01;
	pbsbm[2] = 0x00;
	pbsbm[3] = 0x04;
	pbsbm[4] = 0;
	read_data1(pbsbm,ls,3,0);
	if(ls[0]=='0'||ls[0]=='2')
	{for(j=0;j<=99;j++)
	{fxsj[j]=0;}}
	
	for(i=0;i<=5;i++)
	{mtime[i]=fxsj[i];}
	mtime[6]=0;
	mtime[7]=0;
		  	
       //getdate1(pdate);
	//gettime1(ptime);
	
	//save_sjc(ptime,mtime,1);
	key(0);
}

/*=================================================================================
����:	ȥ0
����:	*ddĿ������,xΪ���鳤��
����:	
=================================================================================*/
void del0(uchar *dd,unsigned int x)
{ 	
	int i,k,ws,feiling,len;
	uchar ls[20];
	k=1;
	for(i=0;i<=x;i++)
	{	if(dd[i]==0)
		{	len=i;break;}
	}
	for(i=0;i<=len;i++)
	{	if(dd[i]=='.')
		{k=2;ws=i;break;}
	}
	if(k==1){ws=len;}
	feiling=ws-1;
	//k=2��С�� k=1��С��
	for(i=0;i<ws;i++)
	{	if(dd[i]!='0')
		{feiling=i;break;}
	}
 	k=0;
	for(i=feiling;i<=len;i++)
	{ls[k]=dd[i];k++; 
	}
	for(i=len-feiling+1;i<x;i++)
	{ls[i]=0;};
  
	for(i=0;i<x;i++)
	{dd[i]=ls[i];}
 }
/*=================================================================================
����:	ȥ0
����:	*ddĿ������,xΪ���鳤��
����:	
=================================================================================*/
void del00(uchar *dd,unsigned int x)
{ 	
	int i,k,ws,feiling,len;
	uchar ls[20];
	k=1;
	for(i=0;i<=x;i++)
	{	if(dd[i]==0)
		{	len=i;break;}
	}
	for(i=0;i<=len;i++)
	{	if(dd[i]=='.')
		{k=2;ws=i;break;}
	}
	if(k==1){ws=len;}
	feiling=ws-1;
	//k=2��С�� k=1��С��
	for(i=len-1;i>ws;i--)
	{	if(dd[i]=='0')
		{dd[i]=0;}
		else{break;}
	}
	if(i==ws){dd[ws]=0;}
 
}

/*=================================================================================
����:	��¼��ʱʱ���
����:	*ptimeΪ�ֳֻ�ʱ��,*mtimeΪ���ʱ��,i�����жϴ��λ��
����:
=================================================================================*/
/*void save_sjc(uchar *ptime , uchar *mtime , int i)
{
	uchar save_time[8],ls[2],ls1[2];
	int j=2,l,m,i0,i1,z;
	long int t,sxh;
	libopen(0);
	t=0x9010;
	sxh=cx(addr1,t);
	while(j>=0)
	{
		ls[1]=0;
		ls[0]=ptime[j*2];
		ls1[1]=0;
		ls1[0]=ptime[j*2+1];
		i0=stoi(3,ls);
		i1=stoi(3,ls1);
		l=i0*10+i1;
		ls[1]=0;
		ls[0]=mtime[j*2];
		ls1[1]=0;
		ls1[0]=mtime[j*2+1];
		i0=stoi(3,ls);
		i1=stoi(3,ls1);
		m=i0*10+i1;

		switch(j)
		{
			case 2:	if(l<m){ito10_2((l+60-m),ls);save_time[3]=ls[0];save_time[4]=ls[1];z=1;}
							else{ito10_2((l-m),ls);save_time[3]=ls[0];save_time[4]=ls[1];z=0;}
							break;
			case 1:	if(l<m){ito10_2((l+60-z-m),ls);save_time[1]=ls[0];save_time[2]=ls[1];z=1;}
							else{ito10_2((l-m),ls);save_time[1]=ls[0];save_time[2]=ls[1];z=0;}
							break;
			case 0:	ito10_2(abs(l-z-m),ls);save_time[0]=ls[1];
							break;
		}
		j--;
	}
	save_time[5]=0;
	if(i==0)
	{
		libset(sxh,DSQSC);
		libwrite(save_time);
	}
	else
	{
		libset(sxh,DSHSC);
		libwrite(save_time);
	}
}
*/
/*=================================================================================
����:	10��������λ��ʮλ�ֱ���������������Ԫ��
����:	archarĿ��10������,*pls���ڴ�ŵ�����
����:
=================================================================================*/
void ito10_2(int achar,uchar *pls)
{	
	int i1,i2,i3,i4,j;
	i1=achar/10;
	if(i1==0){pls[0]='0';} else
	if(i1==1){pls[0]='1';} else
	if(i1==2){pls[0]='2';} else
	if(i1==3){pls[0]='3';} else
	if(i1==4){pls[0]='4';} else
	if(i1==5){pls[0]='5';} else
	if(i1==6){pls[0]='6';} else
	if(i1==7){pls[0]='7';} else
	if(i1==8){pls[0]='8';} else
	if(i1==9){pls[0]='9';} 
	   
	i2=achar-i1*10;
	if(i2==0){pls[1]='0';} else
	if(i2==1){pls[1]='1';} else
	if(i2==2){pls[1]='2';} else
	if(i2==3){pls[1]='3';} else
	if(i2==4){pls[1]='4';} else
	if(i2==5){pls[1]='5';} else
	if(i2==6){pls[1]='6';} else
	if(i2==7){pls[1]='7';} else
	if(i2==8){pls[1]='8';} else
	if(i2==9){pls[1]='9';} 
	
	pls[2]=0;
}

int toBCD(char *pSrc,char *pDest,int destLen)
{
	if(pSrc==NULL)
		return -1;
	int srcLen = strlen(pSrc);
	if(srcLen>=destLen *2)
		return -1;
	int i = srcLen ;
	int j = 0;
	while(1)
	{
	    i--;
	    pDest[j]=(pSrc[i]&0x0F) | (pSrc[i-1]<<4);
	    i--;
	    j++;
	    if(i==0)
	        break;
	}
	return 0;
}

void dleay1(void)
{long int i;
  i=yanshi*1667;
  while(i>0)
  {i--;}
}

void setrtime(void)
{
    uchar k;
    cls();
    moveto(1,1);putstr("���ý�����ʱ  ");
    moveto(3,1);putstr("********************");
    clsn(5,10);
    moveto(7,1);
    putstr("���������ʱ(����):");
    moveto(9,1);
    putstr(YANSHI);
    putstr("_");
    keyss(9,1,5,YANSHI,1);
    yanshi=stoi(5,YANSHI);
    EEROM_write(0x30,5,YANSHI);
    moveto(19,1);putstr("�����������...");
    key(0);return;
}

void keyss(unsigned int x,unsigned int y,unsigned int ws,unsigned char *mkey,unsigned int s)
{ int f,i,k,j,g;
	j=0;
	for(f=1;f<=ws;f++)
	{ //if(j==1){f=ww-1;}
jjj:		i=f-1;
		k=key(0);
		j++;
		if((k==0x88)&&(f==1)&&(s==1))
		{  mkey[0]='-';goto find12;
		}
		if((k<0x30||k>0x39)&&(!(k==0x2e)))
		if(k==0x8d)
		{	if(j==1)
		        {} else
			{	mkey[i]=0;
				for(g=i;g<ws;g++)
				{mkey[g]=0;}
			}
			break;
		}
		else
		if(k==0x82)//���
		{
			mkey[f]=0;
			if(f>1)
			{  moveto(x,i+y-1); putstr_h("_      ");
			}
			else
			{  moveto(x,i+y);putstr_h("_            ");
			}
			putstr_h("_      ");
			if(i<=1)
			{ f=0; }
			else if(i>1){f--;goto jjj;}
			goto find2;
		}
		else
		goto find21;
		mkey[i]=k;
find12:		moveto(x,i+y);
		putch_h(mkey[i]);
		if(j==1)
		{putstr_h("_         ");}
		else
		{putstr_h("_ ");}
		if(f==ws)
		{f--;}
find2:		moveto(9,9);                   
	}
find21:	moveto(9,9);                   
}

/*===============================================================================
����:	�Ӽ��̽���һ��ȫ�������ַ�,������,�����cdata 
����:	���: n1Ϊ����ʾ��ԭcdata�����ݵĳ���,n2Ϊ���������յ����ݳ���,regΪ0ʱֻ�ɽ�������,Ϊ1ʱ�ɽ�����ĸ,�������
����:	����: ���ؽ����ַ����ĳ���,�ַ���Ϊ��ʱ����0(��������ֵ�����ٰ����ܼ�,��ѹ��ܼ�ֵ�����cdata[2],�����ȾͰ��¹��ܼ�,��Ѹü�ֵ�����cdata[1]
===============================================================================*/
unsigned char ksh(uchar *cdata,  uchar n1,  uchar n2,  uchar reg)
{
	uchar x1,x2,y1,y2,k,i1,i2,f,end=0;
	i1=n1;
	x1=getx();
	y1=gety();
	if(n1!=0)
    	putn_h(n1,cdata);
	do
	{
		if(i1!=n2)
		{
			putch_h('_');
			x2=getx();
			y2=gety()-1;
		}
		else
		{
			x2=getx();
			y2=gety();
		}
		moveto(x2,y2);
ksh_1:	k=key(0);
		if(reg==0)
		{
			if(i1==n2&&k>=0x30&&k<=0x39)
				goto ksh_1;
			if(k<0x30||k>0x39&&k!=0x82)
				end=1;
		}
		if(reg==1)
		{
			if(k==0x80)
			goto ksh_1; 
			if(i1==n2&&!(k==0x8d||k==0x87||k==0x88||k==0x89||k==0x8e||k==0x8f||k==0x82||k==0x2b))
			goto ksh_1;
			if(k==0x8d||k==0x87||k==0x88||k==0x89||k==0x8e||k==0x8f||k==0x2b)
			end=1;
		}
		cdata[i1]=k;
		if(end)
		{
			f=0;
			if(i1==0)
			{
				cdata[0]=0;
				cdata[1]=k;
				moveto(x1,y1);
				putch_h(' ');
				moveto(x1,y1);
			}
			else
			{
				if(k==0x8d)
				{
					cdata[i1]=0;
					
					f=i1;
				}
				else
				{
					cdata[0]=0;
					cdata[1]=0;
					cdata[2]=k;
					moveto(x1,y1);
					for(i2=0;i2<=y2-y1;i2++)
					putch_h(' ');
				}
			}
			return(f);
		}
		if(k==0x82)
		{
			if(i1!=0)
			{
				putch_h(' ');
				i1=i1-1;
				y2=y2-1;
				moveto(x2,y2);
			}
		}
		else
		{
			putch_h(cdata[i1]);
			i1=i1+1;
		}
	}while(1);
}
