;/****************************************Copyright (C)**************************************************
;**                               	
;**                                                                            
;**                                   
;**--------------文件信息--------------------------------------------------------------------------------
;**文   件   名: PLC_ProgTest.c
;**版        本: V2.1
;**创   建   人: LuHeDing
;**最后修改日期: 2010年05月08日
;**描        述: PLC程序运行前测试(用于检测程序中有无错误)
;** 
;********************************************************************************************************/
#include "PLC_PUBLIC.H"
/***********************************************
  函数功能：PLC指令测试
***********************************************/

void PLC_PROG_TEST(void)
{

	if(PLC_RUN_BIT==1)
	{
		PLC_RESET_RAM();
		PLC_RUN_BIT=2; 
	}

 	if(PLC_RUN_BIT==2)		//测试运行标志
	{		
		PLC_PC=PLC_PROG_START_ADD2;//初始PLC_PC指针
		while (PLC_PC<PLC_PROG_END_ADD)
		{
			PLC_TEMP1=PLC_RAM16(PLC_PC);//取指令
 			switch (PLC_TEMP1)
			{
/********************纯字指令************************************************/
				 case 0xFFF8: {PLC_PC+=2;debug_send("ANB\r\n");}break;//ANB
				 case 0xFFF9: {PLC_PC+=2;debug_send("ORB\r\n");}break;//ORB
				 case 0xFFFA: {PLC_PC+=2;debug_send("MPS\r\n");}break;//MPS
				 case 0xFFFB: {PLC_PC+=2;debug_send("MRD\r\n");}break;//MRD
				 case 0xFFFC: {PLC_PC+=2;debug_send("MPP\r\n");}break;//MPP
				 case 0xFFFD: {PLC_PC+=2;debug_send("INV\r\n");}break;//INV
				 case 0xFFFF: {PLC_PC+=2;debug_send("NOP\r\n");}break;//NOP
				 
/********************升降沿指令************************************************/
				 case 0x01CA:{PLC_PC+=4;debug_send("LDP\r\n");}break; //LDP
				 case 0x01CB:{PLC_PC+=4;debug_send("LDF\r\n");}break; //LDF
				 case 0x01CC:{PLC_PC+=4;debug_send("ANDP\r\n");}break; //ANDP
				 case 0x01CD:{PLC_PC+=4;debug_send("ANDF\r\n");}break; //ANDF
				 case 0x01CE:{PLC_PC+=4;debug_send("ORP\r\n");}break; //ORP
				 case 0x01CF:{PLC_PC+=4;debug_send("ORF\r\n");}break; //ORF
				 case 0x0008:{
				 				debug_send("PLS Y M M1536~\r\n");
				 				if(((PLC_RAM8(PLC_PC+3)&0xf0)!=0x80) && ((PLC_RAM8(PLC_PC+3)&0xf0)!=0xA0) )
				 				{
									PLC_PROG_ERROR(6501);
									debug_send("PLS Y M M1536~PLC_PROG_ERROR\r\n");
				 				}
								PLC_PC+=4;
							}break; //PLS Y M
				 case 0x0009:{
				 				debug_send("PLF Y M M1536~\r\n");
				 				if(((PLC_RAM8(PLC_PC+3)&0xf0)!=0x80) && ((PLC_RAM8(PLC_PC+3)&0xf0)!=0xA0) )
				 				{
									PLC_PROG_ERROR(6501);
									debug_send("PLF Y M M1536~PLC_PROG_ERROR\r\n");
				 				}
								PLC_PC+=4;
							}break; //PLF Y M
							
/********************复位&步进指令************************************************/
				 case 0x0002:{
								#ifdef	debug
								if(PLC_RAM8(PLC_PC+3)==0x8f)
								{
									debug_send("OUT M8000~\r\n");
								}
								if((PLC_RAM8(PLC_PC+3) & 0xF0) ==0xA0)
								{
									debug_send("OUT M1536~\r\n");
								}
								#endif
				 				if(((PLC_RAM8(PLC_PC+3)&0xf0)!=0x80) && ((PLC_RAM8(PLC_PC+3)&0xf0)!=0xA0) )
				 				{
									PLC_PROG_ERROR(6501);
									debug_send("OUT M8000 M1536~PLC_PROG_ERROR\r\n");
				 				}
								PLC_PC+=4;
							}break; //OUT M8000
				 case 0x0003:{
				 				debug_send("SET M8000 M1536~\r\n");
				 				if(((PLC_RAM8(PLC_PC+3)&0xf0)!=0x80) && ((PLC_RAM8(PLC_PC+3)&0xf0)!=0xA0) )
				 				{
									PLC_PROG_ERROR(6501);
									debug_send("SET M8000 M1536~PLC_PROG_ERROR\r\n");
				 				}
								PLC_PC+=4;
							}break; //SET M8000
				 case 0x0004:{
				 				debug_send("RST M8000 M1536~\r\n");
				 				if(((PLC_RAM8(PLC_PC+3)&0xf0)!=0x80) && ((PLC_RAM8(PLC_PC+3)&0xf0)!=0xA0) )
				 				{
									PLC_PROG_ERROR(6501);
									debug_send("RST M8000 M1536~ PLC_PROG_ERROR\r\n");
				 				}
								PLC_PC+=4;
							}break; //RST M8000
				 case 0x0005:{
				 				debug_send("OUT S\r\n");
				 				if(PLC_RAM8(PLC_PC+3)>0x83)
				 				{
									PLC_PROG_ERROR(6501);
									debug_send("OUT S  PLC_PROG_ERROR\r\n");
								}
								PLC_PC+=4;
							}break; //OUT S
				 case 0x0006:{
				 				debug_send("SET S\r\n");
				 				if(PLC_RAM8(PLC_PC+3)>0x83)
				 				{
									PLC_PROG_ERROR(6501);
									debug_send("SET S PLC_PROG_ERROR\r\n");
				 				}
								PLC_PC+=4;
							}break; //SET S
				 case 0x0007:{
				 				debug_send("RST S\r\n");
				 				if(PLC_RAM8(PLC_PC+3)>0x83) 
				 				{
									PLC_PROG_ERROR(6501);
									debug_send("RST S PLC_PROG_ERROR\r\n");
				 				}
								PLC_PC+=4;
							}break; //RST S
				 case 0xF7FF:{PLC_STL_ADD=0x03FF;PLC_STL_CMD=0;PLC_PC+=2;debug_send("RET 步进返回\r\n");}break;//RET 步进返回
				 case 0x000C:{
				 				debug_send("RST T0||RST C0	 \r\n");
				 				if(PLC_RAM8(PLC_PC+3)!=0x86&&PLC_RAM8(PLC_PC+3)!=0x8e)
				 				{
									PLC_PROG_ERROR(6501);
									debug_send("RST T0||RST C0 PLC_PROG_ERROR\r\n");
				 				}
					 			PLC_PC+=4;
							}break; //RST T0||RST C0	 	 
				 case 0x000D:{
				 				debug_send("RST D0\r\n");
				 				PLC_ProgDataTest(PLC_PC+2,1);
								if(PLC_ProgTypeReturn(PLC_PC+2)!=0x02)//RST D0-D8255
					  			{
					  				PLC_PROG_ERROR(6501);
									debug_send("RST D0 操作的数据数型出错\r\n");
								}//操作的数据数型出错
					 			PLC_PC+=6;
							}break; //RST D0
/********************功能指令************************************************/
/**																		   **/
/********************程序流程************************************************/
				 case 0x0010:{
				 				debug_send("CJ\r\n");
				 				if(PLC_P_TEST(PLC_RAM8(PLC_PC+2)/2)==0&&	//如果测试位没启动
					   				 PLC_RAM16(PLC_R_START_ADD+0x5700+PLC_RAM8(PLC_PC+2))==0)//如果没有地址
					  			{
					  			 	PLC_P_ON(PLC_RAM8(PLC_PC+2)/2);   //启动测试位
					    				PLC_RAM16(PLC_R_START_ADD+0x5700+PLC_RAM8(PLC_PC+2))=(PLC_PC-PLC_PROG_START_ADD2);//保存现调用的地址
								}
								 PLC_PC+=6;
							 }break; //CJ
				 case 0x0012:{
				 				debug_send("CALL\r\n");
				 				if(PLC_P_TEST(PLC_RAM8(PLC_PC+2)/2)==0&&	//如果测试位没启动
									    PLC_RAM16(PLC_R_START_ADD+0x5700+PLC_RAM8(PLC_PC+2))==0)//如果没有地址
					  			{
					  				PLC_P_ON(PLC_RAM8(PLC_PC+2)/2);   //启动测试位
					    				PLC_RAM16(PLC_R_START_ADD+0x5700+PLC_RAM8(PLC_PC+2))=PLC_PC-PLC_PROG_START_ADD2;
								}//保存现调用的地址
								 PLC_PC+=6;
							}break; //CALL
				 case 0x0014:{	
				 				debug_send("SRET\r\n");
				 				if(PLC_P_TEST(PLC_RAM8(PLC_PC+2)/2)==0&&	//如果测试位没启动
					   				 PLC_RAM16(PLC_R_START_ADD+0x5700+PLC_RAM8(PLC_PC+2))==0)//如果没有地址
								{
									PLC_P_ON(PLC_RAM8(PLC_PC+2)/2);   //启动测试位
					    				PLC_RAM16(PLC_R_START_ADD+0x5700+PLC_RAM8(PLC_PC+2))=PLC_PC-PLC_PROG_START_ADD2;}//保存现调用的地址
								 PLC_PC+=2;
								}break; //SRET
				 case 0x001C:{PLC_PC+=2;}break; //FEND
/********************程序流程(P)************************************************/
				 case 0x1010:{
				 				debug_send("CJP P1//10 10 02 88 00 80\r\n");
				 				if(PLC_P_TEST(PLC_RAM8(PLC_PC+2)/2)==0&&	//如果测试位没启动
					  				  PLC_RAM16(PLC_R_START_ADD+0x5700+PLC_RAM8(PLC_PC+2))==0)//如果没有地址
					  			{
					  				PLC_P_ON(PLC_RAM8(PLC_PC+2)/2);   //启动测试位
					    				PLC_RAM16(PLC_R_START_ADD+0x5700+PLC_RAM8(PLC_PC+2))=(PLC_PC-PLC_PROG_START_ADD2);
								}//保存现调用的地址
								 PLC_PC+=6;
							}break; //CJP P1//10 10 02 88 00 80
				 case 0x1012:{
				 				debug_send("CALL P1//12 10 02 88 00 80\r\n");
				 				if(PLC_P_TEST(PLC_RAM8(PLC_PC+2)/2)==0&&	//如果测试位没启动
					  				  PLC_RAM16(PLC_R_START_ADD+0x5700+PLC_RAM8(PLC_PC+2))==0)//如果没有地址
					  			 {
					  			 	PLC_P_ON(PLC_RAM8(PLC_PC+2)/2);   //启动测试位
					    				PLC_RAM16(PLC_R_START_ADD+0x5700+PLC_RAM8(PLC_PC+2))=PLC_PC-PLC_PROG_START_ADD2;
								}//保存现调用的地址
								 PLC_PC+=6;
							}break; //CALL P1//12 10 02 88 00 80
/********************传送比较指令************************************************/
				case 0x0024:{PLC_ProgDataTest(PLC_PC+2,3);PLC_PC+=14;debug_send("CMP\r\n");}break; //CMP
	 			case 0x0026:{PLC_ProgDataTest(PLC_PC+2,4);PLC_PC+=18;debug_send("ZCP\r\n");}break; //ZCP
	 			case 0x0028:{PLC_ProgDataTest(PLC_PC+2,2);PLC_PC+=10;debug_send("MOV\r\n");}break; //MOV
	 			case 0x002E:{PLC_ProgDataTest(PLC_PC+2,3);PLC_PC+=14;debug_send("BMOV(M8024)\r\n");}break; //BMOV(M8024)
/********************(D)传送比较指令*********************************************/
	 			case 0x0025:{PLC_ProgDataTest(PLC_PC+2,6);PLC_PC+=26;debug_send("CMP(D)\r\n");}break; //CMP
	 			case 0x0027:{PLC_ProgDataTest(PLC_PC+2,8);PLC_PC+=34;debug_send("ZCP(D)\r\n");}break; //ZCP
				 case 0x0029:{PLC_ProgDataTest(PLC_PC+2,4);PLC_PC+=18;debug_send("MOV(D)\r\n");}break; //MOV
/********************传送比较指令(P)********************************************/
	 			case 0x1024:{PLC_ProgDataTest(PLC_PC+2,3);PLC_PC+=14;debug_send("CMP(P)\r\n");}break; //CMP
				 case 0x1026:{PLC_ProgDataTest(PLC_PC+2,4);PLC_PC+=18;debug_send("ZCP(P)\r\n");}break; //ZCP
				 case 0x1028:{PLC_ProgDataTest(PLC_PC+2,2);PLC_PC+=10;debug_send("MOV(P)\r\n");}break; //MOV
				 case 0x102E:{PLC_ProgDataTest(PLC_PC+2,3);PLC_PC+=14;debug_send("BMOV(M8024)(P)\r\n");}break; //BMOV(M8024)
/********************(D)传送比较指令(P)******************************************/
				 case 0x1025:{PLC_ProgDataTest(PLC_PC+2,6);PLC_PC+=26;debug_send("CMP(D)(P)\r\n");}break; //CMP
				 case 0x1027:{PLC_ProgDataTest(PLC_PC+2,8);PLC_PC+=34;debug_send("ZCP(D)(P)\r\n");}break; //ZCP
				 case 0x1029:{PLC_ProgDataTest(PLC_PC+2,4);PLC_PC+=18;debug_send("MOV(D)(P)\r\n");}break; //MOV
/********************四则.逻辑运算*******************************************/
				case 0x0038:{PLC_ProgDataTest(PLC_PC+2,3);PLC_PC+=14;debug_send("ADD(+)M8020(零标志)M8021(借位)M8022(进位)\r\n");}break; //ADD(+)M8020(零标志)M8021(借位)M8022(进位)
				case 0x003A:{PLC_ProgDataTest(PLC_PC+2,3);PLC_PC+=14;debug_send("SUB(-)M8020(零标志)M8021(借位)M8022(进位)\r\n");}break; //SUB(-)M8020(零标志)M8021(借位)M8022(进位)
				case 0x003C:{PLC_ProgDataTest(PLC_PC+2,3);PLC_PC+=14;debug_send("MUL(*)\r\n");}break; //MUL(*)
				case 0x003E:{PLC_ProgDataTest(PLC_PC+2,3);PLC_PC+=14;debug_send("DIV(/)\r\n");}break; //DIV(/)
				case 0x0040:{PLC_ProgDataTest(PLC_PC+2,1);PLC_PC+=6;debug_send("INC(++)\r\n");}break;  //INC(++)
				case 0x0042:{PLC_ProgDataTest(PLC_PC+2,1);PLC_PC+=6;debug_send("DEC(--)\r\n");}break;  //DEC(--)
				case 0x0044:{PLC_ProgDataTest(PLC_PC+2,3);PLC_PC+=14;debug_send("WAND\r\n");}break; //WAND
				case 0x0046:{PLC_ProgDataTest(PLC_PC+2,3);PLC_PC+=14;debug_send("WOR\r\n");}break; //WOR
				case 0x0048:{PLC_ProgDataTest(PLC_PC+2,3);PLC_PC+=14;debug_send("WXOR\r\n");}break; //WXOR
/********************(D)四则.逻辑运算*******************************************/
				case 0x0039:{PLC_ProgDataTest(PLC_PC+2,6);PLC_PC+=26;debug_send("ADD(+)M8020(零标志)M8021(借位)M8022(进位)(D)\r\n");}break; //ADD(+)M8020(零标志)M8021(借位)M8022(进位)
				case 0x003B:{PLC_ProgDataTest(PLC_PC+2,6);PLC_PC+=26;debug_send("SUB(-)M8020(零标志)M8021(借位)M8022(进位)(D)\r\n");}break; //SUB(-)M8020(零标志)M8021(借位)M8022(进位)
				case 0x003D:{PLC_ProgDataTest(PLC_PC+2,6);PLC_PC+=26;debug_send("MUL(*)(D)\r\n");}break; //MUL(*)
				case 0x003F:{PLC_ProgDataTest(PLC_PC+2,6);PLC_PC+=26;debug_send("DIV(/)(D)\r\n");}break; //DIV(/)
				case 0x0041:{PLC_ProgDataTest(PLC_PC+2,2);PLC_PC+=10;debug_send("INC(++)(D)\r\n");}break; //INC(++)
				case 0x0043:{PLC_ProgDataTest(PLC_PC+2,2);PLC_PC+=10;debug_send("DEC(--)(D)\r\n");}break; //DEC(--)
				case 0x0045:{PLC_ProgDataTest(PLC_PC+2,6);PLC_PC+=26;debug_send("WAND(D)\r\n");}break; //WAND
				case 0x0047:{PLC_ProgDataTest(PLC_PC+2,6);PLC_PC+=26;debug_send("WOR(D)\r\n");}break; //WOR
				case 0x0049:{PLC_ProgDataTest(PLC_PC+2,6);PLC_PC+=26;debug_send("WXOR(D)\r\n");}break; //WXOR
/********************四则.逻辑运算(P)*******************************************/
				 case 0x1038:{PLC_ProgDataTest(PLC_PC+2,3);PLC_PC+=14;debug_send("ADD(+)M8020(零标志)M8021(借位)M8022(进位)(P)\r\n");}break; //ADD(+)M8020(零标志)M8021(借位)M8022(进位)
				 case 0x103A:{PLC_ProgDataTest(PLC_PC+2,3);PLC_PC+=14;debug_send("SUB(-)M8020(零标志)M8021(借位)M8022(进位)(P)\r\n");}break; //SUB(-)M8020(零标志)M8021(借位)M8022(进位)
				 case 0x103C:{PLC_ProgDataTest(PLC_PC+2,3);PLC_PC+=14;debug_send("MUL(*)(P)\r\n");}break; //MUL(*)
				 case 0x103E:{PLC_ProgDataTest(PLC_PC+2,3);PLC_PC+=14;debug_send("DIV(/)(P)\r\n");}break; //DIV(/)
				 case 0x1040:{PLC_ProgDataTest(PLC_PC+2,1);PLC_PC+=6;debug_send("INC(++)(P)\r\n");}break;  //INC(++)
				 case 0x1042:{PLC_ProgDataTest(PLC_PC+2,1);PLC_PC+=6;debug_send("DEC(--)(P)\r\n");}break;  //DEC(--)
				 case 0x1044:{PLC_ProgDataTest(PLC_PC+2,3);PLC_PC+=14;debug_send("WAND(P)\r\n");}break; //WAND
				 case 0x1046:{PLC_ProgDataTest(PLC_PC+2,3);PLC_PC+=14;debug_send("WOR(P)\r\n");}break; //WOR
				 case 0x1048:{PLC_ProgDataTest(PLC_PC+2,3);PLC_PC+=14;debug_send("WXOR(P)\r\n");}break; //WXOR
/********************(D)四则.逻辑运算(P)*******************************************/
				case 0x1039:{PLC_ProgDataTest(PLC_PC+2,6);PLC_PC+=26;debug_send("ADD(+)M8020(零标志)M8021(借位)M8022(进位)(D)(P)\r\n");}break; //ADD(+)M8020(零标志)M8021(借位)M8022(进位)
				case 0x103B:{PLC_ProgDataTest(PLC_PC+2,6);PLC_PC+=26;debug_send("SUB(-)M8020(零标志)M8021(借位)M8022(进位)(D)(P)\r\n");}break; //SUB(-)M8020(零标志)M8021(借位)M8022(进位)
				case 0x103D:{PLC_ProgDataTest(PLC_PC+2,6);PLC_PC+=26;debug_send("MUL(*)(D)(P)\r\n");}break; //MUL(*)
				case 0x103F:{PLC_ProgDataTest(PLC_PC+2,6);PLC_PC+=26;debug_send("DIV(/)(D)(P)\r\n");}break; //DIV(/)
				case 0x1041:{PLC_ProgDataTest(PLC_PC+2,2);PLC_PC+=10;debug_send("INC(++)(D)(P)\r\n");}break; //INC(++)
				case 0x1043:{PLC_ProgDataTest(PLC_PC+2,2);PLC_PC+=10;debug_send("DEC(--)(D)(P)\r\n");}break; //DEC(--)
				case 0x1045:{PLC_ProgDataTest(PLC_PC+2,6);PLC_PC+=26;debug_send("WAND(D)(P)\r\n");}break; //WAND
				case 0x1047:{PLC_ProgDataTest(PLC_PC+2,6);PLC_PC+=26;debug_send("WOR(D)(P)\r\n");}break; //WOR
				case 0x1049:{PLC_ProgDataTest(PLC_PC+2,6);PLC_PC+=26;debug_send("WXOR(D)(P)\r\n");}break; //WXOR
/********************数据处理************************************************/
				case 0x0060:{
								debug_send("ZRST\r\n");
								PLC_ProgDataTest(PLC_PC+2,2);
								 if(PLC_ProgTypeReturn(PLC_PC+2)!=PLC_ProgTypeReturn(PLC_PC+6))
		   						{
		   							PLC_PROG_ERROR(6501);
									debug_send("操作类型不一至\r\n");
								}//操作类型不一至
								 PLC_PC+=10;
							}break; //ZRST
/********************数据处理(P)*********************************************/
				case 0x1060:{
								debug_send("ZRSTP\r\n");
								PLC_ProgDataTest(PLC_PC+2,2);
								if(PLC_ProgTypeReturn(PLC_PC+2)!=PLC_ProgTypeReturn(PLC_PC+6))
								{
									PLC_PROG_ERROR(6501);
									debug_send("操作类型不一至\r\n");
								}//操作类型不一至
								PLC_PC+=10;
								}break; //ZRSTP
/********************高速指令************************************************/
				 case 0x0082:{debug_send("PLSY\r\n");PLC_ProgDataTest(PLC_PC+2,3);PLC_PC+=14;}break; //PLSY
				 case 0x0084:{debug_send("PWM\r\n");PLC_ProgDataTest(PLC_PC+2,3);PLC_PC+=14;}break; //PWM
/********************(D)高速指令*********************************************/
				case 0x0083:{debug_send("PLSY(D)\r\n");PLC_ProgDataTest(PLC_PC+2,6);PLC_PC+=26;}break; //PLSY
/********************方便指令************************************************/
				case 0x0094:{debug_send("ALT\r\n");PLC_ProgDataTest(PLC_PC+2,1);PLC_PC+=6;}break; //ALT
				case 0x1094:{debug_send("ALT(P)\r\n");PLC_ProgDataTest(PLC_PC+2,1);PLC_PC+=6;}break; //ALT(P)
/********************接点比较************************************************/
				case 0x01D0:{debug_send("LD=\r\n");PLC_ProgDataTest(PLC_PC+2,2);PLC_PC+=10;}break; //LD=
				case 0x01D2:{debug_send("LD>\r\n");PLC_ProgDataTest(PLC_PC+2,2);PLC_PC+=10;}break; //LD>
				case 0x01D4:{debug_send("LD<\r\n");PLC_ProgDataTest(PLC_PC+2,2);PLC_PC+=10;}break; //LD<
				case 0x01D8:{debug_send("LD<>\r\n");PLC_ProgDataTest(PLC_PC+2,2);PLC_PC+=10;}break; //LD<>
				case 0x01DA:{debug_send("LD<=\r\n");PLC_ProgDataTest(PLC_PC+2,2);PLC_PC+=10;}break; //LD<=
				case 0x01DC:{debug_send("LD>=\r\n");PLC_ProgDataTest(PLC_PC+2,2);PLC_PC+=10;}break; //LD>=

				case 0x01E0:{debug_send("AND=\r\n");PLC_ProgDataTest(PLC_PC+2,2);PLC_PC+=10;}break; //AND=
				case 0x01E2:{debug_send("AND>\r\n");PLC_ProgDataTest(PLC_PC+2,2);PLC_PC+=10;}break; //AND>
				case 0x01E4:{debug_send("AND<\r\n");PLC_ProgDataTest(PLC_PC+2,2);PLC_PC+=10;}break; //AND<
				case 0x01E8:{debug_send("AND<>\r\n");PLC_ProgDataTest(PLC_PC+2,2);PLC_PC+=10;}break; //AND<>
				case 0x01EA:{debug_send("AND<=\r\n");PLC_ProgDataTest(PLC_PC+2,2);PLC_PC+=10;}break; //AND<=
				case 0x01EC:{debug_send("AND>=\r\n");PLC_ProgDataTest(PLC_PC+2,2);PLC_PC+=10;}break; //AND>=

				case 0x01F0:{debug_send("OR=\r\n");PLC_ProgDataTest(PLC_PC+2,2);PLC_PC+=10;}break; //OR=
				case 0x01F2:{debug_send("OR>\r\n");PLC_ProgDataTest(PLC_PC+2,2);PLC_PC+=10;}break; //OR>
				case 0x01F4:{debug_send("OR<\r\n");PLC_ProgDataTest(PLC_PC+2,2);PLC_PC+=10;}break; //OR<
				case 0x01F8:{debug_send("OR<>\r\n");PLC_ProgDataTest(PLC_PC+2,2);PLC_PC+=10;}break; //OR<>
				case 0x01FA:{debug_send("OR<=\r\n");PLC_ProgDataTest(PLC_PC+2,2);PLC_PC+=10;}break; //OR<=
				case 0x01FC:{debug_send("OR>=\r\n");PLC_ProgDataTest(PLC_PC+2,2);PLC_PC+=10;}break; //OR>=
/********************(D)接点比较************************************************/
				case 0x01D1:{debug_send("LD=\r\n");PLC_ProgDataTest(PLC_PC+2,4);PLC_PC+=18;}break; //LD=
				case 0x01D3:{debug_send("LD>(D)\r\n");PLC_ProgDataTest(PLC_PC+2,4);PLC_PC+=18;}break; //LD>
				case 0x01D5:{debug_send("LD<(D)\r\n");PLC_ProgDataTest(PLC_PC+2,4);PLC_PC+=18;}break; //LD<
				case 0x01D9:{debug_send("LD<>(D)\r\n");PLC_ProgDataTest(PLC_PC+2,4);PLC_PC+=18;}break; //LD<>
				case 0x01DB:{debug_send("LD<=(D)\r\n");PLC_ProgDataTest(PLC_PC+2,4);PLC_PC+=18;}break; //LD<=
				case 0x01DD:{debug_send("LD>=(D)\r\n");PLC_ProgDataTest(PLC_PC+2,4);PLC_PC+=18;}break; //LD>=

				case 0x01E1:{debug_send("AND=(D)\r\n");PLC_ProgDataTest(PLC_PC+2,4);PLC_PC+=18;}break; //AND=
				case 0x01E3:{debug_send("AND>(D)\r\n");PLC_ProgDataTest(PLC_PC+2,4);PLC_PC+=18;}break; //AND>
				case 0x01E5:{debug_send("AND<(D)\r\n");PLC_ProgDataTest(PLC_PC+2,4);PLC_PC+=18;}break; //AND<
				case 0x01E9:{debug_send("AND<>(D)\r\n");PLC_ProgDataTest(PLC_PC+2,4);PLC_PC+=18;}break; //AND<>
				case 0x01EB:{debug_send("AND<=(D)\r\n");PLC_ProgDataTest(PLC_PC+2,4);PLC_PC+=18;}break; //AND<=
				case 0x01ED:{debug_send("AND>=(D)\r\n");PLC_ProgDataTest(PLC_PC+2,4);PLC_PC+=18;}break; //AND>=

				case 0x01F1:{debug_send("OR=(D)\r\n");PLC_ProgDataTest(PLC_PC+2,4);PLC_PC+=18;}break; //OR=
				case 0x01F3:{debug_send("OR>(D)\r\n");PLC_ProgDataTest(PLC_PC+2,4);PLC_PC+=18;}break; //OR>
				case 0x01F5:{debug_send("OR<(D)\r\n");PLC_ProgDataTest(PLC_PC+2,4);PLC_PC+=18;}break; //OR<
				case 0x01F9:{debug_send("OR<>(D)\r\n");PLC_ProgDataTest(PLC_PC+2,4);PLC_PC+=18;}break; //OR<>
				case 0x01FB:{debug_send("OR<=(D)\r\n");PLC_ProgDataTest(PLC_PC+2,4);PLC_PC+=18;}break; //OR<=
				case 0x01FD:{debug_send("OR>=(D)\r\n");PLC_ProgDataTest(PLC_PC+2,4);PLC_PC+=18;}break; //OR>=
/********************结束指令************************************************/
				case 0x000F:{
				 				debug_send("//END 运行PLC(M8000)\r\n");
								for(PLC_TEMP1=0;PLC_TEMP1<128;PLC_TEMP1++)				//测试P0-P127
								{
									if(PLC_P_TEST(PLC_TEMP1))	//测试P(x)
									{
										if(PLC_RAM16(PLC_R_START_ADD+0x5700+(PLC_TEMP1*2)))//测试保存的地址是否为0
										{
											if(PLC_RAM16(PLC_PROG_START_ADD2+PLC_RAM16(PLC_R_START_ADD+0x5700+(PLC_TEMP1*2)))!=(0xB000+PLC_TEMP1))
											{
												PLC_PC=PLC_RAM16(PLC_R_START_ADD+0x5700+(PLC_TEMP1*2));
												PLC_PROG_ERROR(9501); //指令出错 CJ,CALL,无地址(P)
												debug_send("指令出错 CJ,CALL,无地址(P)\r\n");
												PLC_TEMP1=128;
											}
										}		   //退出测试
									}
								}
								if(PLC_STL_CMD!=0)
								{
									PLC_PROG_ERROR(9501);
									debug_send("无步进返回指令\r\n");
								} //无步进返回指令
								if(D8065==0&&D8068==0)
								{
									PLC_RUN_BIT=3;				 //启动PLC运行标志
									BOT_BIT=0xaa;				 //启动掉电标志
									PLC_BIT_ON(M8002);
									PLC_BIT_OFF(M8003);
									PLC_BIT_ON(M8000);
								}		 //启动M8000
								PLC_PC=PLC_PROG_END_ADD;       //返回PC指针
					           	  }break; //END 运行PLC(M8000)
/*************************************************************************/
				case 0x0088:{PLC_PC+=14;debug_send("IST\r\n");}break;//IST M0 S20 S900
				case 0x00AD:{PLC_PC+=34;debug_send("DFROM\r\n");}break;//DFROM K0 K26 D10 K1
				case 0x00AF:{PLC_PC+=34;debug_send("DTO\r\n");}break;//DTO K0 K17 K999999 K1
				case 0x0030:{PLC_PC+=14;debug_send("FMOV\r\n");}break;//FMOV K0 D1000 K8192
				case 0x00AC:{PLC_PC+=18;debug_send("FROM\r\n");}break;//FROM H0A H0E0 D8255 K4
				case 0x00AE:{PLC_PC+=18;debug_send("TO\r\n");}break;//TO K0 K0 H0 K1
				case 0x0062:{PLC_PC+=14;debug_send("DECO\r\n");}break;//DECO
				case 0x0092:{PLC_PC+=14;debug_send("STMR\r\n");}break;//STMR
				case 0x006C:{PLC_PC+=14;debug_send("ANS\r\n");}break;//ANS
				case 0x006E:{PLC_PC+=2;debug_send("ANR\r\n");}break;//ANR
				case 0x007B:{PLC_PC+=26;debug_send("DHSCS\r\n");}break;//DHSCS
				case 0x0074:{PLC_PC+=10;debug_send("REF\r\n");}break;//REF
				case 0x015C:{PLC_PC+=6;debug_send("TRD\r\n");}break;//TRD 
				case 0x015E:{PLC_PC+=6;debug_send("TWR\r\n");}break;//TWR 
				case 0x000A:{PLC_PC+=6;debug_send("MC\r\n");}break;//MC n0 m0
				case 0x000B:{PLC_PC+=4;debug_send("MCR\r\n");}break;//MCR n0
				case 0x00B4:{PLC_PC+=14;debug_send("ASCI\r\n");}break;//ASCI D0 D1 K1
				case 0x00B6:{PLC_PC+=14;debug_send("HEX\r\n");}break;//HEX D0 D1 K1
				case 0x00B0:{PLC_PC+=18;debug_send("RS\r\n");}break;//RS D200 K11 D500 K0
				case 0x0056:{PLC_PC+=18;debug_send("SFTL\r\n");}break;//SFTL M21 M200 K12 K1
				case 0x0054:{PLC_PC+=18;debug_send("SFTR\r\n");}break;//SFTR M300 M300 K16 K1
				case 0x01C3:
					{
						if((PLC_RAM8(PLC_PC+3)&0xf0)!=0xA0) 
				 		{
							PLC_PROG_ERROR(6501);
							debug_send("LDI M1536~ PLC_PROG_ERROR\r\n");
				 		}
						PLC_PC+=4;
						debug_send("LDI M1536~\r\n");						
					}break;//LDI M1536~
				case 0x01C6:
					{
						if((PLC_RAM8(PLC_PC+3)&0xf0)!=0xA0) 
				 		{
							PLC_PROG_ERROR(6501);
							debug_send("OR M1536~ PLC_PROG_ERROR\r\n");
				 		}
						PLC_PC+=4;
						debug_send("OR M1536~\r\n");
					}break;//OR M1536~
				case 0x01C7:
					{
						if((PLC_RAM8(PLC_PC+3)&0xf0)!=0xA0) 
				 		{
							PLC_PROG_ERROR(6501);
							debug_send("ORI M1536~ PLC_PROG_ERROR\r\n");
				 		}
						PLC_PC+=4;
						debug_send("ORI M1536~\r\n");
					}break;//ORI M1536~
				case 0x01C5:
					{
						if((PLC_RAM8(PLC_PC+3)&0xf0)!=0xA0) 
				 		{
							PLC_PROG_ERROR(6501);
							debug_send("ANI M1536~ PLC_PROG_ERROR\r\n");
				 		}
						PLC_PC+=4;
						debug_send("ANI M1536~\r\n");
					}break;//ANI M1536~
				case 0x01C4:
					{
						if((PLC_RAM8(PLC_PC+3)&0xf0)!=0xA0) 
				 		{
							PLC_PROG_ERROR(6501);
							debug_send("AND M1536~ PLC_PROG_ERROR\r\n");
				 		}
						PLC_PC+=4;
						debug_send("AND M1536~\r\n");
					}break;//AND M1536~
				case 0x01C2:
					{
						if((PLC_RAM8(PLC_PC+3)&0xf0)!=0xA0) 
				 		{
							PLC_PROG_ERROR(6501);
							debug_send("LD M1536~ PLC_PROG_ERROR\r\n");
				 		}
						PLC_PC+=4;
						debug_send("LD M1536~\r\n");
					}break;//LD M1536~
				case 0x001E:{PLC_PC+=2;debug_send("WDT\r\n");}break;//WDT
/********************常规指令************************************************/	 
				default:	{												//default(1)
	 						PLC_CMD=PLC_TEMP1&0Xf000;							   			//分离指令
	 						switch (PLC_CMD)//switch(2)
	 	   					{
	 	   						case 0x2000: {PLC_PC+=2;debug_send("LD\r\n");}break;//LD 
		    						case 0x3000: {PLC_PC+=2;debug_send("LDI\r\n");}break;//LDI 
		   						case 0x4000: {PLC_PC+=2;debug_send("AND\r\n");}break;//AND 
		    						case 0x5000: {PLC_PC+=2;debug_send("ANI\r\n");}break;//ANI 
		    						case 0x6000: {PLC_PC+=2;debug_send("OR\r\n ");}break;//OR  
		    						case 0x7000: {PLC_PC+=2;debug_send("ORI\r\n ");}break;//ORI 
		    						case 0xB000: {
												debug_send("P(1)I(1)\r\n ");
			   									if((PLC_TEMP1&0xff00)==0xb000)//P(x)
				  								{
				  									debug_send("启动测试位\r\n");
				  									PLC_P_ON(PLC_RAM8(PLC_TEMP1&0x00ff));   //启动测试位
				    									PLC_RAM16(PLC_R_START_ADD+0x5700+((PLC_TEMP1&0x00ff)*2))=PLC_PC-PLC_PROG_START_ADD2;
												}
												//else if((PLC_TEMP1&0xff00)==0xb000)//I(x)
												else
												{
													PLC_PROG_ERROR(6501);
													debug_send("指令出错\r\n");
												}	//指令出错
			    									PLC_PC+=2;
											}break;//P(1)I(1) 	
		   						case 0xC000: {PLC_PC+=2;debug_send("OUT Y M\r\n");}break;//OUT Y M	
							  	case 0xD000: {PLC_PC+=2;debug_send("SET Y M	\r\n");}break;//SET Y M	
							    	case 0xE000: {PLC_PC+=2;debug_send("RST Y M	");}break;//RST Y M	
								case 0xF000:	{								//STL 
												debug_send("STL S\r\n");
												if((PLC_TEMP1&0x0fff)>0x03ff)
												{
													PLC_PROG_ERROR(1916);
													debug_send("指令与操作数出错\r\n");
												}	//指令与操作数出错
			     									PLC_STL_CMD=1;																						//********************************************

												if((PLC_PC-PLC_STL_ADD) == 2)
												{
													s[cont]=s[0];
													cont++;
													s[cont]=PLC_TEMP1;
												}
												s[0]=PLC_TEMP1;
												PLC_STL_ADD=PLC_PC;
												PLC_PC+=2;
											}break;//STL S
								default:{								 //default(2)
			  							 	PLC_CMD=PLC_TEMP1&0xFF00;							   			//分离指令
	 	        								switch (PLC_CMD)				//switch(3)
				 							{
				 								case 0x0600:
												{
													debug_send("OUT\r\n");	
													PLC_ProgDataTest(PLC_PC+2,1);
		              									PLC_PC+=6;
													
												}break; //OUT 
		         									case 0x0E00:
												{
													debug_send("END OUT C\r\n");	
													if((PLC_TEMP1&0x00FF)<200) 		 
		 				         						 {
		 				         						 	PLC_ProgDataTest(PLC_PC+2,1);
						          							 PLC_PC+=6;
													}	 				   
		 			          							 else{
														 	PLC_ProgDataTest(PLC_PC+2,2);
					                								 PLC_PC+=10;
														} 
		 			           						 }break;//END OUT C
				  								 default:
												 {
												 	PLC_PROG_ERROR(6506);
													debug_send("指令出错\r\n");	
												}break;	//指令出错
		   		 							 }//END switch(3)
		   	 							}break;//END default(2)
		  					}//END switch(2)
				}break;//END default(1)
			}//END switch(1)									
/***********************************************/  
   }//END while
   }//END test_M8000
}

