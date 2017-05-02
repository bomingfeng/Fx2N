#include "PLC_PUBLIC.H"

/********************纯字指令************************************************/
void anb(void)	//0xFFF8
{
	PLC_ACC_BIT = (PLC_ACC_BIT >> 1) & (PLC_ACC_BIT & 0x01);
	debug_send("ANB\r\n;");
}

void orb(void)	//0xFFF9
{
	PLC_ACC_BIT = (PLC_ACC_BIT >> 1) | (PLC_ACC_BIT & 0x01);
	debug_send("ORB\r\n;");
}

void mps(void)	//0xFFFA
{
	PLC_MPS_BIT = (PLC_MPS_BIT << 1) | (PLC_ACC_BIT & 0x01);
	debug_send("MPS\r\n;");
}

void mrd(void)	//0xFFFB
{
	PLC_ACC_BIT = (PLC_ACC_BIT & 0xfe) | (PLC_MPS_BIT & 0x01);
	debug_send("MRD\r\n;");
}

void mpp(void)	//0xFFFC
{
	PLC_ACC_BIT = (PLC_ACC_BIT & 0xfe) | (PLC_MPS_BIT & 0x01);
	PLC_MPS_BIT >>= 1;
	debug_send("MPP\r\n;");
}

void inv(viod)	//0xFFFD
{
	PLC_ACC_BIT = (PLC_ACC_BIT & 0xfe) | (~PLC_ACC_BIT & 0x01);
	debug_send("INV\r\n;");
}

void nop(void)		//0xFFFF
{
	PLC_PC+=2;
	debug_send("NOP;\r\n");
}

