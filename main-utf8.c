/*/*===============================================================================
  红外抄表程序


===============================================================================*/
#include <hspos.h>


#define uchar unsigned char

#define timeout 100000
#define DELAY_TIME 8500
#define DELAY_TIME2 1000
#define DELAY_TIME3 200

int datal;
int k;//存放按键数据.为了防止按F2一退到顶级菜单问题，退出次级菜单前清空K
int Iaddr[6];//整形表地址，用于抄表
int data[99];//存放数据。
int datacount;
uchar Saddr[12];//字符，表地址，用于接收键盘输入的表地址，以及显示。


void ir_11_data_07(int *dataflag);
void ir_14_data_07(int *dataflag);
void inputaddr();
void char2int();
int ir_read_data_07();
void print_info();
void cb();
void zxyg();
void rdjdn();
void rdjsj();
void zxyg();
void sdsr();
void irtest();
void irreadtest();
void readaddr();
 /*=================================================================================
 函数:	 主程序
 参数:
 返回:
 =================================================================================*/
int main(void){
	screen(1); /* 设定为汉字显示状态 */
start:
	while(1){
		cls();moveto(15,14);  putstr("   ");
		moveto(1, 3);		  putstr("红外测试程序");
		moveto(3, 1);	   putstr("====================");
		moveto(6, 2);	   putstr("电表规约: ");
		moveto(8, 2);	   putstr("[1] irtest");
		moveto(10, 2);   putstr("[2] DLT645-2007");
		moveto(12, 2);   putstr("[3] ir_rx");
		moveto(16, 2);   putstr("[F2] 退出");
		do { k=key(0);}while(k!=0x31&&k!=0x32&&k!=0x33&&k!=0x89);//暂时去掉97规约/while(k!=0x31&&k!=0x32&&k!=0x89); // 判断输入的键值,若输入的不是'1','2','3','4'或'F2'则继续等待输入
		switch(k){
			 case '1':irtest();goto start;
			 case '2':break;
			 case '3':irreadtest();goto start;
			 case 0x89:return;
		}

		while(1){
			cls();moveto(15,14);	putstr("   ");
			moveto(1, 4); 	   putstr("红外测试程序");
			moveto(3, 1); 	putstr("====================");
			moveto(6, 1);	 putstr("[1] 自动读取电表地址");
			moveto(8, 1);	 putstr("[2] 手动输入电表地址");
			moveto(12, 1);   putstr("[F2] 退出");
			do{k=key(0);}while(k!=0x31&&k!=0x32&&k!=0x89); // 判断输入的键值,若输入的不是'1','2','3','4'或'F2'则继续等待输入
			switch(k){
				case '1': readaddr();break;
				case '2': inputaddr();break;
			}
			if (k == 0x89) break;
		}
	}
}

void readaddr(){
	ir_init(B1200,0x2B,UART_ON);
	ir_write(0xFE);delay(DELAY_TIME3);
	ir_write(0xFE);delay(DELAY_TIME3);
	ir_write(0xFE);delay(DELAY_TIME3);
	ir_write(0xFE);delay(DELAY_TIME3);
	ir_write(0x68);delay(DELAY_TIME3);
	ir_write(0xAA);delay(DELAY_TIME3);
	ir_write(0xAA);delay(DELAY_TIME3);
	ir_write(0xAA);delay(DELAY_TIME3);
	ir_write(0xAA);delay(DELAY_TIME3);
	ir_write(0xAA);delay(DELAY_TIME3);
	ir_write(0xAA);delay(DELAY_TIME3);
	ir_write(0x68);delay(DELAY_TIME3);
	ir_write(0x13);delay(DELAY_TIME3);
	ir_write(0x00);delay(DELAY_TIME3);
	ir_write(0xDF);delay(DELAY_TIME3);
	ir_write(0x16);delay(400);

	int xh=0,i=0,x=0,yanshi=0;

	cls();moveto(6,3);putstr("\n正在接收...");
	datacount = 0;
	while(yanshi<timeout){
		if(ir_rxstate()!=0){
			data[datacount]=ir_rxbuf();
			datacount++;
			yanshi=0;
		}else{
			yanshi++;
			continue;
		}
	}
	if (datacount==0){
		cls();
		moveto(6,5);putstr("接收超时！");
		do{k=key(0);}while(k==0);
		return;
	}
	while(data[i]!=0x68){
		i++;
	}
	if((data[i]==0x68)&&(data[i+7]==0x68)){
		switch (data[i+8]){
			 case 0x93: break;
		default: cls();moveto(6,5);putstr("接收错误！");do{k=key(0);}while(k==0); return;
		}//检查控制字
		cls();
		moveto(2,3);putstr("电表地址：");
		moveto(3,2);
		for(x=5;x!=-1;x--){
			Iaddr[x]=data[i+6-x];//print_info(data[x]);
		}
		for(x=0;x!=6;x++){
			putchhex(Iaddr[x]);
		}

	do{k=key(0);}while(k==0);cb();
	}else{
		cls();moveto(6,5);putstr("接收错误！");do{k=key(0);}while(k==0); return;
	}
}



