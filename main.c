/*===============================================================================
���Ⳮ����Գ���

	
===============================================================================*/
#include <hspos.h>


#define uchar unsigned char

//#define YANSHI 280000  /* ���ڴ����ʱ */
//#define RBAK ((int *)0x207FE00)//2050000)  /* ���ڴ������ʾ�ļ�¼�� */
#define DELAY_TIME 8500
#define DELAY_TIME2 1000
#define DELAY_TIME3 200

int datal;
int Iaddr[6];//���α��ַ�����ڳ���
int data[99];//������ݡ�
uchar Saddr[12];//�ַ������ַ�������û����롢��ʾ


void ir_11_data_07(uchar *dataflag);
void ir_14_data_07(int *dataflag);
void hwcb();
void inputaddr();
void char2int();
uchar ir_read_data_07();
void print_info();

 /*=================================================================================
 ����:	 ������
 ����:
 ����:
 =================================================================================*/
int main(void)
{
	 int r,rt;
	 uchar k;
	 
	 screen(1); 			 /* �趨Ϊ������ʾ״̬ */
	 while(1){	   
		 cls();moveto(15,14);  putstr("   ");
		 moveto(1, 3);		  putstr("������Գ���");
		 moveto(3, 1);	   putstr("====================");
		 moveto(6, 2);	   putstr("����Լ: ");
		 moveto(8, 2);	   putstr("[1] DLT645-1997");
		 moveto(10, 2);   putstr("[2] DLT645-2007");
		 moveto(16, 2);   putstr("[F2] �˳�");
		do { k=key(0);}while(k!=0x32&&k!=0x89);//��ʱȥ��97��Լ/while(k!=0x31&&k!=0x32&&k!=0x89); // �ж�����ļ�ֵ,������Ĳ���'1','2','3','4'��'F2'������ȴ�����
		switch(k){
			 //case '1':cbtype=1;break;
			 case '2':break;
			 case 0x89:return;
		} 
		while(1){	   
			cls();moveto(15,14);	putstr("   ");
			moveto(1, 3); 	   putstr("������Գ���");
			moveto(3, 1); 	putstr("====================");
			//moveto(6, 2);	 putstr("[1] ���ý�����ʱ");
			//moveto(8, 2); 	putstr("[2] Уʱ");
			moveto(10, 2);	 putstr("[3] ����");
			moveto(16, 2);   putstr("[F2] �˳�");
			do{k=key(0);
			}while(k!=0x33&&k!=0x89);//��ʱȥ����ʱ��Уʱ��while(k!=0x31&&k!=0x32&&k!=0x33&&k!=0x89); // �ж�����ļ�ֵ,������Ĳ���'1','2','3','4'��'F2'������ȴ�����
				switch(k){
				//case '1':setrtime();break;
				//case '2':if (cbtype == 1) crtime();else crtime1();break;
				case '3': hwcb();break;
				}
			 if (k == 0x89) break;
		}
	}
}
void hwcb(){
	int k=0;
	while(1){	   
		cls();moveto(15,14);	putstr("   ");
		moveto(1, 3); 	   putstr("������Գ���");
		moveto(3, 1); 	putstr("====================");
		//moveto(6, 2);	 putstr("[1] ��ȡ����ַ");
		moveto(10, 2);	 putstr("[3] �ֶ��������ַ");
		moveto(16, 2);   putstr("[F2] �˳�");
		do{k=key(0);
		}while(k!=0x33&&k!=0x89);//��ʱȥ����ʱ��Уʱ��while(k!=0x31&&k!=0x32&&k!=0x33&&k!=0x89); // �ж�����ļ�ֵ,������Ĳ���'1','2','3','4'��'F2'������ȴ�����
			switch(k){
			//case '1':setrtime();break;
			//case '2':if (cbtype == 1) crtime();else crtime1();break;
			case '3': inputaddr();break;
			}
		if (k == 0x89) break;
	}
}
/* =================================================================================
�������û��������ַ������12λ�Զ��ڸ�λ��0��������ȫ�ֱ��� Saddr[6]��
�貹д�ַ�����char 2 int����ת������

==================================================================================*/
void inputaddr(){
	uchar addr[12];;
	int b=11;
	int i, x;
	cls();moveto(15,14);	putstr("   ");
	moveto(1, 3); 	   putstr("���������ַ");
	moveto(10,2);
	keysn(Saddr,12);
	for(i=0;i!=12;i++){
		if (Saddr[i]==0x20||(Saddr[i]>0x2F&&Saddr[i]<0x3A)||Saddr[i]==0x41||Saddr[i]==0x61){
			continue;//print_info(i);
		}	
		else{
			cls();
			moveto(8,2); putstr("����ַ���Ϸ���");
			moveto(10,2); putstr("�����������..");
			do{x=key(0);}while(x==0);//�ȴ����������
			return;
		}
	}//�������Ϸ��ԣ����Ϸ���������
	for(i=5;i!=-1;i--){
		Iaddr[i]=0x00;//print_info(i);
	}//memset(Iaddr, 0x00,sizeof(Iaddr));

	i=11;
	//print_info(i);

	while (Saddr[i]==0x20){
	    i--;//print_info(i);
	}
	memset(addr,0,12);
	for(x=i;x>-1;x--){
	    addr[b]=Saddr[i];
	    b--;
		i--;
	}

	for (i = 5; i != -1; i--) {
		char2int(Iaddr,addr,i);//print_info(Iaddr[i]);print_info(addr[2*i+1]);
	}
	 //putchhex(Iaddr);
	// for(i=5;i!=-1;i--){
		// putchhex(Iaddr[i]);
	// }
	// do {
		// i=key(0);
	// } while (i != 0);
	uchar dataflag[4];
	dataflag[0]=0x00;dataflag[1]=0xff;dataflag[2]=0x01;dataflag[3]=0x00;
	ir_11_data_07(dataflag);
	ir_read_data_07();
}



