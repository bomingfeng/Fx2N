#include "plc_app.H"
#include "stm32f10x.h"
#include "PLC_PUBLIC.H"

#define	leapyear(year)		((year) % 4 == 0)
#define	days_in_year(a) 	(leapyear(a) ? 366 : 365)
#define	days_in_month(a) 	(month_days[(a) - 1])

struct rtc_time {
	uint16 tm_sec;
	uint16 tm_min;
	uint16 tm_hour;
	uint16 tm_mday;
	uint16 tm_mon;
	uint16 tm_year;
	uint16 tm_wday;
};

struct rtc_time systmtime;

uint8_t PLC_UART_T_BUFFER[0x8f];	//发送缓存
uint8_t PLC_UART_BUFFER[0x8f];		//接收缓存
uint8_t  PLC_UART_RECEIVE_CNT = 0;	//接收计数
uint8_t	PLC_UART_T_CNT = 0;		//发送计数
uint8    BOT_BIT;				   //掉电执行标志
extern const uint16_t PROG_CODE2[128];
uint32_t  PLC_1MS_BIT = 0;					//PLC 1MS标志位(用于其它程式运行标志)
uint8_t  PLC_RUN_BIT;	 				//PLC运行标志
// 0=无运行;1=PLC运行前数据复位;2=PLC程序检测中;3=PLC程序下常运行;4=STL;
// 5=PLC程序出错处理;6=PLC程序出错;其它=?	


/*
 *  Program iap
 *   
 *   
 *   
 *    Return Value:   0 - OK,  1 - Failed
 */

void wdt_init(uint8 ms)
{
	/* IWDG timeout equal to 250 ms (the timeout may varies due to LSI frequency
		dispersion) */
	/* Enable write access to IWDG_PR and IWDG_RLR registers */
//	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG->KR = IWDG_WriteAccess_Enable;
	/* IWDG counter clock: LSI/32 */
//	IWDG_SetPrescaler(IWDG_Prescaler_32);
  IWDG->PR = IWDG_Prescaler_32;

	/* Set counter reload value to obtain 250ms IWDG TimeOut.
	Counter Reload Value = 250ms/IWDG counter clock period
                          = 250ms / (LSI/32)
                          = 0.25s / (LsiFreq/32)
                          = LsiFreq/(32 * 4)
                          = LsiFreq/128
                LsiFreq/(32*1/D8000)
	*/
//	IWDG_SetReload(1.25*ms);
	  IWDG->RLR = 1.25*ms;


	/* Reload IWDG counter */
	IWDG_ReloadCounter();

	/* Enable IWDG (the LSI oscillator will be enabled by hardware) */
	IWDG_Enable();
	
}
void wdt_clear(void)
{
	/* Reload IWDG counter */
	IWDG_ReloadCounter();
}

void wdt(void)
{
	/* Check if the system has resumed from IWDG reset */
	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)
	{
		/* IWDGRST flag set */
		PLC_RUN_BIT = 6;//PLC运行标志进入出错
		PLC_BIT_OFF(M8000);	 //关闭M8000
		PLC_BIT_ON(M8037);
		D8065=03;
		LED5(ON);//红灯，出错
		LED4(OFF);//绿灯,运行
		/* Clear reset flags */
		RCC_ClearFlag();
	}
}



