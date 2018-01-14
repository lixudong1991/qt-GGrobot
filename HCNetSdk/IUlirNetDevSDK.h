/*******************************************************************
描述：
********************************************************************/


#ifndef _IULIRNetDevSDK_H_
#define _IULIRNetDevSDK_H_


#ifdef IULIRNETDEVSDK_EXPORTS
#define IULIRNetDevSDK_API __declspec(dllexport)
#else
#define IULIRNetDevSDK_API __declspec(dllimport)
#endif

//数据流类型
enum REALSTREAMTYPE
{
	STREAM_TYPE_AVI = 1,			//AVI数据
	STREAM_TYPE_GRAYDATA = 2		//灰度数据
};

//回调数据类型
enum STREAMTYPE
{
	AVI_HEAD = 0,//avi数据头
	AVI_DATA = 1,//avi数据
	GRAY_HEAD = 2,//灰度头
	GRAY_DATA = 3,//灰度数据
	TEMPOBJECT_DATA = 4,//测温对象信息
};

//连接方式
enum CONNECTTYPE
{
	CONNECT_TYPE_NET_1000 = 1,
	CONNECT_TYPE_COM = 2,
	CONNECT_TYPE_USB = 3,
	CONNECT_TYPE_ULIRNET = 4
};
//温度报警类型
enum ALARMTYPE
{
	ALARM_ABOVE = 0,	//温度超标报警
	ALARM_BLEW = 1,		//温度过低报警
	ALARM_DIF = 2,		//温差超标报警
};

//FTP文件下载 状态 
enum FTP_FILE_STATE
{
	FTP_DOWNLOAD_SUCCEED = 1,	//下载成功
	FTP_DOWNLOAD_UNDERWAY = 2,	//正在下载
	FTP_DOWNLOAD_FAILED = 3		//下载失败
};

//一些异常类型的定义
enum EXPECTION
{
	EX_CMD_BREAK = 1,		//命令连接断开
	EX_CMD_RECONNECT = 2,	//命令连接重新连接成功
	EX_STREAM_BREAK = 3,	//视频连接断开
	EX_STREAM_RECONNECT = 4,//视频连接重新连接成功
	EX_ALARM_BREAK = 5,		//报警连接断开
	EX_ALARM_RECONNECT = 6,	//报警连接重新连接成功
};

