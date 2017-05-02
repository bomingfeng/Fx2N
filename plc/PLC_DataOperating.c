;/****************************************Copyright (C)**************************************************
;**                               
;**                                                                            
;**                                   
;**--------------文件信息--------------------------------------------------------------------------------
;**文   件   名: PLC_DataOperating.c
;**版        本: V2.1
;**创   建   人: LuHeDing
;**最后修改日期: 2010年05月08日
;**描        述: PLC数据操作函数集合
;** 
;********************************************************************************************************/

#include "PLC_PUBLIC.H"
/***********************************************
  函数功能:PLC 数据类型测试(pc(data))
  入口:已提取的数据
  出口:高16位为类型识别号  
  	   0和其它=无效操作; 
	   1=常量;2=变量;3=变量K1(M);4=变量K2(M);5=变量K3(M);6=变量K4(M);
	   7=变量K5(M);8=变量K6(M);9=变量K7(M);A=变量K8(M);B=位变量;
	   低16位为地址   
***********************************************/
uint32 PLC_DataTypeTest(uint32 Data)
{
	uint32 cmd;
	uint32 TempAdd=((Data&0x0f0000)/0x100)+(Data%0x100);
	cmd=Data&0xff00ff00;
	switch(cmd)
	{	
		case 0x80008200:{cmd=0x010000;debug_send("新增常量H\r\n");}break;//常量
		case 0x80008000:{cmd=0x010000;debug_send("常量\r\n");}break;//常量
		case 0x86008600:{cmd=0x020000|(TempAdd+0x1000);debug_send("变量D0-D999\r\n");}break;//变量D0-D999
		case 0x88008600:{cmd=0x020000|(((Data&0xFF0000)/0x100)+(Data%0x100)+0x17D0);debug_send("变量D1000-D7999 \r\n");}break;//变量D1000-D7999  
		case 0x80008600:{cmd=0x020000|(TempAdd+0x0E00);debug_send("变量D8000-D8255\r\n");}break;//变量D8000-D8255
		case 0x82008600:{cmd=0x020000|(TempAdd+0x0800);debug_send("变量T0-T255\r\n");}break;//变量T0-T255
		case 0x84008600:{cmd=0x020000|(TempAdd+0x0A00);debug_send("变量C0-C255\r\n");}break;//变量C0-C255
		case 0x82008400:{cmd=0x030000|TempAdd;debug_send("变量K1(M0) M10 0A 84 08 82\r\n");}break;//变量K1(M0) M10 0A 84 08 82
		case 0x84008400:{cmd=0x040000|TempAdd;debug_send("变量K2(M0) M10 0A 84 08 84\r\n");}break;//变量K2(M0) M10 0A 84 08 84
		case 0x86008400:{cmd=0x050000|TempAdd;debug_send("变量K3(M0) M10 0A 84 08 86\r\n");}break;//变量K3(M0) M10 0A 84 08 86
		case 0x88008400:{cmd=0x060000|TempAdd;debug_send("变量K4(M0) M10 0A 84 08 88\r\n");}break;//变量K4(M0) M10 0A 84 08 88
		case 0x8A008400:{cmd=0x070000|TempAdd;debug_send("变量K5(M0) M10 0A 84 08 8A\r\n");}break;//变量K5(M0) M10 0A 84 08 8A
		case 0x8C008400:{cmd=0x080000|TempAdd;debug_send("变量K6(M0) M10 0A 84 08 8C\r\n");}break;//变量K6(M0) M10 0A 84 08 8C
		case 0x8E008400:{cmd=0x090000|TempAdd;debug_send("变量K7(M0) M10 0A 84 08 8E\r\n");}break;//变量K7(M0) M10 0A 84 08 8E
		case 0x90008400:{cmd=0x0A0000|TempAdd;debug_send("变量K8(M0) M10 0A 84 08 90\r\n");}break;//变量K8(M0) M10 0A 84 08 90
		case 0x80008400:{cmd=0x0B0000|TempAdd;debug_send("Bit变量\r\n");}break;//Bit变量
		//(Z)
	 	case 0x8600A600://变量D0-D999 Z0-Z3
		{
			debug_send("变量D0-D999 Z0-Z3\r\n");
			cmd=Data&0x00f00000;
			switch(cmd)
		    	{
		    		case 0x00000000:{cmd=D8028;debug_send("Z0\r\n");}break;   //Z0
				case 0x00400000:{cmd=D8182;debug_send("Z1\r\n");}break;   //Z1
				case 0x00800000:{cmd=D8184;debug_send("Z2\r\n");}break;   //Z2
				case 0x00c00000:{cmd=D8186;debug_send("Z3\r\n");}break;   //Z3
				default:{cmd=0xFF6000;debug_send("变址Z地址未知\r\n");}break;	//变址Z地址未知
			}
		 	cmd=(cmd*2)+TempAdd+0x1000;
		 	if(cmd>0x4E7E||cmd<0x1000)
			{
				cmd=0xFF6000;debug_send("数据读取地址超出\r\n");
			}//数据读取地址超出
		 	else 
				cmd|=0x020000;
		}break;//END变量D0-D999 Z0-Z3
		case 0x8700A600://变量D0-D999 Z4-Z7
	 	{
			debug_send("变量D0-D999 Z4-Z7\r\n");
			cmd=Data&0x00f00000;
			switch(cmd)
			{
				case 0x00000000:{cmd=D8188;debug_send("Z4\r\n");}break;   //Z4
				case 0x00400000:{cmd=D8190;debug_send("Z5\r\n");}break;   //Z5
				case 0x00800000:{cmd=D8192;debug_send("Z6\r\n");}break;   //Z6
				case 0x00c00000:{cmd=D8194;debug_send("Z7\r\n");}break;   //Z7
				default:{cmd=0xFF6000;debug_send("变址Z地址未知\r\n");}break;	//变址Z地址未知
			}
		 	cmd=(cmd*2)+TempAdd+0x1000;
		 	if(cmd>0x4E7E||cmd<0x1000)
			{
				cmd=0xFF6000;debug_send("数据读取地址超出\r\n");
			}//数据读取地址超出
			else 
				cmd|=0x020000;
		}break;//END 变量D0-D999 Z4-Z7
		case 0x8800A600://变量D1000-D7999 Z0-Z3
	 	{
			debug_send("变量D1000-D7999 Z0-Z3\r\n");
			cmd=(Data&0x00f00000)-((Data&0x00F00000)%0x00400000);
			switch(cmd)
			{
				case 0x00000000:{cmd=D8028;debug_send("Z0\r\n");}break;   //Z0
				case 0x00400000:{cmd=D8182;debug_send("Z1\r\n");}break;   //Z1
				case 0x00800000:{cmd=D8184;debug_send("Z2\r\n");}break;   //Z2
				case 0x00c00000:{cmd=D8186;debug_send("Z3\r\n");}break;   //Z3
				default:{cmd=0xFF6000;debug_send("变址Z地址未知\r\n");}break;	//变址Z地址未知
			}
		 	cmd=((cmd*2)+TempAdd+(((Data&0x00F00000)%0x00400000)/0x100)+0x17D0);
		 	if(cmd>0x4E7E||cmd<0x1000)
			{
				cmd=0xFF6000;debug_send("数据读取地址超出\r\n");
			}//数据读取地址超出
		 	else 
				cmd|=0x020000;
		}break;//END 变量D1000-D7999 Z0-Z3
		case 0x8900A600://变量D1000-D7999 Z4-Z7
	 	{	
			debug_send("变量D1000-D7999 Z4-Z7\r\n");
			cmd=(Data&0x00f00000)-((Data&0x00F00000)%0x00400000);
		 	switch(cmd)
		    	{
				case 0x00000000:{cmd=D8188;debug_send("Z4\r\n");}break;   //Z4
				case 0x00400000:{cmd=D8190;debug_send("Z5\r\n");}break;   //Z5
				case 0x00800000:{cmd=D8192;debug_send("Z6\r\n");}break;   //Z6
				case 0x00c00000:{cmd=D8194;debug_send("Z7\r\n");}break;   //Z7
				default:{cmd=0xFF6000;debug_send("变址Z地址未知\r\n");}break;	//变址Z地址未知
			}
			cmd=((cmd*2)+TempAdd+(((Data&0x00F00000)%0x00400000)/0x100)+0x17D0);
			if(cmd>0x4E7E||cmd<0x1000)
			{
				debug_send("数据读取地址超出\r\n");
				cmd=0xFF6000;
			}//数据读取地址超出
		 	else 
				cmd|=0x020000;
		}break;//END 变量D1000-D7999 Z4-Z7
		default:{cmd=0xFF6000;debug_send("非法操作\r\n");}break;	//非法操作
	}
	return cmd;
}

