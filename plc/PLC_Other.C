;/****************************************Copyright (C)**************************************************
;**                               	Email:luheding@126.com
;**                                 QQ:614090042                                            
;**                          如有意见或不明可联系,但要注明来意.否则不回                                 
;**--------------文件信息--------------------------------------------------------------------------------
;**文   件   名: PLC_Other.c
;**版        本: V2.1
;**创   建   人: LuHeDing
;**最后修改日期: 2010年05月08日
;**描        述: PLC其它程序集合
;** 
;********************************************************************************************************/

#include "PLC_PUBLIC.H"

#define  X_DIY	2 //滤波时间
extern uint32_t    PLC_1MS_BIT;					//PLC 1MS???(??????????)

uint8_t X_FilterDiy[256];
uint32_t X_FilterData,X1_FilterData,X2_FilterData,X3_FilterData,X4_FilterData,X5_FilterData,X6_FilterData,X7_FilterData;

/***********************************************
  函数功能：PLC代码错误处理程序
  err_id=01:指令出错(未识别指令)
  err_id=02:指令出错(暂不支持指令)

  err_id=10:数据出错(无法识别数据类型)
  err_id=11:数据出错(数据读取地址超出)
  err_id=12:数据出错(变址Z地址未知)
  err_id=13:数据出错(变址Z地址超出)
  err_id=20:CJ指令地址出错
  D8061,M8061=PC硬件错误
  D8063,M8063=链接,通信错误
  D8064,M8064=参数错误
  D8065,M8065=语法错误
  D8066,M8066=回路错误
  D8067,M8067=运算错误
  D8068,M8068=运算错误锁存
***********************************************/

void PLC_PROG_ERROR(uint16 err_id)
{
	PLC_BIT_ON(M8067);//出错标志 
	D8010=0;	  //扫描时间
	if (D8068==0)D8065=err_id;//语法错误
	if (D8068==0)D8068=(PLC_PC-PLC_PROG_START_ADD2)/2;//保存出错PC步
	D8069=D8068;
	PLC_RUN_BIT = 6;//PLC运行标志进入出错
	PLC_BIT_OFF(M8000);	 //关闭M8000
	PLC_PC=PLC_PROG_END_ADD;//结束程序运行
	debug_send("PLC_PROG_ERROR\r\n");
}

/***********************************************
  函数功能：PLC通信错误处理程序
  D8063,M8063=链接,通信错误
  0000=无异常;
  6301=奇偶检验错误
  6302=通信字符错误
  6303=通信和校验出错
  6304=数据格式错误
  6305=指令错误
***********************************************/

void PLC_COMM_ERROR(uint16 err_id)
{
if(err_id!=0)PLC_BIT_ON(M8063);//出错标志 
D8063=err_id;
}


/***********************************************
  函数功能：复制数据
***********************************************/

/*void PLC_R_COPY(uint32 C_add_s,uint32 C_add_e,uint32 P_add_s)
{uint32 count=0;
 C_add_e+=1;
 for(;C_add_e>C_add_s;C_add_s++)
 	{PLC_RAM8(P_add_s+count)=PLC_RAM8(C_add_s);count++;}
} */
 


/***********************************************
  函数功能：保存旧线圈值 SXMTCY
***********************************************/

void PLC_O_BIT_KEEP(void)
{
	uint32 S_Add,S_Add2,E_Add;
 	S_Add=PLC_R_START_ADD+0x0400;
	E_Add=PLC_R_START_ADD+0x05FF;
	S_Add2=PLC_R_START_ADD+0x0600;
	for(;S_Add<=E_Add;)
	{
		PLC_RAM32(S_Add2)=PLC_RAM32(S_Add);
		S_Add+=4;S_Add2+=4;
	}//0x0400-0x05FF->0x0600-0x07FF
 	S_Add=PLC_R_START_ADD;
	E_Add=PLC_R_START_ADD+0x01FF;
	S_Add2=PLC_R_START_ADD+0x0400;
	for(;S_Add<=E_Add;)
	{
		PLC_RAM32(S_Add2)=PLC_RAM32(S_Add);
		S_Add+=4;S_Add2+=4;
	}//0x0000-0x01FF->0x0400-0x05FF

	S_Add=PLC_R_START_ADD + 0x58E0;
	E_Add=PLC_R_START_ADD + 0x599F;
	S_Add2=PLC_R_START_ADD+0x59A0;
	for(;S_Add<=E_Add;)
	{
		PLC_RAM32(S_Add2)=PLC_RAM32(S_Add);
		S_Add+=4;S_Add2+=4;
	}
	S_Add=PLC_R_START_ADD + 0x5820;
	E_Add=PLC_R_START_ADD + 0x58DF;
	S_Add2=PLC_R_START_ADD+0x58E0;
	for(;S_Add<=E_Add;)
	{
		PLC_RAM32(S_Add2)=PLC_RAM32(S_Add);
		S_Add+=4;S_Add2+=4;
	}	
}

/***********************************************
  函数功能：计时
  T000-T199 100Ms T200-T245 10Ms
  T246-T249 1Ms	  T250-T255 100Ms(保持)
***********************************************/
uint8 PLC_T_TIME;
void PLC_T_COUNT(void)
{
	uint16 count,count2;
	uint32 TimeAdd;
	PLC_T_TIME++;
	if(PLC_T_TIME%10==0)
	{
		count=200;
		count2=249;
		TimeAdd=PLC_T_START_ADD+400;
	}  //跳过T000-T199&T250-T255
	else
	{
		count=246;
		count2=249;
		TimeAdd=PLC_T_START_ADD+492;
	}//跳过T000-T245&T250-T255
	if(PLC_T_TIME>=100)
	{
		PLC_T_TIME=0;
		count=0;
		count2=255;
		TimeAdd=PLC_T_START_ADD;
	}//全部执行
	for(;count<=count2;count++)
	{
		if(PLC_T_C_BIT_TEST(count)&&	   //测试线圈
		   PLC_T_OUT_BIT_TEST(count)==0&&  //测试输出
		   PLC_T_RST_TEST(count)==0)	   //测试复位标志
		{
			PLC_RAM16(TimeAdd)++;
		}
		TimeAdd+=2;  
	}
}

/***********************************************
  函数功能：结束指令后处理的程序
***********************************************/

void PLC_END_PROG(void)
{
	PLC_PC=PLC_PROG_END_ADD;//初始PC指针
	PLC_O_BIT_KEEP();	 //保存旧线圈值 SXMTCY
	PLC_X_Filter();
	PLC_IO_BREAK();	 //输出刷新
	PLC_BIT_OFF(M8002);
	PLC_BIT_ON(M8003);

	wdt_clear();
	

	
	D8010=PLC_RUN_TIME; //保存扫描时间
	if(PLC_RUN_TIME<D8011)
		D8011=PLC_RUN_TIME;
	if(PLC_RUN_TIME>D8012)
		D8012=PLC_RUN_TIME;
	PLC_RUN_TIME=0;	 //清除扫描时间
	debug_send("扫描时间=%d\r\n",D8012);
}


/***********************************************
  函数功能：STOP_RUN前数据复位
  0x0000-0x009F	S X不复位
  0x00A0-0x012F	Y0-Y177 T0-T255(C) M0-M383
  0x01C0-0x17CF C0-C255(C) M8000-M8255 O_BIT D0-D999
  0x4E80-0x5B8F;空出部分
  0x5B90-0x5FFF;监视部分不复位
***********************************************/

void PLC_RESET_RAM(void)
{
	uint32 S_Add,E_Add;
	 H_Y0_Y1_STOP();
	 S_Add=PLC_R_START_ADD+0x00A0;E_Add=PLC_R_START_ADD+0x01FF;
	 for(;S_Add<=E_Add;){PLC_RAM8(S_Add)=0;S_Add++;}//0x00A0-0x01BF
	 
	 S_Add=PLC_R_START_ADD+0x1000;E_Add=PLC_R_START_ADD+0x4E7F;	
 	for(;S_Add<=E_Add;){PLC_RAM8(S_Add)=0;S_Add++;}//0x01C0-0x118F

	PLC_BIT_ON(M8018);
	 PLC_1MS_BIT=0;
	 PLC_RUN_BIT=0;	 
	PLC_RUN_TIME=0;
 	 PLC_PC=PLC_PROG_START_ADD2;  //初始化PLC程序指针
 	H_Y0_Y1_STOP();
}