void ProgramPage(uint32_t adr, uint32_t sz, uint32_t  buf)
{
	uint32_t EraseCounter, Address = 0x00;
	FLASH_Status FLASHStatus = FLASH_COMPLETE;
/* Porgram FLASH Bank1 ********************************************************/       
  /* Unlock the Flash Bank1 Program Erase controller */
  FLASH_UnlockBank1();

  /* Clear All pending flags */
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	

  /* Erase the FLASH pages */
  for(EraseCounter = 0; (EraseCounter < ( sz / FLASH_PAGE_SIZE)) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
  {
    FLASHStatus = FLASH_ErasePage(adr + (FLASH_PAGE_SIZE * EraseCounter));wdt_clear();
  }
  /* Program Flash Bank1 */
  Address = adr;

  while((Address < (adr + sz)) && (FLASHStatus == FLASH_COMPLETE))
  {
    FLASHStatus = FLASH_ProgramWord(Address, (*(__IO uint32_t*) buf));wdt_clear();
    Address = Address + 4;
	buf = buf + 4;
  }
  FLASH_LockBank1();
}


/***********************************************
  函数功能：上电数据复位
***********************************************/
void PLC_PowerUpReset(void)
{
	unsigned int S_Add,S_Add2,E_Add;
	uint32_t i;
	int temp;
/*		
	m_start=PLC_RAM16(PLC_PROG_START_ADD+0x30) - 0x800;
	m_end=PLC_RAM16(PLC_PROG_START_ADD+0x32) - 0x800;
	s_start=PLC_RAM16(PLC_PROG_START_ADD+0x34);
	s_end=PLC_RAM16(PLC_PROG_START_ADD+0x36);
	c16_start=PLC_RAM16(PLC_PROG_START_ADD+0x38) - 0xE00;
	c16_end=PLC_RAM16(PLC_PROG_START_ADD+0x3A) - 0xE00;	
	c32_start=PLC_RAM16(PLC_PROG_START_ADD+0x3C) - 0xE00;
	c32_end=PLC_RAM16(PLC_PROG_START_ADD+0x3E) - 0xE00;
	d_start=PLC_RAM16(PLC_PROG_START_ADD+0x40)/2;
	d_end=PLC_RAM16(PLC_PROG_START_ADD+0x42)/2;	*/
	S_Add=PLC_R_START_ADD;
	E_Add=PLC_R_END_ADD;
	for(;S_Add<=E_Add;){PLC_RAM32(S_Add)=0;S_Add+=4;}//复位所有寄存器
	
//	ProgramPage(0x08037800,0x800,PLC_R_START_ADD);
	
	S_Add=PLC_F_START_ADD;E_Add=PLC_F_START_ADD + 0x41;S_Add2=PLC_R_START_ADD+0X003E;  //S500-S1024	0x003E-0x007F	FX2N
	for(;S_Add<=E_Add;){PLC_RAM8(S_Add2)=PLC_RAM8(S_Add);S_Add++;S_Add2++;}
	PLC_BIT_OFF(496);PLC_BIT_OFF(497);PLC_BIT_OFF(498);PLC_BIT_OFF(499);      //RST S496-S499 FX2N

	 S_Add=PLC_F_START_ADD  + 0x42;E_Add=PLC_F_START_ADD  + 0x83;S_Add2=PLC_R_START_ADD+0x013E;//M500-M1023		FX2N
	 for(;S_Add<=E_Add;){PLC_RAM8(S_Add2)=PLC_RAM8(S_Add);S_Add++;S_Add2++;}
	 PLC_BIT_OFF(0x09F0);PLC_BIT_OFF(0x09F1);PLC_BIT_OFF(0x09F2);PLC_BIT_OFF(0x09F3);      //RST M496-M499 FX2N
 
	 S_Add=PLC_F_START_ADD  + 0x84;E_Add=PLC_F_START_ADD  + 0x2F3;S_Add2=PLC_R_START_ADD+0x1190;//D200-D511	FX2N
	 for(;S_Add<=E_Add;){PLC_RAM8(S_Add2)=PLC_RAM8(S_Add);S_Add++;S_Add2++;}
 
	 S_Add=PLC_F_START_ADD  + 0x2F4;E_Add=PLC_F_START_ADD  + 0x3BB;S_Add2=PLC_R_START_ADD+0x0AC8;//C100-C199 0x0AC8-0x0B8F  FX2N
	 for(;S_Add<=E_Add;){PLC_RAM8(S_Add2)=PLC_RAM8(S_Add);S_Add++;S_Add2++;}
	 
	  S_Add=PLC_F_START_ADD  + 0x3BC;E_Add=PLC_F_START_ADD  + 0x44B;S_Add2=PLC_R_START_ADD+0x0C54;//C220-C255 0x0C54-0x0CDF  FX2N
	 for(;S_Add<=E_Add;){PLC_RAM8(S_Add2)=PLC_RAM8(S_Add);S_Add++;S_Add2++;} 

	for(i=0;i<128;i++)//D8000~d80128	
		PLC_RAM16(PLC_R_START_ADD+D8000ADD+(i*2)) = PROG_CODE2[i] ;
	PLC_BIT_ON(M8018);

}

void DMASend(void)
{
	if(PLC_UART_T_CNT!=0)
	{
		DMA1_Channel4->CNDTR = (uint16_t)PLC_UART_T_CNT; // 设置要发送的字节数目
		PLC_UART_T_CNT = 0;
		DMA_Cmd(DMA1_Channel4, ENABLE);        //开始DMA发送
		DMA_Cmd(DMA1_Channel5, ENABLE);        //DMA 开启，等待数据。
	}
}

void RGB_LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 			
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);          
}

