/*******************************PLC_CONF.H****************************************
*LuHeDing
*2010年05月08日
*V1.0
*
******************************************************************************/
#ifndef  PLC_CONF_H
#define  PLC_CONF_H
#include "plc_app.H"

//PLC_R_START_ADD+0x0080~0x009c	X0~X377(八进制)
//PLC_R_START_ADD+0x0500~0x051c	Y0~Y377(八进制)
//PLC_R_START_ADD+0x0E00~0x0E1c	D8000~D8225

#define PD8000       (u32)(PLC_R_START_ADD+0x00000E00)
/*************D8000-D8255****************/     
#define D8000   (*(u16*)(u32)(PD8000))			//监控定时器;监控定时器设定值 200(43 38 30 30)			
#define D8001   (*(u16*)(u32)(PD8000+2))		//PLC型号和系统版本;PLC型号和系统版本情报(46 36 35 45)
#define D8002   (*(u16*)(u32)(PD8000+4))		//内存容量;(30 38 30 30)
#define D8003   (*(u16*)(u32)(PD8000+6))		//内存类型(31 30 30 30)
#define D8004   (*(u16*)(u32)(PD8000+8))		//错误M号码(30 30 30 30)
#define D8005   (*(u16*)(u32)(PD8000+10))		//电池电压值(32 24 00 00)
#define D8006   (*(u16*)(u32)(PD8000+12))		//电池电压降低的检测标准;电池电压降低的检测标准值(31 45 00 00)
#define D8007   (*(u16*)(u32)(PD8000+14))		//瞬时停止检测次数(30 30 30 30)
#define D8008   (*(u16*)(u32)(PD8000+16))		//停电检测时间(00 41 00 00)
#define D8009   (*(u16*)(u32)(PD8000+18))		//24V DC故障模块号码(30 30 30 30)
#define D8010   (*(u16*)(u32)(PD8000+20))		//当前扫描值(30 37 00 00)
#define D8011   (*(u16*)(u32)(PD8000+22))		//扫描时间的最小值(31 36 00 00)
#define D8012   (*(u16*)(u32)(PD8000+24))		//最大扫描时间() (31 36 00 00)
#define D8013   (*(u16*)(u32)(PD8000+26))		//秒设置()
#define D8014   (*(u16*)(u32)(PD8000+28))		//分设置
#define D8015   (*(u16*)(u32)(PD8000+30))		//小时设置
#define D8016   (*(u16*)(u32)(PD8000+32))		//日设置
#define D8017   (*(u16*)(u32)(PD8000+34))		//月设置
#define D8018   (*(u16*)(u32)(PD8000+36))		//年设置
#define D8019   (*(u16*)(u32)(PD8000+38))		//星期设置
#define D8020   (*(u16*)(u32)(PD8000+40))		//X000至X007输入滤波设定值(00 41 00 00)
#define D8021   (*(u16*)(u32)(PD8000+42))		//X010至X017输入滤波设定值(00 00 00 00)
#define D8022   (*(u16*)(u32)(PD8000+44))		//30 30 30 30
#define D8023   (*(u16*)(u32)(PD8000+46))		//30 30 30 30
#define D8024   (*(u16*)(u32)(PD8000+48))		//30 30 30 30
#define D8025   (*(u16*)(u32)(PD8000+50))		//30 30 30 30
#define D8026   (*(u16*)(u32)(PD8000+52))		//30 30 30 30
#define D8027   (*(u16*)(u32)(PD8000+54))		//30 30 30 30
#define D8028   (*(u16*)(u32)(PD8000+56))		//Z(Z0) 寄存器内容(30 30 30 30)
#define D8029   (*(u16*)(u32)(PD8000+58))		//V(V0) 寄存器内容(30 30 30 30)
#define D8030   (*(u16*)(u32)(PD8000+60))		//No1 模拟容量值的内容(34 44 00 00)
#define D8031   (*(u16*)(u32)(PD8000+62))		//No2 模拟容量值的内容(31 43 00 00)
#define D8032   (*(u16*)(u32)(PD8000+64))		//30 30 30 30
#define D8033   (*(u16*)(u32)(PD8000+66))		//30 30 30 30
#define D8034   (*(u16*)(u32)(PD8000+68))		//31 34 30 30
#define D8035   (*(u16*)(u32)(PD8000+70))		//46 46 30 30
#define D8036   (*(u16*)(u32)(PD8000+72))		//44 37 30 33
#define D8037   (*(u16*)(u32)(PD8000+74))		//30 30 30 30
#define D8038   (*(u16*)(u32)(PD8000+76))		//30 30 30 30
#define D8039   (*(u16*)(u32)(PD8000+78))		//恒定扫描时间(30 30 30 30)
#define D8040   (*(u16*)(u32)(PD8000+80))		//第1个活动STL状态号(46 46 46 46)
#define D8041   (*(u16*)(u32)(PD8000+82))		//第2个活动STL状态号(46 46 46 46)
#define D8042   (*(u16*)(u32)(PD8000+84))		//第3个活动STL状态号(46 46 46 46)
#define D8043   (*(u16*)(u32)(PD8000+86))		//第4个活动STL状态号(46 46 46 46)
#define D8044   (*(u16*)(u32)(PD8000+88))		//第5个活动STL状态号(46 46 46 46)
#define D8045   (*(u16*)(u32)(PD8000+90))		//第6个活动STL状态号(46 46 46 46)
#define D8046   (*(u16*)(u32)(PD8000+92))		//第7个活动STL状态号(46 46 46 46)
#define D8047   (*(u16*)(u32)(PD8000+94))		//第8个活动STL状态号(46 46 46 46)
#define D8048   (*(u16*)(u32)(PD8000+96))		//30 30 30 30
#define D8049   (*(u16*)(u32)(PD8000+98))		//最小的活动状态(46 46 46 46)
#define D8050   (*(u16*)(u32)(PD8000+100))		//30 30 30 30
#define D8051   (*(u16*)(u32)(PD8000+102))		//30 30 30 30
#define D8052   (*(u16*)(u32)(PD8000+104))		//30 30 30 30
#define D8053   (*(u16*)(u32)(PD8000+106))		//30 30 30 30
#define D8054   (*(u16*)(u32)(PD8000+108))		//30 30 30 30
#define D8055   (*(u16*)(u32)(PD8000+110))		//30 30 30 30
#define D8056   (*(u16*)(u32)(PD8000+112))		//30 30 30 30
#define D8057   (*(u16*)(u32)(PD8000+114))		//30 30 30 30
#define D8058   (*(u16*)(u32)(PD8000+116))		//30 30 30 30
#define D8059   (*(u16*)(u32)(PD8000+118))		//30 30 30 30
#define D8060   (*(u16*)(u32)(PD8000+120))		//I/O配置错误非安装I/O先头号码。(30 30 30 30)
#define D8061   (*(u16*)(u32)(PD8000+122))		//PLC硬件错误的错误代码(30 30 30 30)
#define D8062   (*(u16*)(u32)(PD8000+124))		//PLC/PP通讯错误(30 30 30 30)
#define D8063   (*(u16*)(u32)(PD8000+126))		//串行口通讯错误[Ch1](30 30 30 30)
#define D8064   (*(u16*)(u32)(PD8000+128))		//参数错误的错误代码(30 30 30 30)
#define D8065   (*(u16*)(u32)(PD8000+130))		//如果等于1，出错//语法错误的错误代码(30 30 30 30)
#define D8066   (*(u16*)(u32)(PD8000+132))		//回路错误的错误代码(30 30 30 30)
#define D8067   (*(u16*)(u32)(PD8000+134))		//操作错误的错误代码(30 30 30 30)
#define D8068   (*(u16*)(u32)(PD8000+136))		//操作错误的步号锁存(30 30 30 30)
#define D8069   (*(u16*)(u32)(PD8000+138))		//错误M8065至M8067的步号(30 30 30 30)	
#define D8070   (*(u16*)(u32)(PD8000+140))		//并行链接错误判定时间值46 34 30 31
#define D8071   (*(u16*)(u32)(PD8000+142))		//(30 30 30 30)
#define D8072   (*(u16*)(u32)(PD8000+144))		//(30 30 30 30)
#define D8073   (*(u16*)(u32)(PD8000+146))		//(30 30 30 30)
#define D8074   (*(u16*)(u32)(PD8000+148))		//取样跟踪的剩余取样次数(30 30 30 30)
#define D8075   (*(u16*)(u32)(PD8000+150))		//取样跟踪的取样次数(30 30 30 30)
#define D8076   (*(u16*)(u32)(PD8000+152))		//取样跟踪的取样周期(30 30 30 30)
#define D8077   (*(u16*)(u32)(PD8000+154))		//取样跟踪的触发指定数据(30 30 30 30)
#define D8078   (*(u16*)(u32)(PD8000+156))		//触发条件设备号码设置(30 30 30 30)
#define D8079   (*(u16*)(u32)(PD8000+158))		//取样跟踪的取样数据指针(30 30 30 30)
#define D8080   (*(u16*)(u32)(PD8000+160))		//位设备号码No.0的值(30 30 30 30)
#define D8081   (*(u16*)(u32)(PD8000+162))		//位设备号码No.1的值(30 30 30 30)
#define D8082   (*(u16*)(u32)(PD8000+164))		//位设备号码No.2的值(30 30 30 30)
#define D8083   (*(u16*)(u32)(PD8000+166))		//位设备号码No.3的值(30 30 30 30)
#define D8084   (*(u16*)(u32)(PD8000+168))		//位设备号码No.4的值(30 30 30 30)
#define D8085   (*(u16*)(u32)(PD8000+170))		//位设备号码No.5的值(30 30 30 30)
#define D8086   (*(u16*)(u32)(PD8000+172))		//位设备号码No.6的值(30 30 30 30)
#define D8087   (*(u16*)(u32)(PD8000+174))		//位设备号码No.7的值(30 30 30 30)
#define D8088   (*(u16*)(u32)(PD8000+176))		//位设备号码No.8的值(30 30 30 30)
#define D8089   (*(u16*)(u32)(PD8000+178))		//位设备号码No.9的值(30 30 30 30)
#define D8090   (*(u16*)(u32)(PD8000+180))		//位设备号码No.10的值(30 30 30 30)
#define D8091   (*(u16*)(u32)(PD8000+182))		//位设备号码No.11的值(30 30 30 30)
#define D8092   (*(u16*)(u32)(PD8000+184))		//位设备号码No.12的值(30 30 30 30)
#define D8093   (*(u16*)(u32)(PD8000+186))		//位设备号码No.13的值(30 30 30 30)
#define D8094   (*(u16*)(u32)(PD8000+188))		//位设备号码No.14的值(30 30 30 30)
#define D8095   (*(u16*)(u32)(PD8000+190))		//位设备号码No.15的值(30 30 30 30)
#define D8096   (*(u16*)(u32)(PD8000+192))		//字设备号码No.0的值(30 30 30 30)
#define D8097   (*(u16*)(u32)(PD8000+194))		//字设备号码No.1的值(30 30 30 30)
#define D8098   (*(u16*)(u32)(PD8000+196))		//字设备号码No.2的值(30 30 30 30)
#define D8099   (*(u16*)(u32)(PD8000+198))		//高速循环计数器的设置(30 30 30 30)	
#define D8100   (*(u16*)(u32)(PD8000+200))		//(36 34 30 30)
#define D8101   (*(u16*)(u32)(PD8000+202))		//序列器机种名/版本46 36 35 45
#define D8102   (*(u16*)(u32)(PD8000+204))		//内存容量00 38 00 00
#define D8103   (*(u16*)(u32)(PD8000+206))		//(30 30 30 30)
#define D8104   (*(u16*)(u32)(PD8000+208))		//功能扩展存储固有的种类代码(30 30 30 30)
#define D8105   (*(u16*)(u32)(PD8000+210))		//功能扩展存储器的版本(30 30 30 30)
#define D8106   (*(u16*)(u32)(PD8000+212))		//设备注释登记数(30 30 30 30)
#define D8107   (*(u16*)(u32)(PD8000+214))		//(30 30 30 30)
#define D8108   (*(u16*)(u32)(PD8000+216))		//特殊模块连接台数(30 30 30 30)
#define D8109   (*(u16*)(u32)(PD8000+218))		//输出刷新错误(30 30 30 30)
#define D8110   (*(u16*)(u32)(PD8000+220))		//(30 30 30 30)
#define D8111   (*(u16*)(u32)(PD8000+222))		//(30 30 30 30)
#define D8112   (*(u16*)(u32)(PD8000+224))		//Ch1数字值(FX1N-2AD-BD)(30 30 30 30)
#define D8113   (*(u16*)(u32)(PD8000+226))		//Ch2数字值(FX1N-2AD-BD)(30 30 30 30)
#define D8114   (*(u16*)(u32)(PD8000+228))		//Ch1数字值(FX1N-1AD-BD)(30 30 30 30)
#define D8115   (*(u16*)(u32)(PD8000+230))		//(30 30 30 30)
#define D8116   (*(u16*)(u32)(PD8000+232))		//35 34 45 35//39 39 43 31 							**需验证
#define D8117   (*(u16*)(u32)(PD8000+234))		//42 45 36 32//45 34 30 45							**需验证
#define D8118   (*(u16*)(u32)(PD8000+236))		//(30 30 30 30)
#define D8119   (*(u16*)(u32)(PD8000+238))		//(30 30 30 30)
#define D8120   (*(u16*)(u32)(PD8000+240))		//FNC 80(RS) 计算机链接[Ch1]通讯格式设置(30 30 30 30)
#define D8121   (*(u16*)(u32)(PD8000+242))		//计算机连接[Ch1]本地站号设置(30 30 30 30)
#define D8122   (*(u16*)(u32)(PD8000+244))		//FNC 80(RS)发送数据的残余量(30 30 30 30)
#define D8123   (*(u16*)(u32)(PD8000+246))		//FNC 80(RS)收信份数监视器(30 30 30 30)
#define D8124   (*(u16*)(u32)(PD8000+248))		//FNC 80(RS)标题30 32 30 30
#define D8125   (*(u16*)(u32)(PD8000+250))		//FNC 80(RS)终端30 33 30 30
#define D8126   (*(u16*)(u32)(PD8000+252))		//(30 30 30 30)
#define D8127   (*(u16*)(u32)(PD8000+254))		//计算机链接[Ch1]根据需求先头号码指定(30 30 30 30)
#define D8128   (*(u16*)(u32)(PD8000+256))		//计算机链接[Ch1]根据需求数据量指定
#define D8129   (*(u16*)(u32)(PD8000+258))		//FNC 80(RS) 计算机链接[Ch1]超时设置
#define D8130   (*(u16*)(u32)(PD8000+260))		//FNC55(HSZ)命令高速对照表计数器
#define D8131   (*(u16*)(u32)(PD8000+262))		//FNC55(HSZ), FNC57(PLSY)命令速度模式表计数器
#define D8132   (*(u16*)(u32)(PD8000+264))		//NC55(HSZ), FNC57(PLSY)命令速度模式频率(下位)
#define D8133   (*(u16*)(u32)(PD8000+266))		//FNC55(HSZ), FNC57(PLSY)命令速度模式频率(上位)
#define D8134   (*(u16*)(u32)(PD8000+268))		//FNC55(HSZ), FNC57(PLSY) 命令速度模式目标脉冲数(下位)
#define D8135   (*(u16*)(u32)(PD8000+270))		//FNC55(HSZ), FNC57(PLSY) 命令速度模式目标脉冲数(上位)
#define D8136   (*(u16*)(u32)(PD8000+272))		//FNC57(PLSY),FNC59(PLSR) 命令输出脉冲数的累计(下位)
#define D8137   (*(u16*)(u32)(PD8000+274))		//FNC57(PLSY),FNC59(PLSR) 命令输出脉冲数的累计(上位)
#define D8138   (*(u16*)(u32)(PD8000+276))		//FNC280(HSCT)指令表计数器
#define D8139   (*(u16*)(u32)(PD8000+278))		//(FNC53～55,280)执行中指令数
#define D8140   (*(u16*)(u32)(PD8000+280))		//FNC57(PLSY),FNC59(PLSR)至Y000 的输出脉冲数的累计(下位)	
#define D8141   (*(u16*)(u32)(PD8000+282))		//FNC57(PLSY),FNC59(PLSR)至Y000 的输出脉冲数的累计(上位)
#define D8142   (*(u16*)(u32)(PD8000+284))		//FNC57(PLSY),FNC59(PLSR)至Y001 的输出脉冲数的累计(下位)
#define D8143   (*(u16*)(u32)(PD8000+286))		//FNC57(PLSY),FNC59(PLSR)至Y001 的输出脉冲数的累计(上位)
#define D8144   (*(u16*)(u32)(PD8000+288))		//
#define D8145   (*(u16*)(u32)(PD8000+290))		//FNC156(ZRN),FNC158(DRVI),FNC159(DRVA)执行时的偏压速度
#define D8146   (*(u16*)(u32)(PD8000+292))		//FNC156(ZRN),FNC158(DRVI),FNC159(DRVA)执行时的最高速度(下位)
#define D8147   (*(u16*)(u32)(PD8000+294))		//FNC156(ZRN),FNC158(DRVI),FNC159(DRVA)执行时的最高速度(上位)
#define D8148   (*(u16*)(u32)(PD8000+296))		//FNC156(ZRN),FNC158(DRVI),FNC159(DRVA)执行时的加减速时间
#define D8149   (*(u16*)(u32)(PD8000+298))		//
#define D8150   (*(u16*)(u32)(PD8000+300))		//交换通讯的应答等待时间[Ch1]
#define D8151   (*(u16*)(u32)(PD8000+302))		//交换通讯中的步号码[Ch1]
#define D8152   (*(u16*)(u32)(PD8000+304))		//交换通讯的错误代码[Ch1]
#define D8153   (*(u16*)(u32)(PD8000+306))		//交换通讯的错误发生步插梢[Ch1]
#define D8154   (*(u16*)(u32)(PD8000+308))		//在FNC274(IVBWR)指令发生了错误的参数号码[Ch1]FNC180(EXTR)指令的应答等待时间
#define D8155   (*(u16*)(u32)(PD8000+310))		//交换通讯的应答等待时间[Ch2]/FNC180(EXTR)指令的通讯中的步号码
#define D8156   (*(u16*)(u32)(PD8000+312))		//交换通讯的通讯中的步号码[Ch2]/FNC180(EXTR)指令的错误代码
#define D8157   (*(u16*)(u32)(PD8000+314))		//交换通讯的错误代码[Ch2]/FNC180(EXTR)指令的错误发生步号码锁存
#define D8158   (*(u16*)(u32)(PD8000+316))		//交换通讯的错误发生步插梢[Ch2]/FX1N-5DM用控制设备(D)
#define D8159   (*(u16*)(u32)(PD8000+318))		//在FNC274(IVBWR)指令发生了错误的参数号码[Ch2]/FX1N-5DM用控制设备(M)
#define D8160   (*(u16*)(u32)(PD8000+320))		//
#define D8161   (*(u16*)(u32)(PD8000+322))		//
#define D8162   (*(u16*)(u32)(PD8000+324))		//
#define D8163   (*(u16*)(u32)(PD8000+326))		//
#define D8164   (*(u16*)(u32)(PD8000+328))		//FNC78(FROM),FNC79(TO)命令传送号指定
#define D8165   (*(u16*)(u32)(PD8000+330))		//
#define D8166   (*(u16*)(u32)(PD8000+332))		//
#define D8167   (*(u16*)(u32)(PD8000+334))		//
#define D8168   (*(u16*)(u32)(PD8000+336))		//
#define D8169   (*(u16*)(u32)(PD8000+338))		//新密码的设置状态
#define D8170   (*(u16*)(u32)(PD8000+340))		//
#define D8171   (*(u16*)(u32)(PD8000+342))		//
#define D8172   (*(u16*)(u32)(PD8000+344))		//
#define D8173   (*(u16*)(u32)(PD8000+346))		//站号设置状态
#define D8174   (*(u16*)(u32)(PD8000+348))		//从站设置状态
#define D8175   (*(u16*)(u32)(PD8000+350))		//刷新范围设置状态
#define D8176   (*(u16*)(u32)(PD8000+352))		//站号设置状态
#define D8177   (*(u16*)(u32)(PD8000+354))		//从站数设置
#define D8178   (*(u16*)(u32)(PD8000+356))		//刷新范围设置
#define D8179   (*(u16*)(u32)(PD8000+358))		//重试次数
#define D8180   (*(u16*)(u32)(PD8000+360))		//监视时间
#define D8181   (*(u16*)(u32)(PD8000+362))		//
#define D8182   (*(u16*)(u32)(PD8000+364))		//Z1 寄存器的内容
#define D8183   (*(u16*)(u32)(PD8000+366))		//V1 寄存器的内容
#define D8184   (*(u16*)(u32)(PD8000+368))		//Z2 寄存器的内容
#define D8185   (*(u16*)(u32)(PD8000+370))		//V2 寄存器的内容
#define D8186   (*(u16*)(u32)(PD8000+372))		//Z3 寄存器的内容
#define D8187   (*(u16*)(u32)(PD8000+374))		//V3 寄存器的内容
#define D8188   (*(u16*)(u32)(PD8000+376))		//Z4 寄存器的内容
#define D8189   (*(u16*)(u32)(PD8000+378))		//V4 寄存器的内容
#define D8190   (*(u16*)(u32)(PD8000+380))		//Z5 寄存器的内容
#define D8191   (*(u16*)(u32)(PD8000+382))		//V5 寄存器的内容
#define D8192   (*(u16*)(u32)(PD8000+384))		//Z6 寄存器的内容
#define D8193   (*(u16*)(u32)(PD8000+386))		//V6 寄存器的内容
#define D8194   (*(u16*)(u32)(PD8000+388))		//Z7 寄存器的内容
#define D8195   (*(u16*)(u32)(PD8000+390))		//V7 寄存器的内容
#define D8196   (*(u16*)(u32)(PD8000+392))		//
#define D8197   (*(u16*)(u32)(PD8000+394))		//
#define D8198   (*(u16*)(u32)(PD8000+396))		//
#define D8199   (*(u16*)(u32)(PD8000+398))		//
#define D8200   (*(u16*)(u32)(PD8000+400))		//
#define D8201   (*(u16*)(u32)(PD8000+402))		//当前链接扫描时间
#define D8202   (*(u16*)(u32)(PD8000+404))		//最大链接扫描时间
#define D8203   (*(u16*)(u32)(PD8000+406))		//数据传送顺序错误计数(主站)
#define D8204   (*(u16*)(u32)(PD8000+408))		//数据传送顺序错误计数(站号1)
#define D8205   (*(u16*)(u32)(PD8000+410))		//数据传送顺序错误计数(站号2)
#define D8206   (*(u16*)(u32)(PD8000+412))		//数据传送顺序错误计数(站号3)
#define D8207   (*(u16*)(u32)(PD8000+414))		//数据传送顺序错误计数(站号4)
#define D8208   (*(u16*)(u32)(PD8000+416))		//数据传送顺序错误计数(站号5)
#define D8209   (*(u16*)(u32)(PD8000+418))		//数据传送顺序错误计数(站号6)
#define D8210   (*(u16*)(u32)(PD8000+420))		//数据传送顺序错误计数(站号7)
#define D8211   (*(u16*)(u32)(PD8000+422))		//数据传送错误代号(主站)
#define D8212   (*(u16*)(u32)(PD8000+424))		//数据传送错误代号(站号1)
#define D8213   (*(u16*)(u32)(PD8000+426))		//数据传送错误代号(站号2)
#define D8214   (*(u16*)(u32)(PD8000+428))		//数据传送错误代号(站号3)
#define D8215   (*(u16*)(u32)(PD8000+430))		//数据传送错误代号(站号4)
#define D8216   (*(u16*)(u32)(PD8000+432))		//数据传送错误代号(站号5)
#define D8217   (*(u16*)(u32)(PD8000+434))		//数据传送错误代号(站号6)
#define D8218   (*(u16*)(u32)(PD8000+436))		//数据传送错误代号(站号7)
#define D8219   (*(u16*)(u32)(PD8000+438))		//
#define D8220   (*(u16*)(u32)(PD8000+440))		//
#define D8221   (*(u16*)(u32)(PD8000+442))		//
#define D8222   (*(u16*)(u32)(PD8000+444))		//
#define D8223   (*(u16*)(u32)(PD8000+446))		//
#define D8224   (*(u16*)(u32)(PD8000+448))		//
#define D8225   (*(u16*)(u32)(PD8000+450))		//
#define D8226   (*(u16*)(u32)(PD8000+452))		//
#define D8227   (*(u16*)(u32)(PD8000+454))		//
#define D8228   (*(u16*)(u32)(PD8000+456))		//
#define D8229   (*(u16*)(u32)(PD8000+458))		//
#define D8230   (*(u16*)(u32)(PD8000+460))		//
#define D8231   (*(u16*)(u32)(PD8000+462))		//
#define D8232   (*(u16*)(u32)(PD8000+464))		//
#define D8233   (*(u16*)(u32)(PD8000+466))		//
#define D8234   (*(u16*)(u32)(PD8000+468))		//
#define D8235   (*(u16*)(u32)(PD8000+470))		//
#define D8236   (*(u16*)(u32)(PD8000+472))		//
#define D8237   (*(u16*)(u32)(PD8000+474))		//
#define D8238   (*(u16*)(u32)(PD8000+476))		//
#define D8239   (*(u16*)(u32)(PD8000+478))		//
#define D8240   (*(u16*)(u32)(PD8000+480))		//
#define D8241   (*(u16*)(u32)(PD8000+482))		//
#define D8242   (*(u16*)(u32)(PD8000+484))		//
#define D8243   (*(u16*)(u32)(PD8000+486))		//
#define D8244   (*(u16*)(u32)(PD8000+488))		//
#define D8245   (*(u16*)(u32)(PD8000+490))		//
#define D8246   (*(u16*)(u32)(PD8000+492))		//
#define D8247   (*(u16*)(u32)(PD8000+494))		//
#define D8248   (*(u16*)(u32)(PD8000+496))		//
#define D8249   (*(u16*)(u32)(PD8000+498))		//
#define D8250   (*(u16*)(u32)(PD8000+500))		//
#define D8251   (*(u16*)(u32)(PD8000+502))		//
#define D8252   (*(u16*)(u32)(PD8000+504))		//
#define D8253   (*(u16*)(u32)(PD8000+506))		//
#define D8254   (*(u16*)(u32)(PD8000+508))		//
#define D8255   (*(u16*)(u32)(PD8000+510))		//