//机芯命令
enum ULIR_CONFIG_CMD
{
	ULIR_LINK_CONNECT = 0x0000,					//连接						NULL
	ULIR_CFG_GET_DEVICEINFO = 0x0200,			//获取设备信息				NET_DEV_DEVICEINFO
	ULIR_CFG_GET_SYSCONFIG = 0x0210,			//获取系统配置				NET_DEV_SYSCONFIG
	ULIR_CFG_GET_TEMP_PARA = 0x0211,			//获取全部测温参数			_MeasureTempPara
	ULIR_CFG_SET_TEMP_CALIBPARA = 0x0212,		//设置测温参数(内部使用)		NET_DEV_TEMPCALIBPARA
	ULIR_CFG_SET_TEMP_USERPARA = 0x0213,		//设置测温参数(对用户开放)	NET_DEV_TEMPUSERPARA
	ULIR_CFG_GET_REALTIME_PARA = 0x0214,		//获取实时测温参数			NET_DEV_TEMPREALTIMEPARA
	ULIR_MEASURE_SET_POINT = 0x1010,			//设置点温度					NET_DEV_POINTPARA
	ULIR_MEASURE_SET_RECT = 0x1011,				//设置区域测温				NET_DEV_RECTPARA
	ULIR_MEASURE_SET_LINE = 0x1012,				//设置线测温					NET_DEV_LINEPARA
	ULIR_MEASURE_SET_OBJECT = 0x1013,			//设置对象使能标记			NET_DEV_TEMPOBJECT
	ULIR_MEASURE_SET_REFERENCE = 0x1014,		//设置参考温度				NET_DEV_TEMPREFERENCE
	ULIR_MEASURE_SET_TEMPUNIT = 0x1015,			//设置测温单位				int
	ULIR_MEASURE_SET_TEMPRANGE = 0x1016,		//切换测温档					NET_DEV_TEMPRANGR
	ULIR_MEASURE_GET_POINT = 0x1020,			//获取点温度					NET_DEV_POINTPARA
	ULIR_MEASURE_GET_RECT = 0x1021,				//获取区域测温				NET_DEV_RECTPARA
	ULIR_MEASURE_GET_LINE = 0x1022,				//获取线测温					NET_DEV_LINEPARA
	ULIR_MEASURE_GET_OBJECT = 0x1023,			//获取对象使能标记			NET_DEV_TEMPOBJECT
	ULIR_MEASURE_GET_MAXTEMP = 0x1027,			//获取图像最高温度			int
	ULIR_MEASURE_GET_MAXTEMP2 = 0x1028,			//获取全图最高温度			NET_DEV_FULLRECTPARAM
	ULIR_IMAGE_SET_ISOTEMP = 0x1110,			//等温色						NET_DEV_ISOTHERMTEMP
	ULIR_IMAGE_SET_ALARM = 0x1111,				//设置报警					NET_DEV_ALARMTEMP
	ULIR_IMAGE_SET_COLORRULER = 0x1112,			//切换色标					int
	ULIR_IMAGE_SET_REVERSE = 0x1113,			//图像反向					int
	ULIR_IMAGE_SET_MANUAL = 0x1114,				//手动、自动模式设置			NET_DEV_MANUALPARA
	ULIR_IMAGE_GET_MANUAL = 0x1130,				//手动、自动模式设置			NET_DEV_MANUALPARA
	ULIR_SYS_SET_LANGUAGE = 0x1210,				//设置系统语言				int
	ULIR_SYS_SET_TIME = 0x1211,					//设置系统时间				char[13]
	ULIR_SYS_SET_DEFAULT = 0x1212,				//恢复出厂设置				NULL
	ULIR_SYS_SET_CAPTURETIME = 0x1215,			//设置抓拍时间				int
	ULIR_SYS_SET_AUTORECTIFY = 0x1218,			//设置自动调零时间			int
	ULIR_SYS_SET_MONITOR_MODE = 0x1220,			//设置视频输出制式			int
	ULIR_SYS_GET_ALARM_LVINFO = 0x1221,			//获取报警等级温度			int*
	ULIR_SYS_SET_ALARM_LVINFO = 0x1222,			//设置报警等级温度			int*
	ULIR_SYS_SET_ALARM_INFO = 0x1223,			//设置报警信息		NET_DEV_ALARMTEMPWITHALARMLV /  NET_DEV_ALARMTEMP
	ULIR_KEY_SET_FREEZE = 0x1317,				//图像冻结					int	
	ULIR_KEY_GET_FOCUS_VALUE = 0x1318,			//获取焦距步进值	int
	ULIR_KEY_SET_FOCUS_VALUE = 0x1319,			//设置焦距步进制
	ULIR_KEY_ZOOM = 0x1326,						//图像放大		Int(1：不放大, 2:放大2倍, 4:放大4倍)
	ULIR_SYS_GET_OSD = 0x1700,					//获取系统的OSD设置情况		NET_DEV_OSDSETTING
	ULIR_SYS_SET_OSD = 0x1701,					//设置系统的osd设置情况		NET_DEV_OSDSETTING
};

enum ULIR_ACTION_CMD
{
	ULIR_KEY_AUTO_RECTIFY = 0x1310,				//调零
	ULIR_KEY_AUTO_FOCUS = 0x1311,				//自动调焦
	ULIR_KEY_FOCUS_NEAR = 0x1312,				//手动近焦
	ULIR_KEY_FOCUS_FAR = 0x1313,				//手动远焦
	ULIR_KEY_FOCUS_STOP = 0x1314,				//停止调焦
	ULIR_KEY_CAPTURE = 0x1320,					//机芯抓图（jpg)
	ULIR_KEY_RECODEAVI = 0x1321,				//录像(avi)
	ULIR_KEY_REODEIR = 0x1322,					//录像(灰度数据)
	ULIR_KEY_STOPREODE = 0x1323,				//停止录像
};

//错误码
enum ULIR_NETDEV_ERROR
{
	NETDEV_NOERROR  = 0,			//没有错误
	NETDEV_NOCONNECT = 11,			//端口未连接
	NETDEV_CHANNEL_ERROR = 12,		//通道号错误
	NETDEV_PARAMETER_ERROR = 13,	//参数错误
	NETDEV_ALLOC_RESOURCE_ERROR = 14,//资源分配错误
	NETDEV_SDK_INIT_ERROR = 15,		//SDK初始化失败
	
