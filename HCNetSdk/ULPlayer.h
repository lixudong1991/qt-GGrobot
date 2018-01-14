//第一版
//只做给定窗口的显示，不做YUV回调
//只做实时视频解码，不做历史文件解码


#ifdef ULPLAYER_EXPORTS
#define ULPLAYER_API extern "C" __declspec(dllexport)
#else
#define ULPLAYER_API extern "C" __declspec(dllimport)
#endif

//画图回调函数
typedef void(CALLBACK *DrawFun)(long nPort,HDC hDc,unsigned int nUser);
//解码回调函数,主要作用：可以自己显示，可以用于Y数据分量的灰度分析
//解码端口，解码后YUV类型(yuv420)，三个yuv数据值，yuv数据各自大小，用户参数
typedef void(CALLBACK *DecFun)(long nPort,unsigned int iDecodeDataType,byte *pData[3],unsigned int iWidth,unsigned int iHeight,unsigned int nUser);

//初始化sdk
ULPLAYER_API bool ULPlayM4_Init();

//反初始化sdk
ULPLAYER_API bool ULULPlayM4_UnInit();

//初始化dx（用于显示）
ULPLAYER_API bool ULPlayM4_InitDDraw(unsigned int hwnd);

//反初始化dx
ULPLAYER_API bool ULPlayM4_RealeseDDraw();

//获取解码端口
ULPLAYER_API bool ULPlayM4_GetPort(long*nPort);

//释放解码端口
ULPLAYER_API bool ULPlayM4_FreePort(long nPort);

//实时流解码:需要视频头和缓冲区大小等信息
ULPLAYER_API bool ULPlayM4_OpenStream(long nPort,byte *pFileHeadBuf,unsigned int nSize,unsigned int nBufPoolSize);

//开始播放
ULPLAYER_API bool ULPlayM4_Play(long nPort, unsigned int hWnd);

//停止播放
ULPLAYER_API bool ULPlayM4_Stop(long nPort);

//关闭实时流解码：
ULPLAYER_API bool ULPlayM4_CloseStream(long  nPort);

//塞入视频数据
ULPLAYER_API bool ULPlayM4_InputData(long nPort,byte* pBuf,unsigned int nSize);

//解码抓图，分bmp和jpg
ULPLAYER_API bool ULPlayM4_GetBMP(long nPort,byte *pBitmap,unsigned int nBufSize,unsigned int *pBmpSize);
//jpg图像可以设置图像质量（通过nQuality0-100完成)
ULPLAYER_API bool ULPlayM4_GetJPEG(long nPort,byte*pJpeg,unsigned int nBufSize,unsigned int *pJpegSize,unsigned int nQuality);

//打开文件
ULPLAYER_API bool ULPlayM4_OpenFile(long nPort,char *szFileName);

//关闭文件
ULPLAYER_API bool ULPlayM4_CloseFile(long nPort);

//画图回调。fnDraw 为NULL时不回调
ULPLAYER_API bool ULPlayM4_RegisterDrawFun(long nPort,DrawFun fnDraw,unsigned int nUser);

//获取YUV数据的回调
ULPLAYER_API bool ULPlayM4_SetDecCallBack(long nPort,DecFun fnDec,unsigned int nUser);