#define D8140_1	(*(u32*)(u32)(PD8000+280))
#define D8142_3	(*(u32*)(u32)(PD8000+284))
/*************M8000-M8255****************/     
#define 	M8000  	0x0F00+0					//RUN监视a触点
#define 	M8001	0x0F00+1					//RUN监视b触点
#define 	M8002	0x0F00+2					//初始化脉冲a触点
#define 	M8003	0x0F00+3					//初始化脉冲b触点
#define 	M8004	0x0F00+4					//错误发生
#define 	M8005	0x0F00+5					//电池电压降低
#define 	M8006	0x0F00+6					//电池电压降低锁存
#define 	M8007	0x0F00+7					//瞬时停止检测
#define 	M8008	0x0F00+8					//停电检测
#define 	M8009	0x0F00+9					//DC24V故障
#define 	M8010	0x0F00+10					//
#define 	M8011	0x0F00+11					//10 毫秒时钟脉冲
#define 	M8012	0x0F00+12					//100 毫秒时钟脉冲
#define 	M8013	0x0F00+13					//  1  秒时钟脉冲
#define 	M8014	0x0F00+14					//  1 分时钟脉冲
#define 	M8015	0x0F00+15					//内存实时脉冲；计时停止及预置
#define 	M8016	0x0F00+16					//内存实时脉冲；时间读出时显示停止
#define 	M8017	0x0F00+17					//内存实时脉冲；+-30秒的修正
#define 	M8018	0x0F00+18					//内存实时脉冲；检测RTC盒是否插入
#define 	M8019	0x0F00+19					//内存实时脉冲；实时时钟(RTC)出错
#define 	M8020	0x0F00+20					//零位标志
#define 	M8021	0x0F00+21					//借位标志
#define 	M8022	0x0F00+22					//进位标志
#define 	M8023	0x0F00+23					//小数点演算标志
#define 	M8024	0x0F00+24					//BMOV方向指定
#define 	M8025	0x0F00+25					//HSC模式
#define 	M8026	0x0F00+26					//RAMP模式
#define 	M8027	0x0F00+27					//PR模式
#define 	M8028	0x0F00+28					//FROM/TO指令执行中断许可
#define 	M8029	0x0F00+29					//指令执行结束
#define 	M8030	0x0F00+30					//电池LED消灯指令
#define 	M8031	0x0F00+31					//非锁存内存全部清除
#define 	M8032	0x0F00+32					//锁存内存全部清除
#define 	M8033	0x0F00+33					//内存保持停止
#define 	M8034	0x0F00+34					//所有输出禁止
#define 	M8035	0x0F00+35					//强制RUN模式
#define 	M8036	0x0F00+36					//强制RUN指令
#define 	M8037	0x0F00+37					//强制STOP指令
#define 	M8038	0x0F00+38					//参数设置
#define 	M8039	0x0F00+39					//恒定扫描模式
#define 	M8040	0x0F00+40					//STL传送禁止
#define 	M8041	0x0F00+41					//传送开始
#define 	M8042	0x0F00+42					//开始脉冲
#define 	M8043	0x0F00+43					//零点回归完成
#define 	M8044	0x0F00+44					//原点条件
#define 	M8045	0x0F00+45					//所有输出复位禁止
#define 	M8046	0x0F00+46					//STL状态动作
#define 	M8047	0x0F00+47					//STL监视有效
#define 	M8048	0x0F00+48					//报警器ON
#define 	M8049	0x0F00+49					//允许报警器监视
#define 	M8050	0x0F00+50					//I00□ 禁止
#define 	M8051	0x0F00+51					//I10□ 禁止
#define 	M8052	0x0F00+52					//I20□ 禁止
#define 	M8053	0x0F00+53					//I30□ 禁止
#define 	M8054	0x0F00+54					//I40□ 禁止
#define 	M8055	0x0F00+55					//I50□ 禁止
#define 	M8056	0x0F00+56					//I60□ 禁止
#define 	M8057	0x0F00+57					//I70□ 禁止
#define 	M8058	0x0F00+58					//I80□ 禁止
#define 	M8059	0x0F00+59					//计数中断禁止
#define 	M8060	0x0F00+60					//I/O配置错误
#define 	M8061	0x0F00+61					//PLC硬件错误
#define 	M8062	0x0F00+62					//PLC/PP通讯错误
#define 	M8063	0x0F00+63					//串行口通讯错误
#define 	M8064	0x0F00+64					//参数错误
#define 	M8065	0x0F00+65					//语法错误
#define 	M8066	0x0F00+66					//回路错误
#define 	M8067	0x0F00+67					//操作错误
#define 	M8068	0x0F00+68					//操作错误锁存
#define 	M8069	0x0F00+69					//I/O总线检查
#define 	M8070	0x0F00+70					//并行链接主站
#define 	M8071	0x0F00+71					//并行链接从站
#define 	M8072	0x0F00+72					//并行链接运行中ON
#define 	M8073	0x0F00+73					//并行链接设置错误
#define 	M8074	0x0F00+74					//RAM文件寄存器使用模式
#define 	M8075	0x0F00+75					//准备开始指令
#define 	M8076	0x0F00+76					//准备结束,执行开始指令
#define 	M8077	0x0F00+77					//执行中监视
#define 	M8078	0x0F00+78					//执行完成监视
#define 	M8079	0x0F00+79					//跟踪次数512以上
#define 	M8080	0x0F00+80					//
#define 	M8081	0x0F00+81					//
#define 	M8082	0x0F00+82					//
#define 	M8083	0x0F00+83					//
#define 	M8084	0x0F00+84					//
#define 	M8085	0x0F00+85					//
#define 	M8086	0x0F00+86					//
#define 	M8087	0x0F00+87					//
#define 	M8088	0x0F00+88					//
#define 	M8089	0x0F00+89					//
#define 	M8090	0x0F00+90					//(FNC194～199)BKCMP指令 块比较信号
#define 	M8091	0x0F00+91					//切换输出文字数
#define 	M8092	0x0F00+92					//
#define 	M8093	0x0F00+93					//
#define 	M8094	0x0F00+94					//
#define 	M8095	0x0F00+95					//
#define 	M8096	0x0F00+96					//
#define 	M8097	0x0F00+97					//
#define 	M8098	0x0F00+98					//
#define 	M8099	0x0F00+99					//高速循环计数器
#define 	M8100	0x0F00+100					//
#define 	M8101	0x0F00+101					//
#define 	M8102	0x0F00+102					//
#define 	M8103	0x0F00+103					//
#define 	M8104	0x0F00+104					//安装机能扩展存储器时ON
#define 	M8105	0x0F00+105					//FLASH ROM加注中
#define 	M8106	0x0F00+106					//
#define 	M8107	0x0F00+107					//设备注释登记确认
#define 	M8108	0x0F00+108					//
#define 	M8109	0x0F00+109					//输出刷新错误
#define 	M8110	0x0F00+110					//
#define 	M8111	0x0F00+111					//
#define 	M8112	0x0F00+112					//BXO输入(FX1N-4EX-BD) Ch1输入模式切换(FX1N-2AD-BD) 输出模式切换(FX1N-1DA-BD)
#define 	M8113	0x0F00+113					//BX1输入(FX1N-4EX-BD) Ch2输入模式切换(FX1N-2AD-BD)
#define 	M8114	0x0F00+114					//BX2输入(FX1N-4EX-BD)
#define 	M8115	0x0F00+115					//BX3输入(FX1N-4EX-BD)
#define 	M8116	0x0F00+116					//BY0输出(FX1N-2EYT-BD)
#define 	M8117	0x0F00+117					//BY1输出(FX1N-2EYT-BD)
#define 	M8118	0x0F00+118					//
#define 	M8119	0x0F00+119					//
#define 	M8120	0x0F00+120					//通讯设置维持用
#define 	M8121	0x0F00+121					//FNC80(RS)送信待机标志
#define 	M8122	0x0F00+122					//FNC80(RS)送信标志
#define 	M8123	0x0F00+123					//FNC80(RS)接收结束标志
#define 	M8124	0x0F00+124					//FNC80(RS)信号检测到标志
#define 	M8125	0x0F00+125					//
#define 	M8126	0x0F00+126					//计算机链接[Ch1]全局ON
#define 	M8127	0x0F00+127					//计算机链接[Ch1]根据需求送信中
#define 	M8128	0x0F00+128					//计算机链接[Ch1]根据需求错误标志
#define 	M8129	0x0F00+129					//计算机链接[Ch1]根据需求字节/位切换
#define 	M8130	0x0F00+130					//FNC55(HSZ)指令对照表模式
#define 	M8131	0x0F00+131					//FNC5(HSZ)指令对照表模式结束标志
#define 	M8132	0x0F00+132					//FNC55(HSZ),FNC57(PLSY)指令速度模式频率
#define 	M8133	0x0F00+133					//FNC55(HSZ),FNC57(PLSY)指令速度模式频率执行结束标志
#define 	M8134	0x0F00+134					//
#define 	M8135	0x0F00+135					//
#define 	M8136	0x0F00+136					//
#define 	M8137	0x0F00+137					//
#define 	M8138	0x0F00+138					//FNC280(HSCT)指令执行结束标志
#define 	M8139	0x0F00+139					//(FNC53～55.280)高速计数器比较指令执行中
#define 	M8140	0x0F00+140					//FNC156(ZRN)CLR信号输出机能有效
#define 	M8141	0x0F00+141					//
#define 	M8142	0x0F00+142					//
#define 	M8143	0x0F00+143					//
#define 	M8144	0x0F00+144					//
#define 	M8145	0x0F00+145					//Y000用脉冲输出停止指令
#define 	M8146	0x0F00+146					//Y001用脉冲输出停止指令
#define 	M8147	0x0F00+147					//Y000用脉冲输出中监视(Busy/Ready)
#define 	M8148	0x0F00+148					//Y001用脉冲输出中监视(Busy/Ready)
#define 	M8149	0x0F00+149					//
#define 	M8150	0x0F00+150					//
#define 	M8151	0x0F00+151					//交换通讯中[Ch1]
#define 	M8152	0x0F00+152					//交换通讯错误[Ch1]
#define 	M8153	0x0F00+153					//交换通讯错误锁存[Ch1]
#define 	M8154	0x0F00+154					//FNC274(IVBWR)指令错误[Ch1] FNC180(EXTR)每个指令都定义
#define 	M8155	0x0F00+155					//用FNC180(EXTR)指令通讯通道使用中
#define 	M8156	0x0F00+156					//交换通讯中[Ch2] FNC180(EXTR)指令通讯错误/参数错误
#define 	M8157	0x0F00+157					//交换通讯错误[Ch2] FNC180(EXTR)指令通讯错误锁存
#define 	M8158	0x0F00+158					//交换通讯错误锁存[Ch2]
#define 	M8159	0x0F00+159					//FNC274(IVBWR)指令错误[Ch2]
#define 	M8160	0x0F00+160					//FNC17(XCH)的SWAP功能
#define 	M8161	0x0F00+161					//8位处理模式
#define 	M8162	0x0F00+162					//高速并行链接模式
#define 	M8163	0x0F00+163					//
#define 	M8164	0x0F00+164					//FNC78(FROM),FNC79(TO)指令转送点数可变模式
#define 	M8165	0x0F00+165					//FNC149(SORT2)指令源顺序
#define 	M8166	0x0F00+166					//
#define 	M8167	0x0F00+167					//FNC71(HKY)指令HEX数据处理功能
#define 	M8168	0x0F00+168					//FNC13(SMOV)指令HEX数据处理功能
#define 	M8169	0x0F00+169					//
#define 	M8170	0x0F00+170					//输入X000脉冲插入
#define 	M8171	0x0F00+171					//输入X001脉冲插入
#define 	M8172	0x0F00+172					//输入X002脉冲插入
#define 	M8173	0x0F00+173					//输入X003脉冲插入
#define 	M8174	0x0F00+174					//输入X004脉冲插入
#define 	M8175	0x0F00+175					//输入X005脉冲插入
#define 	M8176	0x0F00+176					//输入X006脉冲插入
#define 	M8177	0x0F00+177					//输入X007脉冲插入
#define 	M8178	0x0F00+178					//并列链接切换频道
#define 	M8179	0x0F00+179					//简易PLC间链接切换频道
#define 	M8180	0x0F00+180					//
#define 	M8181	0x0F00+181					//
#define 	M8182	0x0F00+182					//
#define 	M8183	0x0F00+183					//数据传送顺序错误(主站)
#define 	M8184	0x0F00+184					//数据传送顺序错误(1号站)
#define 	M8185	0x0F00+185					//数据传送顺序错误(2号站)
#define 	M8186	0x0F00+186					//数据传送顺序错误(3号站)
#define 	M8187	0x0F00+187					//数据传送顺序错误(4号站)
#define 	M8188	0x0F00+188					//数据传送顺序错误(5号站)
#define 	M8189	0x0F00+189					//数据传送顺序错误(6号站)
#define 	M8190	0x0F00+190					//数据传送顺序错误(7号站)
#define 	M8191	0x0F00+191					//数据传送顺序执行中
#define 	M8192	0x0F00+192					//
#define 	M8193	0x0F00+193					//
#define 	M8194	0x0F00+194					//
#define 	M8195	0x0F00+195					//
#define 	M8196	0x0F00+196					//
#define 	M8197	0x0F00+197					//
#define 	M8198	0x0F00+198					//C251,C252,C254 1倍增/4倍增切换
#define 	M8199	0x0F00+199					//C253,C254,C235(H/W) 1倍增/4倍增切换
#define 	M8200	0x0F00+200					//C200加/减计数器方向
#define 	M8201	0x0F00+201					//C201加/减计数器方向
#define 	M8202	0x0F00+202					//C202加/减计数器方向
#define 	M8203	0x0F00+203					//C203加/减计数器方向
#define 	M8204	0x0F00+204					//C204加/减计数器方向
#define 	M8205	0x0F00+205					//C205加/减计数器方向
#define 	M8206	0x0F00+206					//C206加/减计数器方向
#define 	M8207	0x0F00+207					//C207加/减计数器方向
#define 	M8208	0x0F00+208					//C208加/减计数器方向
#define 	M8209	0x0F00+209					//C209加/减计数器方向
#define 	M8210	0x0F00+210					//C210加/减计数器方向
#define 	M8211	0x0F00+211					//C211加/减计数器方向
#define 	M8212	0x0F00+212					//C212加/减计数器方向
#define 	M8213	0x0F00+213					//C213加/减计数器方向
#define 	M8214	0x0F00+214					//C214加/减计数器方向
#define 	M8215	0x0F00+215					//C215加/减计数器方向
#define 	M8216	0x0F00+216					//C216加/减计数器方向
#define 	M8217	0x0F00+217					//C217加/减计数器方向
#define 	M8218	0x0F00+218					//C218加/减计数器方向
#define 	M8219	0x0F00+219					//C219加/减计数器方向
#define 	M8220	0x0F00+220					//C220加/减计数器方向
#define 	M8221	0x0F00+221					//C221加/减计数器方向
#define 	M8222	0x0F00+222					//C222加/减计数器方向
#define 	M8223	0x0F00+223					//C223加/减计数器方向
#define 	M8224	0x0F00+224					//C224加/减计数器方向
#define 	M8225	0x0F00+225					//C225加/减计数器方向
#define 	M8226	0x0F00+226					//C226加/减计数器方向
#define 	M8227	0x0F00+227					//C227加/减计数器方向
#define 	M8228	0x0F00+228					//C228加/减计数器方向
#define 	M8229	0x0F00+229					//C229加/减计数器方向
#define 	M8230	0x0F00+230					//C230加/减计数器方向
#define 	M8231	0x0F00+231					//C231加/减计数器方向
#define 	M8232	0x0F00+232					//C232加/减计数器方向
#define 	M8233	0x0F00+233					//C233加/减计数器方向
#define 	M8234	0x0F00+234					//C234加/减计数器方向
#define 	M8235	0x0F00+235					//C235高速计数器方向
#define 	M8236	0x0F00+236					//C236高速计数器方向
#define 	M8237	0x0F00+237					//C237高速计数器方向
#define 	M8238	0x0F00+238					//C238高速计数器方向
#define 	M8239	0x0F00+239					//C239高速计数器方向
#define 	M8240	0x0F00+240					//C240高速计数器方向
#define 	M8241	0x0F00+241					//C241高速计数器方向
#define 	M8242	0x0F00+242					//C242高速计数器方向
#define 	M8243	0x0F00+243					//C243高速计数器方向
#define 	M8244	0x0F00+244					//C244高速计数器方向
#define 	M8245	0x0F00+245					//C245高速计数器方向
#define 	M8246	0x0F00+246					//C246高速计数监视器
#define 	M8247	0x0F00+247					//C247高速计数监视器
#define 	M8248	0x0F00+248					//C248高速计数监视器
#define 	M8249	0x0F00+249					//C249高速计数监视器
#define 	M8250	0x0F00+250					//C250高速计数监视器
#define 	M8251	0x0F00+251					//C251高速计数监视器
#define 	M8252	0x0F00+252					//C252高速计数监视器
#define 	M8253	0x0F00+253					//C253高速计数监视器
#define 	M8254	0x0F00+254					//C254高速计数监视器
#define 	M8255	0x0F00+255					//C255高速计数监视器