/***********************************************
  函数功能:专用于开始程序操作数据测试
  入口参数:pc数据开始地址
           count测试个数
***********************************************/
void PLC_ProgDataTest(uint32 pc,uint8 count)
{
	uint32 temp;
	 for(;count!=0;count--)
	 {
	 	temp=PLC_DataTypeTest((PLC_RAM16(pc+2)*0X10000)+PLC_RAM16(pc));
		pc+=4;
	 	if((temp&0xff0000)==0x010000)
		{
			;
		}
	 	else if((temp&0xff0000)==0x020000)
		{
			if((temp&0xFFFF)>0x4E7F)
			{
				PLC_PROG_ERROR(1020);
				debug_send("字节操作数出错\r\n");
			}
		}//字节操作数出错
		 else if((temp&0xff0000)==0x030000){;}//K1(M0)
		 else if((temp&0xff0000)==0x040000){;}//K2(M0)
		 else if((temp&0xff0000)==0x050000){;}//K3(M0)
		 else if((temp&0xff0000)==0x060000){;}//K4(M0)
	 	else if((temp&0xff0000)==0x070000){;}//K5(M0)
		 else if((temp&0xff0000)==0x080000){;}//K6(M0)
	 	else if((temp&0xff0000)==0x090000){;}//K7(M0)
	 	else if((temp&0xff0000)==0x0A0000){;}//K8(M0)
		 else if((temp&0xff0000)==0x0B0000){;}//Bit
	 	else {PLC_PROG_ERROR(1020);count=0;debug_send("操作数出错\r\n");}//操作数出错
	 }//end for	
}