	NETDEV_SET_CMD_ERROR = 20,		//设置发送命令错误
	NETDEV_SEND_ERROR = 21,			//向设备发送失败
	NETDEV_RECV_ERROR = 22,			//从设备接收数据失败
	NETDEV_RECVDATA_ERROR = 23,		//从设备接收的数据有误

	/************************************************/
	NETDEV_WSASTARTUP_FAILED = 30,	//网络初始化失败
	NETDEV_CREATESOCK_FAILED = 31,	//创建端口失败
	NETDEV_BIND_FAILED = 32,		//端口绑定失败
	NETDEV_WSAJOINLEAF_FAILED = 33, //加入组播失败
	NETDEV_SETPACKAGE_FAILED = 34,  //设置数据包失败
	NETDEV_DEVCONNECT_FAILED = 35 , //连接失败
	NETDEV_MAX_USERNUM = 36 ,		//登入设备用户达到上限
	NETDEV_NOT_SUCC_LOGIN = 37 ,	//用户未登入

	/************************************************/
	NETDEV_RE_ERR_INTER = 60 ,				// 设备内部错误
	NETDEV_RE_ERR_MAXCONNECT = 61 ,			// 达到最大连接上限

	NETDEV_RE_ERR_BADCMD = 70 ,				// 命令错，无此命令
	NETDEV_RE_ERR_BADARG = 71,				// 参数错

	NETDEV_RE_ERR_SD = 80,					// 未检测到SD卡

	NETDEV_RE_ERR_STAT_CAP = 90,            // 处于自动拍照状态
	NETDEV_RE_ERR_STAT_REC = 91,            // 处于录像状态
	NETDEV_RE_ERR_STAT_PLAY_AVI = 92,       // AVI数据传输状态
	NETDEV_RE_ERR_STAT_PLAY_GRAYDATA = 93,  // 灰度数据传输状态

	NETDEV_RE_ERR_SET_IP = 100,				// 设置ip失败
	NETDEV_RE_ERR_SET_ROUTE = 101,          // 设置ip，组播路由设置失败，重启设备
	NETDEV_RE_ERR_SET_POINT = 102,          // 设置点测温失败
	NETDEV_RE_ERR_SET_RECT = 103,           // 设置区域测温失败
	NETDEV_RE_ERR_SET_LINE = 104,           // 设置线测温失败
	NETDEV_RE_ERR_SET_HIDE_MENU = 105,      // 设置隐藏菜单失败
	NETDEV_RE_ERR_SET_TEMP_USERPARA = 106,  // 设置测温参数失败
	NETDEV_RE_ERR_SET_OBJECT = 107,			// 测温对象使能失败
	NETDEV_RE_ERR_SET_TEMPUNIT = 108,		// 设置温度单位失败
	NETDEV_RE_ERR_SET_ALARM = 109,			// 设置报警失败
	NETDEV_RE_ERR_SET_COLORRULER = 110,		// 设置色标失败
	NETDEV_RE_ERR_SET_TIME = 111,			// 设置时间失败

	/***************FTP错误码******************/
	NETDEV_FTP_LOGON_FAILED = 200,			//登录失败
	NETDEV_FTP_OPEN_LOCALFILE_FAILED = 201,	//打开本地文件失败
	NETDEV_FTP_FILE_ERR = 202,				//文件错误
	NETDEV_FTP_NET_ERR = 203,				//网络错误
	NETDEV_FTP_CREATESOCK_FAILED = 204,		//不能创建SOCKET
	NETDEV_FTP_LOADING_FILE = 205,			//正在下载文件
	NETDEV_FTP_MAX_LOADNUM = 206,			//当前下载已经达到上限
	NETDEV_FTP_CREAT_THREAD_ERR = 207,		//创建线程失败
	NETDEV_FTP_DELETEFILE_FAILED = 208,		//删除文件失败
	NETDEV_FTP_SENDCMD_FAILED = 209,		//发送命令失败
	NETDEV_FTP_RECVCMD_FAILED = 210,		//获取响应失败
};

//Com口结构
typedef struct
{

	int nComID;			//串口号
	int nByteSize;		//数据位4,5，6，7，8
	int nStopBit;		//停止位 1，1.5,2 对应的值分别为0，1，2
	int nParity ;		//校验，无 0，奇校验 1，偶校验 2,Mark，标记校验 3,space 4
	int nBaudRate;		//波特率
	int nBuffer;		//缓冲区大小
	int nWaitTime;		//等待时间

}NET_DEV_COMINFO;

