
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
	int nLensID;					// ��ͷID 
	int nClassMinTemp;				// ���µ������
	int nClassMaxTemp;				// ���µ������
	int nDistance100;				// �����100��
	int nHumidity100;				// ����ʪ��100��
	int nAmbientTempManu100;			//�����¶�100��
	unsigned char nGpsEnable;					//GPSʹ�ܱ��
	unsigned nGpsLatitude[40];				//GPSγ��
	unsigned nGpsLongitude[40];				//GPS����
	int nReserve[20];				//Ԥ��λ
}UlirUserTempPara;

typedef float(*Gray2Temp_Init_Back)(int nGray,float fEmissity, float fDistance,char* pAlgBuffer);
typedef float(*Gray2Temp_Real_Back)(int nGray,float fEmissity, float fDistance,char* pAlgBuffer);
typedef double(*GetIT_Back)(char* pAlgBuffer);

#define ULIRTEMPSDK_DLL
//-----------------------�ӿں�������-----------------------------
#ifdef ULIRTEMPSDK_DLL
#ifdef __cplusplus
extern "C" {
#endif
ULIRTEMPSDK_API void __stdcall Temperature_GetVersion(char* cVersion); //��ȡ�汾��
ULIRTEMPSDK_API int __stdcall Temperature_IsAlgSurport(int nCalType); //�ж��Ƿ�֧�ָ��㷨��
ULIRTEMPSDK_API float __stdcall Temperature_Gray2Temp_Once(int nCalType,int nGray,float fEmissity, unsigned char* pBuffer, unsigned long BufferSize, float fDistance); //�Ҷ�ת�¶�
ULIRTEMPSDK_API int __stdcall Temperature_GetTempPara(int nCalType, unsigned char* pBuffer, unsigned long BufferSize, UlirUserTempPara *para);//��ȡ�û���Ҫ�Ĳ���
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
	void Temperature_GetVersion(char* cVersion); //��ȡ�汾��
	int Temperature_IsAlgSurport(int nCalType); //�ж��Ƿ�֧�ָ��㷨��
    float Temperature_Gray2Temp_Once(int nCalType,int nGray,float fEmissity, unsigned char* pBuffer, unsigned long BufferSize, float fDistance); //�Ҷ�ת�¶�
	int Temperature_GetTempPara(int nCalType, unsigned char* pBuffer, unsigned long BufferSize, UlirUserTempPara *para);//��ȡ�û���Ҫ�Ĳ���
	Gray2Temp_Init_Back Temperature_Gray2Temp_Init_Get(int nAlgType);
	Gray2Temp_Real_Back Temperature_Gray2Temp_Real_Get(int nAlgType);
	int Temperature_Temp2Gray(Gray2Temp_Real_Back gray2temp_realtime, char *pTempPara, float fEmissivity,
					int nMinTemp100, int nMaxTemp100, int nMinGray, int nMaxGray, int nTemp100);
#ifdef __cplusplus
};
#endif
#endif