/***********************************************
  函数功能:从程序中返回地址
***********************************************/
uint16 PLC_ProgAddReturn(uint32 pc)
{
	return PLC_DataTypeTest((PLC_RAM16(pc+2)*0X10000)+PLC_RAM16(pc))&0xffff;
}


/***********************************************
  函数功能:从程序中返回类型
  0和其它=无效类型; 
  1=常量;2=变量;3=变量K1(M);4=变量K2(M);5=变量K3(M);6=变量K4(M);
  7=变量K5(M);8=变量K6(M);9=变量K7(M);A=变量K8(M);B=位变量;
***********************************************/
uint16 PLC_ProgTypeReturn(uint32 pc)
{
	return (PLC_DataTypeTest((PLC_RAM16(pc+2)*0X10000)+PLC_RAM16(pc))&0xff0000)/0x10000;
}

/***********************************************
  函数功能:从程序中返回类型及地址
  0和其它=无效类型; 
  1=常量;2=变量;3=变量K1(M);4=变量K2(M);5=变量K3(M);6=变量K4(M);
  7=变量K5(M);8=变量K6(M);9=变量K7(M);A=变量K8(M);B=位变量;
***********************************************/
uint32 PLC_ProgTypeAddReturn(uint32 pc)
{return PLC_DataTypeTest((PLC_RAM16(pc+2)*0X10000)+PLC_RAM16(pc));
}