//(部分可修改)测温参数结构
typedef struct 
{
	int Radiance100;		//辐射率100倍[1,100]；整个屏幕的辐射率
	int Distance100;		//距离100倍[10,100000]；
	int Humidity100;		//湿度100倍[1,100];
	int CorrectFact100;		//修正系数100倍[1,100]；
	int CorrectTemp100;		//修正温度100倍[-10000,10000]
	int transmissivity100;		//透射率[1,100]
	int Eviment100;			//环境温度
	byte reserve[24];			//24个字节的预留空间
}NET_DEV_TEMPUSERPARA;

//实时测温参数
typedef struct
{
	int nShiderTemp100;       //挡片温度的100倍：nShiderTemp100；
	int nLensTemp100;         //腔体温度的100倍：nLensTemp100；
	int nAmbientTemp100;      //环境温度的100倍：nAmbientTemp100；
	int nOpenMachineTimeLong; //运行时间的100倍：nOpenMachineTimeLong；
	int nShiderTemp100_zero;  //调零时刻挡片温度的100倍：nShiderTemp100						//_zero；
	int nLensTemp100_zero;    //腔体温度的100倍：nLensTemp100_zero；
	int nBarrierGray;         //挡片灰度的100倍：nBarrierGray
	int nDetectorTemp100;     //探测器温度的100倍：nDetectorTemp100；
	byte reserve[32];           //32个字节的预留空间
}NET_DEV_TEMPREALTIMEPARA;

//设置测温点结构
typedef struct 
{
	int point_id;			//测温点编号[0,9]；
	int p_xcoord;			//点x坐标；
	int p_ycoord;			//点y坐标;
	int p_radiance100;		//点辐射率100倍[1,100];
	int refer_flag;			//设为参考[0,1]
	short temp100;			//当前温度
	byte reserve[14];         //16个字节的预留空间
}NET_DEV_POINTPARA;

//设置测温区域结构
typedef struct 
{
	int rect_id;			//区域编号[0,4];
	int temptype;			//区域测温类型[0,2]:其中0=最高温，1=最低温，2=平均温;
	int origin_xcoord;		//区域x;区域起点（左上角点）的x坐标
	int origin_ycoord;		//区域y;区域起点（左上角点）的y坐标
	int rect_wide;			//区域w;区域的宽度。
	int rect_high;			//区域h;区域的高度。
	int r_radiance100;		//辐射率100倍[1,100];
	int refer_flag;			//设为参考[0,1];
	short mintemp100;
	short maxtemp100;
	short avgtemp100;
	short MaxX;
	short MaxY;
	short MinX;
	short MinY;
	byte reserve[2];          //16个字节的预留空间
}NET_DEV_RECTPARA;

typedef struct  
{
	short nMinTemp100;
	short nMaxtTemp100;
	short nAvgTemp100;
	short nMinx;
	short nMiny;
	short nMaxx;
	short nMaxy;
	char  reserver[10];
}NET_DEV_FULLRECTPARAM;

//设置测温线结构
typedef struct 
{
	int line_id;			//线编号[0，1]:0为水平线 1为垂直线;
	int l_xcoord;			//坐标x;
	int l_ycoord;			//坐标y;
	int l_radiance100;		//辐射率100倍[1,100]
	short temp100;			//温度
	byte reserve[14];         //16个字节的预留空间
}NET_DEV_LINEPARA;

//每一字节表示测温对象的状态，1表示使能，0表示不使能。第0位至第9位表示点侧温0-9，
//第10位表示水平线第11位表示垂直线（互斥设置，不能同时为1），
//第12位至第16位表示区域测温0-4，其他位预留。
typedef struct 
{
	char point0_enable;
	char point1_enable;
	char point2_enable;
	char point3_enable;
	char point4_enable;
	char point5_enable;
	char point6_enable;
	char point7_enable;
	char point8_enable;
	char point9_enable;
	char line0_enable;
	char line1_enable;
	char rect0_enable;
	char rect1_enable;
	char rect2_enable;
	char rect3_enable;
	char rect4_enable;
	char reserve[15];       //16个字节的预留空间
}NET_DEV_TEMPOBJECT;

//测温对象设为参考
typedef struct 
{
	int enable;				//使能位[0,1]: 0=关闭参考温度 1=设置参考温度
	int ReferTemp100;		//参考温度的100倍；
}NET_DEV_TEMPREFERENCE;