/*===================================================================
������ת���ַ�����ĳ���ַ�Ϊ��������Īһ�ֽڡ�
��ڣ�add1���������飻add2���ַ�����

====================================================================*/
void char2int(int *add1,uchar *add2,int a){
	if (add2[a*2+1]=='1') {add1[a]=add1[a]+0x01;}
	if (add2[a*2+1]=='2') {add1[a]=add1[a]+0x02;}
	if (add2[a*2+1]=='3') {add1[a]=add1[a]+0x03;}
	if (add2[a*2+1]=='4') {add1[a]=add1[a]+0x04;}
	if (add2[a*2+1]=='5') {add1[a]=add1[a]+0x05;}
	if (add2[a*2+1]=='6') {add1[a]=add1[a]+0x06;}
	if (add2[a*2+1]=='7') {add1[a]=add1[a]+0x07;}
	if (add2[a*2+1]=='8') {add1[a]=add1[a]+0x08;}
	if (add2[a*2+1]=='9') {add1[a]=add1[a]+0x09;}
	if (add2[a*2+1]=='A'||add2[a*2+1]=='a') {add1[a]=add1[a]+0x0A;}
	if (add2[a*2+1]=='B'||add2[a*2+1]=='b') {add1[a]=add1[a]+0x0B;}
	if (add2[a*2+1]=='C'||add2[a*2+1]=='c') {add1[a]=add1[a]+0x0C;}
	if (add2[a*2+1]=='D'||add2[a*2+1]=='d') {add1[a]=add1[a]+0x0D;}
	if (add2[a*2+1]=='E'||add2[a*2+1]=='e') {add1[a]=add1[a]+0x0E;}
	if (add2[a*2+1]=='F'||add2[a*2+1]=='f') {add1[a]=add1[a]+0x0F;}

	if (add2[a*2]=='1') {add1[a]=add1[a]+0x10;}
	if (add2[a*2]=='2') {add1[a]=add1[a]+0x20;}
	if (add2[a*2]=='3') {add1[a]=add1[a]+0x30;}
	if (add2[a*2]=='4') {add1[a]=add1[a]+0x40;}
	if (add2[a*2]=='5') {add1[a]=add1[a]+0x50;}
	if (add2[a*2]=='6') {add1[a]=add1[a]+0x60;}
	if (add2[a*2]=='7') {add1[a]=add1[a]+0x70;}
	if (add2[a*2]=='8') {add1[a]=add1[a]+0x80;}
	if (add2[a*2]=='9') {add1[a]=add1[a]+0x90;}
	if (add2[a*2]=='A'||add2[a*2]=='a') {add1[a]=add1[a]+0xA0;}
	if (add2[a*2]=='B'||add2[a*2]=='b') {add1[a]=add1[a]+0xB0;}
	if (add2[a*2]=='C'||add2[a*2]=='c') {add1[a]=add1[a]+0xC0;}
	if (add2[a*2]=='D'||add2[a*2]=='d') {add1[a]=add1[a]+0xD0;}
	if (add2[a*2]=='E'||add2[a*2]=='e') {add1[a]=add1[a]+0xE0;}
	if (add2[a*2]=='F'||add2[a*2]=='f') {add1[a]=add1[a]+0xF0;}
}
/*=================================================================================
����:	��ӡ��Ϣ
�ȴ����̰��¼���ִ��
=================================================================================*/
void print_info(int i ){
	putchhex(i);

	do{
		i=key(0);
	}while(i==0);
}