/***********************************************
  函数功能:字节数据批量复位
***********************************************/
void PLC_ByteReset(uint16 BitStartAdd,uint16 BitEndAdd)
{
	uint32 SAdd,EAdd;
	uint16 Temp;
	if(BitStartAdd>BitEndAdd)//如果地址倒序
	{
		Temp=BitStartAdd;
		BitStartAdd=BitEndAdd;
		BitEndAdd=Temp;
	}
	SAdd=PLC_R_START_ADD+BitStartAdd;
	EAdd=PLC_R_START_ADD+BitEndAdd;
	while (SAdd<=EAdd)
	{
		if(SAdd%4==0&&(EAdd-SAdd)>=4)
		{
			PLC_RAM32(SAdd)=0;
			SAdd+=4;
		}
		else
		{
			PLC_RAM8(SAdd)=0;
			SAdd++;
		}
	} 
}

/***********************************************
  函数功能:位数据批量复位
***********************************************/
void PLC_BitReset(uint16 BitStartAdd,uint16 BitEndAdd)
{
	while (BitStartAdd<=BitEndAdd)
	{
		if(BitStartAdd%8==0&&(BitEndAdd-BitStartAdd)>=8)
	 	{
	 		PLC_RAM8(PLC_R_START_ADD+(BitStartAdd/8))=0;
			BitStartAdd+=8;
		}
		else
		{
			PLC_BIT_OFF(BitStartAdd);BitStartAdd++;
		}
	}
}

/***********************************************
  函数功能:位数据读
  入口参数:BitStartAdd 开始地址 >=0x0000 <=0x0FFF
		   BitCount    读取个数1-32
  出口参数:返回读取的数值
***********************************************/
uint32 PLC_BitDataRead(uint16 BitStartAdd,uint8 BitCount)
{uint32 r_data=0;
 uint16 EndAdd=BitStartAdd+BitCount;
while (1)
 {EndAdd--;
  if(PLC_BIT_TEST(EndAdd))r_data|=0x01;
  if(BitStartAdd==EndAdd)return r_data;
  r_data<<=1;}
}

/***********************************************
  函数功能:位数据写
  入口参数:BitStartAdd 开始地址 >=0x0000 <=0x0FFF
		   BitCount    写入个数1-64
		   data		   要写入的数据
  出口参数:无
***********************************************/
void PLC_BitDataWrite(uint16 BitStartAdd,uint8 BitCount,uint32 data)
{uint16 EndAdd=BitStartAdd+BitCount;
 for(;BitStartAdd<EndAdd;BitStartAdd++)
   {if(data&0x01)PLC_BIT_ON(BitStartAdd);
	else PLC_BIT_OFF(BitStartAdd);
	data>>=1;}
}

/***********************************************
  函数功能:字节数据64位写
  1=常量;2=变量;3=变量K1(M);4=变量K2(M);5=变量K3(M);6=变量K4(M);
  7=变量K5(M);8=变量K6(M);9=变量K7(M);A=变量K8(M);
***********************************************/
void PLC_ByteWrite64(uint32 pc,uint32 Data,uint32 Data2)
{uint32 cmd_add;
 uint32 cmd;
 cmd_add=PLC_DataTypeTest((PLC_RAM16(pc+2)*0X10000)+PLC_RAM16(pc));
 cmd=cmd_add&0xff0000;
 cmd_add&=0x0000ffff;
 switch(cmd)
	{case 0x00020000://变量
		{PLC_RAM16(PLC_R_START_ADD+cmd_add)=Data;
		 PLC_RAM16(PLC_R_START_ADD+cmd_add+2)=(Data/0x10000);
		 PLC_RAM16(PLC_R_START_ADD+cmd_add+4)=Data2;
		 PLC_RAM16(PLC_R_START_ADD+cmd_add+6)=(Data2/0x10000);
		}break;   //END 变量
	 case 0x00030000:
	 	{PLC_BitDataWrite(cmd_add,4,Data);
		 PLC_BitDataWrite(cmd_add+4,4,Data2);}break;    //变量K1(M)
	 case 0x00040000:
	 	{PLC_BitDataWrite(cmd_add,8,Data);
		 PLC_BitDataWrite(cmd_add+8,8,Data2);}break;    //变量K2(M)
	 case 0x00050000:
	 	{PLC_BitDataWrite(cmd_add,12,Data);
		 PLC_BitDataWrite(cmd_add+12,12,Data2);}break;   //变量K3(M)
	 case 0x00060000:
	 	{PLC_BitDataWrite(cmd_add,16,Data);
		 PLC_BitDataWrite(cmd_add+16,16,Data2);}break;   //变量K4(M)
	 case 0x00070000:
	 	{PLC_BitDataWrite(cmd_add,20,Data);
		 PLC_BitDataWrite(cmd_add+20,20,Data2);}break;   //变量K5(M)
	 case 0x00080000:
	 	{PLC_BitDataWrite(cmd_add,24,Data);
		 PLC_BitDataWrite(cmd_add+24,24,Data2);}break;   //变量K6(M)
	 case 0x00090000:
	 	{PLC_BitDataWrite(cmd_add,28,Data);
		 PLC_BitDataWrite(cmd_add+28,28,Data);}break;   //变量K7(M)
	 case 0x000A0000:
	 	{PLC_BitDataWrite(cmd_add,32,Data);
		 PLC_BitDataWrite(cmd_add+32,32,Data);}break;   //变量K8(M)
	 default:{PLC_PROG_ERROR(0x12);}break;	//不支持操作
	}

}