//{Y0L;}	{Y0H;}
//Y0-Y7
#define 	Y0L	
#define 	Y1L	
#define 	Y2L	
#define 	Y3L	
#define 	Y4L	
#define 	Y5L	
#define 	Y6L	
#define 	Y7L	

#define 	Y0H	
#define 	Y1H	
#define 	Y2H	
#define 	Y3H	
#define 	Y4H	
#define 	Y5H	
#define 	Y6H	
#define 	Y7H	

//Y10-Y17
#define 	Y10L	
#define 	Y11L	
#define 	Y12L	
#define 	Y13L	
#define 	Y14L	
#define 	Y15L	
#define 	Y16L	
#define 	Y17L	

#define 	Y10H	
#define 	Y11H	
#define 	Y12H	
#define 	Y13H	
#define 	Y14H	
#define 	Y15H	
#define 	Y16H	
#define 	Y17H	

//Y20-Y27
#define 	Y20L	
#define 	Y21L	
#define 	Y22L	
#define 	Y23L	
#define 	Y24L	
#define 	Y25L	
#define 	Y26L	
#define 	Y27L	

#define 	Y20H	
#define 	Y21H	
#define 	Y22H	
#define 	Y23H	
#define 	Y24H	
#define 	Y25H	
#define 	Y26H	
#define 	Y27H	

