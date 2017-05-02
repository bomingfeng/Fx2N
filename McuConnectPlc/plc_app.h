#ifndef __plc_app_H__
#define __plc_app_H__

#include "stm32f10x.h"

/* 定义CPU ROM RAM开始地区址和结束地址*/
//STM32开始地址   大小	换成十进制
//0x8000000 			0x40000		256k		Flash
//0x20000000		0xC000		48k			RAM

//0x0			0x80000		512K	0x5003E
//0x10000000	0x8000		32K		0x10001000 //PLC_RAM开始地址	0x10006FFF //PLC_RAM结束地址0X7E7E



// PLC_R_START_ADD+0x5700 cj用PLC_RAM16(PLC_R_START_ADD+0x5700+PLC_RAM8(PLC_PC+2))=PLC_PC-PLC_PROG_START_ADD2;

/*
  S0-1023        =  (0-3FF)        =   0-3FF 
  X0-377(八进制) =  (0-FF)   + 400  =  400-4FF
  Y0-377(八进制) =  (0-FF)   + 500  =  500-5FF
  T0-511         =  (0-1FF)  + 600  =  600-7FF  
  M0-1535        =  (0-5FF)  + 800  =  800-DFF 
  M1536-M3071    =  (600-BFF)+ 200  =  800-DFF 
  C0-255         =  (0-FF)   + E00  =  E00-EFF 
  M8000-8255     =  (0-FF)   + F00  =  F00-FFF 

 除以8得到物理地址，+ 200
*/
#define PLC_R_START_ADD  		0x20006000				//PLC_RAM开始地址(S\M\D\C点在RAM地址）。+0xE00 D8000以上的地址 。 +0x1000 D0~D7999地址
#define 	M8000ADD				0x1e0
#define 	D8000ADD				0x00000E00			//D8000~D
#define 	D0ADD					0X1000				//D0~D7999
#define PLC_PROG_B_START_ADD  0x20004000 			//程序写入开始地址
#define PLC_R_END_ADD       		0x2000BFFF	    //PLC_RAM结束地址0X7E7E

/*
M	PLC_F_START_ADD ~ PLC_F_START_ADD + 0x7F			1024
S	PLC_F_START_ADD + 0x80 ~ PLC_F_START_ADD + 0xFC		1000
C16	PLC_F_START_ADD + 0x100 ~ PLC_F_START_ADD + 0x28F	200
C32	PLC_F_START_ADD + 0x300 ~ PLC_F_START_ADD + 0x3E0	56
D	PLC_F_START_ADD + 0x400 ~ PLC_F_START_ADD + 0x800	512
*/

#define PLC_F_START_ADD  		0x08037800				//PLC_ROM开始地址（(S\M\D\C点断电保存在Flash地址）
#define PLC_PROG_START_ADD  	0x08038000 	 			//ROM开始地址
#define PLC_PROG_END_ADD    	0x0803FFFF	 			//ROM结束地址
#define PLC_PROG_START_ADD2  	0x0803805C              //执行ROM开始地址


//PLC_R_START_ADD+(0~0X007f)  s0~s1024;其中S500-S1024	0x003E-0x007F断电保持
//PLC_R_START_ADD+(0x0100~280)	m0~m3071;其中M500-M3071(M1535) 0x013E-0x01DF
//PLC_R_START_ADD+(a00~   c0
/******************************************************************************/
#define PLC_RAM8(x)   (*(u8  *)(u32)(x))					//字节方式	R/W RAM	R ROM
#define PLC_RAM16(x)   (*(u16*)(u32)(x))				//半字方式	R/W RAM	R ROM
#define PLC_RAM32(x)   (*(u32*)(u32)(x))				//字方式	R/W RAM	R ROM

 #define FLASH_PAGE_SIZE    ((uint16_t)0x800)
  
/******************************************************************************/


void plc_main(void);
#ifndef ON
#define ON  0
#endif

#ifndef OFF
#define OFF 1
#endif

#define LED4(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_0);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_0)
#define LED5(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_1);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define LED6(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_2);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_2)

#endif /* __plc_app_H__ */
