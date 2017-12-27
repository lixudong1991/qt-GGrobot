//

#ifdef SHOWIMAGE_EXPORTS
#define SHOWIMAGE_API __declspec(dllexport)
#else
#define SHOWIMAGE_API __declspec(dllimport)
#endif

enum CodeType
{

	CODETYPE_IRON_BOW = 0,			//铁红
	CODETYPE_GREEN_RED= 1,			//绿红
	CODETYPE_GLOW_BOW = 2,			//黄色
	CODETYPE_RAIN_BOW = 3,			//彩虹
	CODETYPE_RED_BOW = 4,			//红色
	CODETYPE_HIGHCONTRAST = 5,		//橙色
	CODETYPE_WHITE = 6,				//
	CODETYPE_JET = 7,				//
	CODETYPE_WHITE_HOT = 8,			//白热
	CODETYPE_BLACK_HOT = 9,			//黑热
	CODETYPE_COLOR10 = 10,			//
	CODETYPE_WINTER = 11,			//

};


typedef void (__stdcall *DrawObjFun)(short sPort,HDC hDc,LONG nUser);

//-----------------------接口函数定义-----------------------------
#ifdef __cplusplus
extern "C" {
#endif
	//初始化 反初始化
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_Init();
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_Cleanup();

	//
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_GetPort(short *sPort);
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_FreePort(short sPort);

	//设置、获取色标ID
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_SetColorCode(short sPort, DWORD dwCodeType);
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_GetColorCode(short sPort, DWORD *dwCodeType);

	//设置等温色状态
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_SetIsoState(short sPort, BOOL bShow);
	//获取等温色状态
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_GetIsoState(short sPort, BOOL *bShow);

	//设置等温色颜色
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_SetIsoColor(short sPort, COLORREF color);
	//获取等温室颜色
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_GetIsoColor(short sPort, COLORREF *color);

	//设置等温色 温度上下限  
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_SetIsoTemp(short sPort, float fTempUp, float fTempDown);
	//获取等温色 温度上下限  
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_GetIsoTemp(short sPort, float *fTempUp, float *fTempDown);

	//设置显示窗口句柄
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_SetShowImageWnd(short sPort, HWND hwnd);

	/* 设置绘图数据 dwPptIndex > -1 || dwPptIndex < 255 */
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_SetObjectMessage(short sPort, char* szObjectMessage);

	//设置图像宽高
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_SetImageSize(short sPort, int iWidth, int iHeight);

	//显示灰图
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_ShowImage(short sPort, BYTE *pBuffer, DWORD nBufferLen, float fMaxTemp, float fMinTemp,DWORD dwZoom = 1);
	//显示灰图2
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_ShowImage2(short sPort, BYTE *pBuffer, DWORD nBufferLen, float fMaxTemp, float fMinTemp,HDC &hMemDC,DWORD dwZoom = 1);
	
	//设置显示回调，主要用来画东西
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_RegisterDrawFun(short sPort,DrawObjFun pDrawFun,LONG nUser);

	//
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_Refrash(short sPort);

	//设置显示色标窗口句柄
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_SetColorBarWnd(short sPort, HWND hwnd);
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_SetColorBarState(short sPort, BOOL bShow);
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_ShowColorBar(short sPort);

	//录像
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_StartRecordAVI(short sPort,char *szPath);
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_StopRecordAVI(short sPort);

	//获取错误信息
	SHOWIMAGE_API LONG __stdcall SHOWIMAGE_GetLastError();
	SHOWIMAGE_API char* __stdcall SHOWIMAGE_GetErrorMsg(LONG *pErrorNo);

#ifdef __cplusplus
}
#endif