/***********************************************
  函数功能:字节数据32位写
  1=常量;2=变量;3=变量K1(M);4=变量K2(M);5=变量K3(M);6=变量K4(M);
  7=变量K5(M);8=变量K6(M);9=变量K7(M);A=变量K8(M);
***********************************************/
void PLC_ByteWrite32(uint32 pc,uint32 Data)
{uint32 cmd_add;
 uint32 cmd;
 cmd_add=PLC_DataTypeTest((PLC_RAM16(pc+2)*0X10000)+PLC_RAM16(pc));
 cmd=cmd_add&0xff0000;
 cmd_add&=0x0000ffff;
 switch(cmd)
	{case 0x00020000://变量
		{PLC_RAM16(PLC_R_START_ADD+cmd_add)=Data;
		 PLC_RAM16(PLC_R_START_ADD+cmd_add+2)=Data/0x10000;
		}break;   //END 变量
	 case 0x00030000:{PLC_BitDataWrite(cmd_add,4,Data);}break;    //变量K1(M)
	 case 0x00040000:{PLC_BitDataWrite(cmd_add,8,Data);}break;    //变量K2(M)
	 case 0x00050000:{PLC_BitDataWrite(cmd_add,12,Data);}break;   //变量K3(M)
	 case 0x00060000:{PLC_BitDataWrite(cmd_add,16,Data);}break;   //变量K4(M)
	 case 0x00070000:{PLC_BitDataWrite(cmd_add,20,Data);}break;   //变量K5(M)
	 case 0x00080000:{PLC_BitDataWrite(cmd_add,24,Data);}break;   //变量K6(M)
	 case 0x00090000:{PLC_BitDataWrite(cmd_add,28,Data);}break;   //变量K7(M)
	 case 0x000A0000:{PLC_BitDataWrite(cmd_add,32,Data);}break;   //变量K8(M)
	 default:{PLC_PROG_ERROR(0x12);}break;	//不支持操作
	}

}

/***********************************************
  函数功能:字节数据16位写
  1=常量;2=变量;3=变量K1(M);4=变量K2(M);5=变量K3(M);6=变量K4(M);
***********************************************/
void PLC_ByteWrite16(uint32 pc,uint16 Data)
{
	uint32 cmd_add;
	uint32 cmd;
	cmd_add=PLC_DataTypeTest((PLC_RAM16(pc+2)*0X10000)+PLC_RAM16(pc));
	cmd=cmd_add&0xff0000;
	cmd_add&=0x0000ffff;
	switch(cmd)
	{
		case 0x00020000:{PLC_RAM16(PLC_R_START_ADD+cmd_add)=Data;}break;   //变量
	 	case 0x00030000:{PLC_BitDataWrite(cmd_add,4,Data);}break;    //变量K1(M)
	 	case 0x00040000:{PLC_BitDataWrite(cmd_add,8,Data);}break;    //变量K2(M)
	 	case 0x00050000:{PLC_BitDataWrite(cmd_add,12,Data);}break;   //变量K3(M)
	 	case 0x00060000:{PLC_BitDataWrite(cmd_add,16,Data);}break;   //变量K4(M)
	 	default:{PLC_PROG_ERROR(0x12);}break;	//不支持操作
	}
}