/*=======================================================================
   ���� : ����07��Լ�����ܱ��ģ�datafalgΪ���ݱ�ʶ������ַΪȫ�ֱ���Saddr[6]
 =======================================================================*/
 void ir_11_data_07(uchar *dataflag)
 {	 
	long int cs;
	int i;
	ir_init(B1200,0x2B,UART_ON);
	//dleay1();
	cs=0x68+Iaddr[0]+Iaddr[1]+Iaddr[2]+Iaddr[3]+Iaddr[4]+Iaddr[5]+0x68+0x11+0x04+dataflag[0]+0x33+dataflag[1]+0x33+dataflag[2]+0x33+dataflag[3]+0x33;
	while(cs>256){
		cs=cs-256;
	}
	ir_write(0xFE);delay(DELAY_TIME3);
	ir_write(0xFE);delay(DELAY_TIME3);
	ir_write(0xFE);delay(DELAY_TIME3);
	ir_write(0xFE);delay(DELAY_TIME3);
	ir_write(0x68);delay(DELAY_TIME3);
	ir_write(Saddr[0]);delay(DELAY_TIME3);
	ir_write(Saddr[1]);delay(DELAY_TIME3);
	ir_write(Saddr[2]);delay(DELAY_TIME3);
	ir_write(Saddr[3]);delay(DELAY_TIME3);
	ir_write(Saddr[4]);delay(DELAY_TIME3);
	ir_write(Saddr[5]);delay(DELAY_TIME3);
	ir_write(0x68);delay(DELAY_TIME3);
	ir_write(0x11);delay(DELAY_TIME3);
	ir_write(0x04);delay(DELAY_TIME3);
	for (i=0; i<4; i++)
	{
		if(dataflag[i]+0x33>255)
		{ir_write(dataflag[i]+0x33-0x100);delay(DELAY_TIME3);}
		else{ir_write(dataflag[i]+0x33);delay(DELAY_TIME3);}
	}
	ir_write(cs);delay(DELAY_TIME3);
	ir_write(0x16);delay(400);
	i=cs;
	print_info(cs);
	}


 /*=======================================================================
	δ���� ����  ����07��Լд���ܱ��ģ�datafalgΪ���ݱ�ʶ������ַΪȫ�ֱ���Saddr[6]
    ����Ϊȫ�ֱ���data[99],���ݳ���Ϊȫ�ֱ���datal.ʹ��ǰdatal �����ò���ֵ
  =======================================================================*/