/* =================================================================================
函数：用户输入电表地址，不足12位自动在高位补0，并存入全局变量 Saddr[6]中
需补写字符数组char 2 int数组转换函数

==================================================================================*/
void inputaddr(){
	uchar addr[12];;
	int b=11;
	int i, x;
	cls();
	moveto(3, 4); 	   putstr("请输入电表地址");
	moveto(10,4);
	keysn(Saddr,12);
	for(i=0;i!=12;i++){
		if (Saddr[i]==0x20||(Saddr[i]>0x2F&&Saddr[i]<0x3A)||Saddr[i]==0x41||Saddr[i]==0x61){
			continue;//print_info(i);
		}
		else{
			cls();
			moveto(8,4); putstr("电表地址不合法！");
			moveto(10,4); putstr("按任意键继续..");
			do{x=key(0);}while(x==0);//等待任意键按下
			return;
		}
	}//检查输入合法性，不合法跳出函数
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
	cb();
}

/*===========================================================================
 * 红外抄表程序
 * =========================================================================*/
void cb(){
	int i=1;
	while (i) {
		cls();
		moveto(5, 1);
		putstr("[1] 当前正有电能");
		moveto(7, 1);
		putstr("[2] 上一次日冻结时间");
		moveto(9, 1);
		putstr("[3] 上一次日冻结电能");
		moveto(11, 1);
		putstr("[4] 手动输入数据项");
		moveto(16, 1);
		putstr("[F2] 退出");
		do {
			k = key(0);
		} while (k != 0x31 && k != 0x32 && k != 0x33 && k != 0x34 && k != 0x89); // 判断输入的键值,若输入的不是'1','2','3','4'或'F2'则继续等待输入
			switch(k){
			case '1': zxyg();break;
			case '2': rdjsj();break;
			case '3': rdjdn();break;
			case '4': sdsr();break;
			case 0x89: i=0;break;
			}
	}k=0;//清空K，防止到上级菜单K为0X89继续退出。
}