//Y30-Y37
#define 	Y30L	
#define 	Y31L	
#define 	Y32L	
#define 	Y33L	
#define 	Y34L	
#define 	Y35L	
#define 	Y36L	
#define 	Y37L	

#define 	Y30H	
#define 	Y31H	
#define 	Y32H	
#define 	Y33H	
#define 	Y34H	
#define 	Y35H	
#define 	Y36H	
#define 	Y37H	

//Y40-Y47
#define 	Y40L	
#define 	Y41L	
#define 	Y42L	
#define 	Y43L	
#define 	Y44L	
#define 	Y45L	
#define 	Y46L	
#define 	Y47L	

#define 	Y40H	
#define 	Y41H	
#define 	Y42H	
#define 	Y43H	
#define 	Y44H	
#define 	Y45H	
#define 	Y46H	
#define 	Y47H	

//Y50-Y57
#define 	Y50L	
#define 	Y51L	
#define 	Y52L	
#define 	Y53L	
#define 	Y54L	
#define 	Y55L	
#define 	Y56L	
#define 	Y57L	

#define 	Y50H	
#define 	Y51H	
#define 	Y52H	
#define 	Y53H	
#define 	Y54H	
#define 	Y55H	
#define 	Y56H	
#define 	Y57H

//Y60-Y67
#define 	Y60L	
#define 	Y61L	
#define 	Y62L	
#define 	Y63L	
#define 	Y64L	
#define 	Y65L	
#define 	Y66L	
#define 	Y67L	