/********************升降沿指令************************************************/
void ldp(void)	//0x01CA
{
	PLC_ACC_BIT <<= 1;
	if((PLC_RAM16(PLC_PC+2)&0xF000)==0xA000)
	{
		if(PLC_O2_M1536_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF)&&PLC_O_M1536_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF)==0)
			PLC_ACC_BIT |=0x01;
	}
	else
	{
		if(PLC_O2_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF)&&PLC_O_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF)==0)
			PLC_ACC_BIT |=0x01;
	}
	#ifdef	debug
	if((PLC_RAM16(PLC_PC+2)&0xF000)==0xA000)
	{
		if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0800) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x0DFF))
			{debug_send("LDP上升沿 M%d=%d\r\n",(PLC_RAM16(PLC_PC+2)&0x0FFF-0x800)+1536,PLC_O2_M1536_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
	}
	else
	{
		if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x03FF))
			{debug_send("LDP上升沿S%d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF,PLC_O2_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
		else if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0400) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x04FF))
				{debug_send("LDP上升沿 X%o=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0x0400,PLC_O2_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0500) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x05FF))
				{debug_send("LDP上升沿 Y%o=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0x500,PLC_O2_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0600) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x07FF))
				{debug_send("LDP上升沿 T%d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0x600,PLC_O2_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}					
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0800) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x0DFF))
				{debug_send("LDP上升沿 M%d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0x800,PLC_O2_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0E00) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x0EFF))
				{debug_send("LDP上升沿 C%d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0xE00,PLC_O2_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}					
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0F00) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x0FFF))
				{debug_send("LDP上升沿 M8%03d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0xF00,PLC_O2_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}//m8000~m8255
	}
	#endif	 
}

void ldf(void)	//0x01CB
{
	PLC_ACC_BIT <<= 1;
	if((PLC_RAM16(PLC_PC+2)&0xF000)==0xA000)
	{
		if(PLC_O2_M1536_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF)==0&&PLC_O_M1536_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF))
			PLC_ACC_BIT |=0x01;
	}
	else
	{
		if(PLC_O2_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF)==0&&PLC_O_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF))
			PLC_ACC_BIT |=0x01;
	}
	#ifdef	debug
	if((PLC_RAM16(PLC_PC+2)&0xF000)==0xA000)
	{
		if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0800) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x0DFF))
			{debug_send("LDP下降沿 M%d=%d\r\n",(PLC_RAM16(PLC_PC+2)&0x0FFF-0x800)+1536,PLC_O_M1536_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
	}
	else
	{					
		if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x03FF))
			{debug_send("LDF下降沿S%d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF,PLC_O_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
		else if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0400) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x04FF))
				{debug_send("LDF下降沿 X%o=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0x0400,PLC_O_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0500) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x05FF))
				{debug_send("LDF下降沿 Y%o=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0x500,PLC_O_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0600) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x07FF))
				{debug_send("LDF下降沿 T%d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0x600,PLC_O_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}					
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0800) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x0DFF))
				{debug_send("LDF下降沿 M%d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0x800,PLC_O_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0E00) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x0EFF))
				{debug_send("LDF下降沿 C%d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0xE00,PLC_O_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}					
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0F00) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x0FFF))
				{debug_send("LDF下降沿 M8%03d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0xF00,PLC_O_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}//m8000~m8255
	}
	#endif	 
}

void andp(void)	//0x01CC
{
	if((PLC_RAM16(PLC_PC+2)&0xF000)==0xA000)
	{					
		if(PLC_O2_M1536_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF)&&PLC_O_M1536_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF)==0)
			PLC_ACC_BIT &=0x01;
		else 
			PLC_ACC_BIT &=0xfe;
	}
	else
	{
		if(PLC_O2_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF)&&PLC_O_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF)==0)
			PLC_ACC_BIT &=0x01;
		else 
			PLC_ACC_BIT &=0xfe;						
	}

#ifdef	debug
	if((PLC_RAM16(PLC_PC+2)&0xF000)==0xA000)
	{	
		if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0800) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x0DFF))
			{debug_send("ANDP上升沿 M%d=%d\r\n",(PLC_RAM16(PLC_PC+2)&0x0FFF-0x800)+1536,PLC_O2_M1536_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
	}
	else
	{
		if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x03FF))
			{debug_send("ANDP上升沿S%d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF,PLC_O2_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
		else if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0400) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x04FF))
				{debug_send("ANDP上升沿 X%o=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0x0400,PLC_O2_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0500) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x05FF))
				{debug_send("ANDP上升沿 Y%o=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0x500,PLC_O2_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0600) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x07FF))
				{debug_send("ANDP上升沿 T%d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0x600,PLC_O2_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}					
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0800) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x0DFF))
				{debug_send("ANDP上升沿 M%d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0x800,PLC_O2_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0E00) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x0EFF))
				{debug_send("ANDP上升沿 C%d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0xE00,PLC_O2_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}					
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0F00) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x0FFF))
				{debug_send("ANDP上升沿 M8%03d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0xF00,PLC_O2_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}//m8000~m8255
	}
#endif	 					
}

void andf(void)	//0x01CD
{
	if((PLC_RAM16(PLC_PC+2)&0xF000)==0xA000)
	{					
		if(PLC_O2_M1536_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF)==0&&PLC_O_M1536_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF))
			PLC_ACC_BIT &=0x01;
		else 
			PLC_ACC_BIT &=0xfe;
	}
	else
	{
		if(PLC_O2_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF)==0&&PLC_O_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF))
			PLC_ACC_BIT &=0x01;
		else 
			PLC_ACC_BIT &=0xfe;
	}					
	#ifdef	debug
	if((PLC_RAM16(PLC_PC+2)&0xF000)==0xA000)
	{
		if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0800) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x0DFF))
			{debug_send("ANDF下降沿 M%d=%d\r\n",(PLC_RAM16(PLC_PC+2)&0x0FFF-0x800)+1536,PLC_O_M1536_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
	}
	else
	{
		if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x03FF))
			{debug_send("ANDF下降沿S%d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF,PLC_O_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
		else if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0400) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x04FF))
				{debug_send("ANDF下降沿 X%o=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0x0400,PLC_O_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0500) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x05FF))
				{debug_send("ANDF下降沿 Y%o=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0x500,PLC_O_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0600) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x07FF))
				{debug_send("ANDF下降沿 T%d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0x600,PLC_O_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}					
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0800) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x0DFF))
				{debug_send("ANDF下降沿 M%d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0x800,PLC_O_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0E00) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x0EFF))
				{debug_send("ANDF下降沿 C%d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0xE00,PLC_O_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}					
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0F00) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x0FFF))
				{debug_send("ANDF下降沿 M8%03d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0xF00,PLC_O_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}//m8000~m8255
	}
	#endif	 					
}

void orp(void)		//0x01CE
{
	if((PLC_RAM16(PLC_PC+2)&0xF000)==0xA000)
	{					
		if(PLC_O2_M1536_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF)&&PLC_O_M1536_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF)==0)
			PLC_ACC_BIT |=0x01;
	}
	else
	{
		if(PLC_O2_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF)&&PLC_O_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF)==0)
			PLC_ACC_BIT |=0x01;
	}					

#ifdef	debug
	if((PLC_RAM16(PLC_PC+2)&0xF000)==0xA000)
	{
		if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0800) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x0DFF))
			{debug_send("ORP上升沿M%d=%d\r\n",(PLC_RAM16(PLC_PC+2)&0x0FFF-0x800)+1536,PLC_O2_M1536_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
	}
	else
	{					
		if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x03FF))
			{debug_send("ORP上升沿S%d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF,PLC_O2_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
		else if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0400) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x04FF))
				{debug_send("ORP上升沿 X%o=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0x0400,PLC_O2_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0500) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x05FF))
				{debug_send("ORP上升沿 Y%o=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0x500,PLC_O2_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0600) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x07FF))
				{debug_send("ORP上升沿 T%d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0x600,PLC_O2_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}					
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0800) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x0DFF))
				{debug_send("ORP上升沿 M%d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0x800,PLC_O2_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0E00) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x0EFF))
				{debug_send("ORP上升沿 C%d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0xE00,PLC_O2_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}					
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0F00) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x0FFF))
				{debug_send("ORP上升沿 M8%03d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0xF00,PLC_O2_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}//m8000~m8255
	}
#endif	 										
}

void orf(void)		//0x01CF
{
	if((PLC_RAM16(PLC_PC+2)&0xF000)==0xA000)
	{					
		if(PLC_O2_M1536_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF)==0&&PLC_O_M1536_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF))
			PLC_ACC_BIT |=0x01;
	}
	else
	{
		if(PLC_O2_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF)==0&&PLC_O_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF))
			PLC_ACC_BIT |=0x01;
	}					
	#ifdef	debug
	if((PLC_RAM16(PLC_PC+2)&0xF000)==0xA000)
	{
		if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0800) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x0DFF))
			{debug_send("ORF下降沿M%d=%d\r\n",(PLC_RAM16(PLC_PC+2)&0x0FFF-0x800)+1536,PLC_O_M1536_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
	}
	else
	{	
		if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x03FF))
			{debug_send("ORF下降沿S%d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF,PLC_O_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
		else if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0400) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x04FF))
				{debug_send("ORF下降沿 X%o=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0x0400,PLC_O_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0500) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x05FF))
				{debug_send("ORF下降沿 Y%o=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0x500,PLC_O_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0600) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x07FF))
				{debug_send("ORF下降沿 T%d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0x600,PLC_O_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}					
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0800) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x0DFF))
				{debug_send("ORF下降沿 M%d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0x800,PLC_O_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0E00) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x0EFF))
				{debug_send("ORF下降沿 C%d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0xE00,PLC_O_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}					
		else  if(((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0F00) && ((PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x0FFF))
				{debug_send("ORF下降沿 M8%03d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0xF00,PLC_O_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));}//m8000~m8255
	}
	#endif	 										
}

void pls_y_m(void)		//0x0008	PLF Y M M1536~
{
	if((PLC_RAM16(PLC_PC+2)&0xF000)==0xA000)
	{			
		if(PLC_ACC_BIT&0x01)
		{
			if(PLC_PL_M1536_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF)==0)
			{	
				PLC_PL_M1536_BIT_ON(PLC_RAM16(PLC_PC+2)&0x0FFF);
				PLC_BIT_M1536_ON(PLC_RAM16(PLC_PC+2)&0x0FFF);	 
			}
			else
			{
				PLC_BIT_M1536_OFF(PLC_RAM16(PLC_PC+2)&0x0FFF);
			}
		}//END PLC_ACC_BIT
		else
		{
			PLC_PL_M1536_BIT_OFF(PLC_RAM16(PLC_PC+2)&0x0FFF);
		}					
	}
	else
	{
		if(PLC_ACC_BIT&0x01)
		{
			if(PLC_PL_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF)==0)
			{	
				PLC_PL_BIT_ON(PLC_RAM16(PLC_PC+2)&0x0FFF);
				PLC_BIT_ON(PLC_RAM16(PLC_PC+2)&0x0FFF);	 
			}
			else
			{
				PLC_BIT_OFF(PLC_RAM16(PLC_PC+2)&0x0FFF);
			}
		}//END PLC_ACC_BIT
		else
		{
			PLC_PL_BIT_OFF(PLC_RAM16(PLC_PC+2)&0x0FFF);
		}
	}
	#ifdef debug
	if((PLC_RAM16(PLC_PC+6)&0xF000)==0xA000)
	{
		debug_send("PLS M%d=%d\r\n",(PLC_RAM16(PLC_PC+2)&0x0FFF-0x800)+1536,PLC_PL_M1536_BIT_TEST((PLC_PC+2)&0x0FFF));
	}
	else
	{
		if((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0500 && (PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x05FF)
				{debug_send("PLS Y%o=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0x500,PLC_PL_BIT_TEST((PLC_PC+2)&0x0FFF));}
		if((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0800 && (PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x0DFF)
				{debug_send("PLS M%d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0x800,PLC_PL_BIT_TEST((PLC_PC+2)&0x0FFF));}					
	}
	#endif
}

void plf_y_m(void)		//0x0009	//PLF Y M M1536~
{
	if((PLC_RAM16(PLC_PC+2)&0xF000)==0xA000)
	{			
		if(PLC_ACC_BIT&0x01)
		{
			if(PLC_PL_M1536_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF)==0)
			{
				PLC_PL_M1536_BIT_ON(PLC_RAM16(PLC_PC+2)&0x0FFF);
			}
		}//END PLC_ACC_BIT
		else
		{
			if(PLC_PL_M1536_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF)) 
			{
				PLC_PL_M1536_BIT_OFF(PLC_RAM16(PLC_PC+2)&0x0FFF);	 
				PLC_BIT_M1536_ON(PLC_RAM16(PLC_PC+2)&0x0FFF);
			}	 
			else
			{
				PLC_BIT_M1536_OFF(PLC_RAM16(PLC_PC+2)&0x0FFF);
			} 
		}				
	}
	else
	{			
		if(PLC_ACC_BIT&0x01)
		{
			if(PLC_PL_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF)==0)
			{
				PLC_PL_BIT_ON(PLC_RAM16(PLC_PC+2)&0x0FFF);
			}
		}//END PLC_ACC_BIT
		else
		{
			if(PLC_PL_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF)) 
			{
				PLC_PL_BIT_OFF(PLC_RAM16(PLC_PC+2)&0x0FFF);	 
				PLC_BIT_ON(PLC_RAM16(PLC_PC+2)&0x0FFF);
			}	 
			else
			{
				PLC_BIT_OFF(PLC_RAM16(PLC_PC+2)&0x0FFF);
			} 
		}
	}
	#ifdef debug
	if((PLC_RAM16(PLC_PC+6)&0xF000)==0xA000)
	{
		debug_send("PLF M%d=%d\r\n",(PLC_RAM16(PLC_PC+2)&0x0FFF-0x800)+1536,PLC_PL_M1536_BIT_TEST((PLC_PC+2)&0x0FFF));
	}
	else
	{
		if((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0500 && (PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x05FF)
				{debug_send("PLF Y%o=%d\r\n",PLC_RAM16(PLC_PC-2)&0x0FFF-0x500,PLC_PL_BIT_TEST((PLC_PC+2)&0x0FFF));}
		if((PLC_RAM16(PLC_PC+2)&0x0FFF)>=0x0800 && (PLC_RAM16(PLC_PC+2)&0x0FFF)<=0x0DFF)
				{debug_send("PLF M%d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0x800,PLC_PL_BIT_TEST((PLC_PC+2)&0x0FFF));}
	}
	#endif					
}

/********************复位&步进指令************************************************/
void out_m8000_m1536(void)//0x0002 //OUT M8000 M1536~
{
	if((PLC_RAM16(PLC_PC+2)&0xF000)==0xA000)
	{
		if(PLC_ACC_BIT&0x01)
		{
			PLC_BIT_M1536_ON(PLC_RAM16(PLC_PC+2)&0x0FFF);
		}
		else 
			PLC_BIT_M1536_OFF(PLC_RAM16(PLC_PC+2)&0x0FFF);						
	}
	else
	{
		if(PLC_ACC_BIT&0x01)
		{
			PLC_BIT_ON(PLC_RAM16(PLC_PC+2)&0x0FFF);
		}
		else 
			PLC_BIT_OFF(PLC_RAM16(PLC_PC+2)&0x0FFF);
	}			
	#ifdef	debug
	if((PLC_RAM16(PLC_PC+2)&0xF000)==0xA000)
	{
		debug_send("OUT M%d=%d\r\n",(PLC_RAM16(PLC_PC+2)&0x0FFF-0x800)+1536,PLC_BIT_M1536_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));
	}
	else
	{
		debug_send("OUT M8%03d=%d\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF-0xF00,PLC_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));					
	}
	#endif
}

void set_m8000_m1536(void)//0x0003	//SET m1536~3071 M8000
{
	if((PLC_RAM16(PLC_PC+2)&0xF000)==0xA000)
	{
		if(PLC_ACC_BIT&0x01)
			PLC_BIT_M1536_ON(PLC_RAM16(PLC_PC+2)&0x0FFF);
	}
	else
	{
		if(PLC_ACC_BIT&0x01)
			PLC_BIT_ON(PLC_RAM16(PLC_PC+2)&0x0FFF);
	}
	#ifdef debug
	if((PLC_RAM16(PLC_PC+2)&0xF000)==0xA000)
	{
		debug_send("SET M%d=%d\r\n",((PLC_RAM16(PLC_PC+2)&0x0FFF)-0x800)+1536,PLC_BIT_M1536_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));	
	}
	else
	{
		debug_send("SET M%d=%d\r\n",((PLC_RAM16(PLC_PC+2)&0x0FFF)-0xF00),PLC_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));	
	}
	#endif
}

void rst_m8000_m1536(void)	//0x0004://RST m1536~3071	M8000
{
	if((PLC_RAM16(PLC_PC+2)&0xF000)==0xA000)
	{
		if(PLC_ACC_BIT&0x01)
			PLC_BIT_M1536_OFF(PLC_RAM16(PLC_PC+2)&0x0FFF);
	}
	else
	{
		if(PLC_ACC_BIT&0x01)
			PLC_BIT_OFF(PLC_RAM16(PLC_PC+2)&0x0FFF);
	}					
#ifdef debug
	if((PLC_RAM16(PLC_PC+2)&0xF000)==0xA000)
	{
		debug_send("RST M%d=%d\r\n",((PLC_RAM16(PLC_PC+2)&0x0FFF)-0x800)+1536,PLC_BIT_M1536_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));
	}
	else
	{
		debug_send("RST M%d=%d\r\n",((PLC_RAM16(PLC_PC+2)&0x0FFF)-0xF00),PLC_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));
	}							
#endif
}

void out_s(void)	//0x0005		OUT  s
{

	if(PLC_ACC_BIT&0x01)
	{
		PLC_BIT_ON(PLC_RAM16(PLC_PC+2)&0x0FFF);
	}
	else 
		PLC_BIT_OFF(PLC_RAM16(PLC_PC+2)&0x0FFF);	
	debug_send("OUT S%d=%d;\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF,PLC_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));
}

void set_s(void)		//0x0006		SET S
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_BIT_ON(PLC_RAM16(PLC_PC+2)&0x0FFF);
	}
	debug_send("SET S%d=%d;\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF,PLC_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));
}

void rst_s(void)	//0x0007		RST s
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_BIT_OFF(PLC_RAM16(PLC_PC+2)&0x0FFF);
	}
	debug_send("RST S%d=%d;\r\n",PLC_RAM16(PLC_PC+2)&0x0FFF,PLC_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));
}

void ret(void)	//0xF7FF		RET 步进返回
{
	PLC_RUN_BIT=3;//返回正常程序执行
	PLC_STL_CMD=0;//复位STL标志
	PLC_BIT_ON(PLC_STL_ADD);
	PLC_STL_ADD=0x03FF;
	PLC_PC+=2;
	debug_send("RET 步进返回\r\n");
}

void rst_t_c(void)	//0x000C
{
	if(PLC_RAM8(PLC_PC+3)==0x86)//RST T
	{
		if(PLC_ACC_BIT&0x01)
		{
			PLC_T_RST_ON(PLC_RAM8(PLC_PC+2));
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);
			PLC_RAM16(PLC_T_START_ADD+(PLC_RAM8(PLC_PC+2)*2))=0;
			PLC_BIT_OFF(PLC_RAM16(PLC_PC+2)&0x0FFF);
		}//END PLC_ACC_BIT
		else
		{
			if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2))
			{
				PLC_T_RST_OFF(PLC_RAM8(PLC_PC+2));
				PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
			}
		}//END ELSE
		#ifdef debug
		debug_send("RST T%d=%d;T_RAM=%d;\r\n",PLC_RAM8(PLC_PC+2),PLC_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF),PLC_RAM16(PLC_T_START_ADD+(PLC_RAM8(PLC_PC+2)*2)));
		#endif
	} //END RST T 
	else //RST C
	{
		if(PLC_ACC_BIT&0x01)
		{
			PLC_C_RST_ON(PLC_RAM8(PLC_PC+2));
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);
			if(PLC_RAM8(PLC_PC+2)<200)//RST C0-199
			{
				PLC_RAM16(PLC_C16_START_ADD+(PLC_RAM8(PLC_PC+2)*2))=0;
				PLC_BIT_OFF(PLC_RAM16(PLC_PC+2)&0x0FFF);
				debug_send("RST C%d=%d;C_RAM=%d;\r\n",PLC_RAM8(PLC_PC+2),PLC_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF),PLC_RAM16(PLC_C16_START_ADD+(PLC_RAM8(PLC_PC+2)*2)));								
			}//END RST C0-199
			else		//RST C200-255
			{
				PLC_RAM16(PLC_C32_START_ADD+((PLC_RAM8(PLC_PC+2)-200)*4))=0;
				PLC_RAM16(PLC_C32_START_ADD+((PLC_RAM8(PLC_PC+2)-200)*4)+2)=0;
				PLC_BIT_OFF(PLC_RAM16(PLC_PC+2)&0x0FFF);
				debug_send("RST C%d=%d;C_RAM=%d;\r\n",PLC_RAM8(PLC_PC+2),PLC_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF),PLC_RAM16(PLC_C32_START_ADD+((PLC_RAM8(PLC_PC+2)-200)*4)+2)<<16+PLC_RAM16(PLC_C32_START_ADD+((PLC_RAM8(PLC_PC+2)-200)*4)));																
			}//END RST C200-255
		}//ENDPLC_ACC_BIT
		else
		{
			if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2))
			{
				PLC_C_RST_OFF(PLC_RAM8(PLC_PC+2));
				PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
			}
			debug_send("RST C%d=%d;\r\n",PLC_RAM8(PLC_PC+2),PLC_BIT_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));															
		}//END ELSE
	}//END RST C	 
}
	