void ir_14_data_07(int *dataflag)
{
	long int cs=0;
	int i;
	ir_init(B1200,0x2B,UART_ON);//��ʼ�������
	//dleay1();
	cs=0x68+Saddr[0]+Saddr[i]+Saddr[2]+Saddr[3]+Saddr[4]+Saddr[5]+0x68+0x14+datal+4+dataflag[0]+0X33+dataflag[1]+0x33+dataflag[2]+0x33+dataflag[3]+0x33;//��ǰ����У��ͣ�
	for(i=0;i<datal;i++){
		cs=cs+data[i];
	}
	while(cs>256){
	 	cs=cs-256;
	}
	 ir_write(0xFE);delay(DELAY_TIME3);
	 ir_write(0xFE);delay(DELAY_TIME3);
	 ir_write(0xFE);delay(DELAY_TIME3);
	 ir_write(0xFE);delay(DELAY_TIME3);
	 ir_write(0x68);delay(DELAY_TIME3);
	 ir_write(Saddr[0]);delay(DELAY_TIME3);
	 ir_write(Saddr[i]);delay(DELAY_TIME3);
	 ir_write(Saddr[2]);delay(DELAY_TIME3);
	 ir_write(Saddr[3]);delay(DELAY_TIME3);
	 ir_write(Saddr[4]);delay(DELAY_TIME3);
	 ir_write(Saddr[5]);delay(DELAY_TIME3);
	 ir_write(0x68);delay(DELAY_TIME3);
	 ir_write(14);delay(DELAY_TIME3);
	 ir_write(datal+4);delay(DELAY_TIME3);
	 for (i=0; i<4; i++){
		 if(dataflag[i]>204)
		 {ir_write(dataflag[i]-205);delay(DELAY_TIME3);}
		 else{ir_write(dataflag[i]+0x33);delay(DELAY_TIME3);}//�������ݱ�ʾ+0X33�Ƿ����FF,��������ݱ�ʶΪ0XCC�����
	}
	 for (i=0;i<datal;i++){
	 	if(data[i]>204){
			ir_write(data[i]-205);delay(DELAY_TIME3);
		}
		else{
			ir_write(data[i]+0x33);delay(DELAY_TIME3);
		}
	}
	 ir_write(cs);delay(DELAY_TIME3);
	 ir_write(0x16);delay(400);
}
 /*==============================================================================
 
 �������07���ܱ����ݣ����ݳ��ȴ���ȫ�ֱ���datal�����ݴ���ȫ�ֱ���data[]��
 
 ==============================================================================*/