#define 	Y60H	
#define 	Y61H	
#define 	Y62H	
#define 	Y63H	
#define 	Y64H	
#define 	Y65H	
#define 	Y66H	
#define 	Y67H	

//Y70-Y77
#define 	Y70L	
#define 	Y71L	
#define 	Y72L	
#define 	Y73L	
#define 	Y74L	
#define 	Y75L	
#define 	Y76L	
#define 	Y77L	

#define 	Y70H	
#define 	Y71H	
#define 	Y72H	
#define 	Y73H	
#define 	Y74H	
#define 	Y75H	
#define 	Y76H	
#define 	Y77H	

//Y100-Y107
#define 	Y100L	
#define 	Y101L	
#define 	Y102L	
#define 	Y103L	
#define 	Y104L	
#define 	Y105L	
#define 	Y106L	
#define 	Y107L	

#define 	Y100H	
#define 	Y101H	
#define 	Y102H	
#define 	Y103H	
#define 	Y104H	
#define 	Y105H	
#define 	Y106H	
#define 	Y107H	

//Y110-Y117
#define 	Y110L	
#define 	Y111L	
#define 	Y112L	
#define 	Y113L	
#define 	Y114L	
#define 	Y115L	
#define 	Y116L	
#define 	Y117L	

#define 	Y110H	
#define 	Y111H	
#define 	Y112H	
#define 	Y113H	
#define 	Y114H	
#define 	Y115H	
#define 	Y116H	
#define 	Y117H	