//设置温度档位
typedef struct 
{
	int TempRangeID;		//测温档位[0,2]；
	int LensId;				//镜头[0,1]
	byte reserve[8];			//8个字节的预留空间
}NET_DEV_TEMPRANGR;

//设置等温色
typedef struct
{
	int IsoTemp100;				//等温温度100倍[-27315,120000]；
	int IsoTempHigh100;			//等温高度100倍[10,120000]；
	int IsoTempColorId;			//等温色的ID[0,10]等温色的数量和RGB值在仪器信息给。
	byte reserve[8];				//8个字节的预留空间
}NET_DEV_ISOTHERMTEMP;

//设置报警温度(无报警等级)
typedef struct 
{
	int AlarmSwitch;		//报警开关[0,2]：0关闭报警，1最高温报警，2最低温报警;
	int AlarmTemp100;		//报警温度100倍：[-27315,120000]；
	int AlarmColorId;		//报警色[0-10]: 0=关闭 1=红色 2=绿色 3=蓝色 4=黑色 5=白色 6=灰色 7= 黄色 8=酒红 9=紫色 10=橙色
	byte reserve[8];			//8个字节的预留空间
}NET_DEV_ALARMTEMP;

//设置报警温度(有报警等级)
typedef struct 
{
	int AlarmSwitch;		//报警开关[0,2]：0关闭报警，1最高温报警，2最低温报警;
	int AlarmLevel;			//报警等级
	int AlarmColorId;		//报警色[0-10]: 0=关闭 1=红色 2=绿色 3=蓝色 4=黑色 5=白色 6=灰色 7= 黄色 8=酒红 9=紫色 10=橙色
	byte reserve[8];			//8个字节的预留空间
}NET_DEV_ALARMTEMPWITHALARMLV;

//模式设置
typedef struct 
{
	int ManualType;			//类型[0, 1]：0 = 自动；1 = 手动：
	int TempHighest;		//  如果手动模式: 手动设置最高温100倍    
	int TempLowest;			// 手动设置最低温100倍 自动模式都为设为0
	byte reserve[16];			//16个字节的预留空间
}NET_DEV_MANUALPARA;

//隐藏菜单结构
typedef struct
{
	int ShowGrayEnable;		//[0,1] 0=不显示灰度 1=显示灰度；
	int CollectEnable;		//[0, 1] 0=不采集定标数据  1=采集定标数据
	int CorrectTemp100;		//内部修正温度的100倍
	int CorrectFact100;		//内部修正系数的100倍
	byte reserve[32];			//32个字节的预留空间
}NET_DEV_HIDEMENUPARA;

//设备信息
typedef struct
{
	char DeviceType[32];		//内部型号 "TI615"
	char OEMDeviceType[32];		//贴牌型号 "IRI-615"
	char DataProtocal[32];		//数据协议 "Ethernet1000M"
	char SerialNumber[20];		//序列号 "9008801013"
	char ProduceTime[16];		//生产日期 "2015-01-01" 
	char SoftwareVersion[16];	//软件版本 "Ver1.1"
	char HardwareVersion[16];	//硬件版本 "HW169"
	int  TempCalcType;			//测温算法编号 21
	int  ImageCalcType;			//图像算法编号 5
	int  DetectorWidth;			//探测器像素宽	640
	int  DetectorHeight;		//探测器高		480
	int  BitsPerPixel;			//像素位数 	14
	int  BytesPerPixel;			//像素字节数	2
	int  ImageWidth;			//图像宽	640
	int  ImageHeight;			//图像高	480 49

	//色标
	char ColorRulerName[64];	// "/home/xia/dm6446/ColorRuler.dat"
	int  ColurRulerNum;			// 色标数目 12
	int  ColorNumPerRuler;		// 色标颜色数 512
	int  BytesPerColor;			// 每个颜色字节数 4
	char ColorRulerType[8];		// "YUV444" 21

	// 语言
	int LangNum;				// 10
	char LangArray[32];			// 语言ID数组 0英语 1中文简体 2中文繁体 3 4 5 6 7 8 9 最多32种语言	
	int PointNum;				// 点数量 10
	int LineNum;				// 线数量 2
	int RectNum;				// 区域数量 10 8

	int TempRangeNum;				// 当前设备档位数 3
	int TempRangeMaxTemp100[5];		// 档位最大值100倍，预留5个档位
	int TempRangeMinTemp100[5];		// 档位最小值100倍，预留5个档位
	int LensNum;					// 当前设备镜头数 2
	int LensDiameter[5];			// 镜头直径，以毫米为单位，预留5个镜头
	byte Reserved[116];
} NET_DEV_DEVICEINFO;					// 512 bytes

