;/****************************************Copyright (C)**************************************************
;**                               	Email:luheding@126.com
;**                                 QQ:614090042                                            
;**                          如有意见或不明可联系,但要注明来意.否则不回                                 
;**--------------文件信息--------------------------------------------------------------------------------
;**文   件   名: PLC_RUN.c
;**版        本: V2.1
;**创   建   人: LuHeDing
;**最后修改日期: 2010年05月08日
;**描        述: PLC指令解释程序
;** 
;********************************************************************************************************/

#include "PLC_PUBLIC.H"
#include "Instructions.h"
/***********************************************
  函数功能：PLC指令运行
***********************************************/
void PLC_PROG_RUN(void)
{ 
	#ifdef debug
	uint16 temp;
	#endif
	if(PLC_RUN_BIT==3)
	{		
  		if(PLC_PC>=PLC_PROG_END_ADD)
			PLC_PC=PLC_PROG_START_ADD2;		
 		 PLC_TEMP1=PLC_RAM16(PLC_PC);		
		 
		 	debug_send("RUN PLC_PC=0x%x;PLC_TEMP1=0x%x\r\n",PLC_PC,PLC_TEMP1);
			
			switch (PLC_TEMP1)
			{
		/********************纯字指令************************************************/
				case 0xFFF8: //ANB
				{
					anb();
					PLC_PC+=2;
				}break;
				case 0xFFF9: //ORB
				{
					orb();
					PLC_PC+=2;
				}break;
				case 0xFFFA: //MPS
				{
					mps();PLC_PC+=2;
				}break;
				case 0xFFFB: //MRD
				{
					mrd();PLC_PC+=2;
				}break;
				case 0xFFFC: //MPP
				{
					mpp();PLC_PC+=2;
				}break;
				case 0xFFFD: //INV
				{
					inv();PLC_PC+=2;
				}break;
				case 0xFFFF: //NOP
				{
					nop();
				}break;
/********************升降沿指令************************************************/
				case 0x01CA:
				{
					ldp();PLC_PC += 4;
				}break; //LDP
				case 0x01CB:
				{
					ldf();PLC_PC += 4;
				}break; //LDF
				case 0x01CC:
				{
					andp();PLC_PC += 4;
				}break; //ANDP
				case 0x01CD:
				{
					andf();PLC_PC += 4;
				}break; //ANDF
				case 0x01CE:
				{
					orp();PLC_PC += 4;
				}break; //ORP
				case 0x01CF:
				{
					orf();PLC_PC += 4;
				}break; //ORF
				case 0x0008://PLS Y M
				{
					pls_y_m();PLC_PC += 4;
				}break; //PLS	Y M	M1536~
				case 0x0009://PLF Y M	M1536~
				{
					plf_y_m();PLC_PC += 4;
				}break; //PLF Y M M1536~//Y4 09 00 04 85
/********************复位&步进指令************************************************/
				case 0x0002://???????????????????????????????????????????
				{
					out_m8000_m1536();PLC_PC += 4;
				}break; //OUT M8000 M1536~
				case 0x0003:
				{
					set_m8000_m1536();PLC_PC += 4;
				}break; //SET	m1536~3071 M8000
				case 0x0004://RST m1536~3071	M8000
				{			
					rst_m8000_m1536();PLC_PC += 4;
				}break; //RST m1536~3071	M8000
				case 0x0005:
				{
					out_s();PLC_PC += 4;
				}break; //OUT  s
				case 0x0006:
				{
					set_s();PLC_PC += 4;
				}break; //SET S
				case 0x0007:
				{
					rst_s();PLC_PC += 4;
				}break; //RST s
				case 0xF7FF: 
				{
					ret();
				}break;//RET 步进返回
				case 0x000C:
				{
					rst_t_c();PLC_PC += 4;
				}break;
				case 0x000D:
				{
					rst_d();PLC_PC+=6;
				}break; 
/********************功能指令************************************************/
/**																		   **/
/********************程序流程************************************************/
				case 0x0010:
				{
					cj();
				}break; //CJ
				case 0x0012:
				{
					call();
				}break; //CALL
				case 0x0014:
				{
					sret();
				}break; //SRET
				 case 0x001C:
				 {
					fend();
				}break; //FEND
/********************程序流程(P)*********************************************/
				case 0x1010:
				{
					cjp();
				}break; //CJP P1//10 10 02 88 00 80
				case 0x1012:
				{
					callp();
				}break; //CALLP P1//12 10 02 88 00 80
/********************传送比较指令************************************************/
				case 0x0024://CMP
				{
					cmp();PLC_PC+=14;
				}break; //CMP
				case 0x0026://ZCP
	 			{
					zcp();PLC_PC+=18;
				}break; //ZCP
				case 0x0028://MOV
	 			{
					mov();PLC_PC+=10;
				}break; //MOV
				case 0x002E://BMOV(M8024)
	 			{
					bmov();PLC_PC+=14;
				}break; //BMOV(M8024)
/********************(D)传送比较指令*********************************************/
				case 0x0025://CMP
	 			{
					dcmp();PLC_PC+=26;
				}break; //CMP
				case 0x0027://ZCP
	 			{
					dzcp();PLC_PC+=34;
	 			}break; //ZCP
				case 0x0029://MOV
				{
					dmov();PLC_PC+=18;
		 		}break; //MOV
/********************传送比较指令(P)********************************************/
				case 0x1024:
				{
					cmpp();PLC_PC+=14;
				}break; //CMP
				case 0x1026:
				{
					zcpp();PLC_PC+=18;
				}break; //ZCP
				case 0x1028:
				{
					movp();PLC_PC+=10;
				}break; //MOV
				case 0x102E:
				{
					bmovp();PLC_PC+=14;
		 		}break; //BMOV(M8024)
/********************(D)传送比较指令(P)******************************************/
				case 0x1025://CMP
				{
					dcmpp();PLC_PC+=26;
		 		}break; //CMP
				case 0x1027://ZCP
				{
					dzcpp();PLC_PC+=34;
		 		}break; //ZCP
				case 0x1029://MOV
				{
					dmovp();PLC_PC+=18;
				}break; //MOV
/********************四则.逻辑运算*******************************************/
				case 0x0038://ADD(+)M8020(零标志)M8021(借位)M8022(进位)
				{
					add();PLC_PC+=14;
		 		}break; //ADD(+)
				case 0x003A://SUB(-)M8020(零标志)M8021(借位)M8022(进位)
				{
					sub();PLC_PC+=14;
		 		}break; //SUB(-)
				case 0x003C://MUL(*)
				{
					mul();PLC_PC+=14;
		 		}break; //MUL(*)
				case 0x003E: //DIV(/)
				{
					div();PLC_PC+=14;
		 		}break; //DIV(/)
				case 0x0040://INC(++)
				{
					inc();PLC_PC+=6;
				}break;  //INC(++)
				case 0x0042://DEC(--)
				{
					dec();PLC_PC+=6;
		 		}break;  //DEC(--)
				case 0x0044://WAND
				{
					wand();PLC_PC+=14;
		 		}break; //WAND
				case 0x0046://WOR
				{
					wor();PLC_PC+=14;
		 		}break; //WOR
				case 0x0048://WXOR
				{
					wxor();PLC_PC+=14;
		 		}break; //WXOR
/********************(D)四则.逻辑运算*******************************************/
				case 0x0039://ADD(+)M8020(零标志)M8021(借位)M8022(进位)
				{
					dadd();PLC_PC+=26;
		 		}break; //ADD(+)
				case 0x003B://SUB(-)
				{
					dsub();PLC_PC+=26;
		 		}break; //SUB(-)M8020(零标志)M8021(借位)M8022(进位)
				case 0x003D://MUL(*)
				{
					dmul();PLC_PC+=26;
		 		}break; //MUL(*)
				case 0x003F://DIV(/)
				{
					ddiv();PLC_PC+=26;
		 		}break; //DIV(/)
				case 0x0041://INC(++)
				{
					dinc();PLC_PC+=10;
		 		}break; //INC(++)
				case 0x0043://DEC(--)
				{
					ddec();PLC_PC+=10;
		 		}break; //DEC(--)
				case 0x0045://WAND
				{
					dwand();PLC_PC+=26;
		 		}break; //WAND
				case 0x0047://WOR
				{
					dwor();PLC_PC+=26;
		 		}break; //WOR
				case 0x0049://WXOR
				{
					dwxor();PLC_PC+=26;
		 		}break; //WXOR
/********************四则.逻辑运算(P)*******************************************/
				case 0x1038://ADD(+)M8020(零标志)M8021(借位)M8022(进位)
				{
					addp();PLC_PC+=14;
				}break; //ADD(+)
				case 0x103A://SUB(-)M8020(零标志)M8021(借位)M8022(进位)
				{
					subp();PLC_PC+=14;
		 		}break; //SUB(-)
				case 0x103C://MUL(*)
				{
					mulp();PLC_PC+=14;
		 		}break; //MUL(*)
				case 0x103E: //DIV(/)
				{
					divp();PLC_PC+=14;
		 		}break; //DIV(/)
				case 0x1040://INC(++)
				{
					incp();PLC_PC+=6;
		 		}break;  //INC(++)
				case 0x1042://DEC(--)
				{
					decp();PLC_PC+=6;
		 		}break;  //DEC(--)
				case 0x1044://WAND
				{
					wandp();PLC_PC+=14;
				}break; //WAND
				case 0x1046://WOR
				{
					worp();PLC_PC+=14;
		 		}break; //WOR
				case 0x1048://WXOR
				{
					wxorp();PLC_PC+=14;
				}break; //WXOR
/********************(D)四则.逻辑运算(P)*******************************************/
				case 0x1039://ADD(+)M8020(零标志)M8021(借位)M8022(进位)
				{
					daddp();PLC_PC+=26;
				}break; //ADD(+)
				case 0x103B://SUB(-)
				{
					dsubp();PLC_PC+=26;
		 		}break; //SUB(-)M8020(零标志)M8021(借位)M8022(进位)
				case 0x103D://MUL(*)
				{
					dmulp();PLC_PC+=26;
		 		}break; //MUL(*)
				case 0x103F://DIV(/)
				{
					ddivp();PLC_PC+=26;
				}break; //DIV(/)
				case 0x1041://INC(++)
				{
					dincp();PLC_PC+=10;
		 		}break; //INC(++)
				case 0x1043://DEC(--)
				{
					ddecp();PLC_PC+=10;
				}break; //DEC(--)
				case 0x1045://WAND
				{
					dwandp();PLC_PC+=26;
		 		}break; //WAND
				case 0x1047://WOR
				{
					dworp();PLC_PC+=26;
		 		}break; //WOR
				case 0x1049://WXOR
				{
					dwxorp();PLC_PC+=26;
		 		}break; //WXOR
/********************数据处理************************************************/
				case 0x0060: //ZRST
				{
					zrst();PLC_PC+=10;
				}break; //ZRST
/********************数据处理(P)*********************************************/
				case 0x1060: //ZRSTP
				{
					zrstp();PLC_PC+=10;
			 	}break; //ZRSTP
/********************高速指令************************************************/
				case 0x0082:
				{
					plsy();PLC_PC+=14;
		 		}break; //PLSY
				case 0x0084://PWM
				{
					pwm();PLC_PC+=14;
		 		}break; //PWM
/********************(D)高速指令*********************************************/
				case 0x0083:
				{
					dplsy();PLC_PC+=26;
		 		}break; //PLSY
/********************方便指令************************************************/
				case 0x0094://ALT
				{
					alt();PLC_PC+=6;
		 		}break; //ALT
/********************方便指令(P)*********************************************/
				case 0x1094://ALT(P)
				{
					altp();PLC_PC+=6;
		 		}break; //ALT(P)
/********************接点比较************************************************/
				case 0x01D0:
				{
					ld_eq();
		 		}break; //LD=
				case 0x01D2:
				{
					ld_gt();
		 		}break; //LD>
				case 0x01D4:
				{
					ld_lt();
		 		}break; //LD<
				case 0x01D8:
				{
					ld_gt_lt();
		 		}break; //LD<>
				case 0x01DA:
				{
					ld_le();
				}break; //LD<=
				case 0x01DC:
				{
					ld_ge();
		 		}break; //LD>=
				case 0x01E0:
				{
					and_eq();
				}break; //AND=
				case 0x01E2:
				{
					and_gt();
		 		}break; //AND>
				case 0x01E4:
				{
					and_lt();
		 		}break; //AND<
				case 0x01E8:
				{
					and_gt_lt();
		 		}break; //AND<>
				case 0x01EA:
				{
					and_le();
		 		}break; //AND<=
				case 0x01EC:
				{
					and_ge();
				}break; //AND>=
				case 0x01F0:
				{
					or_eq();
		 		}break; //OR=
				case 0x01F2:
				{
					or_gt();
		 		}break; //OR>
				case 0x01F4:
				{
					or_lt();
				}break; //OR<
				case 0x01F8:
				{
					or_gt_lt();
		 		}break; //OR<>
				case 0x01FA:
				{
					or_le();
		 		}break; //OR<=
				case 0x01FC:
				{
					or_ge();
		 		}break; //OR>=
/********************(D)接点比较************************************************/
				case 0x01D1:
				{
					dld_eq();
				}break; //LD=
				case 0x01D3:
				{
					dld_gt();
		 		}break; //LD>
				case 0x01D5:
				{
					dld_lt();
				}break; //LD<
				case 0x01D9:
				{
					dld_gt_lt();
		 		}break; //LD<>
				case 0x01DB:
				{
					dld_le();
		 		}break; //LD<=
				case 0x01DD:
				{
					dld_ge();	
		 		}break; //LD>=
				case 0x01E1:
				{
					dand_eq();
		 		}break; //AND=
				case 0x01E3:
				{
					dand_gt();
		 		}break; //AND>
				case 0x01E5:
				{
					dand_lt();
		 		}break; //AND<
				case 0x01E9:
				{
					dand_gt_lt();
		 		}break; //AND<>
				case 0x01EB:
				{
					dand_le();
		 		}break; //AND<=
				case 0x01ED:
				{
					dand_ge();
		 		}break; //AND>=
				case 0x01F1:
				{
					dor_eq();
		 		}break; //OR=
				case 0x01F3:
				{
					dor_gt();
		 		}break; //OR>
				case 0x01F5:
				{
					dor_lt();
		 		}break; //OR<
				case 0x01F9:
				{
					dor_gt_lt();
		 		}break; //OR<>
				case 0x01FB:
				{
					dor_le();
		 		}break; //OR<=
				case 0x01FD:
				{	
					dor_ge();
		 		}break; //OR>=
/********************结束指令************************************************/
				case 0x000F:{end();}break; //END
/*********************************************************************************/
													//????????????????????????????????????????????????????
				case 0x01C3:{ldi_m1536();}break;//LDI M1536~
				case 0x01C6:{or_m1536();}break;//OR M1536~
				case 0x01C7:{ori_m1536();}break;//ORI M1536~
				case 0x01C5:{ani_m1536();}break;//ANI M1536~
				case 0x01C4:{and_m1536();}break;//AND M1536~
				case 0x01C2:{ld_m1536();}break; //LD M1536~
				case 0x001E:{plc_wdt();}break;//WDT
				case 0x015C:{trd();}break;//TRD 
				case 0x015E:{twr();}break;//TWR 
				case 0x0074:{ref();}break;//REF
				case 0x007B:{dhscs();}break;//DHSCS
				case 0x006C:{ans();}break;//ANS
				case 0x006E:{anr();}break;//ANR
				case 0x0092:{stmr();}break;//STMR
				case 0x0062:{deco();}break;//DECO	
				case 0x000A:{mc();}break;//MC n0 m0
				case 0x000B:{mcr();}break;//MCR n0
				case 0x00AC:{from();}break;//FROM H0A H0E0 D8255 K4
				case 0x00AE:{to();}break;//TO K0 K0 H0 K1
				case 0x0030:{fmov();}break;//FMOV K0 D1000 K8192
				case 0x0088:{ist();}break;//IST M0 S20 S900
				case 0x00AD:{dfrom();}break;//DFROM K0 K26 D10 K1
				case 0x00AF:{dto();}break;//DTO K0 K17 K999999 K1
/********************常规指令************************************************/
/**																		   **/
/********************常规指令************************************************/	 
				default:	 //default(1)
				{
					PLC_CMD=PLC_TEMP1&0xF000;
					switch (PLC_CMD)//switch(2)
					{
						case 0x2000:{ld();}break;//LD						
						case 0x3000:{ldi();}break;//LDI
						case 0x4000:{and();}break; //AND				
		    				case 0x5000:{ani();}break;//ANI
						case 0x6000:{or();}break;//OR
						case 0x7000:{ori();}break; //ORI				
						case 0xB000:{PLC_PC+=2;debug_send("未知啥用，p的地址标号\r\n");}break;
						case 0xC000:{out_y_m();}break;//OUT Y M
						case 0xD000:{set_y_m();}break;//SET M0~M1535 Y
						case 0xE000:{rst_y_m();}break;
						case 0xF000:{stl();}break;//STL 
						default: //default(2)
						{
							PLC_CMD=PLC_TEMP1&0xFF00;							   			
							switch (PLC_CMD)//switch(3)
							{
								case 0x0600:{out();}break; 
		           					case 0x0E00:{out_c();}break;//END OUT C
				   				default:{PLC_PROG_ERROR(6505);}break;	//指令出错
							}//END switch(3)
		   	   			}break;//END default(2)
					}//END switch(2)
				}break;//END default(1)
			}//END switch(1)									
/***********************************************/
		}//结束PLC_RUN_BIT==3 
  		else if(PLC_RUN_BIT==4){PLC_STL_RUN();}//
		else if(PLC_RUN_BIT==1){PLC_PROG_TEST();} 	
}