uchar ir_read_data_07(){
	 int xh=0,i=0,x=0,yanshi=0;
	 uchar k;
start:
//	cls();putstr("\n���ڽ���...");
	while (xh==0) {
		if(ir_rxstate()!=0){	  
			data[i]=ir_rxbuf();
			while(data[i]==0xfe){
				i++;
			}
			if((data[i]==0x68)&&(data[i+7]==0x68)){
				switch (data[i+8]){
					 case 0x91: break;
					 case 0x94: goto setseussful;
					 case 0xd1: goto havanotdata;
					 case 0xd4: goto setfail;
				 default: goto dataerro;
				}//��������
				 datal = data[i+9]-4;//������ݳ���
				 for(x=0;x<datal;x++){
					 data[x]=data[i+13];
				}
				goto end;//��������
			}
			else{
				goto dataerro;
			}
		}
		else{
			yanshi++;
			delayms(2);
		}
		if (yanshi>3500) {
			xh=1;
			print_info(yanshi);
		}
	}
timeout:
	cls();
	putstr("\n���յ���ĳ�ʱ");
	putstr("\n�Ƿ�����");
	putstr("\n1.����");
	putstr("\n2.(�س�)����");
	do{
		k=key(0);
	}while(){

	}
	while(key(0)==0){
		k=key(0);
		if(k=='1'){
			 goto end;
		}	 
		else if(k=='2'||k==0x8d){
		goto start;
		}
		goto timeout;
	}
dataerro:	 
	 cls();
	 putstr("\n���յ���ĳ���");
	 putstr("\n�Ƿ�����");
	 putstr("\n1.����");
	 putstr("\n2.(�س�)����");
 
	while(key(0)==0){
		k=key(0);
		if(k=='1'){
			 goto end;
		}	 
		else if(k=='2'||k==0x8d){
		goto start;
		}
		goto dataerro;
	}
setseussful:
	 cls();
	 putstr("\n���óɹ���");
	 putstr("\n�����������..");
	 while(key==0)
	 goto end;
	 
havanotdata:
	 cls();
	 putstr("\n�޴������");
	 putstr("\n�����������..");
	 while(key==0)
	 goto end;
 
setfail:
	 cls();
	 putstr("\n����ʧ�ܣ�");
	 putstr("\n�����������..");
	 while(key==0)
	 goto end;
end:
	 return;
}
/*=================================================================================
����:	����ͨѶ
����:	*pbsbmΪ���������ݱ�ʶ(ͨ�Ź�Լ),*data��Ŷ�������,*resuΪ����ͨѶ�Ƿ�ɹ���־,psxhΪ�ض����ʱ��ʾ���ڶ�ȡ����Ŀ
����:
=================================================================================*/
//void rece4(uchar *pbsbm,uchar *data,uchar *resu,int r)
//{	
//	uchar  i,xh,rt,err,ls[10],k;
// 	long int byanshi,l,j,j1,cs;
// 	err=0;
//stat:   
//	memset(data,0,sizeof(data));
//	xh=0;
//	i=0;
//	rt=0;
//	byanshi=1;
//	l=50;

//	// �����
//	send_read_write_data_07(pbsbm);
//	//cls();
//        while(xh==0)
//	{
//		if (com_tsbz==0)
//		{  
//		    if(ir_rxstate()!=0)                                                                                                                        
//		   {   
//		       data[i]=ir_rxbuf();
//			//putchhex(data[i]);
//		   	if(rt<2)
//		   	{
//		   		if((data[i]==0xfe)&&(rt==0))
//		   		{rt=1;}
//		   		if((data[i]==0x68)&&(rt==1))
//		   		{rt=2;
//		   		i=0;
//		   		data[i]=0x68;
//		   		byanshi=0;
//		   		}
//		   		if(rt!=0&&i>=15+l)  {xh=1;} //15
		   		 
//		   	}
//		   	else
//		   	{
//           			if(i==9){l=data[9];if(l>70){l=0;}}
//		   		if(i==11+l)//11
//		   		{xh=1;}
//		   	}
//		   	i++; 
//		  }else
//		   {	byanshi++;
//		   	if(byanshi>35000)
//		   	{xh=1;}
//		  }
//		}
//		else
//		{
//		    if(comstate()!=0)                                                                                                                        
//		  {   
//		        data[i]=combuf();
//		   	if(rt<2)
//		   	{
//		   		if((data[i]==0xfe)&&(rt==0))
//		   		{rt=1;}
//		   		if((data[i]==0x68)&&(rt==1))
//		   		{rt=2;
//		   		i=0;
//		   		data[i]=0x68;
//		   		byanshi=0;
//		   		}
//		   		if(rt!=0&&i>=15+l)  {xh=1;} //15
		   		
//		   	}
//		   	else
//		   	{
//           			if(i==9){l=data[9];if(l>70){l=0;}}
//		   		if(i==11+l)//11
//		   		{xh=1;}
//		   	}
//		   	i++;
//		  }else
//		   {	byanshi++;
//		   	if(byanshi>35000)
//		   	{xh=1;}
//		  }
//		}
//	}

//	cs=0;
//	l=data[9];
//	if(l>70){l=0;}
//	for(j=0;j<=9+l;j++)
//	{	cs=cs+data[j];
//	}
//	while(cs>256)
//	{cs=cs-256;}
       