//系统信息
typedef struct
{
	// temppara
	int Emissivity100;			// 辐射率
	int Repair100; 				// 用户修正系数100倍
	int RepairTemp100;			// 用户修正温度100倍
	int Distance100;			// 距离100倍
	int Humidity100;			// 湿度100倍
	int ObjectStatus;			// 点线区域选中标志位

	// analysis
	int TempRangeID;			// 档位
	int OtherLensID;			// 镜头
	int TempClass;				// 档位 + 2
	int TempUnit;				// 测温单位
	int RefeTempType;			// 参考温度类型 0  12 ..
	int RefeTemp100;			// 参考温度100倍

	// image
	int AlarmColorID;			// 报警色
	int AlarmSwitch;			// 报警温度开关 0关闭 1最高温 2最低温
	int AlarmTemp100;			// 报警温度100倍
	int IsothermColorID;		// 等温色
	int IsothermTemp100;		// 等温温度100倍
	int IsothermHight100;		// 等温高度100倍
	int ColorRulerID;			// 色标ID
	int ReverseImage;			// 图像反相
	int ManualType;				// 1手动 0自动
	int TempHigh100;			// 当前最高温100倍
	int TempLow100;				// 当前最低温100倍

	// set
	int LanguageID;				// 语言ID
	int AutoZeroTime;			//自动调零时间
	int AutoCapTime;			//自动抓拍时间
	int BlackBodyTemp100;		//黑体温度
	int ZoomRate;				//图像放大倍数
	int MonitorMode;			//视频制式
	char TimeString[16];		// 20150122105333 
	int ShowGrayEnable;			// 灰度显示使能
	int CollectEnable;			// 采集使能
	int InterCorrectTemp100;	// 内部修温
	int InterCorrectFact100;	// 内部修系
	int AlarmLevel;				//当前报警等级
	int AlarmLevelNum;			//报警等级个数9
	int Transmissivity100;		//透射率
	int Eviment100;				//环境温度
	byte Reserve[108];			// 保留
} NET_DEV_SYSCONFIG;					// 256 bytes

//(不对外开放)测温参数结构
typedef struct 
{
	int AllK10;				// 总系数
	int ZeroParaA100;		// 修A
	int ZeroParaB1000;		// 修B
	int InterTemp100;		// 内部修温100倍
	byte Reserve[16];
} NET_DEV_TEMPCALIBPARA;			

//设备Ip信息
typedef struct	//设备信息结构
{

	int Id;
	unsigned char Ip[16];
	unsigned char netmask[16];
	unsigned char gateway[16];
	byte reserve[64];

}NET_DEV_DEVIPINFO; 


//设备时间
typedef struct	
{

	int nYear;
	int nMonth;
	int nDay;
	int nHour;
	int nMinute;

}NET_DEV_DEVTIME; 

//灰度数据流，数据包头结构
typedef struct
{
	int nTag;					// FILEATTR_TAG;
	int nDesLen;				// 结构体大小

	char btFileVersion[8];		// 文件版本号
	char btCreateDate[20];		// 保存日期
	char btCreateTime[20];		// 保存时分
	int nRawFrameSize;			// 每帧原始数据大小
	unsigned int nFileLength;	//整个文件长度
	int nFPS;					// 帧率
	int nTotalFrames;			// 总帧数

	// product
	int nDectorImageBits;		// 探测器位数
	int nDectorImageH;			// 探测器垂直分辨率
	int nDectorImageW;			// 探测器水平分辨率
	char btSoftVer[20];			// 1.0.1
	char btProduct[20];			// TI615x

	// color
	int nColorRuleID;			// 色标ID
	int nAlarmType;				// 报警类型
	int bAlarm;					// 是否报警	
	int nAlarmTemp100;			// 报警温度
	int nColorAlarmID;			// 报警色ID
	int nIsothermalLow100;		// 等温色下限
	int nIsothermalHigh100;		// 等温色上限
	int nIsothermalID;			// 等温色ID

	// measure temp	
	int nTempParaSize;			// 测温参数大小
	int nCalcType;				// 测温算法类型
	byte nReserved[160];			// 保留
} NET_DEV_RAWFILEHEAD;