//Y120-Y127
#define 	Y120L	
#define 	Y121L	
#define 	Y122L	
#define 	Y123L	
#define 	Y124L	
#define 	Y125L	
#define 	Y126L	
#define 	Y127L	

#define 	Y120H	
#define 	Y121H	
#define 	Y122H	
#define 	Y123H	
#define 	Y124H	
#define 	Y125H	
#define 	Y126H	
#define 	Y127H	

//Y130-Y137
#define 	Y130L	
#define 	Y131L	
#define 	Y132L	
#define 	Y133L	
#define 	Y134L	
#define 	Y135L	
#define 	Y136L	
#define 	Y137L	

#define 	Y130H	
#define 	Y131H	
#define 	Y132H	
#define 	Y133H	
#define 	Y134H	
#define 	Y135H	
#define 	Y136H	
#define 	Y137H	

//Y140-Y147
#define 	Y140L	
#define 	Y141L	
#define 	Y142L	
#define 	Y143L	
#define 	Y144L	
#define 	Y145L	
#define 	Y146L	
#define 	Y147L	

#define 	Y140H	
#define 	Y141H	
#define 	Y142H	
#define 	Y143H	
#define 	Y144H	
#define 	Y145H	
#define 	Y146H	
#define 	Y147H	

//Y150-Y157
#define 	Y150L	
#define 	Y151L	
#define 	Y152L	
#define 	Y153L	
#define 	Y154L	
#define 	Y155L	
#define 	Y156L	
#define 	Y157L	