void rst_d(void)	//0x000D	RST D
{
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_RAM8(PLC_PC+5)==0x86)
		{
			PLC_RAM16(PLC_D_START_ADD+PLC_RAM8(PLC_PC+2)+(PLC_RAM8(PLC_PC+4)*0x100))=0;
			debug_send("RST D%d=%d;\r\n",(PLC_RAM8(PLC_PC+2)+(PLC_RAM8(PLC_PC+4)*0x100))/2,PLC_RAM16(PLC_D_START_ADD+PLC_RAM8(PLC_PC+2)+(PLC_RAM8(PLC_PC+4)*0x100)));
		}
		else 
			if(PLC_RAM8(PLC_PC+5)==0x88)
			{
				PLC_RAM16(PLC_D1000_START_ADD+PLC_RAM8(PLC_PC+2)+(PLC_RAM8(PLC_PC+4)*0x100))=0;
				debug_send("RST D%d=%d;\r\n",(PLC_RAM8(PLC_PC+2)+(PLC_RAM8(PLC_PC+4)*0x100))/3+1000,PLC_RAM16(PLC_D1000_START_ADD+PLC_RAM8(PLC_PC+2)+(PLC_RAM8(PLC_PC+4)*0x100)));
			}
			else 
				if(PLC_RAM8(PLC_PC+5)==0x80)
				{
					PLC_RAM16(PLC_D8000_START_ADD+PLC_RAM8(PLC_PC+2)+(PLC_RAM8(PLC_PC+4)*0x100))=0;
					debug_send("RST D8%03d=%d;\r\n",(PLC_RAM8(PLC_PC+2)+(PLC_RAM8(PLC_PC+4)*0x100))/2,PLC_RAM16(PLC_D8000_START_ADD+PLC_RAM8(PLC_PC+2)+(PLC_RAM8(PLC_PC+4)*0x100)));								
				}
				else 
				{
					PLC_PROG_ERROR(6501);
				}//操作的数据数型出错
	}//END PLC_ACC_BIT
}

/********************功能指令************************************************/
/**																		   **/
/********************程序流程************************************************/
void cj(void)		//0x0010
{
	PLC_PC+=6;
	if(PLC_ACC_BIT&0x01)
	{
	PLC_PC=PLC_PROG_START_ADD2+PLC_RAM16(PLC_R_START_ADD+0x5700+(PLC_RAM8(PLC_PC-4)));
	}
	debug_send("CJ PLC_PC=%d;\r\n",PLC_PC);
}

void call(void)	//0x0012
{
	PLC_PC+=6;
	PLC_O_PC=PLC_PC;	 //保存PC
	if(PLC_ACC_BIT&0x01)
	{
		PLC_PC=PLC_PROG_START_ADD2+PLC_RAM16(PLC_R_START_ADD+0x5700+(PLC_RAM8(PLC_PC-4)));
	}
	debug_send("CALL PLC_PC=%d;\r\n",PLC_PC);
}

void sret(void)	//0x0014
{
	PLC_PC=PLC_O_PC; //返回CALL前PC
	/*PLC_PC+=2;*/
	debug_send("SRET PLC_PC=%d;\r\n",PLC_PC);
}

void fend(void)	//0x001C
{
	PLC_END_PROG();
	debug_send("FEND\r\n");
}

/********************程序流程(P)*********************************************/
void cjp(void) //0x1010
{
	PLC_PC+=6;
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2-6)==0) 
		{
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2-6);	  
			PLC_PC=PLC_PROG_START_ADD2+PLC_RAM16(PLC_R_START_ADD+0x5700+(PLC_RAM8(PLC_PC-4)));
		}
	}
	else
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2-6);
	} 
	debug_send("CJP PLC_FNC_P_BIT=%d;PLC_PC=%d;\r\n",PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2-6),PLC_PC);					
}

void callp(void)	//0x1012
{
	PLC_PC+=6;
	PLC_O_PC=PLC_PC;	 //保存PC
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2-6)==0) 
		{
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2-6);	  
			PLC_PC=PLC_PROG_START_ADD2+PLC_RAM16(PLC_R_START_ADD+0x5700+(PLC_RAM8(PLC_PC-4)));
		}
	}
	else
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2-6);
	} 
	debug_send("CALL PLC_FNC_P_BIT=%d; PLC_PC=%d;\r\n",PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2-6),PLC_PC);					
}

void cmp(void)	//0x0024
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_TEMP1=PLC_ByteRead16(PLC_PC+2);
		PLC_TEMP2=PLC_ByteRead16(PLC_PC+6);
		PLC_TEMP3=PLC_ProgAddReturn(PLC_PC+10);
		if(PLC_TEMP1>PLC_TEMP2)
		{
			PLC_BIT_ON(PLC_TEMP3);
			PLC_BIT_OFF(PLC_TEMP3+1);
			PLC_BIT_OFF(PLC_TEMP3+2);
		}
		else 
			if(PLC_TEMP1==PLC_TEMP2)
			{
				PLC_BIT_OFF(PLC_TEMP3);
				PLC_BIT_ON(PLC_TEMP3+1);
				PLC_BIT_OFF(PLC_TEMP3+2);
			}
			else
			{
				PLC_BIT_OFF(PLC_TEMP3);
				PLC_BIT_OFF(PLC_TEMP3+1);
				PLC_BIT_ON(PLC_TEMP3+2);
			}
	}//END PLC_ACC_BIT&0x01
}

void zcp(void)		//0x0026
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_TEMP1=PLC_ByteRead16(PLC_PC+2);
		PLC_TEMP2=PLC_ByteRead16(PLC_PC+6);
		PLC_TEMP3=PLC_ByteRead16(PLC_PC+10);
		PLC_TEMP4=PLC_ProgAddReturn(PLC_PC+14);
		if(PLC_TEMP1>PLC_TEMP3)
		{
			PLC_BIT_ON(PLC_TEMP4);
			PLC_BIT_OFF(PLC_TEMP4+1);
			PLC_BIT_OFF(PLC_TEMP4+2);
		}
		else if(PLC_TEMP2<PLC_TEMP3)
		{
			PLC_BIT_OFF(PLC_TEMP4);
			PLC_BIT_OFF(PLC_TEMP4+1);
			PLC_BIT_ON(PLC_TEMP4+2);
		}
		else
		{
			PLC_BIT_OFF(PLC_TEMP4);
			PLC_BIT_ON(PLC_TEMP4+1);
			PLC_BIT_OFF(PLC_TEMP4+2);
		}
	}//END PLC_ACC_BIT&0x01
}

void mov(void)	//0x0028
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_ByteWrite16(PLC_PC+6,PLC_ByteRead16(PLC_PC+2));
	}
}

void bmov(void)		//0x002E
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_TEMP5=PLC_ProgAddReturn(PLC_PC+2)+PLC_R_START_ADD;
		PLC_TEMP6=PLC_ProgAddReturn(PLC_PC+6)+PLC_R_START_ADD;
		PLC_TEMP3=PLC_ByteRead16(PLC_PC+10)*2;
		for(PLC_TEMP4=0;PLC_TEMP3>PLC_TEMP4;PLC_TEMP4+=2)
		{
			if(PLC_BIT_TEST(M8024))
			{
				PLC_RAM16(PLC_TEMP5+PLC_TEMP4)=PLC_RAM16(PLC_TEMP6+PLC_TEMP4);
			}
			else 
			{
				PLC_RAM16(PLC_TEMP6+PLC_TEMP4)=PLC_RAM16(PLC_TEMP5+PLC_TEMP4);
			}
		}
	}//END PLC_ACC_BIT&0x01
}

void dcmp(void)	//0x0025
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_TEMP5=PLC_ByteRead32(PLC_PC+2);
		PLC_TEMP6=PLC_ByteRead32(PLC_PC+10);
		PLC_TEMP3=PLC_ProgAddReturn(PLC_PC+18);
		if(PLC_TEMP5>PLC_TEMP6)
		{
			PLC_BIT_ON(PLC_TEMP3);
			PLC_BIT_OFF(PLC_TEMP3+1);
			PLC_BIT_OFF(PLC_TEMP3+2);
		}
		else if(PLC_TEMP5==PLC_TEMP6)
		{
			PLC_BIT_OFF(PLC_TEMP3);
			PLC_BIT_ON(PLC_TEMP3+1);
			PLC_BIT_OFF(PLC_TEMP3+2);
		}
		else
		{
			PLC_BIT_OFF(PLC_TEMP3);
			PLC_BIT_OFF(PLC_TEMP3+1);
			PLC_BIT_ON(PLC_TEMP3+2);
		}
	}//END PLC_ACC_BIT&0x01
}

void dzcp(void)		//0x0027
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_TEMP5=PLC_ByteRead32(PLC_PC+2);
		PLC_TEMP6=PLC_ByteRead32(PLC_PC+10);
		PLC_TEMPA=PLC_ByteRead32(PLC_PC+18);
		PLC_TEMP4=PLC_ProgAddReturn(PLC_PC+26);
		if(PLC_TEMP5>PLC_TEMPA)
		{
			PLC_BIT_ON(PLC_TEMP4);
			PLC_BIT_OFF(PLC_TEMP4+1);
			PLC_BIT_OFF(PLC_TEMP4+2);
		}
		else if(PLC_TEMP6<PLC_TEMPA)
		{
			PLC_BIT_OFF(PLC_TEMP4);
			PLC_BIT_OFF(PLC_TEMP4+1);
			PLC_BIT_ON(PLC_TEMP4+2);
		}
		else
		{
			PLC_BIT_OFF(PLC_TEMP4);
			PLC_BIT_ON(PLC_TEMP4+1);
			PLC_BIT_OFF(PLC_TEMP4+2);
		}
	}//END PLC_ACC_BIT&0x01
}

void dmov(void)	//0x0029
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_ByteWrite32(PLC_PC+10,PLC_ByteRead32(PLC_PC+2));
	}
}	

/********************传送比较指令(P)********************************************/
void cmpp(void)	//0x1024
{
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2)==0) 
		{
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);	  
			PLC_TEMP1=PLC_ByteRead16(PLC_PC+2);
			PLC_TEMP2=PLC_ByteRead16(PLC_PC+6);
			PLC_TEMP3=PLC_ProgAddReturn(PLC_PC+10);
			if(PLC_TEMP1>PLC_TEMP2)
			{
				PLC_BIT_ON(PLC_TEMP3);
				PLC_BIT_OFF(PLC_TEMP3+1);
				PLC_BIT_OFF(PLC_TEMP3+2);
			}
			else if(PLC_TEMP1==PLC_TEMP2)
			{
				PLC_BIT_OFF(PLC_TEMP3);
				PLC_BIT_ON(PLC_TEMP3+1);
				PLC_BIT_OFF(PLC_TEMP3+2);
			}
			else
			{
				PLC_BIT_OFF(PLC_TEMP3);
				PLC_BIT_OFF(PLC_TEMP3+1);
				PLC_BIT_ON(PLC_TEMP3+2);
			}
		}
	}//END PLC_ACC_BIT&0x01
	else
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
	}	  
}