void PLC_X_Filter(void)
{
	if(X0){if(X_FilterDiy[0x00]<X_DIY){X_FilterDiy[0x00]++;}else{X_FilterData|=0x00000001;}}//X00
	else{X_FilterDiy[0x00]=0;X_FilterData&=0xFFFFFFFE;}

	if(X1){if(X_FilterDiy[0x01]<X_DIY){X_FilterDiy[0x01]++;}else{X_FilterData|=0x00000002;}}//X01
	else{X_FilterDiy[0x01]=0;X_FilterData&=0xFFFFFFFD;}

	if(X2){if(X_FilterDiy[0x02]<X_DIY){X_FilterDiy[0x02]++;}else{X_FilterData|=0x00000004;}}//X02
	else{X_FilterDiy[0x02]=0;X_FilterData&=0xFFFFFFFB;}

	if(X3){if(X_FilterDiy[0x03]<X_DIY){X_FilterDiy[0x03]++;}else{X_FilterData|=0x00000008;}}//X03
	else{X_FilterDiy[0x03]=0;X_FilterData&=0xFFFFFFF7;}

	if(X4){if(X_FilterDiy[0x04]<X_DIY){X_FilterDiy[0x04]++;}else{X_FilterData|=0x00000010;}}//X04
	else{X_FilterDiy[0x04]=0;X_FilterData&=0xFFFFFFEF;}

	if(X5){if(X_FilterDiy[0x05]<X_DIY){X_FilterDiy[0x05]++;}else{X_FilterData|=0x00000020;}}//X05
	else{X_FilterDiy[0x05]=0;X_FilterData&=0xFFFFFFDF;}

	if(X6){if(X_FilterDiy[0x06]<X_DIY){X_FilterDiy[0x06]++;}else{X_FilterData|=0x00000040;}}//X06
	else{X_FilterDiy[0x06]=0;X_FilterData&=0xFFFFFFBF;}

	if(X7){if(X_FilterDiy[0x07]<X_DIY){X_FilterDiy[0x07]++;}else{X_FilterData|=0x00000080;}}//X07
	else{X_FilterDiy[0x07]=0;X_FilterData&=0xFFFFFF7F;}

	if(X10){if(X_FilterDiy[0x08]<X_DIY){X_FilterDiy[0x08]++;}else{X_FilterData|=0x00000100;}}//X10
	else{X_FilterDiy[0x08]=0;X_FilterData&=0xFFFFFEFF;}

	if(X11){if(X_FilterDiy[0x09]<X_DIY){X_FilterDiy[0x09]++;}else{X_FilterData|=0x00000200;}}//X11
	else{X_FilterDiy[0x09]=0;X_FilterData&=0xFFFFFDFF;}

	if(X12){if(X_FilterDiy[0x0A]<X_DIY){X_FilterDiy[0x0A]++;}else{X_FilterData|=0x00000400;}}//X12
	else{X_FilterDiy[0x0A]=0;X_FilterData&=0xFFFFFBFF;}

	if(X13){if(X_FilterDiy[0x0B]<X_DIY){X_FilterDiy[0x0B]++;}else{X_FilterData|=0x00000800;}}//X13
	else{X_FilterDiy[0x0B]=0;X_FilterData&=0xFFFFF7FF;}

	if(X14){if(X_FilterDiy[0x0C]<X_DIY){X_FilterDiy[0x0C]++;}else{X_FilterData|=0x00001000;}}//X14
	else{X_FilterDiy[0x0C]=0;X_FilterData&=0xFFFFEFFF;}

	if(X15){if(X_FilterDiy[0x0D]<X_DIY){X_FilterDiy[0x0D]++;}else{X_FilterData|=0x00002000;}}//X15
	else{X_FilterDiy[0x0D]=0;X_FilterData&=0xFFFFDFFF;}

	if(X16){if(X_FilterDiy[0x0E]<X_DIY){X_FilterDiy[0x0E]++;}else{X_FilterData|=0x00004000;}}//X16
	else{X_FilterDiy[0x0E]=0;X_FilterData&=0xFFFFBFFF;}

	if(X17){if(X_FilterDiy[0x0F]<X_DIY){X_FilterDiy[0x0F]++;}else{X_FilterData|=0x00008000;}}//X17
	else{X_FilterDiy[0x0F]=0;X_FilterData&=0xFFFF7FFF;}

	if(X20){if(X_FilterDiy[0x10]<X_DIY){X_FilterDiy[0x10]++;}else{X_FilterData|=0x00010000;}}//X20
	else{X_FilterDiy[0x10]=0;X_FilterData&=0xFFFEFFFF;}

	if(X21){if(X_FilterDiy[0x11]<X_DIY){X_FilterDiy[0x11]++;}else{X_FilterData|=0x00020000;}}//X21
	else{X_FilterDiy[0x11]=0;X_FilterData&=0xFFFDFFFF;}

	if(X22){if(X_FilterDiy[0x12]<X_DIY){X_FilterDiy[0x12]++;}else{X_FilterData|=0x00040000;}}//X22
	else{X_FilterDiy[0x12]=0;X_FilterData&=0xFFFBFFFF;}

	if(X23){if(X_FilterDiy[0x13]<X_DIY){X_FilterDiy[0x13]++;}else{X_FilterData|=0x00080000;}}//X23
	else{X_FilterDiy[0x13]=0;X_FilterData&=0xFFF7FFFF;}

	if(X24){if(X_FilterDiy[0x14]<X_DIY){X_FilterDiy[0x14]++;}else{X_FilterData|=0x00100000;}}//X24
	else{X_FilterDiy[0x14]=0;X_FilterData&=0xFFEFFFFF;}

	if(X25){if(X_FilterDiy[0x15]<X_DIY){X_FilterDiy[0x15]++;}else{X_FilterData|=0x00200000;}}//X25
	else{X_FilterDiy[0x15]=0;X_FilterData&=0xFFDFFFFF;}

	if(X26){if(X_FilterDiy[0x16]<X_DIY){X_FilterDiy[0x16]++;}else{X_FilterData|=0x00400000;}}//X26
	else{X_FilterDiy[0x16]=0;X_FilterData&=0xFFBFFFFF;}

	if(X27){if(X_FilterDiy[0x17]<X_DIY){X_FilterDiy[0x17]++;}else{X_FilterData|=0x00800000;}}//X27
	else{X_FilterDiy[0x17]=0;X_FilterData&=0xFF7FFFFF;}

	if(X30){if(X_FilterDiy[0x18]<X_DIY){X_FilterDiy[0x18]++;}else{X_FilterData|=0x01000000;}}//X30
	else{X_FilterDiy[0x18]=0;X_FilterData&=0xFEFFFFFF;}

	if(X31){if(X_FilterDiy[0x19]<X_DIY){X_FilterDiy[0x19]++;}else{X_FilterData|=0x02000000;}}//X31
	else{X_FilterDiy[0x19]=0;X_FilterData&=0xFDFFFFFF;}

	if(X32){if(X_FilterDiy[0x1A]<X_DIY){X_FilterDiy[0x1A]++;}else{X_FilterData|=0x04000000;}}//X32
	else{X_FilterDiy[0x1A]=0;X_FilterData&=0xFBFFFFFF;}

	if(X33){if(X_FilterDiy[0x1B]<X_DIY){X_FilterDiy[0x1B]++;}else{X_FilterData|=0x08000000;}}//X33
	else{X_FilterDiy[0x1B]=0;X_FilterData&=0xF7FFFFFF;}

	if(X34){if(X_FilterDiy[0x1C]<X_DIY){X_FilterDiy[0x1C]++;}else{X_FilterData|=0x10000000;}}//X34
	else{X_FilterDiy[0x1C]=0;X_FilterData&=0xEFFFFFFF;}

	if(X35){if(X_FilterDiy[0x1D]<X_DIY){X_FilterDiy[0x1D]++;}else{X_FilterData|=0x20000000;}}//X35
	else{X_FilterDiy[0x1D]=0;X_FilterData&=0xDFFFFFFF;}

	if(X36){if(X_FilterDiy[0x1E]<X_DIY){X_FilterDiy[0x1E]++;}else{X_FilterData|=0x40000000;}}//X36
	else{X_FilterDiy[0x1E]=0;X_FilterData&=0xBFFFFFFF;}

	if(X37){if(X_FilterDiy[0x1F]<X_DIY){X_FilterDiy[0x1F]++;}else{X_FilterData|=0x80000000;}}//X37
	else{X_FilterDiy[0x1F]=0;X_FilterData&=0x7FFFFFFF;}

	if(X40){if(X_FilterDiy[0x20]<X_DIY){X_FilterDiy[0x20]++;}else{X1_FilterData|=0x00000001;}}//X40
	else{X_FilterDiy[0x20]=0;X1_FilterData&=0xFFFFFFFE;}

	if(X41){if(X_FilterDiy[0x21]<X_DIY){X_FilterDiy[0x21]++;}else{X1_FilterData|=0x00000002;}}//X41
	else{X_FilterDiy[0x21]=0;X1_FilterData&=0xFFFFFFFD;}

	if(X42){if(X_FilterDiy[0x22]<X_DIY){X_FilterDiy[0x22]++;}else{X1_FilterData|=0x00000004;}}//X42
	else{X_FilterDiy[0x22]=0;X1_FilterData&=0xFFFFFFFB;}

	if(X43){if(X_FilterDiy[0x23]<X_DIY){X_FilterDiy[0x23]++;}else{X1_FilterData|=0x00000008;}}//X43
	else{X_FilterDiy[0x23]=0;X1_FilterData&=0xFFFFFFF7;}

	if(X44){if(X_FilterDiy[0x24]<X_DIY){X_FilterDiy[0x24]++;}else{X1_FilterData|=0x00000010;}}//X44
	else{X_FilterDiy[0x24]=0;X1_FilterData&=0xFFFFFFEF;}

	if(X45){if(X_FilterDiy[0x25]<X_DIY){X_FilterDiy[0x25]++;}else{X1_FilterData|=0x00000020;}}//X45
	else{X_FilterDiy[0x25]=0;X1_FilterData&=0xFFFFFFDF;}

	if(X46){if(X_FilterDiy[0x26]<X_DIY){X_FilterDiy[0x26]++;}else{X1_FilterData|=0x00000040;}}//X46
	else{X_FilterDiy[0x26]=0;X1_FilterData&=0xFFFFFFBF;}

	if(X47){if(X_FilterDiy[0x27]<X_DIY){X_FilterDiy[0x27]++;}else{X1_FilterData|=0x00000080;}}//X47
	else{X_FilterDiy[0x27]=0;X1_FilterData&=0xFFFFFF7F;}

	if(X50){if(X_FilterDiy[0x28]<X_DIY){X_FilterDiy[0x28]++;}else{X1_FilterData|=0x00000100;}}//X50
	else{X_FilterDiy[0x28]=0;X1_FilterData&=0xFFFFFEFF;}

	if(X51){if(X_FilterDiy[0x29]<X_DIY){X_FilterDiy[0x29]++;}else{X1_FilterData|=0x00000200;}}//X51
	else{X_FilterDiy[0x29]=0;X1_FilterData&=0xFFFFFDFF;}

	if(X52){if(X_FilterDiy[0x2A]<X_DIY){X_FilterDiy[0x2A]++;}else{X1_FilterData|=0x00000400;}}//X52
	else{X_FilterDiy[0x2A]=0;X1_FilterData&=0xFFFFFBFF;}

	if(X53){if(X_FilterDiy[0x2B]<X_DIY){X_FilterDiy[0x2B]++;}else{X1_FilterData|=0x00000800;}}//X53
	else{X_FilterDiy[0x2B]=0;X1_FilterData&=0xFFFFF7FF;}

	if(X54){if(X_FilterDiy[0x2C]<X_DIY){X_FilterDiy[0x2C]++;}else{X1_FilterData|=0x00001000;}}//X54
	else{X_FilterDiy[0x2C]=0;X1_FilterData&=0xFFFFEFFF;}

	if(X55){if(X_FilterDiy[0x2D]<X_DIY){X_FilterDiy[0x2D]++;}else{X1_FilterData|=0x00002000;}}//X55
	else{X_FilterDiy[0x2D]=0;X1_FilterData&=0xFFFFDFFF;}

	if(X56){if(X_FilterDiy[0x2E]<X_DIY){X_FilterDiy[0x2E]++;}else{X1_FilterData|=0x00004000;}}//X56
	else{X_FilterDiy[0x2E]=0;X1_FilterData&=0xFFFFBFFF;}

	if(X57){if(X_FilterDiy[0x2F]<X_DIY){X_FilterDiy[0x2F]++;}else{X1_FilterData|=0x00008000;}}//X57
	else{X_FilterDiy[0x2F]=0;X1_FilterData&=0xFFFF7FFF;}

	if(X60){if(X_FilterDiy[0x30]<X_DIY){X_FilterDiy[0x30]++;}else{X1_FilterData|=0x00010000;}}//X60
	else{X_FilterDiy[0x30]=0;X1_FilterData&=0xFFFEFFFF;}

	if(X61){if(X_FilterDiy[0x31]<X_DIY){X_FilterDiy[0x31]++;}else{X1_FilterData|=0x00020000;}}//X61
	else{X_FilterDiy[0x31]=0;X1_FilterData&=0xFFFDFFFF;}

	if(X62){if(X_FilterDiy[0x32]<X_DIY){X_FilterDiy[0x32]++;}else{X1_FilterData|=0x00040000;}}//X62
	else{X_FilterDiy[0x32]=0;X1_FilterData&=0xFFFBFFFF;}

	if(X63){if(X_FilterDiy[0x33]<X_DIY){X_FilterDiy[0x33]++;}else{X1_FilterData|=0x00080000;}}//X63
	else{X_FilterDiy[0x33]=0;X1_FilterData&=0xFFF7FFFF;}

	if(X64){if(X_FilterDiy[0x34]<X_DIY){X_FilterDiy[0x34]++;}else{X1_FilterData|=0x00100000;}}//X64
	else{X_FilterDiy[0x34]=0;X1_FilterData&=0xFFEFFFFF;}

	if(X65){if(X_FilterDiy[0x35]<X_DIY){X_FilterDiy[0x35]++;}else{X1_FilterData|=0x00200000;}}//X65
	else{X_FilterDiy[0x35]=0;X1_FilterData&=0xFFDFFFFF;}

	if(X66){if(X_FilterDiy[0x36]<X_DIY){X_FilterDiy[0x36]++;}else{X1_FilterData|=0x00400000;}}//X66
	else{X_FilterDiy[0x36]=0;X1_FilterData&=0xFFBFFFFF;}

	if(X67){if(X_FilterDiy[0x37]<X_DIY){X_FilterDiy[0x37]++;}else{X1_FilterData|=0x00800000;}}//X67
	else{X_FilterDiy[0x37]=0;X1_FilterData&=0xFF7FFFFF;}

	if(X70){if(X_FilterDiy[0x38]<X_DIY){X_FilterDiy[0x38]++;}else{X1_FilterData|=0x01000000;}}//X70
	else{X_FilterDiy[0x38]=0;X1_FilterData&=0xFEFFFFFF;}

	if(X71){if(X_FilterDiy[0x39]<X_DIY){X_FilterDiy[0x39]++;}else{X1_FilterData|=0x02000000;}}//X71
	else{X_FilterDiy[0x39]=0;X1_FilterData&=0xFDFFFFFF;}

	if(X72){if(X_FilterDiy[0x3A]<X_DIY){X_FilterDiy[0x3A]++;}else{X1_FilterData|=0x04000000;}}//X72
	else{X_FilterDiy[0x3A]=0;X1_FilterData&=0xFBFFFFFF;}

	if(X73){if(X_FilterDiy[0x3B]<X_DIY){X_FilterDiy[0x3B]++;}else{X1_FilterData|=0x08000000;}}//X73
	else{X_FilterDiy[0x3B]=0;X1_FilterData&=0xF7FFFFFF;}

	if(X74){if(X_FilterDiy[0x3C]<X_DIY){X_FilterDiy[0x3C]++;}else{X1_FilterData|=0x10000000;}}//X74
	else{X_FilterDiy[0x3C]=0;X1_FilterData&=0xEFFFFFFF;}

	if(X75){if(X_FilterDiy[0x3D]<X_DIY){X_FilterDiy[0x3D]++;}else{X1_FilterData|=0x20000000;}}//X75
	else{X_FilterDiy[0x3D]=0;X1_FilterData&=0xDFFFFFFF;}

	if(X76){if(X_FilterDiy[0x3E]<X_DIY){X_FilterDiy[0x3E]++;}else{X1_FilterData|=0x40000000;}}//X76
	else{X_FilterDiy[0x3E]=0;X1_FilterData&=0xBFFFFFFF;}

	if(X77){if(X_FilterDiy[0x3F]<X_DIY){X_FilterDiy[0x3F]++;}else{X1_FilterData|=0x80000000;}}//X77
	else{X_FilterDiy[0x3F]=0;X1_FilterData&=0x7FFFFFFF;}

	if(X100){if(X_FilterDiy[0x40]<X_DIY){X_FilterDiy[0x40]++;}else{X2_FilterData|=0x00000001;}}//X100
	else{X_FilterDiy[0x40]=0;X2_FilterData&=0xFFFFFFFE;}

	if(X101){if(X_FilterDiy[0x41]<X_DIY){X_FilterDiy[0x41]++;}else{X2_FilterData|=0x00000002;}}//X101
	else{X_FilterDiy[0x41]=0;X2_FilterData&=0xFFFFFFFD;}

	if(X102){if(X_FilterDiy[0x42]<X_DIY){X_FilterDiy[0x42]++;}else{X2_FilterData|=0x00000004;}}//X102
	else{X_FilterDiy[0x42]=0;X2_FilterData&=0xFFFFFFFB;}

	if(X103){if(X_FilterDiy[0x43]<X_DIY){X_FilterDiy[0x43]++;}else{X2_FilterData|=0x00000008;}}//X103
	else{X_FilterDiy[0x43]=0;X2_FilterData&=0xFFFFFFF7;}

	if(X104){if(X_FilterDiy[0x44]<X_DIY){X_FilterDiy[0x44]++;}else{X2_FilterData|=0x00000010;}}//X104
	else{X_FilterDiy[0x44]=0;X2_FilterData&=0xFFFFFFEF;}

	if(X105){if(X_FilterDiy[0x45]<X_DIY){X_FilterDiy[0x45]++;}else{X2_FilterData|=0x00000020;}}//X105
	else{X_FilterDiy[0x45]=0;X2_FilterData&=0xFFFFFFDF;}

	if(X106){if(X_FilterDiy[0x46]<X_DIY){X_FilterDiy[0x46]++;}else{X2_FilterData|=0x00000040;}}//X106
	else{X_FilterDiy[0x46]=0;X2_FilterData&=0xFFFFFFBF;}

	if(X107){if(X_FilterDiy[0x47]<X_DIY){X_FilterDiy[0x47]++;}else{X2_FilterData|=0x00000080;}}//X107
	else{X_FilterDiy[0x47]=0;X2_FilterData&=0xFFFFFF7F;}

	if(X110){if(X_FilterDiy[0x48]<X_DIY){X_FilterDiy[0x48]++;}else{X2_FilterData|=0x00000100;}}//X110
	else{X_FilterDiy[0x48]=0;X2_FilterData&=0xFFFFFEFF;}

	if(X111){if(X_FilterDiy[0x49]<X_DIY){X_FilterDiy[0x49]++;}else{X2_FilterData|=0x00000200;}}//X111
	else{X_FilterDiy[0x49]=0;X2_FilterData&=0xFFFFFDFF;}

	if(X112){if(X_FilterDiy[0x4A]<X_DIY){X_FilterDiy[0x4A]++;}else{X2_FilterData|=0x00000400;}}//X112
	else{X_FilterDiy[0x4A]=0;X2_FilterData&=0xFFFFFBFF;}

	if(X113){if(X_FilterDiy[0x4B]<X_DIY){X_FilterDiy[0x4B]++;}else{X2_FilterData|=0x00000800;}}//X113
	else{X_FilterDiy[0x4B]=0;X2_FilterData&=0xFFFFF7FF;}

	if(X114){if(X_FilterDiy[0x4C]<X_DIY){X_FilterDiy[0x4C]++;}else{X2_FilterData|=0x00001000;}}//X114
	else{X_FilterDiy[0x4C]=0;X2_FilterData&=0xFFFFEFFF;}

	if(X115){if(X_FilterDiy[0x4D]<X_DIY){X_FilterDiy[0x4D]++;}else{X2_FilterData|=0x00002000;}}//X115
	else{X_FilterDiy[0x4D]=0;X2_FilterData&=0xFFFFDFFF;}

	if(X116){if(X_FilterDiy[0x4E]<X_DIY){X_FilterDiy[0x4E]++;}else{X2_FilterData|=0x00004000;}}//X116
	else{X_FilterDiy[0x4E]=0;X2_FilterData&=0xFFFFBFFF;}

	if(X117){if(X_FilterDiy[0x4F]<X_DIY){X_FilterDiy[0x4F]++;}else{X2_FilterData|=0x00008000;}}//X117
	else{X_FilterDiy[0x4F]=0;X2_FilterData&=0xFFFF7FFF;}

	if(X120){if(X_FilterDiy[0x50]<X_DIY){X_FilterDiy[0x50]++;}else{X2_FilterData|=0x00010000;}}//X120
	else{X_FilterDiy[0x50]=0;X2_FilterData&=0xFFFEFFFF;}

	if(X121){if(X_FilterDiy[0x51]<X_DIY){X_FilterDiy[0x51]++;}else{X2_FilterData|=0x00020000;}}//X121
	else{X_FilterDiy[0x51]=0;X2_FilterData&=0xFFFDFFFF;}

	if(X122){if(X_FilterDiy[0x52]<X_DIY){X_FilterDiy[0x52]++;}else{X2_FilterData|=0x00040000;}}//X122
	else{X_FilterDiy[0x52]=0;X2_FilterData&=0xFFFBFFFF;}

	if(X123){if(X_FilterDiy[0x53]<X_DIY){X_FilterDiy[0x53]++;}else{X2_FilterData|=0x00080000;}}//X123
	else{X_FilterDiy[0x53]=0;X2_FilterData&=0xFFF7FFFF;}

	if(X124){if(X_FilterDiy[0x54]<X_DIY){X_FilterDiy[0x54]++;}else{X2_FilterData|=0x00100000;}}//X124
	else{X_FilterDiy[0x54]=0;X2_FilterData&=0xFFEFFFFF;}

	if(X125){if(X_FilterDiy[0x55]<X_DIY){X_FilterDiy[0x55]++;}else{X2_FilterData|=0x00200000;}}//X125
	else{X_FilterDiy[0x55]=0;X2_FilterData&=0xFFDFFFFF;}

	if(X126){if(X_FilterDiy[0x56]<X_DIY){X_FilterDiy[0x56]++;}else{X2_FilterData|=0x00400000;}}//X126
	else{X_FilterDiy[0x56]=0;X2_FilterData&=0xFFBFFFFF;}

	if(X127){if(X_FilterDiy[0x57]<X_DIY){X_FilterDiy[0x57]++;}else{X2_FilterData|=0x00800000;}}//X127
	else{X_FilterDiy[0x57]=0;X2_FilterData&=0xFF7FFFFF;}

	if(X130){if(X_FilterDiy[0x58]<X_DIY){X_FilterDiy[0x58]++;}else{X2_FilterData|=0x01000000;}}//X130
	else{X_FilterDiy[0x58]=0;X2_FilterData&=0xFEFFFFFF;}

	if(X131){if(X_FilterDiy[0x59]<X_DIY){X_FilterDiy[0x59]++;}else{X2_FilterData|=0x02000000;}}//X131
	else{X_FilterDiy[0x59]=0;X2_FilterData&=0xFDFFFFFF;}

	if(X132){if(X_FilterDiy[0x5A]<X_DIY){X_FilterDiy[0x5A]++;}else{X2_FilterData|=0x04000000;}}//X132
	else{X_FilterDiy[0x5A]=0;X2_FilterData&=0xFBFFFFFF;}

	if(X133){if(X_FilterDiy[0x5B]<X_DIY){X_FilterDiy[0x5B]++;}else{X2_FilterData|=0x08000000;}}//X133
	else{X_FilterDiy[0x5B]=0;X2_FilterData&=0xF7FFFFFF;}

	if(X134){if(X_FilterDiy[0x5C]<X_DIY){X_FilterDiy[0x5C]++;}else{X2_FilterData|=0x10000000;}}//X134
	else{X_FilterDiy[0x5C]=0;X2_FilterData&=0xEFFFFFFF;}

	if(X135){if(X_FilterDiy[0x5D]<X_DIY){X_FilterDiy[0x5D]++;}else{X2_FilterData|=0x20000000;}}//X135
	else{X_FilterDiy[0x5D]=0;X2_FilterData&=0xDFFFFFFF;}

	if(X136){if(X_FilterDiy[0x5E]<X_DIY){X_FilterDiy[0x5E]++;}else{X2_FilterData|=0x40000000;}}//X136
	else{X_FilterDiy[0x5E]=0;X2_FilterData&=0xBFFFFFFF;}

	if(X137){if(X_FilterDiy[0x5F]<X_DIY){X_FilterDiy[0x5F]++;}else{X2_FilterData|=0x80000000;}}//X137
	else{X_FilterDiy[0x5F]=0;X2_FilterData&=0x7FFFFFFF;}

	if(X140){if(X_FilterDiy[0x60]<X_DIY){X_FilterDiy[0x60]++;}else{X3_FilterData|=0x00000001;}}//X140
	else{X_FilterDiy[0x60]=0;X3_FilterData&=0xFFFFFFFE;}

	if(X141){if(X_FilterDiy[0x61]<X_DIY){X_FilterDiy[0x61]++;}else{X3_FilterData|=0x00000002;}}//X141
	else{X_FilterDiy[0x61]=0;X3_FilterData&=0xFFFFFFFD;}

	if(X142){if(X_FilterDiy[0x62]<X_DIY){X_FilterDiy[0x62]++;}else{X3_FilterData|=0x00000004;}}//X142
	else{X_FilterDiy[0x62]=0;X3_FilterData&=0xFFFFFFFB;}

	if(X143){if(X_FilterDiy[0x63]<X_DIY){X_FilterDiy[0x63]++;}else{X3_FilterData|=0x00000008;}}//X143
	else{X_FilterDiy[0x63]=0;X3_FilterData&=0xFFFFFFF7;}

	if(X144){if(X_FilterDiy[0x64]<X_DIY){X_FilterDiy[0x64]++;}else{X3_FilterData|=0x00000010;}}//X144
	else{X_FilterDiy[0x64]=0;X3_FilterData&=0xFFFFFFEF;}

	if(X145){if(X_FilterDiy[0x65]<X_DIY){X_FilterDiy[0x65]++;}else{X3_FilterData|=0x00000020;}}//X145
	else{X_FilterDiy[0x65]=0;X3_FilterData&=0xFFFFFFDF;}

	if(X146){if(X_FilterDiy[0x66]<X_DIY){X_FilterDiy[0x66]++;}else{X3_FilterData|=0x00000040;}}//X146
	else{X_FilterDiy[0x66]=0;X3_FilterData&=0xFFFFFFBF;}

	if(X147){if(X_FilterDiy[0x67]<X_DIY){X_FilterDiy[0x67]++;}else{X3_FilterData|=0x00000080;}}//X147
	else{X_FilterDiy[0x67]=0;X3_FilterData&=0xFFFFFF7F;}

	if(X150){if(X_FilterDiy[0x68]<X_DIY){X_FilterDiy[0x68]++;}else{X3_FilterData|=0x00000100;}}//X150
	else{X_FilterDiy[0x68]=0;X3_FilterData&=0xFFFFFEFF;}

	if(X151){if(X_FilterDiy[0x69]<X_DIY){X_FilterDiy[0x69]++;}else{X3_FilterData|=0x00000200;}}//X151
	else{X_FilterDiy[0x69]=0;X3_FilterData&=0xFFFFFDFF;}

	if(X152){if(X_FilterDiy[0x6A]<X_DIY){X_FilterDiy[0x6A]++;}else{X3_FilterData|=0x00000400;}}//X152
	else{X_FilterDiy[0x6A]=0;X3_FilterData&=0xFFFFFBFF;}

	if(X153){if(X_FilterDiy[0x6B]<X_DIY){X_FilterDiy[0x6B]++;}else{X3_FilterData|=0x00000800;}}//X153
	else{X_FilterDiy[0x6B]=0;X3_FilterData&=0xFFFFF7FF;}

	if(X154){if(X_FilterDiy[0x6C]<X_DIY){X_FilterDiy[0x6C]++;}else{X3_FilterData|=0x00001000;}}//X154
	else{X_FilterDiy[0x6C]=0;X3_FilterData&=0xFFFFEFFF;}

	if(X155){if(X_FilterDiy[0x6D]<X_DIY){X_FilterDiy[0x6D]++;}else{X3_FilterData|=0x00002000;}}//X155
	else{X_FilterDiy[0x6D]=0;X3_FilterData&=0xFFFFDFFF;}

	if(X156){if(X_FilterDiy[0x6E]<X_DIY){X_FilterDiy[0x6E]++;}else{X3_FilterData|=0x00004000;}}//X156
	else{X_FilterDiy[0x6E]=0;X3_FilterData&=0xFFFFBFFF;}

	if(X157){if(X_FilterDiy[0x6F]<X_DIY){X_FilterDiy[0x6F]++;}else{X3_FilterData|=0x00008000;}}//X157
	else{X_FilterDiy[0x6F]=0;X3_FilterData&=0xFFFF7FFF;}

	if(X160){if(X_FilterDiy[0x70]<X_DIY){X_FilterDiy[0x70]++;}else{X3_FilterData|=0x00010000;}}//X160
	else{X_FilterDiy[0x70]=0;X3_FilterData&=0xFFFEFFFF;}

	if(X161){if(X_FilterDiy[0x71]<X_DIY){X_FilterDiy[0x71]++;}else{X3_FilterData|=0x00020000;}}//X161
	else{X_FilterDiy[0x71]=0;X3_FilterData&=0xFFFDFFFF;}

	if(X162){if(X_FilterDiy[0x72]<X_DIY){X_FilterDiy[0x72]++;}else{X3_FilterData|=0x00040000;}}//X162
	else{X_FilterDiy[0x72]=0;X3_FilterData&=0xFFFBFFFF;}

	if(X163){if(X_FilterDiy[0x73]<X_DIY){X_FilterDiy[0x73]++;}else{X3_FilterData|=0x00080000;}}//X163
	else{X_FilterDiy[0x73]=0;X3_FilterData&=0xFFF7FFFF;}

	if(X164){if(X_FilterDiy[0x74]<X_DIY){X_FilterDiy[0x74]++;}else{X3_FilterData|=0x00100000;}}//X164
	else{X_FilterDiy[0x74]=0;X3_FilterData&=0xFFEFFFFF;}

	if(X165){if(X_FilterDiy[0x75]<X_DIY){X_FilterDiy[0x75]++;}else{X3_FilterData|=0x00200000;}}//X165
	else{X_FilterDiy[0x75]=0;X3_FilterData&=0xFFDFFFFF;}

	if(X166){if(X_FilterDiy[0x76]<X_DIY){X_FilterDiy[0x76]++;}else{X3_FilterData|=0x00400000;}}//X166
	else{X_FilterDiy[0x76]=0;X3_FilterData&=0xFFBFFFFF;}

	if(X167){if(X_FilterDiy[0x77]<X_DIY){X_FilterDiy[0x77]++;}else{X3_FilterData|=0x00800000;}}//X167
	else{X_FilterDiy[0x77]=0;X3_FilterData&=0xFF7FFFFF;}

	if(X170){if(X_FilterDiy[0x78]<X_DIY){X_FilterDiy[0x78]++;}else{X3_FilterData|=0x01000000;}}//X170
	else{X_FilterDiy[0x78]=0;X3_FilterData&=0xFEFFFFFF;}

	if(X171){if(X_FilterDiy[0x79]<X_DIY){X_FilterDiy[0x79]++;}else{X3_FilterData|=0x02000000;}}//X171
	else{X_FilterDiy[0x79]=0;X3_FilterData&=0xFDFFFFFF;}

	if(X172){if(X_FilterDiy[0x7A]<X_DIY){X_FilterDiy[0x7A]++;}else{X3_FilterData|=0x04000000;}}//X172
	else{X_FilterDiy[0x7A]=0;X3_FilterData&=0xFBFFFFFF;}

	if(X173){if(X_FilterDiy[0x7B]<X_DIY){X_FilterDiy[0x7B]++;}else{X3_FilterData|=0x08000000;}}//X173
	else{X_FilterDiy[0x7B]=0;X3_FilterData&=0xF7FFFFFF;}

	if(X174){if(X_FilterDiy[0x7C]<X_DIY){X_FilterDiy[0x7C]++;}else{X3_FilterData|=0x10000000;}}//X174
	else{X_FilterDiy[0x7C]=0;X3_FilterData&=0xEFFFFFFF;}

	if(X175){if(X_FilterDiy[0x7D]<X_DIY){X_FilterDiy[0x7D]++;}else{X3_FilterData|=0x20000000;}}//X175
	else{X_FilterDiy[0x7D]=0;X3_FilterData&=0xDFFFFFFF;}

	if(X176){if(X_FilterDiy[0x7E]<X_DIY){X_FilterDiy[0x7E]++;}else{X3_FilterData|=0x40000000;}}//X176
	else{X_FilterDiy[0x7E]=0;X3_FilterData&=0xBFFFFFFF;}

	if(X177){if(X_FilterDiy[0x7F]<X_DIY){X_FilterDiy[0x7F]++;}else{X3_FilterData|=0x80000000;}}//X177
	else{X_FilterDiy[0x7F]=0;X3_FilterData&=0x7FFFFFFF;}

	if(X200){if(X_FilterDiy[0x80]<X_DIY){X_FilterDiy[0x80]++;}else{X4_FilterData|=0x00000001;}}//X200
	else{X_FilterDiy[0x80]=0;X4_FilterData&=0xFFFFFFFE;}

	if(X201){if(X_FilterDiy[0x81]<X_DIY){X_FilterDiy[0x81]++;}else{X4_FilterData|=0x00000002;}}//X201
	else{X_FilterDiy[0x81]=0;X4_FilterData&=0xFFFFFFFD;}

	if(X202){if(X_FilterDiy[0x82]<X_DIY){X_FilterDiy[0x82]++;}else{X4_FilterData|=0x00000004;}}//X202
	else{X_FilterDiy[0x82]=0;X4_FilterData&=0xFFFFFFFB;}

	if(X203){if(X_FilterDiy[0x83]<X_DIY){X_FilterDiy[0x83]++;}else{X4_FilterData|=0x00000008;}}//X203
	else{X_FilterDiy[0x83]=0;X4_FilterData&=0xFFFFFFF7;}

	if(X204){if(X_FilterDiy[0x84]<X_DIY){X_FilterDiy[0x84]++;}else{X4_FilterData|=0x00000010;}}//X204
	else{X_FilterDiy[0x84]=0;X4_FilterData&=0xFFFFFFEF;}

	if(X205){if(X_FilterDiy[0x85]<X_DIY){X_FilterDiy[0x85]++;}else{X4_FilterData|=0x00000020;}}//X205
	else{X_FilterDiy[0x85]=0;X4_FilterData&=0xFFFFFFDF;}

	if(X206){if(X_FilterDiy[0x86]<X_DIY){X_FilterDiy[0x86]++;}else{X4_FilterData|=0x00000040;}}//X206
	else{X_FilterDiy[0x86]=0;X4_FilterData&=0xFFFFFFBF;}

	if(X207){if(X_FilterDiy[0x87]<X_DIY){X_FilterDiy[0x87]++;}else{X4_FilterData|=0x00000080;}}//X207
	else{X_FilterDiy[0x87]=0;X4_FilterData&=0xFFFFFF7F;}

	if(X210){if(X_FilterDiy[0x88]<X_DIY){X_FilterDiy[0x88]++;}else{X4_FilterData|=0x00000100;}}//X210
	else{X_FilterDiy[0x88]=0;X4_FilterData&=0xFFFFFEFF;}

	if(X211){if(X_FilterDiy[0x89]<X_DIY){X_FilterDiy[0x89]++;}else{X4_FilterData|=0x00000200;}}//X211
	else{X_FilterDiy[0x89]=0;X4_FilterData&=0xFFFFFDFF;}

	if(X212){if(X_FilterDiy[0x8A]<X_DIY){X_FilterDiy[0x8A]++;}else{X4_FilterData|=0x00000400;}}//X212
	else{X_FilterDiy[0x8A]=0;X4_FilterData&=0xFFFFFBFF;}

	if(X213){if(X_FilterDiy[0x8B]<X_DIY){X_FilterDiy[0x8B]++;}else{X4_FilterData|=0x00000800;}}//X213
	else{X_FilterDiy[0x8B]=0;X4_FilterData&=0xFFFFF7FF;}

	if(X214){if(X_FilterDiy[0x8C]<X_DIY){X_FilterDiy[0x8C]++;}else{X4_FilterData|=0x00001000;}}//X214
	else{X_FilterDiy[0x8C]=0;X4_FilterData&=0xFFFFEFFF;}

	if(X215){if(X_FilterDiy[0x8D]<X_DIY){X_FilterDiy[0x8D]++;}else{X4_FilterData|=0x00002000;}}//X215
	else{X_FilterDiy[0x8D]=0;X4_FilterData&=0xFFFFDFFF;}

	if(X216){if(X_FilterDiy[0x8E]<X_DIY){X_FilterDiy[0x8E]++;}else{X4_FilterData|=0x00004000;}}//X216
	else{X_FilterDiy[0x8E]=0;X4_FilterData&=0xFFFFBFFF;}

	if(X217){if(X_FilterDiy[0x8F]<X_DIY){X_FilterDiy[0x8F]++;}else{X4_FilterData|=0x00008000;}}//X217
	else{X_FilterDiy[0x8F]=0;X4_FilterData&=0xFFFF7FFF;}

	if(X220){if(X_FilterDiy[0x90]<X_DIY){X_FilterDiy[0x90]++;}else{X4_FilterData|=0x00010000;}}//X220
	else{X_FilterDiy[0x90]=0;X4_FilterData&=0xFFFEFFFF;}

	if(X221){if(X_FilterDiy[0x91]<X_DIY){X_FilterDiy[0x91]++;}else{X4_FilterData|=0x00020000;}}//X221
	else{X_FilterDiy[0x91]=0;X4_FilterData&=0xFFFDFFFF;}

	if(X222){if(X_FilterDiy[0x92]<X_DIY){X_FilterDiy[0x92]++;}else{X4_FilterData|=0x00040000;}}//X222
	else{X_FilterDiy[0x92]=0;X4_FilterData&=0xFFFBFFFF;}

	if(X223){if(X_FilterDiy[0x93]<X_DIY){X_FilterDiy[0x93]++;}else{X4_FilterData|=0x00080000;}}//X223
	else{X_FilterDiy[0x93]=0;X4_FilterData&=0xFFF7FFFF;}

	if(X224){if(X_FilterDiy[0x94]<X_DIY){X_FilterDiy[0x94]++;}else{X4_FilterData|=0x00100000;}}//X224
	else{X_FilterDiy[0x94]=0;X4_FilterData&=0xFFEFFFFF;}

	if(X225){if(X_FilterDiy[0x95]<X_DIY){X_FilterDiy[0x95]++;}else{X4_FilterData|=0x00200000;}}//X225
	else{X_FilterDiy[0x95]=0;X4_FilterData&=0xFFDFFFFF;}

	if(X226){if(X_FilterDiy[0x96]<X_DIY){X_FilterDiy[0x96]++;}else{X4_FilterData|=0x00400000;}}//X226
	else{X_FilterDiy[0x96]=0;X4_FilterData&=0xFFBFFFFF;}

	if(X227){if(X_FilterDiy[0x97]<X_DIY){X_FilterDiy[0x97]++;}else{X4_FilterData|=0x00800000;}}//X227
	else{X_FilterDiy[0x97]=0;X4_FilterData&=0xFF7FFFFF;}

	if(X230){if(X_FilterDiy[0x98]<X_DIY){X_FilterDiy[0x98]++;}else{X4_FilterData|=0x01000000;}}//X230
	else{X_FilterDiy[0x98]=0;X4_FilterData&=0xFEFFFFFF;}

	if(X231){if(X_FilterDiy[0x99]<X_DIY){X_FilterDiy[0x99]++;}else{X4_FilterData|=0x02000000;}}//X231
	else{X_FilterDiy[0x99]=0;X4_FilterData&=0xFDFFFFFF;}

	if(X232){if(X_FilterDiy[0x9A]<X_DIY){X_FilterDiy[0x9A]++;}else{X4_FilterData|=0x04000000;}}//X232
	else{X_FilterDiy[0x9A]=0;X4_FilterData&=0xFBFFFFFF;}

	if(X233){if(X_FilterDiy[0x9B]<X_DIY){X_FilterDiy[0x9B]++;}else{X4_FilterData|=0x08000000;}}//X233
	else{X_FilterDiy[0x9B]=0;X4_FilterData&=0xF7FFFFFF;}

	if(X234){if(X_FilterDiy[0x9C]<X_DIY){X_FilterDiy[0x9C]++;}else{X4_FilterData|=0x10000000;}}//X234
	else{X_FilterDiy[0x9C]=0;X4_FilterData&=0xEFFFFFFF;}

	if(X235){if(X_FilterDiy[0x9D]<X_DIY){X_FilterDiy[0x9D]++;}else{X4_FilterData|=0x20000000;}}//X235
	else{X_FilterDiy[0x9D]=0;X4_FilterData&=0xDFFFFFFF;}

	if(X236){if(X_FilterDiy[0x9E]<X_DIY){X_FilterDiy[0x9E]++;}else{X4_FilterData|=0x40000000;}}//X236
	else{X_FilterDiy[0x9E]=0;X4_FilterData&=0xBFFFFFFF;}

	if(X237){if(X_FilterDiy[0x9F]<X_DIY){X_FilterDiy[0x9F]++;}else{X4_FilterData|=0x80000000;}}//X237
	else{X_FilterDiy[0x9F]=0;X4_FilterData&=0x7FFFFFFF;}

	if(X240){if(X_FilterDiy[0xA0]<X_DIY){X_FilterDiy[0xA0]++;}else{X5_FilterData|=0x00000001;}}//X240
	else{X_FilterDiy[0xA0]=0;X5_FilterData&=0xFFFFFFFE;}

	if(X241){if(X_FilterDiy[0xA1]<X_DIY){X_FilterDiy[0xA1]++;}else{X5_FilterData|=0x00000002;}}//X241
	else{X_FilterDiy[0xA1]=0;X5_FilterData&=0xFFFFFFFD;}

	if(X242){if(X_FilterDiy[0xA2]<X_DIY){X_FilterDiy[0xA2]++;}else{X5_FilterData|=0x00000004;}}//X242
	else{X_FilterDiy[0xA2]=0;X5_FilterData&=0xFFFFFFFB;}

	if(X243){if(X_FilterDiy[0xA3]<X_DIY){X_FilterDiy[0xA3]++;}else{X5_FilterData|=0x00000008;}}//X243
	else{X_FilterDiy[0xA3]=0;X5_FilterData&=0xFFFFFFF7;}

	if(X244){if(X_FilterDiy[0xA4]<X_DIY){X_FilterDiy[0xA4]++;}else{X5_FilterData|=0x00000010;}}//X244
	else{X_FilterDiy[0xA4]=0;X5_FilterData&=0xFFFFFFEF;}

	if(X245){if(X_FilterDiy[0xA5]<X_DIY){X_FilterDiy[0xA5]++;}else{X5_FilterData|=0x00000020;}}//X245
	else{X_FilterDiy[0xA5]=0;X5_FilterData&=0xFFFFFFDF;}

	if(X246){if(X_FilterDiy[0xA6]<X_DIY){X_FilterDiy[0xA6]++;}else{X5_FilterData|=0x00000040;}}//X246
	else{X_FilterDiy[0xA6]=0;X5_FilterData&=0xFFFFFFBF;}

	if(X247){if(X_FilterDiy[0xA7]<X_DIY){X_FilterDiy[0xA7]++;}else{X5_FilterData|=0x00000080;}}//X247
	else{X_FilterDiy[0xA7]=0;X5_FilterData&=0xFFFFFF7F;}

	if(X250){if(X_FilterDiy[0xA8]<X_DIY){X_FilterDiy[0xA8]++;}else{X5_FilterData|=0x00000100;}}//X250
	else{X_FilterDiy[0xA8]=0;X5_FilterData&=0xFFFFFEFF;}

	if(X251){if(X_FilterDiy[0xA9]<X_DIY){X_FilterDiy[0xA9]++;}else{X5_FilterData|=0x00000200;}}//X251
	else{X_FilterDiy[0xA9]=0;X5_FilterData&=0xFFFFFDFF;}

	if(X252){if(X_FilterDiy[0xAA]<X_DIY){X_FilterDiy[0xAA]++;}else{X5_FilterData|=0x00000400;}}//X252
	else{X_FilterDiy[0xAA]=0;X5_FilterData&=0xFFFFFBFF;}

	if(X253){if(X_FilterDiy[0xAB]<X_DIY){X_FilterDiy[0xAB]++;}else{X5_FilterData|=0x00000800;}}//X253
	else{X_FilterDiy[0xAB]=0;X5_FilterData&=0xFFFFF7FF;}

	if(X254){if(X_FilterDiy[0xAC]<X_DIY){X_FilterDiy[0xAC]++;}else{X5_FilterData|=0x00001000;}}//X254
	else{X_FilterDiy[0xAC]=0;X5_FilterData&=0xFFFFEFFF;}

	if(X255){if(X_FilterDiy[0xAD]<X_DIY){X_FilterDiy[0xAD]++;}else{X5_FilterData|=0x00002000;}}//X255
	else{X_FilterDiy[0xAD]=0;X5_FilterData&=0xFFFFDFFF;}

	if(X256){if(X_FilterDiy[0xAE]<X_DIY){X_FilterDiy[0xAE]++;}else{X5_FilterData|=0x00004000;}}//X256
	else{X_FilterDiy[0xAE]=0;X5_FilterData&=0xFFFFBFFF;}

	if(X257){if(X_FilterDiy[0xAF]<X_DIY){X_FilterDiy[0xAF]++;}else{X5_FilterData|=0x00008000;}}//X257
	else{X_FilterDiy[0xAF]=0;X5_FilterData&=0xFFFF7FFF;}

	if(X260){if(X_FilterDiy[0xB0]<X_DIY){X_FilterDiy[0xB0]++;}else{X5_FilterData|=0x00010000;}}//X260
	else{X_FilterDiy[0xB0]=0;X5_FilterData&=0xFFFEFFFF;}

	if(X261){if(X_FilterDiy[0xB1]<X_DIY){X_FilterDiy[0xB1]++;}else{X5_FilterData|=0x00020000;}}//X261
	else{X_FilterDiy[0xB1]=0;X5_FilterData&=0xFFFDFFFF;}

	if(X262){if(X_FilterDiy[0xB2]<X_DIY){X_FilterDiy[0xB2]++;}else{X5_FilterData|=0x00040000;}}//X262
	else{X_FilterDiy[0xB2]=0;X5_FilterData&=0xFFFBFFFF;}

	if(X263){if(X_FilterDiy[0xB3]<X_DIY){X_FilterDiy[0xB3]++;}else{X5_FilterData|=0x00080000;}}//X263
	else{X_FilterDiy[0xB3]=0;X5_FilterData&=0xFFF7FFFF;}

	if(X264){if(X_FilterDiy[0xB4]<X_DIY){X_FilterDiy[0xB4]++;}else{X5_FilterData|=0x00100000;}}//X264
	else{X_FilterDiy[0xB4]=0;X5_FilterData&=0xFFEFFFFF;}

	if(X265){if(X_FilterDiy[0xB5]<X_DIY){X_FilterDiy[0xB5]++;}else{X5_FilterData|=0x00200000;}}//X265
	else{X_FilterDiy[0xB5]=0;X5_FilterData&=0xFFDFFFFF;}

	if(X266){if(X_FilterDiy[0xB6]<X_DIY){X_FilterDiy[0xB6]++;}else{X5_FilterData|=0x00400000;}}//X266
	else{X_FilterDiy[0xB6]=0;X5_FilterData&=0xFFBFFFFF;}

	if(X267){if(X_FilterDiy[0xB7]<X_DIY){X_FilterDiy[0xB7]++;}else{X5_FilterData|=0x00800000;}}//X267
	else{X_FilterDiy[0xB7]=0;X5_FilterData&=0xFF7FFFFF;}

	if(X270){if(X_FilterDiy[0xB8]<X_DIY){X_FilterDiy[0xB8]++;}else{X5_FilterData|=0x01000000;}}//X270
	else{X_FilterDiy[0xB8]=0;X5_FilterData&=0xFEFFFFFF;}

	if(X271){if(X_FilterDiy[0xB9]<X_DIY){X_FilterDiy[0xB9]++;}else{X5_FilterData|=0x02000000;}}//X271
	else{X_FilterDiy[0xB9]=0;X5_FilterData&=0xFDFFFFFF;}

	if(X272){if(X_FilterDiy[0xBA]<X_DIY){X_FilterDiy[0xBA]++;}else{X5_FilterData|=0x04000000;}}//X272
	else{X_FilterDiy[0xBA]=0;X5_FilterData&=0xFBFFFFFF;}

	if(X273){if(X_FilterDiy[0xBB]<X_DIY){X_FilterDiy[0xBB]++;}else{X5_FilterData|=0x08000000;}}//X273
	else{X_FilterDiy[0xBB]=0;X5_FilterData&=0xF7FFFFFF;}

	if(X274){if(X_FilterDiy[0xBC]<X_DIY){X_FilterDiy[0xBC]++;}else{X5_FilterData|=0x10000000;}}//X274
	else{X_FilterDiy[0xBC]=0;X5_FilterData&=0xEFFFFFFF;}

	if(X275){if(X_FilterDiy[0xBD]<X_DIY){X_FilterDiy[0xBD]++;}else{X5_FilterData|=0x20000000;}}//X275
	else{X_FilterDiy[0xBD]=0;X5_FilterData&=0xDFFFFFFF;}

	if(X276){if(X_FilterDiy[0xBE]<X_DIY){X_FilterDiy[0xBE]++;}else{X5_FilterData|=0x40000000;}}//X276
	else{X_FilterDiy[0xBE]=0;X5_FilterData&=0xBFFFFFFF;}

	if(X277){if(X_FilterDiy[0xBF]<X_DIY){X_FilterDiy[0xBF]++;}else{X5_FilterData|=0x80000000;}}//X277
	else{X_FilterDiy[0xBF]=0;X5_FilterData&=0x7FFFFFFF;}

	if(X300){if(X_FilterDiy[0xC0]<X_DIY){X_FilterDiy[0xC0]++;}else{X6_FilterData|=0x00000001;}}//X300
	else{X_FilterDiy[0xC0]=0;X6_FilterData&=0xFFFFFFFE;}

	if(X301){if(X_FilterDiy[0xC1]<X_DIY){X_FilterDiy[0xC1]++;}else{X6_FilterData|=0x00000002;}}//X301
	else{X_FilterDiy[0xC1]=0;X6_FilterData&=0xFFFFFFFD;}

	if(X302){if(X_FilterDiy[0xC2]<X_DIY){X_FilterDiy[0xC2]++;}else{X6_FilterData|=0x00000004;}}//X302
	else{X_FilterDiy[0xC2]=0;X6_FilterData&=0xFFFFFFFB;}

	if(X303){if(X_FilterDiy[0xC3]<X_DIY){X_FilterDiy[0xC3]++;}else{X6_FilterData|=0x00000008;}}//X303
	else{X_FilterDiy[0xC3]=0;X6_FilterData&=0xFFFFFFF7;}

	if(X304){if(X_FilterDiy[0xC4]<X_DIY){X_FilterDiy[0xC4]++;}else{X6_FilterData|=0x00000010;}}//X304
	else{X_FilterDiy[0xC4]=0;X6_FilterData&=0xFFFFFFEF;}

	if(X305){if(X_FilterDiy[0xC5]<X_DIY){X_FilterDiy[0xC5]++;}else{X6_FilterData|=0x00000020;}}//X305
	else{X_FilterDiy[0xC5]=0;X6_FilterData&=0xFFFFFFDF;}

	if(X306){if(X_FilterDiy[0xC6]<X_DIY){X_FilterDiy[0xC6]++;}else{X6_FilterData|=0x00000040;}}//X306
	else{X_FilterDiy[0xC6]=0;X6_FilterData&=0xFFFFFFBF;}

	if(X307){if(X_FilterDiy[0xC7]<X_DIY){X_FilterDiy[0xC7]++;}else{X6_FilterData|=0x00000080;}}//X307
	else{X_FilterDiy[0xC7]=0;X6_FilterData&=0xFFFFFF7F;}

	if(X310){if(X_FilterDiy[0xC8]<X_DIY){X_FilterDiy[0xC8]++;}else{X6_FilterData|=0x00000100;}}//X310
	else{X_FilterDiy[0xC8]=0;X6_FilterData&=0xFFFFFEFF;}

	if(X311){if(X_FilterDiy[0xC9]<X_DIY){X_FilterDiy[0xC9]++;}else{X6_FilterData|=0x00000200;}}//X311
	else{X_FilterDiy[0xC9]=0;X6_FilterData&=0xFFFFFDFF;}

	if(X312){if(X_FilterDiy[0xCA]<X_DIY){X_FilterDiy[0xCA]++;}else{X6_FilterData|=0x00000400;}}//X312
	else{X_FilterDiy[0xCA]=0;X6_FilterData&=0xFFFFFBFF;}

	if(X313){if(X_FilterDiy[0xCB]<X_DIY){X_FilterDiy[0xCB]++;}else{X6_FilterData|=0x00000800;}}//X313
	else{X_FilterDiy[0xCB]=0;X6_FilterData&=0xFFFFF7FF;}

	if(X314){if(X_FilterDiy[0xCC]<X_DIY){X_FilterDiy[0xCC]++;}else{X6_FilterData|=0x00001000;}}//X314
	else{X_FilterDiy[0xCC]=0;X6_FilterData&=0xFFFFEFFF;}

	if(X315){if(X_FilterDiy[0xCD]<X_DIY){X_FilterDiy[0xCD]++;}else{X6_FilterData|=0x00002000;}}//X315
	else{X_FilterDiy[0xCD]=0;X6_FilterData&=0xFFFFDFFF;}

	if(X316){if(X_FilterDiy[0xCE]<X_DIY){X_FilterDiy[0xCE]++;}else{X6_FilterData|=0x00004000;}}//X316
	else{X_FilterDiy[0xCE]=0;X6_FilterData&=0xFFFFBFFF;}

	if(X317){if(X_FilterDiy[0xCF]<X_DIY){X_FilterDiy[0xCF]++;}else{X6_FilterData|=0x00008000;}}//X317
	else{X_FilterDiy[0xCF]=0;X6_FilterData&=0xFFFF7FFF;}

	if(X320){if(X_FilterDiy[0xD0]<X_DIY){X_FilterDiy[0xD0]++;}else{X6_FilterData|=0x00010000;}}//X320
	else{X_FilterDiy[0xD0]=0;X6_FilterData&=0xFFFEFFFF;}

	if(X321){if(X_FilterDiy[0xD1]<X_DIY){X_FilterDiy[0xD1]++;}else{X6_FilterData|=0x00020000;}}//X321
	else{X_FilterDiy[0xD1]=0;X6_FilterData&=0xFFFDFFFF;}

	if(X322){if(X_FilterDiy[0xD2]<X_DIY){X_FilterDiy[0xD2]++;}else{X6_FilterData|=0x00040000;}}//X322
	else{X_FilterDiy[0xD2]=0;X6_FilterData&=0xFFFBFFFF;}

	if(X323){if(X_FilterDiy[0xD3]<X_DIY){X_FilterDiy[0xD3]++;}else{X6_FilterData|=0x00080000;}}//X323
	else{X_FilterDiy[0xD3]=0;X6_FilterData&=0xFFF7FFFF;}

	if(X324){if(X_FilterDiy[0xD4]<X_DIY){X_FilterDiy[0xD4]++;}else{X6_FilterData|=0x00100000;}}//X324
	else{X_FilterDiy[0xD4]=0;X6_FilterData&=0xFFEFFFFF;}

	if(X325){if(X_FilterDiy[0xD5]<X_DIY){X_FilterDiy[0xD5]++;}else{X6_FilterData|=0x00200000;}}//X325
	else{X_FilterDiy[0xD5]=0;X6_FilterData&=0xFFDFFFFF;}

	if(X326){if(X_FilterDiy[0xD6]<X_DIY){X_FilterDiy[0xD6]++;}else{X6_FilterData|=0x00400000;}}//X326
	else{X_FilterDiy[0xD6]=0;X6_FilterData&=0xFFBFFFFF;}

	if(X327){if(X_FilterDiy[0xD7]<X_DIY){X_FilterDiy[0xD7]++;}else{X6_FilterData|=0x00800000;}}//X327
	else{X_FilterDiy[0xD7]=0;X6_FilterData&=0xFF7FFFFF;}

	if(X330){if(X_FilterDiy[0xD8]<X_DIY){X_FilterDiy[0xD8]++;}else{X6_FilterData|=0x01000000;}}//X330
	else{X_FilterDiy[0xD8]=0;X6_FilterData&=0xFEFFFFFF;}

	if(X331){if(X_FilterDiy[0xD9]<X_DIY){X_FilterDiy[0xD9]++;}else{X6_FilterData|=0x02000000;}}//X331
	else{X_FilterDiy[0xD9]=0;X6_FilterData&=0xFDFFFFFF;}

	if(X332){if(X_FilterDiy[0xDA]<X_DIY){X_FilterDiy[0xDA]++;}else{X6_FilterData|=0x04000000;}}//X332
	else{X_FilterDiy[0xDA]=0;X6_FilterData&=0xFBFFFFFF;}

	if(X333){if(X_FilterDiy[0xDB]<X_DIY){X_FilterDiy[0xDB]++;}else{X6_FilterData|=0x08000000;}}//X333
	else{X_FilterDiy[0xDB]=0;X6_FilterData&=0xF7FFFFFF;}

	if(X334){if(X_FilterDiy[0xDC]<X_DIY){X_FilterDiy[0xDC]++;}else{X6_FilterData|=0x10000000;}}//X334
	else{X_FilterDiy[0xDC]=0;X6_FilterData&=0xEFFFFFFF;}

	if(X335){if(X_FilterDiy[0xDD]<X_DIY){X_FilterDiy[0xDD]++;}else{X6_FilterData|=0x20000000;}}//X335
	else{X_FilterDiy[0xDD]=0;X6_FilterData&=0xDFFFFFFF;}

	if(X336){if(X_FilterDiy[0xDE]<X_DIY){X_FilterDiy[0xDE]++;}else{X6_FilterData|=0x40000000;}}//X336
	else{X_FilterDiy[0xDE]=0;X6_FilterData&=0xBFFFFFFF;}

	if(X337){if(X_FilterDiy[0xDF]<X_DIY){X_FilterDiy[0xDF]++;}else{X6_FilterData|=0x80000000;}}//X337
	else{X_FilterDiy[0xDF]=0;X6_FilterData&=0x7FFFFFFF;}

	if(X340){if(X_FilterDiy[0xE0]<X_DIY){X_FilterDiy[0xE0]++;}else{X7_FilterData|=0x00000001;}}//X340
	else{X_FilterDiy[0xE0]=0;X7_FilterData&=0xFFFFFFFE;}

	if(X341){if(X_FilterDiy[0xE1]<X_DIY){X_FilterDiy[0xE1]++;}else{X7_FilterData|=0x00000002;}}//X341
	else{X_FilterDiy[0xE1]=0;X7_FilterData&=0xFFFFFFFD;}

	if(X342){if(X_FilterDiy[0xE2]<X_DIY){X_FilterDiy[0xE2]++;}else{X7_FilterData|=0x00000004;}}//X342
	else{X_FilterDiy[0xE2]=0;X7_FilterData&=0xFFFFFFFB;}

	if(X343){if(X_FilterDiy[0xE3]<X_DIY){X_FilterDiy[0xE3]++;}else{X7_FilterData|=0x00000008;}}//X343
	else{X_FilterDiy[0xE3]=0;X7_FilterData&=0xFFFFFFF7;}

	if(X344){if(X_FilterDiy[0xE4]<X_DIY){X_FilterDiy[0xE4]++;}else{X7_FilterData|=0x00000010;}}//X344
	else{X_FilterDiy[0xE4]=0;X7_FilterData&=0xFFFFFFEF;}

	if(X345){if(X_FilterDiy[0xE5]<X_DIY){X_FilterDiy[0xE5]++;}else{X7_FilterData|=0x00000020;}}//X345
	else{X_FilterDiy[0xE5]=0;X7_FilterData&=0xFFFFFFDF;}

	if(X346){if(X_FilterDiy[0xE6]<X_DIY){X_FilterDiy[0xE6]++;}else{X7_FilterData|=0x00000040;}}//X346
	else{X_FilterDiy[0xE6]=0;X7_FilterData&=0xFFFFFFBF;}

	if(X347){if(X_FilterDiy[0xE7]<X_DIY){X_FilterDiy[0xE7]++;}else{X7_FilterData|=0x00000080;}}//X347
	else{X_FilterDiy[0xE7]=0;X7_FilterData&=0xFFFFFF7F;}

	if(X350){if(X_FilterDiy[0xE8]<X_DIY){X_FilterDiy[0xE8]++;}else{X7_FilterData|=0x00000100;}}//X350
	else{X_FilterDiy[0xE8]=0;X7_FilterData&=0xFFFFFEFF;}

	if(X351){if(X_FilterDiy[0xE9]<X_DIY){X_FilterDiy[0xE9]++;}else{X7_FilterData|=0x00000200;}}//X351
	else{X_FilterDiy[0xE9]=0;X7_FilterData&=0xFFFFFDFF;}

	if(X352){if(X_FilterDiy[0xEA]<X_DIY){X_FilterDiy[0xEA]++;}else{X7_FilterData|=0x00000400;}}//X352
	else{X_FilterDiy[0xEA]=0;X7_FilterData&=0xFFFFFBFF;}

	if(X353){if(X_FilterDiy[0xEB]<X_DIY){X_FilterDiy[0xEB]++;}else{X7_FilterData|=0x00000800;}}//X353
	else{X_FilterDiy[0xEB]=0;X7_FilterData&=0xFFFFF7FF;}

	if(X354){if(X_FilterDiy[0xEC]<X_DIY){X_FilterDiy[0xEC]++;}else{X7_FilterData|=0x00001000;}}//X354
	else{X_FilterDiy[0xEC]=0;X7_FilterData&=0xFFFFEFFF;}

	if(X355){if(X_FilterDiy[0xED]<X_DIY){X_FilterDiy[0xED]++;}else{X7_FilterData|=0x00002000;}}//X355
	else{X_FilterDiy[0xED]=0;X7_FilterData&=0xFFFFDFFF;}

	if(X356){if(X_FilterDiy[0xEE]<X_DIY){X_FilterDiy[0xEE]++;}else{X7_FilterData|=0x00004000;}}//X356
	else{X_FilterDiy[0xEE]=0;X7_FilterData&=0xFFFFBFFF;}

	if(X357){if(X_FilterDiy[0xEF]<X_DIY){X_FilterDiy[0xEF]++;}else{X7_FilterData|=0x00008000;}}//X357
	else{X_FilterDiy[0xEF]=0;X7_FilterData&=0xFFFF7FFF;}

	if(X360){if(X_FilterDiy[0xF0]<X_DIY){X_FilterDiy[0xF0]++;}else{X7_FilterData|=0x00010000;}}//X360
	else{X_FilterDiy[0xF0]=0;X7_FilterData&=0xFFFEFFFF;}

	if(X361){if(X_FilterDiy[0xF1]<X_DIY){X_FilterDiy[0xF1]++;}else{X7_FilterData|=0x00020000;}}//X361
	else{X_FilterDiy[0xF1]=0;X7_FilterData&=0xFFFDFFFF;}

	if(X362){if(X_FilterDiy[0xF2]<X_DIY){X_FilterDiy[0xF2]++;}else{X7_FilterData|=0x00040000;}}//X362
	else{X_FilterDiy[0xF2]=0;X7_FilterData&=0xFFFBFFFF;}

	if(X363){if(X_FilterDiy[0xF3]<X_DIY){X_FilterDiy[0xF3]++;}else{X7_FilterData|=0x00080000;}}//X363
	else{X_FilterDiy[0xF3]=0;X7_FilterData&=0xFFF7FFFF;}

	if(X364){if(X_FilterDiy[0xF4]<X_DIY){X_FilterDiy[0xF4]++;}else{X7_FilterData|=0x00100000;}}//X364
	else{X_FilterDiy[0xF4]=0;X7_FilterData&=0xFFEFFFFF;}

	if(X365){if(X_FilterDiy[0xF5]<X_DIY){X_FilterDiy[0xF5]++;}else{X7_FilterData|=0x00200000;}}//X365
	else{X_FilterDiy[0xF5]=0;X7_FilterData&=0xFFDFFFFF;}

	if(X366){if(X_FilterDiy[0xF6]<X_DIY){X_FilterDiy[0xF6]++;}else{X7_FilterData|=0x00400000;}}//X366
	else{X_FilterDiy[0xF6]=0;X7_FilterData&=0xFFBFFFFF;}

	if(X367){if(X_FilterDiy[0xF7]<X_DIY){X_FilterDiy[0xF7]++;}else{X7_FilterData|=0x00800000;}}//X367
	else{X_FilterDiy[0xF7]=0;X7_FilterData&=0xFF7FFFFF;}

	if(X370){if(X_FilterDiy[0xF8]<X_DIY){X_FilterDiy[0xF8]++;}else{X7_FilterData|=0x01000000;}}//X370
	else{X_FilterDiy[0xF8]=0;X7_FilterData&=0xFEFFFFFF;}

	if(X371){if(X_FilterDiy[0xF9]<X_DIY){X_FilterDiy[0xF9]++;}else{X7_FilterData|=0x02000000;}}//X371
	else{X_FilterDiy[0xF9]=0;X7_FilterData&=0xFDFFFFFF;}

	if(X372){if(X_FilterDiy[0xFA]<X_DIY){X_FilterDiy[0xFA]++;}else{X7_FilterData|=0x04000000;}}//X372
	else{X_FilterDiy[0xFA]=0;X7_FilterData&=0xFBFFFFFF;}

	if(X373){if(X_FilterDiy[0xFB]<X_DIY){X_FilterDiy[0xFB]++;}else{X7_FilterData|=0x08000000;}}//X373
	else{X_FilterDiy[0xFB]=0;X7_FilterData&=0xF7FFFFFF;}

	if(X374){if(X_FilterDiy[0xFC]<X_DIY){X_FilterDiy[0xFC]++;}else{X7_FilterData|=0x10000000;}}//X374
	else{X_FilterDiy[0xFC]=0;X7_FilterData&=0xEFFFFFFF;}

	if(X375){if(X_FilterDiy[0xFD]<X_DIY){X_FilterDiy[0xFD]++;}else{X7_FilterData|=0x20000000;}}//X375
	else{X_FilterDiy[0xFD]=0;X7_FilterData&=0xDFFFFFFF;}

	if(X376){if(X_FilterDiy[0xFE]<X_DIY){X_FilterDiy[0xFE]++;}else{X7_FilterData|=0x40000000;}}//X376
	else{X_FilterDiy[0xFE]=0;X7_FilterData&=0xBFFFFFFF;}

	if(X377){if(X_FilterDiy[0xFF]<X_DIY){X_FilterDiy[0xFF]++;}else{X7_FilterData|=0x80000000;}}//X377
	else{X_FilterDiy[0xFF]=0;X7_FilterData&=0x7FFFFFFF;}

	PLC_RAM32(PLC_R_START_ADD+0x0080)=X_FilterData;
	PLC_RAM32(PLC_R_START_ADD+0x0084)=X1_FilterData;
	PLC_RAM32(PLC_R_START_ADD+0x0088)=X2_FilterData;
	PLC_RAM32(PLC_R_START_ADD+0x008c)=X3_FilterData;
	PLC_RAM32(PLC_R_START_ADD+0x0090)=X4_FilterData;
	PLC_RAM32(PLC_R_START_ADD+0x0094)=X5_FilterData;
	PLC_RAM32(PLC_R_START_ADD+0x0098)=X6_FilterData;
	PLC_RAM32(PLC_R_START_ADD+0x009c)=X7_FilterData;

}