#define 	Y150H	
#define 	Y151H	
#define 	Y152H	
#define 	Y153H	
#define 	Y154H	
#define 	Y155H	
#define 	Y156H	
#define 	Y157H	

//Y160-Y167
#define 	Y160L	
#define 	Y161L	
#define 	Y162L	
#define 	Y163L	
#define 	Y164L	
#define 	Y165L	
#define 	Y166L	
#define 	Y167L	

#define 	Y160H	
#define 	Y161H	
#define 	Y162H	
#define 	Y163H	
#define 	Y164H	
#define 	Y165H	
#define 	Y166H	
#define 	Y167H	

//Y170-Y177
#define 	Y170L	
#define 	Y171L	
#define 	Y172L	
#define 	Y173L	
#define 	Y174L	
#define 	Y175L	
#define 	Y176L	
#define 	Y177L	

#define 	Y170H	
#define 	Y171H	
#define 	Y172H	
#define 	Y173H	
#define 	Y174H	
#define 	Y175H	
#define 	Y176H	
#define 	Y177H	

//Y200-Y207
#define 	Y200L	
#define 	Y201L	
#define 	Y202L	
#define 	Y203L	
#define 	Y204L	
#define 	Y205L	
#define 	Y206L	
#define 	Y207L	

#define 	Y200H	
#define 	Y201H	
#define 	Y202H	
#define 	Y203H	
#define 	Y204H	
#define 	Y205H	
#define 	Y206H	
#define 	Y207H	

//Y210-Y217
#define 	Y210L	
#define 	Y211L	
#define 	Y212L	
#define 	Y213L	
#define 	Y214L	
#define 	Y215L	
#define 	Y216L	
#define 	Y217L	

#define 	Y210H	
#define 	Y211H	
#define 	Y212H	
#define 	Y213H	
#define 	Y214H	
#define 	Y215H	
#define 	Y216H	
#define 	Y217H	

//Y220-Y227
#define 	Y220L	
#define 	Y221L	
#define 	Y222L	
#define 	Y223L	
#define 	Y224L	
#define 	Y225L	
#define 	Y226L	
#define 	Y227L	

#define 	Y220H	
#define 	Y221H	
#define 	Y222H	
#define 	Y223H	
#define 	Y224H	
#define 	Y225H	
#define 	Y226H	
#define 	Y227H	

//Y230-Y237
#define 	Y230L	
#define 	Y231L	
#define 	Y232L	
#define 	Y233L	
#define 	Y234L	
#define 	Y235L	
#define 	Y236L	
#define 	Y237L	

#define 	Y230H	
#define 	Y231H	
#define 	Y232H	
#define 	Y233H	
#define 	Y234H	
#define 	Y235H	
#define 	Y236H	
#define 	Y237H	

//Y240-Y247
#define 	Y240L	
#define 	Y241L	
#define 	Y242L	
#define 	Y243L	
#define 	Y244L	
#define 	Y245L	
#define 	Y246L	
#define 	Y247L	

#define 	Y240H	
#define 	Y241H	
#define 	Y242H	
#define 	Y243H	
#define 	Y244H	
#define 	Y245H	
#define 	Y246H	
#define 	Y247H	

//Y250-Y257
#define 	Y250L	
#define 	Y251L	
#define 	Y252L	
#define 	Y253L	
#define 	Y254L	
#define 	Y255L	
#define 	Y256L	
#define 	Y257L	

#define 	Y250H	
#define 	Y251H	
#define 	Y252H	
#define 	Y253H	
#define 	Y254H	
#define 	Y255H	
#define 	Y256H	
#define 	Y257H	

//Y260-Y267
#define 	Y260L	
#define 	Y261L	
#define 	Y262L	
#define 	Y263L	
#define 	Y264L	
#define 	Y265L	
#define 	Y266L	
#define 	Y267L	

#define 	Y260H	
#define 	Y261H	
#define 	Y262H	
#define 	Y263H	
#define 	Y264H	
#define 	Y265H	
#define 	Y266H	
#define 	Y267H	

//Y270-Y277
#define 	Y270L	
#define 	Y271L	
#define 	Y272L	
#define 	Y273L	
#define 	Y274L	
#define 	Y275L	
#define 	Y276L	
#define 	Y277L	

#define 	Y270H	
#define 	Y271H	
#define 	Y272H	
#define 	Y273H	
#define 	Y274H	
#define 	Y275H	
#define 	Y276H	
#define 	Y277H	

//Y300-Y307
#define 	Y300L	
#define 	Y301L	
#define 	Y302L	
#define 	Y303L	
#define 	Y304L	
#define 	Y305L	
#define 	Y306L	
#define 	Y307L	

#define 	Y300H	
#define 	Y301H	
#define 	Y302H	
#define 	Y303H	
#define 	Y304H	
#define 	Y305H	
#define 	Y306H	
#define 	Y307H	

//Y310-Y317
#define 	Y310L	
#define 	Y311L	
#define 	Y312L	
#define 	Y313L	
#define 	Y314L	
#define 	Y315L	
#define 	Y316L	
#define 	Y317L	

#define 	Y310H	
#define 	Y311H	
#define 	Y312H	
#define 	Y313H	
#define 	Y314H	
#define 	Y315H	
#define 	Y316H	
#define 	Y317H	

//Y320-Y327
#define 	Y320L	
#define 	Y321L	
#define 	Y322L	
#define 	Y323L	
#define 	Y324L	
#define 	Y325L	
#define 	Y326L	
#define 	Y327L	

#define 	Y320H	
#define 	Y321H	
#define 	Y322H	
#define 	Y323H	
#define 	Y324H	
#define 	Y325H	
#define 	Y326H	
#define 	Y327H	

//Y330-Y337
#define 	Y330L	
#define 	Y331L	
#define 	Y332L	
#define 	Y333L	
#define 	Y334L	
#define 	Y335L	
#define 	Y336L	
#define 	Y337L	

#define 	Y330H	
#define 	Y331H	
#define 	Y332H	
#define 	Y333H	
#define 	Y334H	
#define 	Y335H	
#define 	Y336H	
#define 	Y337H	