//	if((data[10+l]==cs)&&(data[8]==0x91))
//		{
//		resu[0]='9';resu[1]=0;
//		}
//	else
//		{
//		resu[0]='0';resu[1]=0;
//		l=i;
//		memset(ls, 0, sizeof(ls));
//		libset(r,DBH);libwrite(ls);
//		libset(r,ZDL);libwrite(ls);
//		cls();moveto(15,14);putstr("   ");moveto(3,2);putstr("��ȡ����ʧ��");
//		moveto(5,1);for (i=0;i<l;i++){putchhex(data[i]);putstr(" ");}
//		key(0);
//		}



 /*===============================================================================
����:	�Ӽ��̽���һ��ȫ�������ַ�,������,�����cdata 
����:	���: n1Ϊ����ʾ��ԭcdata�����ݵĳ���,n2Ϊ���������յ����ݳ���,regΪ0ʱֻ�ɽ�������,Ϊ1ʱ�ɽ�����ĸ,�������
����:	����: ���ؽ����ַ����ĳ���,�ַ���Ϊ��ʱ����0(��������ֵ�����ٰ����ܼ�,��ѹ��ܼ�ֵ�����cdata[2],�����ȾͰ��¹��ܼ�,��Ѹü�ֵ�����cdata[1]
===============================================================================*/
// unsigned char ksh(uchar *cdata,  uchar n1,  uchar n2,	uchar reg)
// {
//	 uchar x1,x2,y1,y2,k,i1,i2,f,end=0;
//	 i1=n1;
//	 x1=getx();//��ȡ���λ��x
//	 y1=gety();//��ȡ���λ��y
//	 if(n1!=0)
//		 putn_h(n1,cdata);
//	 do
//	 {
//		 if(i1!=n2)
//		 {
//			 putch_h('_');
//			 x2=getx();
//			 y2=gety()-1;
//		}
//		 else
//		 {
//			 x2=getx();
//			 y2=gety();
//		}
//		 moveto(x2,y2);
// ksh_1:  k=key(0);
//		 if(reg==0)
//		 {
//			 if(i1==n2&&k>=0x30&&k<=0x39)
//				 goto ksh_1;
//			 if(k<0x30||k>0x39&&k!=0x82)
//				 end=1;
//		}
//		 if(reg==1)
//		 {
//			 if(k==0x80)
//			 goto ksh_1; 
//			 if(i1==n2&&!(k==0x8d||k==0x87||k==0x88||k==0x89||k==0x8e||k==0x8f||k==0x82||k==0x2b))
//			 goto ksh_1;
//			 if(k==0x8d||k==0x87||k==0x88||k==0x89||k==0x8e||k==0x8f||k==0x2b)
//			 end=1;
//		}
//		 cdata[i1]=k;
//		 if(end)
//		 {
//			 f=0;
//			 if(i1==0)
//			 {
//				 cdata[0]=0;
//				 cdata[1]=k;
//				 moveto(x1,y1);
//				 putch_h(' ');
//				 moveto(x1,y1);
//			}
//			 else
//			 {
//				 if(k==0x8d)
//				 {
//					 cdata[i1]=0;
					 
//					 f=i1;
//				}
//				 else
//				 {
//					 cdata[0]=0;
//					 cdata[1]=0;
//					 cdata[2]=k;
//					 moveto(x1,y1);
//					 for(i2=0;i2<=y2-y1;i2++)
//					 putch_h(' ');
//				}
//			}
//			 return(f);
//		}
//		 if(k==0x82)
//		 {
//			 if(i1!=0)
//			 {
//				 putch_h(' ');
//				 i1=i1-1;
//				 y2=y2-1;
//				 moveto(x2,y2);
//			}
//		}
//		 else
//		 {
//			 putch_h(cdata[i1]);
//			 i1=i1+1;
//		}
//	}while(1);
//}

 
//void dleay1(void){
//	long int i;
//	i=yanshi*1667;
//	while(i>0)
//	{i--;}
//}