void PLC_IO_BREAK(void)
{


	if(PLC_BIT_TEST(0x0500)){Y0H;}else{Y0L;}	if(PLC_BIT_TEST(0x0501)){Y1H;}else{Y1L;}	
	if(PLC_BIT_TEST(0x0502)){Y2H;}else{Y2L;}	if(PLC_BIT_TEST(0x0503)){Y3H;}else{Y3L;}	
	if(PLC_BIT_TEST(0x0504)){Y4H;}else{Y4L;}	if(PLC_BIT_TEST(0x0505)){Y5H;}else{Y5L;}	
	if(PLC_BIT_TEST(0x0506)){Y6H;}else{Y6L;}	if(PLC_BIT_TEST(0x0507)){Y7H;}else{Y7L;}	

	if(PLC_BIT_TEST(0x0508)){Y10H;}else{Y10L;}	if(PLC_BIT_TEST(0x0509)){Y11H;}else{Y11L;}	
	if(PLC_BIT_TEST(0x050A)){Y12H;}else{Y12L;}	if(PLC_BIT_TEST(0x050B)){Y13H;}else{Y13L;}	
	if(PLC_BIT_TEST(0x050C)){Y14H;}else{Y14L;}	if(PLC_BIT_TEST(0x050D)){Y15H;}else{Y15L;}	
	if(PLC_BIT_TEST(0x050E)){Y16H;}else{Y16L;}	if(PLC_BIT_TEST(0x050F)){Y17H;}else{Y17L;}	

	if(PLC_BIT_TEST(0x0510)){Y20H;}else{Y20L;}	if(PLC_BIT_TEST(0x0511)){Y21H;}else{Y21L;}	
	if(PLC_BIT_TEST(0x0512)){Y22H;}else{Y22L;}	if(PLC_BIT_TEST(0x0513)){Y23H;}else{Y23L;}	
	if(PLC_BIT_TEST(0x0514)){Y24H;}else{Y24L;}	if(PLC_BIT_TEST(0x0515)){Y25H;}else{Y25L;}	
	if(PLC_BIT_TEST(0x0516)){Y26H;}else{Y26L;}	if(PLC_BIT_TEST(0x0517)){Y27H;}else{Y27L;}	

	if(PLC_BIT_TEST(0x0518)){Y30H;}else{Y30L;}	if(PLC_BIT_TEST(0x0519)){Y31H;}else{Y31L;}	
	if(PLC_BIT_TEST(0x051A)){Y32H;}else{Y32L;}	if(PLC_BIT_TEST(0x051B)){Y33H;}else{Y33L;}	
	if(PLC_BIT_TEST(0x051C)){Y34H;}else{Y34L;}	if(PLC_BIT_TEST(0x051D)){Y35H;}else{Y35L;}	
	if(PLC_BIT_TEST(0x051E)){Y36H;}else{Y36L;}	if(PLC_BIT_TEST(0x051F)){Y37H;}else{Y37L;}	

	if(PLC_BIT_TEST(0x0520)){Y40H;}else{Y40L;}	if(PLC_BIT_TEST(0x0521)){Y41H;}else{Y41L;}	
	if(PLC_BIT_TEST(0x0522)){Y42H;}else{Y42L;}	if(PLC_BIT_TEST(0x0523)){Y43H;}else{Y43L;}	
	if(PLC_BIT_TEST(0x0524)){Y44H;}else{Y44L;}	if(PLC_BIT_TEST(0x0525)){Y45H;}else{Y45L;}	
	if(PLC_BIT_TEST(0x0526)){Y46H;}else{Y46L;}	if(PLC_BIT_TEST(0x0527)){Y47H;}else{Y47L;}	

	if(PLC_BIT_TEST(0x0528)){Y50H;}else{Y50L;}	if(PLC_BIT_TEST(0x0529)){Y51H;}else{Y51L;}	
	if(PLC_BIT_TEST(0x0530)){Y52H;}else{Y52L;}	if(PLC_BIT_TEST(0x0531)){Y53H;}else{Y53L;}	
	if(PLC_BIT_TEST(0x0532)){Y54H;}else{Y54L;}	if(PLC_BIT_TEST(0x0533)){Y55H;}else{Y55L;}	
	if(PLC_BIT_TEST(0x0534)){Y56H;}else{Y56L;}	if(PLC_BIT_TEST(0x0535)){Y57H;}else{Y57L;}	

	if(PLC_BIT_TEST(0x0538)){Y60H;}else{Y60L;}	if(PLC_BIT_TEST(0x0539)){Y61H;}else{Y61L;}	
	if(PLC_BIT_TEST(0x053A)){Y62H;}else{Y62L;}	if(PLC_BIT_TEST(0x053B)){Y63H;}else{Y63L;}	
	if(PLC_BIT_TEST(0x053C)){Y64H;}else{Y64L;}	if(PLC_BIT_TEST(0x053D)){Y65H;}else{Y65L;}	
	if(PLC_BIT_TEST(0x053E)){Y66H;}else{Y66L;}	if(PLC_BIT_TEST(0x053F)){Y67H;}else{Y67L;}	

	if(PLC_BIT_TEST(0x0540)){Y70H;}else{Y70L;}	if(PLC_BIT_TEST(0x0541)){Y71H;}else{Y71L;}	
	if(PLC_BIT_TEST(0x0542)){Y72H;}else{Y72L;}	if(PLC_BIT_TEST(0x0543)){Y73H;}else{Y73L;}	
	if(PLC_BIT_TEST(0x0544)){Y74H;}else{Y74L;}	if(PLC_BIT_TEST(0x0545)){Y75H;}else{Y75L;}	
	if(PLC_BIT_TEST(0x0546)){Y76H;}else{Y76L;}	if(PLC_BIT_TEST(0x0547)){Y77H;}else{Y77L;}	

	if(PLC_BIT_TEST(0x0548)){Y100H;}else{Y100L;}	if(PLC_BIT_TEST(0x0549)){Y101H;}else{Y101L;}	
	if(PLC_BIT_TEST(0x054A)){Y102H;}else{Y102L;}	if(PLC_BIT_TEST(0x054B)){Y103H;}else{Y103L;}	
	if(PLC_BIT_TEST(0x054C)){Y104H;}else{Y104L;}	if(PLC_BIT_TEST(0x054D)){Y105H;}else{Y105L;}	
	if(PLC_BIT_TEST(0x054E)){Y106H;}else{Y106L;}	if(PLC_BIT_TEST(0x054F)){Y107H;}else{Y107L;}	

	if(PLC_BIT_TEST(0x0550)){Y110H;}else{Y110L;}	if(PLC_BIT_TEST(0x0551)){Y111H;}else{Y111L;}	
	if(PLC_BIT_TEST(0x0552)){Y112H;}else{Y112L;}	if(PLC_BIT_TEST(0x0553)){Y113H;}else{Y113L;}	
	if(PLC_BIT_TEST(0x0554)){Y114H;}else{Y114L;}	if(PLC_BIT_TEST(0x0555)){Y115H;}else{Y115L;}	
	if(PLC_BIT_TEST(0x0556)){Y116H;}else{Y116L;}	if(PLC_BIT_TEST(0x0557)){Y117H;}else{Y117L;}	

	if(PLC_BIT_TEST(0x0558)){Y120H;}else{Y120L;}	if(PLC_BIT_TEST(0x0559)){Y121H;}else{Y121L;}	
	if(PLC_BIT_TEST(0x055A)){Y122H;}else{Y122L;}	if(PLC_BIT_TEST(0x055B)){Y123H;}else{Y123L;}	
	if(PLC_BIT_TEST(0x055C)){Y124H;}else{Y124L;}	if(PLC_BIT_TEST(0x055D)){Y125H;}else{Y125L;}	
	if(PLC_BIT_TEST(0x055E)){Y126H;}else{Y126L;}	if(PLC_BIT_TEST(0x055F)){Y127H;}else{Y127L;}	

	if(PLC_BIT_TEST(0x0560)){Y130H;}else{Y130L;}	if(PLC_BIT_TEST(0x0561)){Y131H;}else{Y131L;}	
	if(PLC_BIT_TEST(0x0562)){Y132H;}else{Y132L;}	if(PLC_BIT_TEST(0x0563)){Y133H;}else{Y133L;}	
	if(PLC_BIT_TEST(0x0564)){Y134H;}else{Y134L;}	if(PLC_BIT_TEST(0x0565)){Y135H;}else{Y135L;}	
	if(PLC_BIT_TEST(0x0566)){Y136H;}else{Y136L;}	if(PLC_BIT_TEST(0x0567)){Y137H;}else{Y137L;}	

	if(PLC_BIT_TEST(0x0568)){Y140H;}else{Y140L;}	if(PLC_BIT_TEST(0x0569)){Y141H;}else{Y141L;}	
	if(PLC_BIT_TEST(0x056A)){Y142H;}else{Y142L;}	if(PLC_BIT_TEST(0x056B)){Y143H;}else{Y143L;}	
	if(PLC_BIT_TEST(0x056C)){Y144H;}else{Y144L;}	if(PLC_BIT_TEST(0x056D)){Y145H;}else{Y145L;}	
	if(PLC_BIT_TEST(0x056E)){Y146H;}else{Y146L;}	if(PLC_BIT_TEST(0x056F)){Y147H;}else{Y147L;}	

	if(PLC_BIT_TEST(0x0570)){Y150H;}else{Y150L;}	if(PLC_BIT_TEST(0x0571)){Y151H;}else{Y151L;}	
	if(PLC_BIT_TEST(0x0572)){Y152H;}else{Y152L;}	if(PLC_BIT_TEST(0x0573)){Y153H;}else{Y153L;}	
	if(PLC_BIT_TEST(0x0574)){Y154H;}else{Y154L;}	if(PLC_BIT_TEST(0x0575)){Y155H;}else{Y155L;}	
	if(PLC_BIT_TEST(0x0576)){Y156H;}else{Y156L;}	if(PLC_BIT_TEST(0x0577)){Y157H;}else{Y157L;}	

	if(PLC_BIT_TEST(0x0578)){Y160H;}else{Y160L;}	if(PLC_BIT_TEST(0x0579)){Y161H;}else{Y161L;}	
	if(PLC_BIT_TEST(0x057A)){Y162H;}else{Y162L;}	if(PLC_BIT_TEST(0x057B)){Y163H;}else{Y163L;}	
	if(PLC_BIT_TEST(0x057C)){Y164H;}else{Y164L;}	if(PLC_BIT_TEST(0x057D)){Y165H;}else{Y165L;}	
	if(PLC_BIT_TEST(0x057E)){Y166H;}else{Y166L;}	if(PLC_BIT_TEST(0x057F)){Y167H;}else{Y167L;}	

	if(PLC_BIT_TEST(0x0580)){Y170H;}else{Y170L;}	if(PLC_BIT_TEST(0x0581)){Y171H;}else{Y171L;}	
	if(PLC_BIT_TEST(0x0582)){Y172H;}else{Y172L;}	if(PLC_BIT_TEST(0x0583)){Y173H;}else{Y173L;}	
	if(PLC_BIT_TEST(0x0584)){Y174H;}else{Y174L;}	if(PLC_BIT_TEST(0x0585)){Y175H;}else{Y175L;}	
	if(PLC_BIT_TEST(0x0586)){Y176H;}else{Y176L;}	if(PLC_BIT_TEST(0x0587)){Y177H;}else{Y177L;}	

	if(PLC_BIT_TEST(0x0588)){Y200H;}else{Y200L;}	if(PLC_BIT_TEST(0x0589)){Y201H;}else{Y201L;}	
	if(PLC_BIT_TEST(0x058A)){Y202H;}else{Y202L;}	if(PLC_BIT_TEST(0x058B)){Y203H;}else{Y203L;}	
	if(PLC_BIT_TEST(0x058C)){Y204H;}else{Y204L;}	if(PLC_BIT_TEST(0x058D)){Y205H;}else{Y205L;}	
	if(PLC_BIT_TEST(0x058E)){Y206H;}else{Y206L;}	if(PLC_BIT_TEST(0x058F)){Y207H;}else{Y207L;}	
}


