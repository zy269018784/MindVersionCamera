#pragma once
#include "MvCameraControl.h"

class HIKCamera
{
public:
	HIKCamera(const MV_CC_DEVICE_INFO* pDeviceInfo);
	~HIKCamera();
public:
	int TriggerModeOn();
	int TriggerModeOff();
public:
	int MV_CC_CreateHandle(const MV_CC_DEVICE_INFO* pDeviceInfo);
	int MV_CC_DestroyHandle();
	int MV_CC_OpenDevice(unsigned int nAccessMode = MV_ACCESS_Exclusive, unsigned short nSwitchoverKey = 0);
	int MV_CC_CloseDevice();
	int MV_CC_StartGrabbing();
	int MV_CC_StopGrabbing();
	int MV_CC_GetIntValueEx(const char* strKey, MVCC_INTVALUE_EX* pstIntValue);
	int MV_CC_SetIntValueEx(const char* strKey, int64_t nValue);
	int MV_CC_GetEnumValue(const char* strKey, MVCC_ENUMVALUE* pstEnumValue);	
	int MV_CC_GetEnumValueEx(const char* strKey, MVCC_ENUMVALUE_EX* pstEnumValue);
	int MV_CC_SetEnumValue(const char* strKey, unsigned int nValue);
	int MV_CC_GetFloatValue(const char* strKey, MVCC_FLOATVALUE* pstFloatValue);
	int MV_CC_SetFloatValue(const char* strKey, float fValue);
	int MV_CC_GetBoolValue(const char* strKey, bool* pbValue);
	int MV_CC_SetBoolValue(const char* strKey, bool bValue);
	int MV_CC_GetStringValue(const char* strKey, MVCC_STRINGVALUE* pstStringValue);
	int MV_CC_SetStringValue(const char* strKey, const char* strValue);
	int MV_CC_SetCommandValue(const char* strKey);
private:
	void* Handle;
};