void zcpp(void)	//0x1026
{
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2)==0) 
		{
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);	  
			PLC_TEMP1=PLC_ByteRead16(PLC_PC+2);
			PLC_TEMP2=PLC_ByteRead16(PLC_PC+6);
			PLC_TEMP3=PLC_ByteRead16(PLC_PC+10);
			PLC_TEMP4=PLC_ProgAddReturn(PLC_PC+14);
			if(PLC_TEMP1>PLC_TEMP3)
			{
				PLC_BIT_ON(PLC_TEMP4);
				PLC_BIT_OFF(PLC_TEMP4+1);
				PLC_BIT_OFF(PLC_TEMP4+2);
			}
			else if(PLC_TEMP2<PLC_TEMP3)
			{
				PLC_BIT_OFF(PLC_TEMP4);
				PLC_BIT_OFF(PLC_TEMP4+1);
				PLC_BIT_ON(PLC_TEMP4+2);
			}
			else
			{
				PLC_BIT_OFF(PLC_TEMP4);
				PLC_BIT_ON(PLC_TEMP4+1);
				PLC_BIT_OFF(PLC_TEMP4+2);
			}
		}
	}//END PLC_ACC_BIT&0x01
	else
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
	}	  
}

void movp(void)		//0x1028
{
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2)==0) 
		{
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);	  
			PLC_ByteWrite16(PLC_PC+6,PLC_ByteRead16(PLC_PC+2));
		}
	}
	else
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
	}	  
}

void bmovp(void)		//0x102E
{
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2)==0) 
		{
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);	  
			PLC_TEMP5=PLC_ProgAddReturn(PLC_PC+2)+PLC_R_START_ADD;
			PLC_TEMP6=PLC_ProgAddReturn(PLC_PC+6)+PLC_R_START_ADD;
			PLC_TEMP3=PLC_ByteRead16(PLC_PC+10)*2;
			for(PLC_TEMP4=0;PLC_TEMP3>PLC_TEMP4;PLC_TEMP4+=2)
			{
				if(PLC_BIT_TEST(M8024))
				{
					PLC_RAM16(PLC_TEMP5+PLC_TEMP4)=PLC_RAM16(PLC_TEMP6+PLC_TEMP4);
				}
				else 
				{	
					PLC_RAM16(PLC_TEMP6+PLC_TEMP4)=PLC_RAM16(PLC_TEMP5+PLC_TEMP4);
				}
			}
		}
	}//END PLC_ACC_BIT&0x01
	else
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
	}	  
}

/********************(D)传送比较指令(P)******************************************/
void dcmpp(void)	//0x1025
{
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2)==0) 
		{
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);	  
			PLC_TEMP5=PLC_ByteRead32(PLC_PC+2);
			PLC_TEMP6=PLC_ByteRead32(PLC_PC+10);
			PLC_TEMP3=PLC_ProgAddReturn(PLC_PC+18);
			if(PLC_TEMP5>PLC_TEMP6)
			{
				PLC_BIT_ON(PLC_TEMP3);
				PLC_BIT_OFF(PLC_TEMP3+1);
				PLC_BIT_OFF(PLC_TEMP3+2);
			}
			else if(PLC_TEMP5==PLC_TEMP6)
			{
				PLC_BIT_OFF(PLC_TEMP3);
				PLC_BIT_ON(PLC_TEMP3+1);
				PLC_BIT_OFF(PLC_TEMP3+2);
			}
			else
			{
				PLC_BIT_OFF(PLC_TEMP3);
				PLC_BIT_OFF(PLC_TEMP3+1);
				PLC_BIT_ON(PLC_TEMP3+2);
			}
		}
	}//END PLC_ACC_BIT&0x01
	else
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
	}	  
}

void dzcpp(void)	//0x1027
{
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2)==0) 
		{
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);	  
			PLC_TEMP5=PLC_ByteRead32(PLC_PC+2);
			PLC_TEMP6=PLC_ByteRead32(PLC_PC+10);
			PLC_TEMPA=PLC_ByteRead32(PLC_PC+18);
			PLC_TEMP4=PLC_ProgAddReturn(PLC_PC+26);
			if(PLC_TEMP5>PLC_TEMPA)
			{
				PLC_BIT_ON(PLC_TEMP4);
				PLC_BIT_OFF(PLC_TEMP4+1);
				PLC_BIT_OFF(PLC_TEMP4+2);
			}
			else if(PLC_TEMP6<PLC_TEMPA)
			{
				PLC_BIT_OFF(PLC_TEMP4);
				PLC_BIT_OFF(PLC_TEMP4+1);
				PLC_BIT_ON(PLC_TEMP4+2);
			}
			else
			{
				PLC_BIT_OFF(PLC_TEMP4);
				PLC_BIT_ON(PLC_TEMP4+1);
				PLC_BIT_OFF(PLC_TEMP4+2);
			}
		}
	}//END PLC_ACC_BIT&0x01
	else
	{	
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
	}	  
}

void dmovp(void)	//0x1029
{
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2)==0) 
		{
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);	  
			PLC_ByteWrite32(PLC_PC+10,PLC_ByteRead32(PLC_PC+2));
		}
	}
	else
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
	}	  
}

/********************四则.逻辑运算*******************************************/

void add(void)		//0x0038
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_ByteWrite16(PLC_PC+10,PLC_ByteRead16(PLC_PC+2)+PLC_ByteRead16(PLC_PC+6));
	}
}

void sub(void)		//0x003A
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_ByteWrite16(PLC_PC+10,PLC_ByteRead16(PLC_PC+2)-PLC_ByteRead16(PLC_PC+6));
	}
}

void mul(void)	//0x003C
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_ByteWrite32(PLC_PC+10,PLC_ByteRead16(PLC_PC+2)*PLC_ByteRead16(PLC_PC+6));
	}
}

void div(void)	//0x003E
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_TEMP1=PLC_ByteRead16(PLC_PC+2);
		PLC_TEMP2=PLC_ByteRead16(PLC_PC+6);
		PLC_ByteWrite32(PLC_PC+10,(PLC_TEMP1/PLC_TEMP2)+((PLC_TEMP1%PLC_TEMP2)*0x10000));
	}//END PLC_ACC_BIT
}

void inc(void)		//0x0040
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_ByteWrite16(PLC_PC+2,PLC_ByteRead16(PLC_PC+2)+1);
	}
}

void dec(void)	//0x0042
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_ByteWrite16(PLC_PC+2,PLC_ByteRead16(PLC_PC+2)-1);
	}
}

void wand(void)		//0x0044
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_ByteWrite16(PLC_PC+10,PLC_ByteRead16(PLC_PC+2)&PLC_ByteRead16(PLC_PC+6));
	}
}

void wor(void)		//0x0046
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_ByteWrite16(PLC_PC+10,PLC_ByteRead16(PLC_PC+2)|PLC_ByteRead16(PLC_PC+6));
	}
}

void wxor(void)	//0x0048
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_ByteWrite16(PLC_PC+10,PLC_ByteRead16(PLC_PC+2)^PLC_ByteRead16(PLC_PC+6));
	}
}

/********************(D)四则.逻辑运算*******************************************/
void dadd(void)	//0x0039
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_ByteWrite32(PLC_PC+18,PLC_ByteRead32(PLC_PC+2)+PLC_ByteRead32(PLC_PC+10));
	}
}

void dsub(void)	//0x003B
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_ByteWrite32(PLC_PC+18,PLC_ByteRead32(PLC_PC+2)-PLC_ByteRead32(PLC_PC+10));
	}
}

void dmul(void)	//0x003D
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_TEMP8=PLC_ByteRead32(PLC_PC+2);
		PLC_TEMP9=PLC_ByteRead32(PLC_PC+10);
		PLC_TEMP7=PLC_TEMP8*PLC_TEMP9;
		PLC_ByteWrite64(PLC_PC+18,PLC_TEMP7,(PLC_TEMP7/0x100000000));
	}
}

void ddiv(void)	//0x003F
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_TEMP5=PLC_ByteRead32(PLC_PC+2);
		PLC_TEMP6=PLC_ByteRead32(PLC_PC+10);
		PLC_ByteWrite64(PLC_PC+18,PLC_TEMP5/PLC_TEMP6,PLC_TEMP5%PLC_TEMP6);
	}//END PLC_ACC_BIT
}

void dinc(void)	//0x0041
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_ByteWrite32(PLC_PC+2,PLC_ByteRead32(PLC_PC+2)+1);
	}
}

void ddec(void)	//0x0043
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_ByteWrite32(PLC_PC+2,PLC_ByteRead32(PLC_PC+2)-1);
	}
}

void dwand(void)	//0x0045
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_ByteWrite32(PLC_PC+18,PLC_ByteRead32(PLC_PC+2)&PLC_ByteRead32(PLC_PC+10));
	}
}

void dwor(void)	//0x0047
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_ByteWrite32(PLC_PC+18,PLC_ByteRead32(PLC_PC+2)|PLC_ByteRead32(PLC_PC+10));
	}
}

void dwxor(void)	//0x0049
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_ByteWrite32(PLC_PC+18,PLC_ByteRead32(PLC_PC+2)^PLC_ByteRead32(PLC_PC+10));
	}
}

/********************四则.逻辑运算(P)*******************************************/
void addp(void)	//0x1038
{
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2)==0) 
		{
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);	  
	   		PLC_ByteWrite16(PLC_PC+10,PLC_ByteRead16(PLC_PC+2)+PLC_ByteRead16(PLC_PC+6));
		}
	}
	else 
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
	} 
}

void subp(void)	//0x103A
{
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2)==0) 
		{
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);	  
			PLC_ByteWrite16(PLC_PC+10,PLC_ByteRead16(PLC_PC+2)-PLC_ByteRead16(PLC_PC+6));
		}
	}
	else 
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
	} 
}

void mulp(void)	//0x103C
{
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2)==0) 
		{
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);	  
			PLC_ByteWrite32(PLC_PC+10,PLC_ByteRead16(PLC_PC+2)*PLC_ByteRead16(PLC_PC+6));
		}
	}
	else 
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
	} 
}

void divp(void)	//0x103E
{
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2)==0) 
		{
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);	  
			PLC_TEMP1=PLC_ByteRead16(PLC_PC+2);
			PLC_TEMP2=PLC_ByteRead16(PLC_PC+6);
			PLC_ByteWrite32(PLC_PC+10,(PLC_TEMP1/PLC_TEMP2)+((PLC_TEMP1%PLC_TEMP2)*0x10000));
		}
	}//END PLC_ACC_BIT
	else 
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
	} 
}

void incp(void)		//0x1040
{
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2)==0) 
		{
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);	  
			PLC_ByteWrite16(PLC_PC+2,PLC_ByteRead16(PLC_PC+2)+1);
		}
	}
	else 
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
	} 
}

void decp(void)	//0x1042
{
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2)==0) 
	  	{
	  		PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);	  
			PLC_ByteWrite16(PLC_PC+2,PLC_ByteRead16(PLC_PC+2)-1);
		}
	}
	else 
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
	} 
}

void wandp(void)	//0x1044
{
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2)==0) 
		{
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);	  
			PLC_ByteWrite16(PLC_PC+10,PLC_ByteRead16(PLC_PC+2)&PLC_ByteRead16(PLC_PC+6));
		}
	}
	else 
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
	} 
}

void worp(void)	//0x1046
{
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2)==0) 
		{
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);	  
			PLC_ByteWrite16(PLC_PC+10,PLC_ByteRead16(PLC_PC+2)|PLC_ByteRead16(PLC_PC+6));
		}
	}
	else 
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
	} 
}

void wxorp(void)	//0x1048
{
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2)==0) 
		{
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);	  
			PLC_ByteWrite16(PLC_PC+10,PLC_ByteRead16(PLC_PC+2)^PLC_ByteRead16(PLC_PC+6));
		}
	}
	else 
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
	} 
}