void zxyg(){
	int flag[4];
	int i;
	flag[0]=0x00;
	flag[1]=0x01;
	flag[2]=0xFF;
	flag[3]=0x00;
	ir_11_data_07(flag);
	i=ir_read_data_07();
	switch(i){
	case 0: cls();moveto(3,3);putstr("抄读成功");moveto(6,2);putchhex(data[3]-0x33);putchhex(data[2]-0x33);putchhex(data[1]-0x33);putstr(".");putchhex(data[0]-0x33);putstr("kWh");do{
		i=key(0);
	}while(i==0);break;
	case 4: cls();moveto(9,5);putstr("接收错误！") ;moveto(5,1);for(i=0;i!=35;i++){putchhex(data[i]);}do{i=key(0);}while(1==0);break;
	case 5: cls();moveto(9,5);putstr("接收超时！");do{i=key(0);}while(1==0);break;
	default: cls();putchhex(i);moveto(5,1);for(i=0;i!=datacount;i++){putchhex(data[datacount]);}do{i=key(0);}while(1==0);break;
	}

}
void rdjsj(){
	int flag[4];
	int i;
	flag[0]=0x05;
	flag[1]=0x06;
	flag[2]=0x00;
	flag[3]=0x01;
	ir_11_data_07(flag);
	i=ir_read_data_07();
	switch(i){
	case 0: cls();moveto(3,3);putstr("抄读成功");moveto(6,2);putchhex(data[4]-0x33);putstr("年");putchhex(data[3]-0x33);putstr("月");putchhex(data[2]-0x33);putstr("日");putchhex(data[1]-0x33);putstr("时");putchhex(data[0]-0x33);putstr("分");do{i=key(0);}while(i==0);break;
	case 4: cls();moveto(9,5);putstr("接收错误！") ;moveto(5,1);for(i=0;i!=35;i++){putchhex(data[i]);}do{i=key(0);}while(1==0);break;
	case 5: cls();moveto(9,5);putstr("接收超时！");do{i=key(0);}while(1==0);break;
	default: cls();putchhex(i);moveto(5,1);for(i=0;i!=datacount;i++){putchhex(data[datacount]);}do{i=key(0);}while(1==0);break;
	}
}


void rdjdn(){
	int flag[4];
		int i;
		flag[0]=0x05;
		flag[1]=0x06;
		flag[2]=0x01;
		flag[3]=0x01;
		ir_11_data_07(flag);
		i=ir_read_data_07();
		switch(i){
		case 0: cls();moveto(3,3);putstr("抄读成功");moveto(6,2);putchhex(data[3]-0x33);putchhex(data[2]-0x33);putchhex(data[1]-0x33);putstr(".");putchhex(data[0]-0x33);putstr("kWh");do{i=key(0);}while(i==0);break;
		case 4: cls();moveto(9,5);putstr("接收错误！") ;moveto(5,1);for(i=0;i!=35;i++){putchhex(data[i]);}do{i=key(0);}while(1==0);break;
		case 5: cls();moveto(9,5);putstr("接收超时！");do{i=key(0);}while(1==0);break;
		default: cls();putchhex(i);moveto(5,1);for(i=0;i!=datacount;i++){putchhex(data[datacount]);}do{i=key(0);}while(1==0);break;
		}
}
void sdsr(){
	int flag[4];
	uchar sflag[8];
	int i;
	cls();
	moveto(6, 4);putstr("请输入数据项");
	moveto(10,6);
	keysn(sflag,8);
	for(i=0;i!=8;i++){
		if ((sflag[i]>0x2F&&sflag[i]<0x3A)||(sflag[i]>0x3D&&sflag[i]<0x47)||(sflag[i]>0x60&&sflag[i]<0x67)){
			continue;//print_info(i);
		}
		else{
			cls();
			moveto(8,2); putstr("数据项不合法！");
			moveto(10,2); putstr("按任意键继续..");
			do{k=key(0);}while(k==0);//等待任意键按下
			return;
		}
	}//检查输入合法性，不合法跳出函数
	//这玩意怎么用？改flag为uchar都不对。。memset(flag,0,sizeof(flag));
	for(i=0;i!=4;i++){
		flag[i]=0;
	}
	for (i = 0; i != 4; i++) {
		char2int(flag,sflag,i);//print_info(flag[i]);print_info(sflag[2*i+1]);print_info(sflag[2*i]);
		}
	ir_11_data_07(flag);
	i=ir_read_data_07();
	switch(i){
	case 0: cls();moveto(3,3);putstr("抄读成功！");moveto(4,2);for(i=0;i!=datal;i++){putchhex(data[i]-0x33);}do{i=key(0);}while(i==0);break;
	//case 2: cls();moveto(2,2);putstr("无此数据项！");do{i=key(0);}while(i==0);break;
	case 4: cls();moveto(9,5);putstr("接收错误！") ;moveto(5,1);for(i=0;i!=35;i++){putchhex(data[i]);}do{i=key(0);}while(1==0);break;
	case 5: cls();moveto(9,5);putstr("接收超时！");do{i=key(0);}while(1==0);break;
	default: cls();putstr("错误代码：");putchhex(i);moveto(3,1);for(i=0;i!=datacount;i++){putchhex(data[datacount]);}do{i=key(0);}while(1==0);break;
	}
}