void PLC_PWM_RUN(uint16 PWM_Width,uint16 PWM_Cycle,uint16 Y_num)
{if (Y_num==0x0500)
  {if(PWM_Width<PWM_Cycle&&Y0_H_OE==0)
     {Y0_H_OE=1;
	  PWM_Y0_ON_TIMER=PWM_Width;
      PWM_Y0_CYCLE=PWM_Cycle;
	  return;
	  }
  }
 else if(Y_num==0x0501)
  {if(PWM_Width<PWM_Cycle&&Y1_H_OE==0)
     {Y1_H_OE=1;
      PWM_Y1_ON_TIMER=PWM_Width;
      PWM_Y1_CYCLE=PWM_Cycle;
	  return;
	  }
   }
}

void PLC_PWM_STOP(uint16 Y_num)
{if (Y_num==0x0500&&Y0_H_OE==1)
  {Y0_H_OE=3;
   PLC_BIT_OFF(0x0500);
   PLC_BIT_OFF(0x0500);
   Y0_H_OE=0;
   return;}
 else if(Y_num==0x0501&&Y1_H_OE==1)
  {Y1_H_OE=3;
   PLC_BIT_OFF(0x0501);
   PLC_BIT_OFF(0x0501);
   Y1_H_OE=0;
   return;}
}