void GregorianDay(struct rtc_time * tm)
{
	int leapsToDate;
	int lastYear;
	int day;
	int MonthOffset[] = { 0,31,59,90,120,151,181,212,243,273,304,334 };

	lastYear=tm->tm_year-1;

	/*计算从公元元年到计数的前一年之中一共经历了多少个闰年*/
	leapsToDate = lastYear/4 - lastYear/100 + lastYear/400;      

     /*如若计数的这一年为闰年，且计数的月份在2月之后，则日数加1，否则不加1*/
	if((tm->tm_year%4==0) &&
	   ((tm->tm_year%100!=0) || (tm->tm_year%400==0)) &&
	   (tm->tm_mon>2)) {
		/*
		 * We are past Feb. 29 in a leap year
		 */
		day=1;
	} else {
		day=0;
	}

	day += lastYear*365 + leapsToDate + MonthOffset[tm->tm_mon-1] + tm->tm_mday; /*计算从公元元年元旦到计数日期一共有多少天*/

	tm->tm_wday=day%7;
}

void D_to_RTC(struct rtc_time *time)
{
	uint32 tmp;
	time->tm_year = (D8018&0x00FF) + 2000;
	time->tm_mon= D8017;
	time->tm_mday= D8016;
	time->tm_hour= D8015;
	time->tm_min= D8014;
	time->tm_sec= D8013;
	if (0 >= (int) (time->tm_mon -= 2)) {	/* 1..12 -> 11,12,1..10 */
		time->tm_mon += 12;		/* Puts Feb last since it has leap day */
		time->tm_year -= 1;
	}

	tmp= (((
		(u32) (time->tm_year/4 - time->tm_year/100 + time->tm_year/400 + 367*time->tm_mon/12 + time->tm_mday) +
			time->tm_year*365 - 719499
	    )*24 + time->tm_hour /* now have hours */
	  )*60 + time->tm_min /* now have minutes */
	)*60 + time->tm_sec; /* finally seconds */
	/* RTC Configuration */
		 /* 修改当前RTC计数寄存器内容 */
	RTC_SetCounter(tmp);
}

