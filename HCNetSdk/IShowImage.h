//

#ifdef SHOWIMAGE_EXPORTS
#define SHOWIMAGE_API __declspec(dllexport)
#else
#define SHOWIMAGE_API __declspec(dllimport)
#endif

enum CodeType
{

	CODETYPE_IRON_BOW = 0,			//����
	CODETYPE_GREEN_RED= 1,			//�̺�
	CODETYPE_GLOW_BOW = 2,			//��ɫ
	CODETYPE_RAIN_BOW = 3,			//�ʺ�
	CODETYPE_RED_BOW = 4,			//��ɫ
	CODETYPE_HIGHCONTRAST = 5,		//��ɫ
	CODETYPE_WHITE = 6,				//
	CODETYPE_JET = 7,				//
	CODETYPE_WHITE_HOT = 8,			//����
	CODETYPE_BLACK_HOT = 9,			//����
	CODETYPE_COLOR10 = 10,			//
	CODETYPE_WINTER = 11,			//

};


typedef void (__stdcall *DrawObjFun)(short sPort,HDC hDc,LONG nUser);

//-----------------------�ӿں�������-----------------------------
#ifdef __cplusplus
extern "C" {
#endif
	//��ʼ�� ����ʼ��
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_Init();
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_Cleanup();

	//
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_GetPort(short *sPort);
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_FreePort(short sPort);

	//���á���ȡɫ��ID
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_SetColorCode(short sPort, DWORD dwCodeType);
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_GetColorCode(short sPort, DWORD *dwCodeType);

	//���õ���ɫ״̬
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_SetIsoState(short sPort, BOOL bShow);
	//��ȡ����ɫ״̬
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_GetIsoState(short sPort, BOOL *bShow);

	//���õ���ɫ��ɫ
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_SetIsoColor(short sPort, COLORREF color);
	//��ȡ��������ɫ
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_GetIsoColor(short sPort, COLORREF *color);

	//���õ���ɫ �¶�������  
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_SetIsoTemp(short sPort, float fTempUp, float fTempDown);
	//��ȡ����ɫ �¶�������  
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_GetIsoTemp(short sPort, float *fTempUp, float *fTempDown);

	//������ʾ���ھ��
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_SetShowImageWnd(short sPort, HWND hwnd);

	/* ���û�ͼ���� dwPptIndex > -1 || dwPptIndex < 255 */
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_SetObjectMessage(short sPort, char* szObjectMessage);

	//����ͼ����
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_SetImageSize(short sPort, int iWidth, int iHeight);

	//��ʾ��ͼ
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_ShowImage(short sPort, BYTE *pBuffer, DWORD nBufferLen, float fMaxTemp, float fMinTemp,DWORD dwZoom = 1);
	//��ʾ��ͼ2
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_ShowImage2(short sPort, BYTE *pBuffer, DWORD nBufferLen, float fMaxTemp, float fMinTemp,HDC &hMemDC,DWORD dwZoom = 1);
	
	//������ʾ�ص�����Ҫ����������
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_RegisterDrawFun(short sPort,DrawObjFun pDrawFun,LONG nUser);

	//
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_Refrash(short sPort);

	//������ʾɫ�괰�ھ��
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_SetColorBarWnd(short sPort, HWND hwnd);
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_SetColorBarState(short sPort, BOOL bShow);
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_ShowColorBar(short sPort);

	//¼��
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_StartRecordAVI(short sPort,char *szPath);
	SHOWIMAGE_API BOOL __stdcall SHOWIMAGE_StopRecordAVI(short sPort);

	//��ȡ������Ϣ
	SHOWIMAGE_API LONG __stdcall SHOWIMAGE_GetLastError();
	SHOWIMAGE_API char* __stdcall SHOWIMAGE_GetErrorMsg(LONG *pErrorNo);

#ifdef __cplusplus
}
#endif


