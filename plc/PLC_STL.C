;/****************************************Copyright (C)**************************************************
;**                               	Email:luheding@126.com
;**                                 QQ:614090042                                            
;**                          如有意见或不明可联系,但要注明来意.否则不回                               
;**--------------文件信息--------------------------------------------------------------------------------
;**文   件   名: PLC_STL.c
;**版        本: V2.1
;**创   建   人: LuHeDing
;**最后修改日期: 2010年05月08日
;**描        述: PLC专用于STL指令中的程序解释
;** 
;********************************************************************************************************/

#include "PLC_PUBLIC.H"
/***********************************************
  函数功能：PLC指令运行
***********************************************/
void PLC_STL_RUN(void)
{ 
	PLC_TEMP1=PLC_RAM16(PLC_PC);										//取指令
	debug_send("STL PLC_PC=0x%x;PLC_TEMP1=0x%x\r\n",PLC_PC,PLC_TEMP1);
	switch (PLC_TEMP1)
	{
/********************纯字指令************************************************/
		case 0xFFF8: {if(PLC_STL_CMD==1)anb();PLC_PC += 2;}break;//ANB
		case 0xFFF9: {if(PLC_STL_CMD==1)orb();PLC_PC += 2;}break;//ORB
		case 0xFFFA: {if(PLC_STL_CMD==1)mps();PLC_PC += 2;}break;//MPS
		case 0xFFFB: {if(PLC_STL_CMD==1)mrd();PLC_PC += 2;}break;//MRD
		case 0xFFFC: {if(PLC_STL_CMD==1)mpp();PLC_PC += 2;}break;//MPP
		case 0xFFFD: {if(PLC_STL_CMD==1)inv();PLC_PC += 2;}break;//INV
		case 0xFFFF: {nop();}break;//NOP
/********************升降沿指令************************************************/
		case 0x01CA:{if(PLC_STL_CMD==1)ldp();PLC_PC += 4;}break; //LDP
		case 0x01CB:{if(PLC_STL_CMD==1)ldf();PLC_PC += 4;}break; //LDF
		case 0x01CC:{if(PLC_STL_CMD==1)andp();PLC_PC += 4;}break; //ANDP
		case 0x01CD:{if(PLC_STL_CMD==1)andf();PLC_PC += 4;}break; //ANDF
		case 0x01CE:{if(PLC_STL_CMD==1)orp();PLC_PC+=4;}break; //ORP
		case 0x01CF:{if(PLC_STL_CMD==1)orf();PLC_PC+=4;}break; //ORF
		case 0x0008:{if(PLC_STL_CMD==1)pls_y_m();PLC_PC+=4;}break;  
		case 0x0009:{if(PLC_STL_CMD==1)plf_y_m();PLC_PC+=4;}break; 
/********************复位&步进指令************************************************/
		case 0x0002:{if(PLC_STL_CMD==1)out_m8000_m1536();PLC_PC+=4;}break; 
		case 0x0003:{if(PLC_STL_CMD==1)set_m8000_m1536();PLC_PC+=4;}break; 
		case 0x0004:{if(PLC_STL_CMD==1)rst_m8000_m1536();PLC_PC+=4;}break; 
		case 0x0005:
		{
			if(PLC_STL_CMD == 1)
			{
//				if(PLC_ACC_BIT&0x01)
//				{
//					if(PLC_STL_ADD != (PLC_RAM16(PLC_PC+2)&0x0FFF))
//						PLC_BIT_OFF(PLC_STL_ADD);
//					PLC_STL_ADD=PLC_RAM16(PLC_PC+2)&0x0FFF;
//				}
				out_s();
			}
			PLC_PC+=4;
		}break; 
		case 0x0006:
		{
			if(PLC_STL_CMD == 1)
			{
//				if(PLC_ACC_BIT&0x01)
//				{
	//				if(PLC_STL_ADD != (PLC_RAM16(PLC_PC+2)&0x0FFF))
	//					PLC_BIT_OFF(PLC_STL_ADD);
	//				PLC_STL_ADD=PLC_RAM16(PLC_PC+2)&0x0FFF;
	//			}
				set_s();
			}
			PLC_PC+=4;
		}break; 
		case 0x0007:{if(PLC_STL_CMD == 1)rst_s();PLC_PC+=4;}break; 
		case 0xF7FF:{ret();}break;
		case 0x000C:{if(PLC_STL_CMD==1)rst_t_c();PLC_PC+=4;}break; 
		case 0x000D:{if(PLC_STL_CMD==1)rst_d();PLC_PC+=6;}break; 
/********************功能指令************************************************/
/**																		   **/
/********************程序流程************************************************/
	 case 0x0010:{if(PLC_STL_CMD==1)cj();else PLC_PC+=6;}break; //CJ
	 case 0x0012:{if(PLC_STL_CMD==1)call();else PLC_PC+=6;}break; //CALL
	 case 0x0014:{if(PLC_STL_CMD==1)sret();}break; //SRET
	 case 0x001C:{if(PLC_STL_CMD==1)fend();}break; //FEND //无步进返回指令
/********************程序流程(P)************************************************/
	 case 0x1010:{if(PLC_STL_CMD==1)cjp();else PLC_PC+=6;}break; 
	 case 0x1012:{if(PLC_STL_CMD==1)callp();else PLC_PC+=6;}break; 
/********************传送比较指令************************************************/
	 case 0x0024:{if(PLC_STL_CMD==1)cmp();PLC_PC+=14;}break; //CMP
	 case 0x0026:{if(PLC_STL_CMD==1)zcp();PLC_PC+=18;}break; //ZCP
	 case 0x0028:{if(PLC_STL_CMD==1)mov();PLC_PC+=10;}break; //MOV
	 case 0x002E:{if(PLC_STL_CMD==1)bmov();PLC_PC+=14;}break; //BMOV(M8024)
/********************(D)传送比较指令*********************************************/
	 case 0x0025:{if(PLC_STL_CMD==1)dcmp();PLC_PC+=26;}break; //CMP
	 case 0x0027:{if(PLC_STL_CMD==1)dzcp();PLC_PC+=34;}break; //ZCP
	 case 0x0029:{if(PLC_STL_CMD==1)dmov();PLC_PC+=18;}break; //MOV
/********************传送比较指令(P)********************************************/
	 case 0x1024:{if(PLC_STL_CMD==1)cmpp();PLC_PC+=14;}break; //CMP
	 case 0x1026:{if(PLC_STL_CMD==1)zcpp();PLC_PC+=18;}break; //ZCP
	 case 0x1028:{if(PLC_STL_CMD==1)movp();PLC_PC+=10;}break; //MOV
	 case 0x102E:{if(PLC_STL_CMD==1)bmovp();PLC_PC+=14;}break; //BMOV(M8024)
/********************(D)传送比较指令(P)******************************************/
	 case 0x1025:{if(PLC_STL_CMD==1)dcmpp();PLC_PC+=26;}break; //CMP
	 case 0x1027:{if(PLC_STL_CMD==1)dzcpp();PLC_PC+=34;}break; //ZCP
	 case 0x1029:{if(PLC_STL_CMD==1)dmovp();PLC_PC+=18;}break; //MOV
/********************四则.逻辑运算*******************************************/
	 case 0x0038:{if(PLC_STL_CMD==1)add();PLC_PC+=14;}break; //ADD(+)M8020(零标志)M8021(借位)M8022(进位)
	 case 0x003A:{if(PLC_STL_CMD==1)sub();PLC_PC+=14;}break; //SUB(-)M8020(零标志)M8021(借位)M8022(进位)
	 case 0x003C:{if(PLC_STL_CMD==1)mul();PLC_PC+=14;}break; //MUL(*)
	 case 0x003E:{if(PLC_STL_CMD==1)div();PLC_PC+=14;}break; //DIV(/)
	 case 0x0040:{if(PLC_STL_CMD==1)inc();PLC_PC+=6;}break;  //INC(++)
	 case 0x0042:{if(PLC_STL_CMD==1)dec();PLC_PC+=6;}break;  //DEC(--)
	 case 0x0044:{if(PLC_STL_CMD==1)wand();PLC_PC+=14;}break; //WAND
	 case 0x0046:{if(PLC_STL_CMD==1)wor();PLC_PC+=14;}break; //WOR
	 case 0x0048:{if(PLC_STL_CMD==1)wxor();PLC_PC+=14;}break; //WXOR
/********************(D)四则.逻辑运算*******************************************/
	 case 0x0039:{if(PLC_STL_CMD==1)dadd();PLC_PC+=26;}break; //ADD(+)M8020(零标志)M8021(借位)M8022(进位)
	 case 0x003B:{if(PLC_STL_CMD==1)dsub();PLC_PC+=26;}break; //SUB(-)M8020(零标志)M8021(借位)M8022(进位)
	 case 0x003D:{if(PLC_STL_CMD==1)dmul();PLC_PC+=26;}break; //MUL(*)
	 case 0x003F:{if(PLC_STL_CMD==1)ddiv();PLC_PC+=26;}break; //DIV(/)
	 case 0x0041:{if(PLC_STL_CMD==1)dinc();PLC_PC+=10;}break; //INC(++)
	 case 0x0043:{if(PLC_STL_CMD==1)ddec();PLC_PC+=10;}break; //DEC(--)
	 case 0x0045:{if(PLC_STL_CMD==1)dwand();PLC_PC+=26;}break; //WAND
	 case 0x0047:{if(PLC_STL_CMD==1)dwor();PLC_PC+=26;}break; //WOR
	 case 0x0049:{if(PLC_STL_CMD==1)dwxor();PLC_PC+=26;}break; //WXOR
/********************四则.逻辑运算(P)*******************************************/
	 case 0x1038:{if(PLC_STL_CMD==1)addp();PLC_PC+=14;}break; //ADD(+)M8020(零标志)M8021(借位)M8022(进位)
	 case 0x103A:{if(PLC_STL_CMD==1)subp();PLC_PC+=14;}break; //SUB(-)M8020(零标志)M8021(借位)M8022(进位)
	 case 0x103C:{if(PLC_STL_CMD==1)mulp();PLC_PC+=14;}break; //MUL(*)
	 case 0x103E:{if(PLC_STL_CMD==1)divp();PLC_PC+=14;}break; //DIV(/)
	 case 0x1040:{if(PLC_STL_CMD==1)incp();PLC_PC+=6;}break;  //INC(++)
	 case 0x1042:{if(PLC_STL_CMD==1)decp();PLC_PC+=6;}break;  //DEC(--)
	 case 0x1044:{if(PLC_STL_CMD==1)wandp();PLC_PC+=14;}break; //WAND
	 case 0x1046:{if(PLC_STL_CMD==1)worp();PLC_PC+=14;}break; //WOR
	 case 0x1048:{if(PLC_STL_CMD==1)wxorp();PLC_PC+=14;}break; //WXOR
/********************(D)四则.逻辑运算(P)*******************************************/
	 case 0x1039:{if(PLC_STL_CMD==1)daddp();PLC_PC+=26;}break; //ADD(+)M8020(零标志)M8021(借位)M8022(进位)
	 case 0x103B:{if(PLC_STL_CMD==1)dsubp();PLC_PC+=26;}break; //SUB(-)M8020(零标志)M8021(借位)M8022(进位)
	 case 0x103D:{if(PLC_STL_CMD==1)dmulp();PLC_PC+=26;}break; //MUL(*)
	 case 0x103F:{if(PLC_STL_CMD==1)ddivp();PLC_PC+=26;}break; //DIV(/)
	 case 0x1041:{if(PLC_STL_CMD==1)dincp();PLC_PC+=10;}break; //INC(++)
	 case 0x1043:{if(PLC_STL_CMD==1)ddecp();PLC_PC+=10;}break; //DEC(--)
	 case 0x1045:{if(PLC_STL_CMD==1)dwandp();PLC_PC+=26;}break; //WAND
	 case 0x1047:{if(PLC_STL_CMD==1)dworp();PLC_PC+=26;}break; //WOR
	 case 0x1049:{if(PLC_STL_CMD==1)dwxorp();PLC_PC+=26;}break; //WXOR
/********************数据处理************************************************/
	 case 0x0060:{if(PLC_STL_CMD==1)zrst();PLC_PC+=10;}break; //ZRST
/********************数据处理(P)*********************************************/
	 case 0x1060:{if(PLC_STL_CMD==1)zrstp();PLC_PC+=10;}break; //ZRSTP
/********************高速指令************************************************/
     case 0x0082:{if(PLC_STL_CMD==1)plsy();PLC_PC+=14;}break; //PLSY(M8029)
	 case 0x0084:{if(PLC_STL_CMD==1)pwm();PLC_PC+=14;}break;  //PWM
/********************(D)高速指令*********************************************/
     case 0x0083:{if(PLC_STL_CMD==1)dplsy();PLC_PC+=26;}break; //PLSY(M8029)
/********************方便指令************************************************/
	 case 0x0094:{if(PLC_STL_CMD==1)alt();PLC_PC+=6;}break; //ALT
/********************方便指令(P)*********************************************/
	 case 0x1094:{if(PLC_STL_CMD==1)altp();PLC_PC+=6;}break; //ALT(P)
/********************接点比较************************************************/
	 case 0x01D0:{PLC_PC+=10;}break; //LD=
	 case 0x01D2:{PLC_PC+=10;}break; //LD>
	 case 0x01D4:{PLC_PC+=10;}break; //LD<
	 case 0x01D8:{PLC_PC+=10;}break; //LD<>
	 case 0x01DA:{PLC_PC+=10;}break; //LD<=
	 case 0x01DC:{PLC_PC+=10;}break; //LD>=

	 case 0x01E0:{PLC_PC+=10;}break; //AND=
	 case 0x01E2:{PLC_PC+=10;}break; //AND>
	 case 0x01E4:{PLC_PC+=10;}break; //AND<
	 case 0x01E8:{PLC_PC+=10;}break; //AND<>
	 case 0x01EA:{PLC_PC+=10;}break; //AND<=
	 case 0x01EC:{PLC_PC+=10;}break; //AND>=

	 case 0x01F0:{PLC_PC+=10;}break; //OR=
	 case 0x01F2:{PLC_PC+=10;}break; //OR>
	 case 0x01F4:{PLC_PC+=10;}break; //OR<
	 case 0x01F8:{PLC_PC+=10;}break; //OR<>
	 case 0x01FA:{PLC_PC+=10;}break; //OR<=
	 case 0x01FC:{PLC_PC+=10;}break; //OR>=
/********************(D)接点比较************************************************/
	 case 0x01D1:{PLC_PC+=18;}break; //LD=
	 case 0x01D3:{PLC_PC+=18;}break; //LD>
	 case 0x01D5:{PLC_PC+=18;}break; //LD<
	 case 0x01D9:{PLC_PC+=18;}break; //LD<>
	 case 0x01DB:{PLC_PC+=18;}break; //LD<=
	 case 0x01DD:{PLC_PC+=18;}break; //LD>=

	 case 0x01E1:{PLC_PC+=18;}break; //AND=
	 case 0x01E3:{PLC_PC+=18;}break; //AND>
	 case 0x01E5:{PLC_PC+=18;}break; //AND<
	 case 0x01E9:{PLC_PC+=18;}break; //AND<>
	 case 0x01EB:{PLC_PC+=18;}break; //AND<=
	 case 0x01ED:{PLC_PC+=18;}break; //AND>=

	 case 0x01F1:{PLC_PC+=18;}break; //OR=
	 case 0x01F3:{PLC_PC+=18;}break; //OR>
	 case 0x01F5:{PLC_PC+=18;}break; //OR<
	 case 0x01F9:{PLC_PC+=18;}break; //OR<>
	 case 0x01FB:{PLC_PC+=18;}break; //OR<=
	 case 0x01FD:{PLC_PC+=18;}break; //OR>=
/********************结束指令************************************************/
	 case 0x000F:
	 	{PLC_PROG_ERROR(9999); //无步进返回指令
		}break; //END
/********************常规指令************************************************/	 
	 default:	 //default(1)
	 	{PLC_CMD=PLC_TEMP1&0xF000;							   			//分离指令
	 	 switch (PLC_CMD)//switch(2)
	 	   {case 0x2000:{if(PLC_STL_CMD == 1)ld();else PLC_PC+=2;}break;
		    case 0x3000:{PLC_PC+=2;}break;
		    case 0x4000:{PLC_PC+=2;}break;
		    case 0x5000:{PLC_PC+=2;}break;
		    case 0x6000:{PLC_PC+=2;}break;
		    case 0x7000:{PLC_PC+=2;}break;
		    case 0xB000:{PLC_PC+=2;}break;
		    case 0xC000:{if(PLC_STL_CMD == 1)out_y_m();else PLC_PC+=2;}break;
		    case 0xD000:{PLC_PC+=2;}break;
		    case 0xE000:{PLC_PC+=2;}break;
			case 0xF000:
			{
//				if((PLC_TEMP1&0x0fff)>0x03ff)
//				{
//					PLC_PROG_ERROR(1916);
//				}	//指令与操作数出错
//				else 
//				{
					stl();
//					PLC_RUN_BIT=3;//返回正常程序中测试S
//				      PLC_STL_CMD=0;
//				}
			}break;
			default: //default(2)
			   {PLC_CMD=PLC_TEMP1&0xFF00;							   			//分离指令
	 	        switch (PLC_CMD)//switch(3)
				  {
					case 0x0600://OUT
					{
						if(PLC_STL_CMD==1)
						{
							out();
//							PLC_T_OUT_BIT_OFF(PLC_TEMP1&0x0FFF);
//							PLC_T_C_BIT_OFF(PLC_TEMP1&0x0FFF);
						}
						else 
				       		PLC_PC+=6;
					}break; 
		           case 0x0E00:
				   	  {if((PLC_TEMP1&0x00FF)<200) 		 
		 				{if(PLC_STL_CMD==1)
				  		  {PLC_C_OUT_BIT_OFF(PLC_TEMP1&0x0FFF);
						   PLC_C_C_BIT_OFF(PLC_TEMP1&0x0FFF);}
						 PLC_PC+=6;}	 				   
		 			   else{
						    PLC_PC+=10;} 
		 			   }break;
				   default:{PLC_PROG_ERROR(6505);}break;	//指令出错
		   		  }//END switch(3)
		   	   }break;//END default(2)
		   }//END switch(2)
		}break;//END default(1)
	}//END switch(1)									
/***********************************************/
}
