
#ifndef _ULIRTEMPSDK_H_
#define _ULIRTEMPSDK_H_
#endif
#ifdef ULIRTEMPSDK_EXPORTS
#define ULIRTEMPSDK_API __declspec(dllexport)
#else
#define ULIRTEMPSDK_API  __declspec(dllimport)
#endif

typedef unsigned char byte;

typedef struct
{
	int nLensID;					// 镜头ID 
	int nClassMinTemp;				// 测温档最低温
	int nClassMaxTemp;				// 测温档最高温
	int nDistance100;				// 距离的100倍
	int nHumidity100;				// 环境湿度100倍
	int nAmbientTempManu100;			//环境温度100倍
	unsigned char nGpsEnable;					//GPS使能标记
	unsigned nGpsLatitude[40];				//GPS纬度
	unsigned nGpsLongitude[40];				//GPS经度
	int nReserve[20];				//预留位
}UlirUserTempPara;

typedef float(*Gray2Temp_Init_Back)(int nGray,float fEmissity, float fDistance,char* pAlgBuffer);
typedef float(*Gray2Temp_Real_Back)(int nGray,float fEmissity, float fDistance,char* pAlgBuffer);
typedef double(*GetIT_Back)(char* pAlgBuffer);

#define ULIRTEMPSDK_DLL
//-----------------------接口函数定义-----------------------------
#ifdef ULIRTEMPSDK_DLL
#ifdef __cplusplus
extern "C" {
#endif
ULIRTEMPSDK_API void __stdcall Temperature_GetVersion(char* cVersion); //获取版本号
ULIRTEMPSDK_API int __stdcall Temperature_IsAlgSurport(int nCalType); //判断是否支持该算法号
ULIRTEMPSDK_API float __stdcall Temperature_Gray2Temp_Once(int nCalType,int nGray,float fEmissity, unsigned char* pBuffer, unsigned long BufferSize, float fDistance); //灰度转温度
ULIRTEMPSDK_API int __stdcall Temperature_GetTempPara(int nCalType, unsigned char* pBuffer, unsigned long BufferSize, UlirUserTempPara *para);//获取用户需要的参数
ULIRTEMPSDK_API Gray2Temp_Init_Back __stdcall Temperature_Gray2Temp_Init_Get(int nAlgType);
ULIRTEMPSDK_API Gray2Temp_Real_Back __stdcall Temperature_Gray2Temp_Real_Get(int nAlgType);
ULIRTEMPSDK_API int __stdcall Temperature_Temp2Gray(Gray2Temp_Real_Back gray2temp_realtime, char *pTempPara, float fEmissivity,
					int nMinTemp100, int nMaxTemp100, int nMinGray, int nMaxGray, int nTemp100);
#ifdef __cplusplus
}
#endif

#else
#ifdef __cplusplus
extern "C" {
#endif
	void Temperature_GetVersion(char* cVersion); //获取版本号
	int Temperature_IsAlgSurport(int nCalType); //判断是否支持该算法号
    float Temperature_Gray2Temp_Once(int nCalType,int nGray,float fEmissity, unsigned char* pBuffer, unsigned long BufferSize, float fDistance); //灰度转温度
	int Temperature_GetTempPara(int nCalType, unsigned char* pBuffer, unsigned long BufferSize, UlirUserTempPara *para);//获取用户需要的参数
	Gray2Temp_Init_Back Temperature_Gray2Temp_Init_Get(int nAlgType);
	Gray2Temp_Real_Back Temperature_Gray2Temp_Real_Get(int nAlgType);
	int Temperature_Temp2Gray(Gray2Temp_Real_Back gray2temp_realtime, char *pTempPara, float fEmissivity,
					int nMinTemp100, int nMaxTemp100, int nMinGray, int nMaxGray, int nTemp100);
#ifdef __cplusplus
};
#endif
#endif