/********************(D)四则.逻辑运算(P)*******************************************/
void daddp(void)		//0x1039
{
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2)==0) 
		{
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);	  
			PLC_ByteWrite32(PLC_PC+18,PLC_ByteRead32(PLC_PC+2)+PLC_ByteRead32(PLC_PC+10));
		}
	}
	else 
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
	} 
}

void dsubp(void)		//0x103B
{
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2)==0) 
		{
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);	 
			PLC_ByteWrite32(PLC_PC+18,PLC_ByteRead32(PLC_PC+2)-PLC_ByteRead32(PLC_PC+10));
		}
	}
	else 
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
	} 
}

void dmulp(void)		//0x103D
{
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2)==0) 
		{
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);	  
			PLC_TEMP8=PLC_ByteRead32(PLC_PC+2);
			PLC_TEMP9=PLC_ByteRead32(PLC_PC+10);
			PLC_TEMP7=PLC_TEMP8*PLC_TEMP9;
			PLC_ByteWrite64(PLC_PC+18,PLC_TEMP7,PLC_TEMP7/0x100000000);
		}
	}
	else 
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
	} 
}

void ddivp(void)		//0x103F
{
	if(PLC_ACC_BIT&0x01){
	if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2)==0) 
	{
		PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);	  
		PLC_TEMP5=PLC_ByteRead32(PLC_PC+2);
		PLC_TEMP6=PLC_ByteRead32(PLC_PC+10);
		PLC_ByteWrite64(PLC_PC+18,PLC_TEMP5/PLC_TEMP6,PLC_TEMP5%PLC_TEMP6);
	}
	}//END PLC_ACC_BIT
	else 
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
	} 
}

void dincp(void)	//0x1041
{
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2)==0) 
		{
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);	  
			PLC_ByteWrite32(PLC_PC+2,PLC_ByteRead32(PLC_PC+2)+1);
		}
	}
	else 
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
	} 
}

void ddecp(void)		//0x1043
{
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2)==0) 
		{
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);	  
			PLC_ByteWrite32(PLC_PC+2,PLC_ByteRead32(PLC_PC+2)-1);
		}
	}
	else
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
	} 
}
 
void dwandp(void)	//0x1045
{
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2)==0) 
		{
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);	  
			PLC_ByteWrite32(PLC_PC+18,PLC_ByteRead32(PLC_PC+2)&PLC_ByteRead32(PLC_PC+10));
		}
	}
	else 
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
	} 
}

void dworp(void)		//0x1047
{
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2)==0) 
		{
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);	  
			PLC_ByteWrite32(PLC_PC+18,PLC_ByteRead32(PLC_PC+2)|PLC_ByteRead32(PLC_PC+10));
		}
	}
	else 
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
	}
}

void dwxorp(void)	//0x1049
{
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2)==0) 
		{
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);	  
			PLC_ByteWrite32(PLC_PC+18,PLC_ByteRead32(PLC_PC+2)^PLC_ByteRead32(PLC_PC+10));
		}
	}
	else 
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
	} 
}

/********************数据处理************************************************/
void zrst(void)	//0x0060
{
	if(PLC_ACC_BIT&0x01)
  	{
  		PLC_TEMP1=PLC_ProgTypeReturn(PLC_PC+2);
  		if(PLC_TEMP1==0x02)
	  	{
	  		PLC_TEMP2=PLC_ProgAddReturn(PLC_PC+6)+1;
	   		if(PLC_TEMP2>=0x0C00&&PLC_TEMP2<=0x0CDF)
			{
				PLC_TEMP2+=2;
			}
	   		PLC_ByteReset(PLC_ProgAddReturn(PLC_PC+2),PLC_TEMP2);
			#ifdef debug
			if(PLC_ProgAddReturn(PLC_PC+2)>=0x1000 && PLC_ProgAddReturn(PLC_PC+2)<=0x4E7F)
			{					
				debug_send("ZRST D%d~D%d\r\n",PLC_ProgAddReturn(PLC_PC+2)-0x1000,(PLC_TEMP2-0x1000)/2);
				for(temp=PLC_ProgAddReturn(PLC_PC+2)-0x1000;temp<=(PLC_TEMP2-0x1000)/2;temp++)
					{debug_send("D%d=%d;",temp,PLC_RAM16(temp*2+PLC_R_START_ADD+0x1000));}
				debug_send("\r\n");
			}
			if(PLC_ProgAddReturn(PLC_PC+2)>=0x800 && PLC_ProgAddReturn(PLC_PC+2)<=0x9FF)
			{					
				debug_send("ZRST T%d~T%d\r\n",PLC_ProgAddReturn(PLC_PC+2)-0x800,(PLC_TEMP2-0x800)/2);
				for(temp=PLC_ProgAddReturn(PLC_PC+2)-0x800;temp<=(PLC_TEMP2-0x800)/2;temp++)
					{debug_send("T%d=%d;",temp,PLC_RAM16(temp*2+PLC_R_START_ADD+0x800));}
				debug_send("\r\n");	
			}				
			if(PLC_ProgAddReturn(PLC_PC+2)>=0xA00 && PLC_ProgAddReturn(PLC_PC+2)<=0xCDF)
			{
				if(PLC_TEMP2<0xC00)
					{debug_send("ZRST C%d~C%d\r\n",PLC_ProgAddReturn(PLC_PC+2)-0xA00,(PLC_TEMP2-0xA00)/2);
					for(temp=PLC_ProgAddReturn(PLC_PC+2)-0xA00;temp<=(PLC_TEMP2-0xA00)/2;temp++)
						{debug_send("C%d=%d;",temp,PLC_RAM16(temp*2+PLC_R_START_ADD+0xA00));}
						debug_send("\r\n");}
				else if(PLC_ProgAddReturn(PLC_PC+2)>=0xC00)
					{debug_send("ZRST C%d~C%d\r\n",PLC_ProgAddReturn(PLC_PC+2)-0xC00+0xC8,(PLC_TEMP2-0xC00)/4+0xC8);
					for(temp=PLC_ProgAddReturn(PLC_PC+2)-0xC00+0xC8;temp<=(PLC_TEMP2-0xC00)/4+0xC8;temp++)
					{debug_send("C%d=%d;",temp,PLC_RAM16(temp*4+PLC_R_START_ADD+0xC00));}
					debug_send("\r\n");}
				else
				{
					debug_send("ZRST C%d~C%d\r\n",PLC_ProgAddReturn(PLC_PC+2)-0xA00,0xC7);
					for(temp=PLC_ProgAddReturn(PLC_PC+2)-0xA00;temp<=0xC7;temp++)
					{debug_send("C%d=%d;",temp,PLC_RAM16(temp*2+PLC_R_START_ADD+0xA00));}
					debug_send("\r\n");
					
					debug_send("ZRST C%d~C%d\r\n",0xc8,(PLC_TEMP2-0xC00)/4+0xC8);
					for(temp=0xc8;temp<=((PLC_TEMP2-0xC00)/4+0xC8);temp++)
					{debug_send("C%d=%d;",temp,PLC_RAM16(temp*4+PLC_R_START_ADD+0xC00));}
					debug_send("\r\n");	
				}
			}
			if(PLC_ProgAddReturn(PLC_PC+2)>=0xE00 && PLC_ProgAddReturn(PLC_PC+2)<=0xFFF) //******************
			{
				debug_send("ZRST D8%03d~D8%03d\r\n",PLC_ProgAddReturn(PLC_PC+2)-0xE00,(PLC_TEMP2-0xE00)/2);
				for(temp=PLC_ProgAddReturn(PLC_PC+2)-0xE00;temp<=(PLC_TEMP2-0xE00)/2;temp++)
					{debug_send("D8%03d=%d;",temp,PLC_RAM16(temp*2+PLC_R_START_ADD+0xE00));}
				debug_send("\r\n");	
			}						
			#endif
		}
		else if(PLC_TEMP1==0x0b)
	   		{
	   			PLC_BitReset(PLC_ProgAddReturn(PLC_PC+2),PLC_ProgAddReturn(PLC_PC+6));
				#ifdef debug
				if(PLC_ProgAddReturn(PLC_PC+6)>=0 && PLC_ProgAddReturn(PLC_PC+6)<=0x3FF)
				{
					debug_send("ZRST S%d~S%d\r\n",PLC_ProgAddReturn(PLC_PC+2),PLC_ProgAddReturn(PLC_PC+6));
					for(temp=PLC_ProgAddReturn(PLC_PC+2);temp<=PLC_ProgAddReturn(PLC_PC+6);temp++)
						{debug_send("S%d=%d;",temp,PLC_BIT_TEST(temp));}
					debug_send("\r\n");
				}
				if(PLC_ProgAddReturn(PLC_PC+6)>=0x800 && PLC_ProgAddReturn(PLC_PC+6)<=0xDFF)
				{
					debug_send("ZRST M%d~M%d\r\n",PLC_ProgAddReturn(PLC_PC+2)-0x800,PLC_ProgAddReturn(PLC_PC+6)-0x800);
					for(temp=PLC_ProgAddReturn(PLC_PC+2);temp<=PLC_ProgAddReturn(PLC_PC+6);temp++)
						{debug_send("M%d=%d;",temp-0x800,PLC_BIT_TEST(temp-0x800));}
					debug_send("\r\n");
				}		
				if(PLC_ProgAddReturn(PLC_PC+6)>=0x500 && PLC_ProgAddReturn(PLC_PC+6)<=0x5FF)
				{
					debug_send("ZRST Y%o~Y%o\r\n",PLC_ProgAddReturn(PLC_PC+2)-0x500,PLC_ProgAddReturn(PLC_PC+6)-0x500);
					for(temp=PLC_ProgAddReturn(PLC_PC+2);temp<=PLC_ProgAddReturn(PLC_PC+6);temp++)
						{debug_send("Y%o=%d;",temp-0x500,PLC_BIT_TEST(temp-0x500));}
					debug_send("\r\n");
				}			
				#endif
			}
			else
			{
				PLC_PROG_ERROR(6501);
			}//操作的数据数型出错
	}//END PLC_ACC_BIT
}

void zrstp(void)		//0x1060
{
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2)==0)
		{ 
		 	PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);	  
		 	if(PLC_TEMP1==0x02)
			{
				PLC_TEMP2=PLC_ProgAddReturn(PLC_PC+6)+1;
				if(PLC_TEMP2>=0x0C00&&PLC_TEMP2<=0x0CDF)
				{
					PLC_TEMP2+=2;
				}
				PLC_ByteReset(PLC_ProgAddReturn(PLC_PC+2),PLC_TEMP2);
			}
			else if(PLC_TEMP1==0x0b)
			{
				PLC_BitReset(PLC_ProgAddReturn(PLC_PC+2),PLC_ProgAddReturn(PLC_PC+6));
			}
			else 
			{	
				PLC_PROG_ERROR(6501);
			}//操作的数据数型出错
		}//END 
	}//END PLC_ACC_BIT
	else
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
	}	  
}

/********************高速指令************************************************/
void plsy(void)		//0x0082
{
	PLC_BIT_OFF(M8029);
	if(PLC_ACC_BIT&0x01)
	{
		PLC_PLSY_RUN(PLC_ByteRead16(PLC_PC+2),PLC_ByteRead16(PLC_PC+6),PLC_ProgAddReturn(PLC_PC+10));
	}
	else 
	{	
		PLC_PLSY_STOP(PLC_ProgAddReturn(PLC_PC+10));
	}
}