/***********************************************
  函数功能:字节数据32位读
  1=常量;2=变量;3=变量K1(M);4=变量K2(M);5=变量K3(M);6=变量K4(M);
  7=变量K5(M);8=变量K6(M);9=变量K7(M);A=变量K8(M);
***********************************************/
uint32 PLC_ByteRead32(uint32 pc)
{uint32 cmd_add;
 uint32 cmd;
 cmd_add=PLC_DataTypeTest((PLC_RAM16(pc+2)*0X10000)+PLC_RAM16(pc));
 cmd=cmd_add&0xff0000;
 cmd_add&=0x0000ffff;
 switch(cmd)
	{case 0x00010000://常量
		{cmd=((PLC_RAM8(pc+2)*0X100)+PLC_RAM8(pc)+
		      (PLC_RAM8(pc+6)*0X1000000)+(PLC_RAM8(pc+4)*0X10000));
		}break;   //END 常量
	 case 0x00020000://变量
		{cmd=PLC_RAM16(PLC_R_START_ADD+cmd_add)+(PLC_RAM16(PLC_R_START_ADD+cmd_add+2)*0x10000);
		}break;   //END 变量
	 case 0x00030000:{cmd=PLC_BitDataRead(cmd_add,4);}break;    //变量K1(M)
	 case 0x00040000:{cmd=PLC_BitDataRead(cmd_add,8);}break;    //变量K2(M)
	 case 0x00050000:{cmd=PLC_BitDataRead(cmd_add,12);}break;   //变量K3(M)
	 case 0x00060000:{cmd=PLC_BitDataRead(cmd_add,16);}break;   //变量K4(M)
	 case 0x00070000:{cmd=PLC_BitDataRead(cmd_add,20);}break;   //变量K5(M)
	 case 0x00080000:{cmd=PLC_BitDataRead(cmd_add,24);}break;   //变量K6(M)
	 case 0x00090000:{cmd=PLC_BitDataRead(cmd_add,28);}break;   //变量K7(M)
	 case 0x000A0000:{cmd=PLC_BitDataRead(cmd_add,32);}break;   //变量K8(M)
	 default:{PLC_PROG_ERROR(0x12);}break;	//不支持操作
	}
return cmd;
}

/***********************************************
  函数功能:字节数据16位读
  1=常量;2=变量;3=变量K1(M);4=变量K2(M);5=变量K3(M);6=变量K4(M);
***********************************************/
uint16 PLC_ByteRead16(uint32 pc)
{
	uint32 cmd_add;
	uint32 cmd;
	cmd_add=PLC_DataTypeTest((PLC_RAM16(pc+2)*0X10000)+PLC_RAM16(pc));
	cmd=cmd_add&0xff0000;
	cmd_add&=0x0000ffff;
	switch(cmd)
	{
		case 0x00010000:
		{
			cmd=(PLC_RAM8(pc+2)*0X100)+PLC_RAM8(pc);
		}break;//END 常量
		case 0x00020000://变量
		{
			cmd=PLC_RAM16(PLC_R_START_ADD+cmd_add)+(PLC_RAM16(PLC_R_START_ADD+cmd_add+2)*0x10000);
		}break;   //END 变量
		case 0x00030000:
		{
			cmd=PLC_BitDataRead(cmd_add,4);
		}break;    //变量K1(M)
		case 0x00040000:
		{
			cmd=PLC_BitDataRead(cmd_add,8);
		}break;    //变量K2(M)
		case 0x00050000:
		{
			cmd=PLC_BitDataRead(cmd_add,12);
		}break;   //变量K3(M)
		case 0x00060000:
		{
			cmd=PLC_BitDataRead(cmd_add,16);
		}break;   //变量K4(M)
		default:
		{
			PLC_PROG_ERROR(0x12);
		}break;	//不支持操作
	}
	return cmd;
}