void PLC_PLSY_RUN(uint32 PLSY_Frequency,uint32 PLSY_Count,uint16 Y_num)
{if (Y_num==0x0500)
  {if(Y0_H_OE==0)
     {Y0_H_OE=2;
	  PLSY_Y0_COUNT=PLSY_Count;
	  if(PLSY_Frequency==0){PLSY_Frequency=2;}
	  else if(PLSY_Frequency>20000){PLSY_Frequency=20000;}
	  }
  if(PLSY_Count==0){PLSY_Y0_COUNT=0x1000000;}
  if(PLSY_Count!=0&&PLSY_Y0_COUNT==0){PLC_BIT_ON(M8029);}
  return;}
 else if(Y_num==0x0501)
  {if(Y1_H_OE==0)
     {Y1_H_OE=2;
	  PLSY_Y1_COUNT=PLSY_Count;
	  if(PLSY_Frequency==0){PLSY_Frequency=2;}
	  else if(PLSY_Frequency>20000){PLSY_Frequency=20000;}
	  }
   if(PLSY_Count==0){PLSY_Y1_COUNT=0x1000000;}
   if(PLSY_Count!=0&&PLSY_Y1_COUNT==0){PLC_BIT_ON(M8029);}
   return;}	
}

void PLC_PLSY_STOP(uint16 Y_num)
{if (Y_num==0x0500&&Y0_H_OE==2)
  {Y0_H_OE=3;
   //if(LPC_GPIO2->FIOPIN&Y0!=Y0)
     /*{*/
      PLC_BIT_OFF(0x0500);
	  //D8140_1++;}
   Y0_H_OE=0;
   return;}
 else if(Y_num==0x0501&&Y1_H_OE==2)
  {Y1_H_OE=3;
   if(1)
     {
      PLC_BIT_OFF(0x0501);
	  D8142_3++;}
   Y1_H_OE=0;
   return;}
}

void H_Y0_Y1_STOP(void)
{
	if(Y0_H_OE!=0)
	{
  		  PLC_BIT_OFF(0x0500);
	}
	 if(Y1_H_OE!=0)
 	{
		PLC_BIT_OFF(0x0501);
	}
}
uint32 PLC_MMS_TIME;
void PLC_M_MS(void)
{
	PLC_MMS_TIME++;
	if(PLC_MMS_TIME%5==0)     {if(PLC_BIT_TEST(M8011)){PLC_BIT_OFF(M8011);}else{PLC_BIT_ON(M8011);}}
	if(PLC_MMS_TIME%50==0)    {if(PLC_BIT_TEST(M8012)){PLC_BIT_OFF(M8012);}else{PLC_BIT_ON(M8012);}}
	if(PLC_MMS_TIME%500==0)   {if(PLC_BIT_TEST(M8013)){PLC_BIT_OFF(M8013);}else{PLC_BIT_ON(M8013);}}
	if(PLC_MMS_TIME%30000==0) {PLC_MMS_TIME=0;if(PLC_BIT_TEST(M8014)){PLC_BIT_OFF(M8014);}else{PLC_BIT_ON(M8014);}}
}