void pwm(void)		//0x0084
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_PWM_RUN(PLC_ByteRead16(PLC_PC+2),PLC_ByteRead16(PLC_PC+6),PLC_ProgAddReturn(PLC_PC+10));
	}
	else 
	{	
		PLC_PWM_STOP(PLC_ProgAddReturn(PLC_PC+10));
	}
}

/********************(D)高速指令*********************************************/
void dplsy(void)	//0x0083
{
	PLC_BIT_OFF(M8029);
	if(PLC_ACC_BIT&0x01)
	{
		PLC_PLSY_RUN(PLC_ByteRead32(PLC_PC+2),PLC_ByteRead32(PLC_PC+10),PLC_ProgAddReturn(PLC_PC+18));
	}
	else 
	{
		PLC_PLSY_STOP(PLC_ProgAddReturn(PLC_PC+18));
	}
}

/********************方便指令************************************************/
void alt(void)		//0x0094
{
	if(PLC_ACC_BIT&0x01)
	{
		PLC_TEMP1=PLC_ProgAddReturn(PLC_PC+2);
		if(PLC_BIT_TEST(PLC_TEMP1))
		{
			PLC_BIT_OFF(PLC_TEMP1);
		}
		else 
		{
			PLC_BIT_ON(PLC_TEMP1);
		}
	}//END PLC_ACC_BIT
}

/********************方便指令(P)*********************************************/
void altp(void)		//0x1094
{
	if(PLC_ACC_BIT&0x01)
	{
		if(PLC_FNC_P_BIT_TEST(PLC_PC-PLC_PROG_START_ADD2)==0)
		{ 
			PLC_FNC_P_BIT_ON(PLC_PC-PLC_PROG_START_ADD2);	  
			PLC_TEMP1=PLC_ProgAddReturn(PLC_PC+2);
			if(PLC_BIT_TEST(PLC_TEMP1))
			{
				PLC_BIT_OFF(PLC_TEMP1);
			}
			else 
			{	
				PLC_BIT_ON(PLC_TEMP1);
			}
		}//END 测试执行标志
	}//END PLC_ACC_BIT
	else
	{
		PLC_FNC_P_BIT_OFF(PLC_PC-PLC_PROG_START_ADD2);
	}	 
}

/********************接点比较************************************************/
void ld_eq(void)		//0x01D0
{
	PLC_ACC_BIT <<= 1;
	if(PLC_ByteRead16(PLC_PC+2)==PLC_ByteRead16(PLC_PC+6))
		PLC_ACC_BIT |=0x01;
	PLC_PC+=10;
}

void ld_gt(void)		//0x01D2
{
	PLC_ACC_BIT <<= 1;
	if(PLC_ByteRead16(PLC_PC+2)>PLC_ByteRead16(PLC_PC+6))
		PLC_ACC_BIT |=0x01;
	PLC_PC+=10;	
}

void ld_lt(void)	//0x01D4
{
	PLC_ACC_BIT <<= 1;
	if(PLC_ByteRead16(PLC_PC+2)<PLC_ByteRead16(PLC_PC+6))
		PLC_ACC_BIT |=0x01;
	PLC_PC+=10;
}

void ld_gt_lt(void)	//0x01D8
{
	PLC_ACC_BIT <<= 1;
	if(PLC_ByteRead16(PLC_PC+2)!=PLC_ByteRead16(PLC_PC+6))
		PLC_ACC_BIT |=0x01;
	PLC_PC+=10;
}

void ld_le(void)	//0x01DA
{
	PLC_ACC_BIT <<= 1;
	if(PLC_ByteRead16(PLC_PC+2)<=PLC_ByteRead16(PLC_PC+6))
		PLC_ACC_BIT |=0x01;
	PLC_PC+=10;
}

void ld_ge(void)	//0x01DC
{
	PLC_ACC_BIT <<= 1;
	if(PLC_ByteRead16(PLC_PC+2)>=PLC_ByteRead16(PLC_PC+6))
		PLC_ACC_BIT |=0x01;
	PLC_PC+=10;
}

void and_eq(void)	//0x01E0
{
	if(PLC_ByteRead16(PLC_PC+2)==PLC_ByteRead16(PLC_PC+6))
		PLC_ACC_BIT &=0x01;
	else 
		PLC_ACC_BIT &=0xfe;
	PLC_PC+=10;
}

void and_gt(void)	//0x01E2
{
	if(PLC_ByteRead16(PLC_PC+2)>PLC_ByteRead16(PLC_PC+6))
		PLC_ACC_BIT &=0x01;
	else
		PLC_ACC_BIT &=0xfe;
	PLC_PC+=10;
}

void and_lt(void)	//0x01E4
{
	if(PLC_ByteRead16(PLC_PC+2)<PLC_ByteRead16(PLC_PC+6))
		PLC_ACC_BIT &=0x01;
	else 
		PLC_ACC_BIT &=0xfe;
	PLC_PC+=10;
}

void and_gt_lt(void)	//0x01E8
{
	if(PLC_ByteRead16(PLC_PC+2)!=PLC_ByteRead16(PLC_PC+6))
		PLC_ACC_BIT &=0x01;
	else 
		PLC_ACC_BIT &=0xfe;
	PLC_PC+=10;
}

void and_le(void)	//0x01EA
{
	if(PLC_ByteRead16(PLC_PC+2)<=PLC_ByteRead16(PLC_PC+6))
		PLC_ACC_BIT &=0x01;
	else 
		PLC_ACC_BIT &=0xfe;
	PLC_PC+=10;
}

void and_ge(void)	//0x01EC
{
	if(PLC_ByteRead16(PLC_PC+2)>=PLC_ByteRead16(PLC_PC+6))
		PLC_ACC_BIT &=0x01;
	else 
		PLC_ACC_BIT &=0xfe;
	PLC_PC+=10;
}

void or_eq(void)	//0x01F0
{
	if(PLC_ByteRead16(PLC_PC+2)==PLC_ByteRead16(PLC_PC+6))
		PLC_ACC_BIT |=0x01;
	PLC_PC+=10;
}

void or_gt(void)	//0x01F2
{
	if(PLC_ByteRead16(PLC_PC+2)>PLC_ByteRead16(PLC_PC+6))
		PLC_ACC_BIT |=0x01;
	PLC_PC+=10;
}

void or_lt(void)	//0x01F4
{
	if(PLC_ByteRead16(PLC_PC+2)<PLC_ByteRead16(PLC_PC+6))
		PLC_ACC_BIT |=0x01;
	PLC_PC+=10;
}

void or_gt_lt(void)	//0x01F8
{
	if(PLC_ByteRead16(PLC_PC+2)!=PLC_ByteRead16(PLC_PC+6))
		PLC_ACC_BIT |=0x01;
	PLC_PC+=10;
}

void or_le(void)	//0x01FA
{
	if(PLC_ByteRead16(PLC_PC+2)<=PLC_ByteRead16(PLC_PC+6))
		PLC_ACC_BIT |=0x01;
	PLC_PC+=10;
}

void or_ge(void)	//0x01FC
{
	if(PLC_ByteRead16(PLC_PC+2)>=PLC_ByteRead16(PLC_PC+6))
		PLC_ACC_BIT |=0x01;
	PLC_PC+=10;
}

/********************(D)接点比较************************************************/
void dld_eq(void)	//0x01D1
{
	PLC_ACC_BIT <<= 1;
	if(PLC_ByteRead32(PLC_PC+2)==PLC_ByteRead32(PLC_PC+10))
		PLC_ACC_BIT |=0x01;
	PLC_PC+=18;
}

void dld_gt(void)	//0x01D3
{
	PLC_ACC_BIT <<= 1;
	if(PLC_ByteRead32(PLC_PC+2)>PLC_ByteRead32(PLC_PC+10))
		PLC_ACC_BIT |=0x01;
	PLC_PC+=18;
}

void dld_lt(void)		//0x01D5
{
	PLC_ACC_BIT <<= 1;
	if(PLC_ByteRead32(PLC_PC+2)<PLC_ByteRead32(PLC_PC+10))
		PLC_ACC_BIT |=0x01;
	PLC_PC+=18;
}

void dld_gt_lt(void)	//0x01D9
{
	PLC_ACC_BIT <<= 1;
	if(PLC_ByteRead32(PLC_PC+2)!=PLC_ByteRead32(PLC_PC+10))
		PLC_ACC_BIT |=0x01;
	PLC_PC+=18;
}

void dld_le(void)	//0x01DB
{
	PLC_ACC_BIT <<= 1;
	if(PLC_ByteRead32(PLC_PC+2)<=PLC_ByteRead32(PLC_PC+10))
		PLC_ACC_BIT |=0x01;
	PLC_PC+=18;
}

void dld_ge(void)		//0x01DD
{
	PLC_ACC_BIT <<= 1;
	if(PLC_ByteRead32(PLC_PC+2)>=PLC_ByteRead32(PLC_PC+10))
		PLC_ACC_BIT |=0x01;
	PLC_PC+=18;
}

void dand_eq(void)		//0x01E1
{
	if(PLC_ByteRead32(PLC_PC+2)==PLC_ByteRead32(PLC_PC+10))
		PLC_ACC_BIT &=0x01;
	else 
		PLC_ACC_BIT &=0xfe;
	PLC_PC+=18;
}

void dand_gt(void)		//0x01E3
{
	if(PLC_ByteRead32(PLC_PC+2)>PLC_ByteRead32(PLC_PC+10))
		PLC_ACC_BIT &=0x01;
	else 
		PLC_ACC_BIT &=0xfe;
	PLC_PC+=18;
}

void dand_lt(void)	//0x01E5
{
	if(PLC_ByteRead32(PLC_PC+2)<PLC_ByteRead32(PLC_PC+10))
		PLC_ACC_BIT &=0x01;
	else
		PLC_ACC_BIT &=0xfe;
	PLC_PC+=18;
}

void dand_gt_lt(void)	//0x01E9
{
	if(PLC_ByteRead32(PLC_PC+2)!=PLC_ByteRead32(PLC_PC+10))
		PLC_ACC_BIT &=0x01;
	else 
		PLC_ACC_BIT &=0xfe;
	PLC_PC+=18;
}

void dand_le(void)		//0x01EB
{
	if(PLC_ByteRead32(PLC_PC+2)<=PLC_ByteRead32(PLC_PC+10))
		PLC_ACC_BIT &=0x01;
	else 
		PLC_ACC_BIT &=0xfe;
	PLC_PC+=18;
}

void dand_ge(void)		//0x01ED
{
	if(PLC_ByteRead32(PLC_PC+2)>=PLC_ByteRead32(PLC_PC+10))
		PLC_ACC_BIT &=0x01;
	else 
		PLC_ACC_BIT &=0xfe;
	PLC_PC+=18;
}

void dor_eq(void)	//0x01F1
{
	if(PLC_ByteRead32(PLC_PC+2)==PLC_ByteRead32(PLC_PC+10))
		PLC_ACC_BIT |=0x01;
	PLC_PC+=18;
}

void dor_gt(void)	//0x01F3
{
	if(PLC_ByteRead32(PLC_PC+2)>PLC_ByteRead32(PLC_PC+10))
		PLC_ACC_BIT |=0x01;
	PLC_PC+=18;
}

void dor_lt(void)	//0x01F5
{
	if(PLC_ByteRead32(PLC_PC+2)<PLC_ByteRead32(PLC_PC+10))
		PLC_ACC_BIT |=0x01;
	PLC_PC+=18;
}

void dor_gt_lt(void)	//0x01F9
{
	if(PLC_ByteRead32(PLC_PC+2)!=PLC_ByteRead32(PLC_PC+10))
		PLC_ACC_BIT |=0x01;
	PLC_PC+=18;
}

