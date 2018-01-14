/*******************************************************************
描述：
********************************************************************/


#ifndef _IULIRTemperatureSDK_H_
#define _IULIRTemperatureSDK_H_

#ifdef ULIRTEMPERATURESDK_EXPORTS
#define ULIRTemperatureSDK_API __declspec(dllexport)
#else
#define ULIRTemperatureSDK_API __declspec(dllimport)
#endif

typedef unsigned char byte;


//-----------------------接口函数定义-----------------------------
#ifdef __cplusplus
extern "C" {
#endif

	//将获得数据获取帧头和数据
	ULIRTemperatureSDK_API bool __stdcall Temperature_GetFrameInfo(int dwCalType,byte *pBuffer,DWORD dwBufSize,byte **pData,DWORD *dwDataSize,byte **pFrameHead,DWORD *dwHeadSize);
	ULIRTemperatureSDK_API float __stdcall Temperature_GetTempFromGray( unsigned short nGray,float fEmissivity, byte *pFrameHead,DWORD dwHeadSize,int dwCalType,float fDistance = 0);
	//ULIRTemperatureSDK_API void __stdcall temp_init();
	//ULIRTemperatureSDK_API void __stdcall temp_uninit();

	//ULIRTemperatureSDK_API void __stdcall chagedif(unsigned short *nGray,DWORD dwSize,byte*pFrameHead,DWORD dwHeadSize,int dwCalType,BOOL HANDSAVE);
	//ULIRTemperatureSDK_API void __stdcall changeGray(unsigned short *nGray,DWORD dwSize,byte*pFrameHead,DWORD dwHeadSize,int dwCalType,short &CH1,short &CH5);
	//ULIRTemperatureSDK_API void __stdcall savedifs();
	//ULIRTemperatureSDK_API void __stdcall getdifs();
	//ULIRTemperatureSDK_API void __stdcall writePointGray(WORD x,WORD y,char *szFileName);
	//ULIRTemperatureSDK_API void __stdcall writePointDif(WORD x,WORD y,char *szFileName);
	//ULIRTemperatureSDK_API void __stdcall CalGQ(unsigned short *pGrayHigh,unsigned short *pGrayLow);

	//ULIRTemperatureSDK_API BOOL __stdcall openData(char *szFileName);
	//ULIRTemperatureSDK_API BOOL __stdcall readData(BYTE **pData,DWORD &dwDataSize,BYTE **pHead,DWORD &dwHeadSize);
	//ULIRTemperatureSDK_API BOOL __stdcall closeData();
#ifdef __cplusplus
};
#endif

#endif