//Y340-Y347
#define 	Y340L	
#define 	Y341L	
#define 	Y342L	
#define 	Y343L	
#define 	Y344L	
#define 	Y345L	
#define 	Y346L	
#define 	Y347L	

#define 	Y340H	
#define 	Y341H	
#define 	Y342H	
#define 	Y343H	
#define 	Y344H	
#define 	Y345H	
#define 	Y346H	
#define 	Y347H	

//Y350-Y357
#define 	Y350L	
#define 	Y351L	
#define 	Y352L	
#define 	Y353L	
#define 	Y354L	
#define 	Y355L	
#define 	Y356L	
#define 	Y357L	

#define 	Y350H	
#define 	Y351H	
#define 	Y352H	
#define 	Y353H	
#define 	Y354H	
#define 	Y355H	
#define 	Y356H	
#define 	Y357H	

//Y360-Y367
#define 	Y360L	
#define 	Y361L	
#define 	Y362L	
#define 	Y363L	
#define 	Y364L	
#define 	Y365L	
#define 	Y366L	
#define 	Y367L	

#define 	Y360H	
#define 	Y361H	
#define 	Y362H	
#define 	Y363H	
#define 	Y364H	
#define 	Y365H	
#define 	Y366H	
#define 	Y367H	

//Y370-Y377
#define 	Y370L	
#define 	Y371L	
#define 	Y372L	
#define 	Y373L	
#define 	Y374L	
#define 	Y375L	
#define 	Y376L	
#define 	Y377L	

#define 	Y370H	
#define 	Y371H	
#define 	Y372H	
#define 	Y373H	
#define 	Y374H	
#define 	Y375H	
#define 	Y376H	
#define 	Y377H	

//if(X376)
//X0-X7 
#define 	X0	0
#define 	X1	0
#define 	X2	0
#define 	X3	0
#define 	X4	0
#define 	X5	0
#define 	X6	0
#define 	X7	0
//X10-X17 
#define 	X10 0	
#define 	X11	0
#define 	X12	0
#define 	X13	0
#define 	X14	0
#define 	X15	0
#define 	X16	0
#define 	X17	0
//X20-X27 
#define 	X20 0
#define 	X21 0
#define 	X22 0
#define 	X23 0
#define 	X24 0
#define 	X25 0
#define 	X26 0
#define 	X27 0
//X30-X37 
#define 	X30 0
#define 	X31 0
#define 	X32 0
#define 	X33 0
#define 	X34 0
#define 	X35 0
#define 	X36 0
#define 	X37 0
//X40-X47  
#define 	X40 0
#define 	X41 0
#define 	X42 0
#define 	X43 0
#define 	X44 0
#define 	X45 0
#define 	X46 0
#define 	X47 0
//X50-X57  
#define 	X50 0
#define 	X51 0
#define 	X52 0
#define 	X53 0
#define 	X54 0
#define 	X55 0
#define 	X56 0
#define 	X57 0
//X60-X67 
#define 	X60 0
#define 	X61 0
#define 	X62 0
#define 	X63 0
#define 	X64 0
#define 	X65 0
#define 	X66 0
#define 	X67 0
//X70-X77 
#define 	X70 0
#define 	X71 0
#define 	X72 0
#define 	X73 0
#define 	X74 0
#define 	X75 0
#define 	X76 0
#define 	X77 0
//X100-X107  
#define 	X100 0
#define 	X101 0
#define 	X102 0
#define 	X103 0
#define 	X104 0
#define 	X105 0
#define 	X106 0
#define 	X107 0
//X110-X117 
#define 	X110 0
#define 	X111 0
#define 	X112 0
#define 	X113 0
#define 	X114 0
#define 	X115 0
#define 	X116 0
#define 	X117 0
//X120-X127 
#define 	X120 0
#define 	X121 0
#define 	X122 0
#define 	X123 0
#define 	X124 0
#define 	X125 0
#define 	X126 0
#define 	X127 0
//X130-X137 
#define 	X130 0
#define 	X131 0
#define 	X132 0
#define 	X133 0
#define 	X134 0
#define 	X135 0
#define 	X136 0
#define 	X137 0
 //X140-X147 
 #define 	X140 0
#define 	X141 0
#define 	X142 0
#define 	X143 0
#define 	X144 0
#define 	X145 0
#define 	X146 0
#define 	X147 0
//X150-X157 
#define 	X150 0
#define 	X151 0
#define 	X152 0
#define 	X153 0
#define 	X154 0
#define 	X155 0
#define 	X156 0
#define 	X157 0
//X160-X167 
#define 	X160 0
#define 	X161 0
#define 	X162 0
#define 	X163 0
#define 	X164 0
#define 	X165 0
#define 	X166 0
#define 	X167 0
//X170-X177 
#define 	X170 0
#define 	X171 0
#define 	X172 0
#define 	X173 0
#define 	X174 0
#define 	X175 0
#define 	X176 0
#define 	X177 0
//X200-X207 
#define 	X200 0
#define 	X201 0
#define 	X202 0
#define 	X203 0
#define 	X204 0
#define 	X205 0
#define 	X206 0
#define 	X207 0
//X210-X217 
#define 	X210 0
#define 	X211 0
#define 	X212 0
#define 	X213 0
#define 	X214 0
#define 	X215 0
#define 	X216 0
#define 	X217 0
//X220-X227 
#define 	X220 0
#define 	X221 0
#define 	X222 0
#define 	X223 0
#define 	X224 0
#define 	X225 0
#define 	X226 0
#define 	X227 0
//X230-X237 
#define 	X230 0
#define 	X231 0
#define 	X232 0
#define 	X233 0
#define 	X234 0
#define 	X235 0
#define 	X236 0
#define 	X237 0
//X240-X247 
#define 	X240 0
#define 	X241 0
#define 	X242 0
#define 	X243 0
#define 	X244 0
#define 	X245 0
#define 	X246 0
#define 	X247 0
//X250-X257 
#define 	X250 0
#define 	X251 0
#define 	X252 0
#define 	X253 0
#define 	X254 0
#define 	X255 0
#define 	X256 0
#define 	X257 0
//X260-X267 
#define 	X260 0
#define 	X261 0
#define 	X262 0
#define 	X263 0
#define 	X264 0
#define 	X265 0
#define 	X266 0
#define 	X267 0
//X270-X277 
#define 	X270 0
#define 	X271 0
#define 	X272 0
#define 	X273 0
#define 	X274 0
#define 	X275 0
#define 	X276 0
#define 	X277 0
//X300-X307 
#define 	X300 0
#define 	X301 0
#define 	X302 0
#define 	X303 0
#define 	X304 0
#define 	X305 0
#define 	X306 0
#define 	X307 0
//X310-X317 
#define 	X310 0
#define 	X311 0
#define 	X312 0
#define 	X313 0
#define 	X314 0
#define 	X315 0
#define 	X316 0
#define 	X317 0
//X320-X327 
#define 	X320 0
#define 	X321 0
#define 	X322 0
#define 	X323 0
#define 	X324 0
#define 	X325 0
#define 	X326 0
#define 	X327 0
//X330-X337 
#define 	X330 0
#define 	X331 0
#define 	X332 0
#define 	X333 0
#define 	X334 0
#define 	X335 0
#define 	X336 0
#define 	X337 0
//X340-X347 
#define 	X340 0
#define 	X341 0
#define 	X342 0 
#define 	X343 0
#define 	X344 0
#define 	X345 0
#define 	X346 0
#define 	X347 0
//X350-X357 
#define 	X350 0
#define 	X351 0
#define 	X352 0
#define 	X353 0
#define 	X354 0
#define 	X355 0
#define 	X356 0
#define 	X357 0
//X360-X367 
#define 	X360 0
#define 	X361 0
#define 	X362 0
#define 	X363 0
#define 	X364 0
#define 	X365 0
#define 	X366 0
#define 	X367 0
//X370-X377 
#define 	X370 0
#define 	X371 0
#define 	X372 0
#define 	X373 0
#define 	X374 0
#define 	X375 0
#define 	X376 0
#define 	X377 0
#endif   
/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