void RTC_to_D(uint32 tim,struct rtc_time *time)
{
	u32    i;
	u32   hms, day;
	int month_days[12] = {	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	hms = tim % 86400;
	time->tm_sec = (hms % 3600) % 60;
	if(D8013 != time->tm_sec)
	{
		day = tim / 86400;
		/* Hours, minutes, seconds are easy */
		time->tm_hour = hms / 3600;
		time->tm_min = (hms % 3600) / 60;
		time->tm_sec = (hms % 3600) % 60;

		/* Number of years in days */ /*算出当前年份，起始的计数年份为1970年*/
		for (i = 1970; day >= days_in_year(i); i++) {
			day -= days_in_year(i);
		}
		time->tm_year = i;

		/* Number of months in days left */ /*计算当前的月份*/
		if (leapyear(time->tm_year)) {
			days_in_month(2) = 29;
		}
		for (i = 1; day >= days_in_month(i); i++) {
			day -= days_in_month(i);
		}
		days_in_month(2) = 28;
		time->tm_mon = i;

		/* Days are what is left over (+1) from all that. *//*计算当前日期*/
		time->tm_mday = day + 1;

		/*
		 * Determine the day of week
		 */
		GregorianDay(time);	
		D8018 = time->tm_year;
		D8017 = time->tm_mon;
		D8016 = time->tm_mday;
		D8015 = time->tm_hour;
		D8014 = time->tm_min;
		D8013 = time->tm_sec;
		D8019 = time->tm_wday;
	}
}

#define HARDWARE_VERSION               "V1.0.0"
#define SOFTWARE_VERSION               "V0.1.0"
void plc_main(void)
{
	uint32 ddddd;
	uint8 temp;
	RGB_LED_Init();
	LED4(OFF);//绿灯,运行
	LED5(OFF);//红灯，出错
	LED6(OFF);//蓝灯，电池低
	DMA_Uart_Init();
	USB2Serial_Init();
        
        /* CmBacktrace initialize */
 //       cm_backtrace_init("CmBacktrace", HARDWARE_VERSION, SOFTWARE_VERSION);
                  
	PLC_PowerUpReset();		
	debug_send("调式开始X=%d, Y=%d, Z=%d\r\n", 1,3, 2);
	if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
	{
		/* RTC Configuration */
		RTC_Configuration();
		BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
	}
	else
	{
		RTC_WaitForSynchro();
		/* Enable the RTC Second */
		RTC_ITConfig(RTC_IT_SEC, ENABLE);
		/* Wait until last write operation on RTC registers has finished */
		RTC_WaitForLastTask();
	}
	while(1)
	{
		PLC_PROG_RUN();
		if(PLC_1MS_BIT>70)
		{
			wdt();
			PLC_1MS_BIT=0;
			PLC_UART_CMD();
			DMASend();
			if(D8065)
			{
				LED5(ON);//红灯，出错
			}
			else
			{
				LED5(OFF);//红灯，出错
			}
			if(D8065==0 && PLC_BIT_TEST(M8037)==0)
			{
				if(PLC_RUN_BIT==0)
				{
					PLC_RUN_BIT=1;
				}	//开始运行测试
				LED4(ON);//绿灯,运行				
				if(PLC_BIT_TEST(M8015) || PLC_BIT_TEST(M8019) || PLC_BIT_TEST(M8018)==0)
				{
					RCC_RTCCLKCmd(DISABLE);
					temp=2;
				}
				else
				{
					if(temp==2)
					{
						RCC_RTCCLKCmd(ENABLE);
						temp=1;
						D_to_RTC(&systmtime);
					}
					else
						RTC_to_D(RTC_GetCounter(),&systmtime);
				}				
				
				#ifndef debug
				if(PLC_RUN_BIT==3)
				{
					wdt_init(D8000);
				}
				#endif
			}
			else
			{
				wdt_clear();
				LED4(OFF);//绿灯,运行
				if(PLC_RUN_BIT!=0)
				{
					PLC_BIT_OFF(M8000);
					PLC_RUN_BIT=0;
					PLC_BIT_ON(M8037);
				}
			}
		}
		#ifndef debug
		PLC_RUN_BIT==3;
		#endif
	}
}

void Plc_Program_iap(void) 
{
	uint16 i;
        
	ProgramPage(PLC_PROG_START_ADD,0x8000,PLC_PROG_B_START_ADD);//0x7d5c0x8800,0x4000
	for(i=0;i<0x2000;i++)
        {
		if(PLC_RAM32(PLC_PROG_START_ADD+i*4) != PLC_RAM32(PLC_PROG_B_START_ADD+i*4))
		{
			PLC_COMM_ERROR(1);
			debug_send("校验程序出错buf=0x%x;\r\n",PLC_PROG_START_ADD+i*4);
		}
        }
}

void Plc_parameter_iap(void)
{										//写入参数
	ProgramPage(PLC_PROG_START_ADD,0x800,PLC_PROG_B_START_ADD);
}

void Plc_Data_Bod_iap(void) 
{
	uint32 i;
	for(i=0;i<=0x41;i++)
		PLC_RAM8(PLC_R_START_ADD+i)=PLC_RAM8(PLC_R_START_ADD+0X003E+i);
	for(i=0x42;i<=0x83;i++)
		PLC_RAM8(PLC_R_START_ADD+i)=PLC_RAM8(PLC_R_START_ADD+0x013E+i);	
	for(i=0x84;i<=0x2F3;i++)
		PLC_RAM8(PLC_R_START_ADD+i)=PLC_RAM8(PLC_R_START_ADD+0x1190+i);	
	for(i=0x2F4;i<=0x3BB;i++)
		PLC_RAM8(PLC_R_START_ADD+i)=PLC_RAM8(PLC_R_START_ADD+0x0AC8+i);	
	for(i=0x3BC;i<=0x44B;i++)
		PLC_RAM8(PLC_R_START_ADD+i)=PLC_RAM8(PLC_R_START_ADD+0x0C54+i);	
	ProgramPage(PLC_F_START_ADD,0x800,PLC_R_START_ADD);
}	

/**************************************************************/
/*
1ms系统中断节拍调用
*/
void SysTick_Handler(void)
{
	PLC_RUN_TIME++;		   //运行时间+1MS
	PLC_1MS_BIT++;
	PLC_T_COUNT();           //计时
	PLC_M_MS();
}



/*******************************************************************************/
/*
掉电中断
*/
void BOD_IRQHandler (void)
{ 
	if(BOT_BIT==0xaa)
	{
		Plc_Data_Bod_iap();
		BOT_BIT=0;
	}
}