void dor_le(void)	//0x01FB
{
	if(PLC_ByteRead32(PLC_PC+2)<=PLC_ByteRead32(PLC_PC+10))
		PLC_ACC_BIT |=0x01;
	PLC_PC+=18;
}

void dor_ge(void)	//0x01FD
{
	if(PLC_ByteRead32(PLC_PC+2)>=PLC_ByteRead32(PLC_PC+10))
		PLC_ACC_BIT |=0x01;
	PLC_PC+=18;
}

void end(void)	//0x000F
{
	PLC_END_PROG();
	debug_send("-------END--------\r\n");
}

void ldi_m1536(void)	//0x01C3
{
	PLC_ACC_BIT <<= 1;
	if(PLC_BIT_M1536_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));
	else	
		PLC_ACC_BIT |=0x01;
	PLC_PC+=4;
	debug_send("LDI M%d=%d\r\n",((PLC_RAM16(PLC_PC+2)&0x0FFF)-0x800)+1536,PLC_BIT_M1536_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));
}

void or_m1536(void)		//0x01C6
{
	if(PLC_BIT_M1536_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF))
		PLC_ACC_BIT |=0x01;						
	PLC_PC+=4;
	debug_send("OR M%d=%d\r\n",((PLC_RAM16(PLC_PC+2)&0x0FFF)-0x800)+1536,PLC_BIT_M1536_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));						
}

void ori_m1536(void)	//0x01C7
{
	if(PLC_BIT_M1536_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));
	else 
		PLC_ACC_BIT |=0x01;
	PLC_PC+=4;
	debug_send("ORI M%d=%d\r\n",((PLC_RAM16(PLC_PC+2)&0x0FFF)-0x800)+1536,PLC_BIT_M1536_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));						
}

void ani_m1536(void)		//0x01C5
{
	if(PLC_BIT_M1536_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF))
		PLC_ACC_BIT &=0xfe;
	else
		PLC_ACC_BIT &=0x01;
	PLC_PC+=4;
	debug_send("ANI M%d=%d\r\n",((PLC_RAM16(PLC_PC+2)&0x0FFF)-0x800)+1536,PLC_BIT_M1536_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));						
}

void and_m1536(void)	//0x01C4
{
	if(PLC_BIT_M1536_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF))
		PLC_ACC_BIT &=0x01;
	else	
		PLC_ACC_BIT &=0xfe;
	PLC_PC+=4;
	debug_send("AND M%d=%d\r\n",((PLC_RAM16(PLC_PC+2)&0x0FFF)-0x800)+1536,PLC_BIT_M1536_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));
}

void ld_m1536(void)	//0x01C2
{
	PLC_ACC_BIT <<= 1;
	if(PLC_BIT_M1536_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF))
	{
		PLC_ACC_BIT |=0x01; 	
	}
	debug_send("LD M%d=%d\r\n",((PLC_RAM16(PLC_PC+2)&0x0FFF)-0x800)+1536,PLC_BIT_M1536_TEST(PLC_RAM16(PLC_PC+2)&0x0FFF));
	PLC_PC+=4;	
}

void plc_wdt(void)	//0x001E
{
	if(PLC_ACC_BIT & 0x01)
		wdt_clear();
	PLC_PC+=2;
	debug_send("WDT\r\n");
}

void trd(void)	//0x015C
{
	PLC_PC+=6;
	debug_send("TRD\r\n");
}

void twr(void)		//0x015E
{
	PLC_PC+=6;
	debug_send("TWR\r\n");
}

void ref(void)	//0x0074
{
	PLC_PC+=10;
	debug_send("REF\r\n");
}

void dhscs(void)	//0x007B
{
	PLC_PC+=26;
	debug_send("DHSCS\r\n");
}

void ans(void)	//0x006C
{
	PLC_PC+=14;
	debug_send("ANS\r\n");
}

void anr(void)		//0x006E
{
	PLC_PC+=2;
	debug_send("ANR\r\n");
}

void stmr(void)	//0x0092
{
	PLC_PC+=14;
	debug_send("STMR\r\n");
}

void deco(void)	//0x0062
{
	PLC_PC+=14;
	debug_send("DECO\r\n");
}

void mc(void)	//0x000A
{
	PLC_PC+=6;
	debug_send("MC\r\n");
}

void mcr(void)		//0x000B
{
	PLC_PC+=4;
	debug_send("MCR\r\n");
}

void from(void)		//0x00AC
{
	PLC_PC+=18;
	debug_send("FROM\r\n");
}

void to(void)	//0x00AE
{
	PLC_PC+=18;
	debug_send("TO\r\n");
}

void fmov(void)	//0x0030
{
	PLC_PC+=14;
	debug_send("FMOV\r\n");
}

void ist(void)	//0x0088
{
	PLC_PC+=14;
	debug_send("IST\r\n");
}

void dfrom(void)	//0x00AD
{
	PLC_PC+=34;
	debug_send("DFROM\r\n");
}

void dto(void)	//0x00AF
{
	PLC_PC+=34;
	debug_send("DTO\r\n");
}

