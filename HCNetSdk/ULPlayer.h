//��һ��
//ֻ���������ڵ���ʾ������YUV�ص�
//ֻ��ʵʱ��Ƶ���룬������ʷ�ļ�����


#ifdef ULPLAYER_EXPORTS
#define ULPLAYER_API extern "C" __declspec(dllexport)
#else
#define ULPLAYER_API extern "C" __declspec(dllimport)
#endif

//��ͼ�ص�����
typedef void(CALLBACK *DrawFun)(long nPort,HDC hDc,unsigned int nUser);
//����ص�����,��Ҫ���ã������Լ���ʾ����������Y���ݷ����ĻҶȷ���
//����˿ڣ������YUV����(yuv420)������yuv����ֵ��yuv���ݸ��Դ�С���û�����
typedef void(CALLBACK *DecFun)(long nPort,unsigned int iDecodeDataType,byte *pData[3],unsigned int iWidth,unsigned int iHeight,unsigned int nUser);

//��ʼ��sdk
ULPLAYER_API bool ULPlayM4_Init();

//����ʼ��sdk
ULPLAYER_API bool ULULPlayM4_UnInit();

//��ʼ��dx��������ʾ��
ULPLAYER_API bool ULPlayM4_InitDDraw(unsigned int hwnd);

//����ʼ��dx
ULPLAYER_API bool ULPlayM4_RealeseDDraw();

//��ȡ����˿�
ULPLAYER_API bool ULPlayM4_GetPort(long*nPort);

//�ͷŽ���˿�
ULPLAYER_API bool ULPlayM4_FreePort(long nPort);

//ʵʱ������:��Ҫ��Ƶͷ�ͻ�������С����Ϣ
ULPLAYER_API bool ULPlayM4_OpenStream(long nPort,byte *pFileHeadBuf,unsigned int nSize,unsigned int nBufPoolSize);

//��ʼ����
ULPLAYER_API bool ULPlayM4_Play(long nPort, unsigned int hWnd);

//ֹͣ����
ULPLAYER_API bool ULPlayM4_Stop(long nPort);

//�ر�ʵʱ�����룺
ULPLAYER_API bool ULPlayM4_CloseStream(long  nPort);

//������Ƶ����
ULPLAYER_API bool ULPlayM4_InputData(long nPort,byte* pBuf,unsigned int nSize);

//����ץͼ����bmp��jpg
ULPLAYER_API bool ULPlayM4_GetBMP(long nPort,byte *pBitmap,unsigned int nBufSize,unsigned int *pBmpSize);
//jpgͼ���������ͼ��������ͨ��nQuality0-100���)
ULPLAYER_API bool ULPlayM4_GetJPEG(long nPort,byte*pJpeg,unsigned int nBufSize,unsigned int *pJpegSize,unsigned int nQuality);

//���ļ�
ULPLAYER_API bool ULPlayM4_OpenFile(long nPort,char *szFileName);

//�ر��ļ�
ULPLAYER_API bool ULPlayM4_CloseFile(long nPort);

//��ͼ�ص���fnDraw ΪNULLʱ���ص�
ULPLAYER_API bool ULPlayM4_RegisterDrawFun(long nPort,DrawFun fnDraw,unsigned int nUser);

//��ȡYUV���ݵĻص�
ULPLAYER_API bool ULPlayM4_SetDecCallBack(long nPort,DecFun fnDec,unsigned int nUser);