//osd使能应用
struct NET_DEV_OSDSETTING
{
	char  color_ruler;			//0: 不显示1:显示
	char  max_temp_obj;			//0: 不显示1:显示
	char  user_setting_obj;		//0: 不显示1:显示
	char  time;					//0: 不显示1:显示
	char  min_temp_obj;			//0: 不显示1:显示
	char  avg_temp_obj;			//0: 不显示1:显示
	char  gps;					//0: 不显示1:显示
	char  video_mode;			//0: 不显示1:显示
	char  emissivity;			//0: 不显示1:显示
	char  reserve[11];
};

#include <vector>
using namespace std;

/**************************回调函数*****************************************************************/
//获取实时数据
typedef void (CALLBACK *GetRealStreamCallBack)(DWORD dwDataType, char* pDataBuffer, DWORD dwDataSize,DWORD dwUser, short shPort);
/**************************回调函数*****************************************************************/
typedef void(CALLBACK *fExceptionCallBack)(DWORD dwType,LONG lHandle,void *pUser);
/**************************回调函数*****************************************************************/
typedef void (CALLBACK *fAlarmCallBack)(short sHandle,DWORD dwAlarmType,BYTE *pBuffer,DWORD dwBuferSize,DWORD dwUser);

//-----------------------接口函数定义-----------------------------
#ifdef __cplusplus
extern "C" {
#endif


	//初始化网络库
	IULIRNetDevSDK_API BOOL __stdcall NetDev_Init();
	//反初始化网络库
	IULIRNetDevSDK_API BOOL __stdcall NetDev_Cleanup();

	//连接设备  失败：返回-1； 
	//连接方式参考枚举CONNECTTYPE。
	IULIRNetDevSDK_API short __stdcall NetDev_Connect(char *szIP, DWORD dwConnectType);
	//断开连接
	IULIRNetDevSDK_API BOOL __stdcall NetDev_DisConnect(short shHandle);

	//设置网络异常信息，异常类型具体定义见EXPECTION枚举
	IULIRNetDevSDK_API BOOL __stdcall NetDev_SetExceptionCallBack(fExceptionCallBack cbExceptionCallBack,void* pUser);
	////获取灰图数据
	//IULIRNetDevSDK_API BOOL __stdcall NetDev_GetImage(short shHandle,BYTE **pBuffer,DWORD *dwBufSize, LPVOID lpOutRealTimePara = NULL);
	
	//对设备的动作
	IULIRNetDevSDK_API BOOL __stdcall NetDev_DoAction(short shHandle,DWORD dwActionType);
	//设置设备
	IULIRNetDevSDK_API BOOL __stdcall NetDev_SetConfig(short shHandle,DWORD dwCmdType,LPVOID lpInBuffer, DWORD dwInBufSize, LPVOID lpOutBuffer = NULL, DWORD dwOutBufferSize = 0);
	//获取设备信息
	IULIRNetDevSDK_API BOOL __stdcall NetDev_GetConfig(short shHandle,DWORD dwCmdType, LPVOID lpOutBuffer, DWORD dwOutBufferSize,DWORD *lpBytesReturned);
	//获取错误码
	IULIRNetDevSDK_API DWORD __stdcall NetDev_GetLastError();
	//获取错误信息
	IULIRNetDevSDK_API char* __stdcall NetDev_GetErrorInfo(DWORD dwErrorID);

//	IULIRNetDevSDK_API float __stdcall NetDev_GetTempFromGray(short shHandle, short nGray, float fEmissivity, _MeasureTempPara *pTempPara,int iType);

	//收索在线设备个数
	IULIRNetDevSDK_API BOOL __stdcall NetDev_SearchDev(DWORD *dwDevNum);
	//获取设备信息
	IULIRNetDevSDK_API BOOL __stdcall NetDev_GetDevIpInfo(DWORD dwDevIndex, NET_DEV_DEVIPINFO* pDevInfo);
	//修改设备IP信息
	IULIRNetDevSDK_API BOOL __stdcall NetDev_SetDevIpInfo(NET_DEV_DEVIPINFO* pDevInfo);

	//抓灰图
	IULIRNetDevSDK_API BOOL __stdcall NetDev_CaptureGrayImage(short shHandle, char* szInBuf, DWORD dwInBufSize, DWORD *dwRealSize);				
	//抓jpg
	IULIRNetDevSDK_API BOOL __stdcall NetDev_CaptureJPEGPicture(short shHandle,char *szInBuf,DWORD dwInBufSize,DWORD *dwRealSize);
	//抓bmp
	IULIRNetDevSDK_API BOOL __stdcall NetDev_CaptureBMPPicture(short shHandle,char *szInBuf,DWORD dwInBufSize,DWORD *dwRealSize);

	//开始获取数据
	//类型定义见REALSTREAMTYPE
	IULIRNetDevSDK_API BOOL __stdcall NetDev_StartRealStream(short shHandle, DWORD dwStreamType);       	 
	//结束获取数据
	IULIRNetDevSDK_API BOOL __stdcall NetDev_StopRealStream(short shHandle);  
	//设置实时数据回调
	IULIRNetDevSDK_API BOOL __stdcall NetDev_SetRealStreamCallBack(short shHandle, GetRealStreamCallBack funRealStream, DWORD dwUser);
	//通知设备，插入关键帧
	IULIRNetDevSDK_API BOOL __stdcall NetDev_MakeKeyFrame(short shHandle );   

	//开启报警通道
	IULIRNetDevSDK_API  BOOL __stdcall NetDev_OpenAlarmChan(short shHandle);
	//结束报警通道
	IULIRNetDevSDK_API  BOOL __stdcall NetDev_CloseAlarmChan(short shHandle);
	//设置报警回掉函数
	IULIRNetDevSDK_API  BOOL __stdcall NetDev_SetAlarmCallback(short shHandle,fAlarmCallBack funAlarm,DWORD dwUser);


	//连接服务器(FTP)(返回 -1 失败)
	IULIRNetDevSDK_API short __stdcall NetDev_FtpConnect(char *szSeverIp);
	//断开服务器(FTP)
	IULIRNetDevSDK_API BOOL __stdcall NetDev_FtpDisConnect(short shFtpHandle);

	//获取文件个数
	IULIRNetDevSDK_API BOOL __stdcall NetDev_FtpGetFileNum(short shFtpHandle, DWORD *dwFileNum);
	//获取文件名称
	IULIRNetDevSDK_API BOOL __stdcall NetDev_FtpGetFileName(short shFtpHandle, DWORD dwIndex ,char *szRemoteFile);
	//获取文件大小
	IULIRNetDevSDK_API BOOL __stdcall NetDev_FtpGetFileSize(short shFtpHandle, DWORD dwIndex ,LONG *lFileSize);


	//下载文件 (服务器文件名称， 本地文件名称、路径)
	IULIRNetDevSDK_API BOOL __stdcall NetDev_FtpDownLoadFile(short shFtpHandle, char *szRemoteFile, char *szNewFile);
	//上传文件 (本地文件名称、路径， 服务器文件名称)
	IULIRNetDevSDK_API BOOL __stdcall NetDev_FtpUpLoadFile(short shFtpHandle, char *szLocalFile, char *szNewRemoteFile);
	//删除文件 (服务器文件名称)
	IULIRNetDevSDK_API BOOL __stdcall NetDev_FtpDeleteFile(short shFtpHandle, char *szRemoteFile);
	//获取文件下载状态(状态， 进度)
	IULIRNetDevSDK_API BOOL __stdcall NetDev_FtpGetDownloadState(short shFtpHandle, char *szRemoteFile,DWORD *dwState, float *fRatio);
	
	//设备存储文件，读取数据，可交给测温算法和灰度显示算法。
	//打开文件,如果不是设备产生的文件，将返回-1
	IULIRNetDevSDK_API  short __stdcall NetDev_FileOpen(char *szFileName);
	//关闭文件
	IULIRNetDevSDK_API  BOOL __stdcall NetDev_FileClose(short sFileHandle);
	//获取帧数
	IULIRNetDevSDK_API  int __stdcall NetDev_FileGetFrameNum(short sFileHandle);
	//获取数据头
	IULIRNetDevSDK_API  BOOL __stdcall NetDev_FileGetHead(short sFileHandle,NET_DEV_RAWFILEHEAD *pHead);
	//获取灰度数据
	IULIRNetDevSDK_API  BOOL __stdcall NetDev_FileGetFrameData(short sFileHandle,DWORD dwFrameIndex,BYTE **pData,DWORD *dwDataSize);


	//////////////////////////////////////////////////////
	//
	//
	IULIRNetDevSDK_API BOOL __stdcall NetDev_StartPlayAVI(short shHandle, void* hwnd);       	 
	//
	IULIRNetDevSDK_API BOOL __stdcall NetDev_StopPlayAVI(short shHandle);  



#ifdef __cplusplus
};
#endif

#endif