void ld(void)	//0x2000
{
	PLC_ACC_BIT <<= 1;
	if(PLC_BIT_TEST(PLC_TEMP1&0x0FFF))
 		PLC_ACC_BIT |=0x01;
 	PLC_PC+=2;
	#ifdef	debug
	if((PLC_TEMP1&0x0FFF)>=0x0 && (PLC_TEMP1&0x0FFF)<=0x03FF)
		{debug_send("LD S%d=%d\r\n",PLC_TEMP1&0x0FFF,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else if((PLC_TEMP1&0x0FFF)>=0x0400 && (PLC_TEMP1&0x0FFF)<=0x04FF)
			{debug_send("LD X%o=%d\r\n",PLC_TEMP1&0x0FFF-0x400,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0500 && (PLC_TEMP1&0x0FFF)<=0x05FF)
			{debug_send("LD Y%o=%d\r\n",PLC_TEMP1&0x0FFF-0x500,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0600 && (PLC_TEMP1&0x0FFF)<=0x07FF)
			{debug_send("LD T%d=%d\r\n",PLC_TEMP1&0x0FFF-0x600,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0800 && (PLC_TEMP1&0x0FFF)<=0x0DFF)
			{debug_send("LD M%d=%d\r\n",PLC_TEMP1&0x0FFF-0x800,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0E00   && (PLC_TEMP1&0x0FFF)<=0x0EFF)
			{debug_send("LD C%d=%d\r\n",PLC_TEMP1&0x0FFF-0xE00,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0F00 && (PLC_TEMP1&0x0FFF)<=0x0FFF)
			{debug_send("LD M8%03d=%d\r\n",PLC_TEMP1&0x0FFF-0xF00,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	#endif	 
}

void ldi(void)	//0x3000
{
	PLC_ACC_BIT <<= 1;
	if(PLC_BIT_TEST(PLC_TEMP1&0x0FFF));
	else	
		PLC_ACC_BIT |=0x01;
	PLC_PC+=2;
	#ifdef	debug
	if((PLC_TEMP1&0x0FFF)>=0x0 && (PLC_TEMP1&0x0FFF)<=0x03FF)
		{debug_send("LDI S%d=%d\r\n",PLC_TEMP1&0x0FFF,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else if((PLC_TEMP1&0x0FFF)>=0x0400 && (PLC_TEMP1&0x0FFF)<=0x04FF)
			{debug_send("LDI X%o=%d\r\n",PLC_TEMP1&0x0FFF-0x400,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0500 && (PLC_TEMP1&0x0FFF)<=0x05FF)
			{debug_send("LDI Y%o=%d\r\n",PLC_TEMP1&0x0FFF-0x500,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0600 && (PLC_TEMP1&0x0FFF)<=0x07FF)
			{debug_send("LDI T%d=%d\r\n",PLC_TEMP1&0x0FFF-0x600,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0800 && (PLC_TEMP1&0x0FFF)<=0x0DFF)
			{debug_send("LDI M%d=%d\r\n",PLC_TEMP1&0x0FFF-0x800,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0E00   && (PLC_TEMP1&0x0FFF)<=0x0EFF)
			{debug_send("LDI C%d=%d\r\n",PLC_TEMP1&0x0FFF-0xE00,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0F00 && (PLC_TEMP1&0x0FFF)<=0x0FFF)
			{debug_send("LDI M8%03d=%d\r\n",PLC_TEMP1&0x0FFF-0xF00,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	#endif	 
}

void and(void)		//0x4000
{
	if(PLC_BIT_TEST(PLC_TEMP1&0x0FFF))
		PLC_ACC_BIT &=0x01;
	 else	
	 	PLC_ACC_BIT &=0xfe;
	 PLC_PC+=2;
#ifdef	debug
	if((PLC_TEMP1&0x0FFF)>=0x0 && (PLC_TEMP1&0x0FFF)<=0x03FF)
		{debug_send("AND S%d=%d\r\n",PLC_TEMP1&0x0FFF,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else if((PLC_TEMP1&0x0FFF)>=0x0400 && (PLC_TEMP1&0x0FFF)<=0x04FF)
			{debug_send("AND X%o=%d\r\n",PLC_TEMP1&0x0FFF-0x400,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0500 && (PLC_TEMP1&0x0FFF)<=0x05FF)
			{debug_send("AND Y%o=%d\r\n",PLC_TEMP1&0x0FFF-0x500,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0600 && (PLC_TEMP1&0x0FFF)<=0x07FF)
			{debug_send("AND T%d=%d\r\n",PLC_TEMP1&0x0FFF-0x600,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0800 && (PLC_TEMP1&0x0FFF)<=0x0DFF)
			{debug_send("AND M%d=%d\r\n",PLC_TEMP1&0x0FFF-0x800,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0E00   && (PLC_TEMP1&0x0FFF)<=0x0EFF)
			{debug_send("AND C%d=%d\r\n",PLC_TEMP1&0x0FFF-0xE00,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0F00 && (PLC_TEMP1&0x0FFF)<=0x0FFF)
			{debug_send("AND M8%03d=%d\r\n",PLC_TEMP1&0x0FFF-0xF00,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
#endif	 
}

void ani(void)	//0x5000
{
	if(PLC_BIT_TEST(PLC_TEMP1&0x0FFF))
		PLC_ACC_BIT &=0xfe;
	else 
	 	PLC_ACC_BIT &=0x01;
	PLC_PC+=2;
	#ifdef	debug
	if((PLC_TEMP1&0x0FFF)>=0x0 && (PLC_TEMP1&0x0FFF)<=0x03FF)
		{debug_send("ANI S%d=%d\r\n",PLC_TEMP1&0x0FFF,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else if((PLC_TEMP1&0x0FFF)>=0x0400 && (PLC_TEMP1&0x0FFF)<=0x04FF)
			{debug_send("ANI X%o=%d\r\n",PLC_TEMP1&0x0FFF-0x400,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0500 && (PLC_TEMP1&0x0FFF)<=0x05FF)
			{debug_send("ANI Y%o=%d\r\n",PLC_TEMP1&0x0FFF-0x500,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0600 && (PLC_TEMP1&0x0FFF)<=0x07FF)
			{debug_send("ANI T%d=%d\r\n",PLC_TEMP1&0x0FFF-0x600,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0800 && (PLC_TEMP1&0x0FFF)<=0x0DFF)
			{debug_send("ANI M%d=%d\r\n",PLC_TEMP1&0x0FFF-0x800,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0E00   && (PLC_TEMP1&0x0FFF)<=0x0EFF)
			{debug_send("ANI C%d=%d\r\n",PLC_TEMP1&0x0FFF-0xE00,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0F00 && (PLC_TEMP1&0x0FFF)<=0x0FFF)
			{debug_send("ANI M8%03d=%d\r\n",PLC_TEMP1&0x0FFF-0xF00,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	#endif	 
}

void or(void)		//0x6000
{
	if(PLC_BIT_TEST(PLC_TEMP1&0x0FFF))
		PLC_ACC_BIT |=0x01;
	PLC_PC+=2;
#ifdef	debug
	if((PLC_TEMP1&0x0FFF)>=0x0 && (PLC_TEMP1&0x0FFF)<=0x03FF)
		{debug_send("OR S%d=%d\r\n",PLC_TEMP1&0x0FFF,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else if((PLC_TEMP1&0x0FFF)>=0x0400 && (PLC_TEMP1&0x0FFF)<=0x04FF)
			{debug_send("OR X%o=%d\r\n",PLC_TEMP1&0x0FFF-0x400,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0500 && (PLC_TEMP1&0x0FFF)<=0x05FF)
			{debug_send("OR Y%o=%d\r\n",PLC_TEMP1&0x0FFF-0x500,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0600 && (PLC_TEMP1&0x0FFF)<=0x07FF)
			{debug_send("OR T%d=%d\r\n",PLC_TEMP1&0x0FFF-0x600,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0800 && (PLC_TEMP1&0x0FFF)<=0x0DFF)
			{debug_send("OR M%d=%d\r\n",PLC_TEMP1&0x0FFF-0x800,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0E00   && (PLC_TEMP1&0x0FFF)<=0x0EFF)
			{debug_send("OR C%d=%d\r\n",PLC_TEMP1&0x0FFF-0xE00,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0F00 && (PLC_TEMP1&0x0FFF)<=0x0FFF)
			{debug_send("OR M8%03d=%d\r\n",PLC_TEMP1&0x0FFF-0xF00,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
#endif	 
}

void ori(void)	//0x7000
{
	if(PLC_BIT_TEST(PLC_TEMP1&0x0FFF));
	else 
		PLC_ACC_BIT |=0x01;
	PLC_PC+=2;
#ifdef	debug
	if((PLC_TEMP1&0x0FFF)>=0x0 && (PLC_TEMP1&0x0FFF)<=0x03FF)
	{
		debug_send("ORI S%d=%d\r\n",PLC_TEMP1&0x0FFF,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else if((PLC_TEMP1&0x0FFF)>=0x0400 && (PLC_TEMP1&0x0FFF)<=0x04FF)
			{debug_send("ORI X%o=%d\r\n",PLC_TEMP1&0x0FFF-0x400,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0500 && (PLC_TEMP1&0x0FFF)<=0x05FF)
			{debug_send("ORI Y%o=%d\r\n",PLC_TEMP1&0x0FFF-0x500,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0600 && (PLC_TEMP1&0x0FFF)<=0x07FF)
			{debug_send("ORI T%d=%d\r\n",PLC_TEMP1&0x0FFF-0x600,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0800 && (PLC_TEMP1&0x0FFF)<=0x0DFF)
			{debug_send("ORI M%d=%d\r\n",PLC_TEMP1&0x0FFF-0x800,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0E00   && (PLC_TEMP1&0x0FFF)<=0x0EFF)
			{debug_send("ORI C%d=%d\r\n",PLC_TEMP1&0x0FFF-0xE00,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0F00 && (PLC_TEMP1&0x0FFF)<=0x0FFF)
			{debug_send("ORI M8%03d=%d\r\n",PLC_TEMP1&0x0FFF-0xF00,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
#endif	 
}

void out_y_m(void)	//0xC000
{
	if(PLC_ACC_BIT & 0x01)
	{
		PLC_BIT_ON(PLC_TEMP1&0x0FFF);
	}
 	else
	{
		PLC_BIT_OFF(PLC_TEMP1&0x0FFF);
	}
 	PLC_PC+=2;
	#ifdef	debug
	if((PLC_TEMP1&0x0FFF)>=0x0500 && (PLC_TEMP1&0x0FFF)<=0x05FF)
		{debug_send("OUT Y%o=%d\r\n",PLC_TEMP1&0x0FFF-0x500,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	else  if((PLC_TEMP1&0x0FFF)>=0x0800 && (PLC_TEMP1&0x0FFF)<=0x0DFF)
			{debug_send("OUT M%d=%d\r\n",PLC_TEMP1&0x0FFF-0x800,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	#endif	 
}

void set_y_m(void)	//0xD000
{
	if(PLC_ACC_BIT & 0x01)
	{
		PLC_BIT_ON(PLC_TEMP1&0x0FFF);
	}
	PLC_PC+=2;
	#ifdef debug
	if((PLC_TEMP1&0x0FFF)>=0x500 && (PLC_TEMP1&0x0FFF)<=0x5FF)
		{debug_send("SET Y%o=%d\r\n",PLC_TEMP1&0x0FFF-0x500,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	if((PLC_TEMP1&0x0FFF)>=0x800 &&(PLC_TEMP1&0x0FFF)<=0xDFF)
		{debug_send("SET M%d=%d\r\n",PLC_TEMP1&0x0FFF-0x800,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	#endif				 	
}

void rst_y_m(void)		//0xE000
{
	if(PLC_ACC_BIT & 0x01)
	{
		PLC_BIT_OFF(PLC_TEMP1&0x0FFF);
	}
	 PLC_PC+=2;
	#ifdef debug
	if((PLC_TEMP1&0x0FFF)>=0x500 && (PLC_TEMP1&0x0FFF)<=0x5FF)
		{debug_send("RST Y%o=%d\r\n",PLC_TEMP1&0x0FFF-0x500,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	if((PLC_TEMP1&0x0FFF)>=0x800 &&(PLC_TEMP1&0x0FFF)<=0xDFF)
		{debug_send("RST M%d=%d\r\n",PLC_TEMP1&0x0FFF-0x800,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));}
	#endif						 
}

void stl(void)		//
{
	uint32  tem;
	if((PLC_TEMP1&0x0fff)>0x03ff)
	{
		PLC_PROG_ERROR(1916);
	}	
 	else
	{
		 PLC_PC+=2;
		if(PLC_BIT_TEST(PLC_TEMP1&0x0FFF))
		{
			PLC_STL_CMD = 1;//执行
			PLC_ACC_BIT |= 0x01;
			PLC_RUN_BIT = 4;
			if(PLC_STL_ADD != (PLC_TEMP1&0x0FFF))
			{
				if((PLC_STL_ADD != 0x03ff) && (PLC_STL_PC != (PLC_PC-2)))
				{
					tem=PLC_PC-2;
					PLC_PC=PLC_STL_PC+2;
					PLC_STL_PC=tem;
					PLC_ACC_BIT &= 0xFE;
				}
				else
					PLC_STL_PC=PLC_PC-2;
				PLC_BIT_OFF(PLC_STL_ADD);
			}
			else
				PLC_BIT_ON(PLC_STL_ADD);
			PLC_STL_ADD=PLC_TEMP1&0x0FFF;
		}
		else if((PLC_O2_BIT_TEST(PLC_TEMP1&0x0FFF)==0) && PLC_O_BIT_TEST(PLC_TEMP1&0x0FFF))
		{
			PLC_RUN_BIT=4;
			PLC_ACC_BIT &= 0xFE;
			PLC_STL_CMD=1;		//复原
		}
		else
		{
			PLC_RUN_BIT=4;
			PLC_STL_CMD=2;//跳转
		}
	}//END else
	debug_send("STL S%d=%d\r\n",PLC_TEMP1&0x0fff,PLC_BIT_TEST(PLC_TEMP1&0x0FFF));
}

void out(void)	//0x0600
{
	if(PLC_ACC_BIT & 0x01)
	{
		PLC_T_C_BIT_ON(PLC_TEMP1&0x00ff);
		if(PLC_T_RST_TEST(PLC_TEMP1&0x00ff)==0)
		{
			if(PLC_RAM16(PLC_T_START_ADD+((PLC_TEMP1&0x00FF)*2))>=PLC_ByteRead16(PLC_PC+2))//测试量与计数值是否一致
		  	{
		  		PLC_T_OUT_BIT_ON(PLC_TEMP1&0x00ff);
			}
		    	else 
			{
				PLC_T_OUT_BIT_OFF(PLC_TEMP1&0x00ff);
			}
		  }//END 
	}//END PLC_ACC_BIT
	else 
	{
		PLC_T_C_BIT_OFF(PLC_TEMP1&0x00ff);
		PLC_T_OUT_BIT_OFF(PLC_TEMP1&0x00ff);
		PLC_RAM16(PLC_T_START_ADD+((PLC_TEMP1&0x00FF)*2))=0;
	}//清除计时
	debug_send("OUT T%d;PLC_T_C_BIT=%d;PLC_T_RST=%d;PLC_T_OUT_BIT=%d;PLC_T_RAM=%d;\r\n",PLC_TEMP1&0x00ff,PLC_T_C_BIT_TEST(PLC_TEMP1&0x00ff),PLC_T_RST_TEST(PLC_TEMP1&0x00ff),PLC_T_OUT_BIT_TEST(PLC_TEMP1&0x00ff),PLC_RAM16(PLC_T_START_ADD+((PLC_TEMP1&0x00FF)*2)));
	PLC_PC += 6;
}

void out_c(void)	//0x0E00
{
	if((PLC_TEMP1&0x00FF)<200) 		 
	{
	   	if(PLC_ACC_BIT & 0x01)
		{
			if(PLC_C_C_BIT_TEST(PLC_TEMP1&0x00FF)==0)  
			{
				PLC_C_C_BIT_ON(PLC_TEMP1&0x00FF);		 
				if(PLC_C_RST_TEST(PLC_TEMP1&0x00FF)==0)
				{
					PLC_RAM16(PLC_C16_START_ADD+((PLC_TEMP1&0x00FF)*2))+=1;//加1
		       		if(PLC_RAM16(PLC_C16_START_ADD+((PLC_TEMP1&0x00FF)*2))>=PLC_ByteRead16(PLC_PC+2))//测试量与计数值是否一致
		          		{
		          			PLC_C_OUT_BIT_ON(PLC_TEMP1&0x00FF);
					}
	            			else 
					{
						PLC_C_OUT_BIT_OFF(PLC_TEMP1&0x00FF);
					}
			 	}//END
			}//END
		}//END PLC_ACC_BIT
		else
		{
			PLC_C_C_BIT_OFF(PLC_TEMP1&0x00FF);
		}
		debug_send("OUT C%d;PLC_C_C_BIT=%d;PLC_C_RST=%d;PLC_C_OUT_BIT=%d;PLC_C_RAM=%d;\r\n",PLC_TEMP1&0x00ff,PLC_C_C_BIT_TEST(PLC_TEMP1&0x00ff),PLC_C_RST_TEST(PLC_TEMP1&0x00ff),PLC_C_OUT_BIT_TEST(PLC_TEMP1&0x00ff),PLC_RAM16(PLC_C16_START_ADD+((PLC_TEMP1&0x00FF)*2)));				   								     
		PLC_PC += 6;
	}	 				   
	else
	{//C200-C255
		debug_send("OUT C%d;PLC_C_C_BIT=%d;PLC_C_RST=%d;PLC_C_OUT_BIT=%d;PLC_C_RAM=%d;\r\n",PLC_TEMP1&0x00ff,PLC_C_C_BIT_TEST(PLC_TEMP1&0x00ff),PLC_C_RST_TEST(PLC_TEMP1&0x00ff),PLC_C_OUT_BIT_TEST(PLC_TEMP1&0x00ff),PLC_RAM16(PLC_C32_START_ADD+((PLC_TEMP1&0x00FF)*4)));				   								     							
		PLC_PC += 10;
	} 
}