/*===================================================================
函数：转换字符数组某两字符为整型数组莫一字节。
入口：add1，整型数组；add2，字符数组

====================================================================*/
void char2int(int *add1,uchar *add2,int a){
	if (add2[a*2+1]=='0') {add1[a]=add1[a]+0x00;}
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

	if (add2[a*2]=='0') {add1[a]=add1[a]+0x00;}
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
函数:	打印信息
等待键盘按下继续执行
=================================================================================*/
void print_info(int i ){
	putchhex(i);

	do{
		i=key(0);
	}while(i==0);
}

/*=======================================================================
   函数 : 发送07规约读电能表报文，datafalg为数据标识。电表地址为全局变量Saddr[6]
 =======================================================================*/
 void ir_11_data_07(int *dataflag)
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
	ir_write(Iaddr[5]);delay(DELAY_TIME3);
	ir_write(Iaddr[4]);delay(DELAY_TIME3);
	ir_write(Iaddr[3]);delay(DELAY_TIME3);
	ir_write(Iaddr[2]);delay(DELAY_TIME3);
	ir_write(Iaddr[1]);delay(DELAY_TIME3);
	ir_write(Iaddr[0]);delay(DELAY_TIME3);
	ir_write(0x68);delay(DELAY_TIME3);
	ir_write(0x11);delay(DELAY_TIME3);
	ir_write(0x04);delay(DELAY_TIME3);
	for (i=3; i!=-1; i--)
	{
		if(dataflag[i]+0x33>255)
		{ir_write(dataflag[i]+0x33-0x100);delay(DELAY_TIME3);}
		else{ir_write(dataflag[i]+0x33);delay(DELAY_TIME3);}
	}
	ir_write(cs);delay(DELAY_TIME3);
	ir_write(0x16);delay(400);
}


 /*=======================================================================
	未完善 函数  发送07规约写电能表报文，datafalg为数据标�
��。电表地址为全局变量Saddr[6]
    数据为全局变量data[99],数据长度为全局变量datal.使用前datal 因计算好并赋值
  =======================================================================*/
void ir_14_data_07(int *dataflag)
{
	long int cs=0;
	int i;
	ir_init(B1200,0x2B,UART_ON);//初始化红外口
	//dleay1();
	cs=0x68+Saddr[0]+Saddr[i]+Saddr[2]+Saddr[3]+Saddr[4]+Saddr[5]+0x68+0x14+datal+4+dataflag[0]+0X33+dataflag[1]+0x33+dataflag[2]+0x33+dataflag[3]+0x33;//提前计算校验和；
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
	 ir_write(Saddr[1]);delay(DELAY_TIME3);
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
		 else{ir_write(dataflag[i]+0x33);delay(DELAY_TIME3);}//计算数据表示+0X33是否大于FF,因测试数据标识为0XCC的情况
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

 红外接收07电能表数据，数据长度存于全局变量datal，数据存于全局变量data[]。
 返回抄读结果标识：0，抄读成功；1设置成功；2无此数据项；3设置失败；4接收数据错误；5接收超时

 ==============================================================================*/
int ir_read_data_07(){
	int xh=0,i=0,x=0,yanshi=0;

	cls();putstr("\n正在接收...");
	datacount = 0;
	while(xh==0){
		if(ir_rxstate()!=0){   
			data[datacount]=ir_rxbuf();
			datacount++;
			yanshi=0;
		}
		else{
			yanshi++;
			if(yanshi>timeout)xh=1;//延长时间为10万
			continue;
		}
	}
	if (datacount==0){
		return 5;
	}
	while(data[i]==0xfe||data[i]==0x00){
		i++;
	}
	if((data[i]==0x68)&&(data[i+7]==0x68)){
		switch (data[i+8]){
			 case 0x91: break;
			 case 0x94: return 1;
			 case 0xd1: return 2;
			 case 0xd4: return 3;
		 default: return 4;
		}//检查控制字
		datal = data[i+9]-4;//print_info(data[i+9]);print_info(datal);//检查数据长度
		for(x=0;x!=datal;x++){
			data[x]=data[i+14+x];//print_info(data[x]);
		}
		return  0;//返回数据
	}else{
		return 4;
	}
}


void irtest(){
	//v+ A535FA  V- A535FA CH+ A935FE CH- A935FD

	while(1){
		 cls();
		 moveto(6, 2);	   putstr("[1] vol+ ");
		 moveto(8, 2);	   putstr("[2] vol-");
		 moveto(10, 2);   putstr("[3] ch+");
		 moveto(12, 2);   putstr("[4] ch-");
		 moveto(16, 2);   putstr("[F2] 退出");
		do { k=key(0);}while(k!=0x34&&k!=0x31&&k!=0x33&&k!=0x32&&k!=0x89);
		switch(k){
			 case '1':ir_init(B1200,0x2B,UART_ON);ir_write(0xA5);delay(DELAY_TIME3);ir_write(0x35);delay(DELAY_TIME3);ir_write(0xFA);delay(DELAY_TIME3);break;
			 case '2':ir_init(B1200,0x2B,UART_ON);ir_write(0xFE);delay(DELAY_TIME3);ir_write(0xFE);delay(DELAY_TIME3);ir_write(0xFE);delay(DELAY_TIME3);break;
			 case '3':ir_init(B1200,0x2B,UART_ON);ir_write(0xFE);delay(DELAY_TIME3);ir_write(0xFE);delay(DELAY_TIME3);ir_write(0xFE);delay(DELAY_TIME3);break;
			 case '4':ir_init(B1200,0x2B,UART_ON);ir_write(0xFE);delay(DELAY_TIME3);ir_write(0xFE);delay(DELAY_TIME3);ir_write(0xFE);delay(DELAY_TIME3);break;
			 case 0x89:return;
		}
	}
}

void irreadtest(){
	int irdata,yanshi=0;
	cls();
	putstr("按任意键开始接收...");
	moveto(3,2);
	do{k=key(0);}while(k==0);
	cls();putstr("接收报文：");
	ir_init(B1200,0x2B,UART_ON);

	while(yanshi<200000){
		if(ir_rxstate()!=0){
			irdata=ir_rxbuf();
			putchhex(irdata);
			yanshi=0;
		}
		else{
			yanshi++;
			continue;
		}
	}
	do{k=key(0);}while(k==0);
}
/*=================================================================================
函数:	红外通讯
参数:	*pbsbm为电能量数据标识(通信规约),*data存放读出数据,*resu为红外通讯是否成功标志,psxh为重读书据时显示正在读取的条目
返回:
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

//	// 读表号
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
//		cls();moveto(15,14);putstr("   ");moveto(3,2);putstr("读取电表号失败");
//		moveto(5,1);for (i=0;i<l;i++){putchhex(data[i]);putstr(" ");}
//		key(0);
//		}



 /*===============================================================================
函数:	从键盘接收一串全高数字字符,带回显,存放在cdata
参数:	入口: n1为欲显示的原cdata中数据的长度,n2为最多允许接收的数据长度,reg为0时只可接收数字,为1时可接收字母,运算符等
返回:	出口: 返回接收字符串的长度,字符串为空时返回0(若按下数值键后再按功能键,则把功能键值存放在cdata[2],若首先就按下功能键,则把该键值存放在cdata[1]
===============================================================================*/
// unsigned char ksh(uchar *cdata,  uchar n1,  uchar n2,	uchar reg)
// {
//	 uchar x1,x2,y1,y2,k,i1,i2,f,end=0;
//	 i1=n1;
//	 x1=getx();//获取光标位置x
//	 y1=gety();//获取光标位置y
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
