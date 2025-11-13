#include "MvCameraControl.h"
#include "HIKCamera.h"
#include <stdio.h>
HIKCamera::HIKCamera(const MV_CC_DEVICE_INFO* pDeviceInfo)
{
    int Ret = 0;
    Ret = MV_CC_CreateHandle(pDeviceInfo);
    if (MV_OK != Ret)
    {
        printf("CreateHandle fail! nRet [0x%x]\n", Ret);
    }
    //Ret = MV_CC_OpenDevice();
    //if (MV_OK != Ret)
    //{
    //    printf("OpenDevice fail! nRet [0x%x]\n", Ret);
    //}
}

HIKCamera::~HIKCamera()
{
    int Ret = 0;    
    Ret = MV_CC_CloseDevice();
    if (MV_OK != Ret)
    {
        printf("CloseDevice fail! nRet [0x%x]\n", Ret);
    }
    Ret = MV_CC_DestroyHandle();
    if (MV_OK != Ret)
    {
        printf("DestroyHandle fail! nRet [0x%x]\n", Ret);
    }
}

int HIKCamera::TriggerModeOn()
{
    return MV_CC_SetEnumValue("TriggerMode", MV_TRIGGER_MODE_ON);
}

int HIKCamera::TriggerModeOff()
{
    return MV_CC_SetEnumValue("TriggerMode", MV_TRIGGER_MODE_OFF);
}

int HIKCamera::MV_CC_CreateHandle(const MV_CC_DEVICE_INFO* pDeviceInfo)
{
    return ::MV_CC_CreateHandle(&Handle, pDeviceInfo);
}

int HIKCamera::MV_CC_DestroyHandle()
{
    return ::MV_CC_DestroyHandle(Handle);
}

int HIKCamera::MV_CC_OpenDevice(unsigned int nAccessMode, unsigned short nSwitchoverKey)
{
    return ::MV_CC_OpenDevice(Handle, nAccessMode, nSwitchoverKey);
}

int HIKCamera::MV_CC_CloseDevice()
{
    return ::MV_CC_CloseDevice(Handle);
}

int HIKCamera::MV_CC_StartGrabbing()
{
    return ::MV_CC_StartGrabbing(Handle);
}

int HIKCamera::MV_CC_StopGrabbing()
{
    return ::MV_CC_StopGrabbing(Handle);
}

int HIKCamera::MV_CC_GetIntValueEx(const char* strKey, MVCC_INTVALUE_EX* pstIntValue)
{
    return ::MV_CC_GetIntValueEx(Handle, strKey, pstIntValue);
}

int HIKCamera::MV_CC_SetIntValueEx(const char* strKey, int64_t nValue)
{
    return ::MV_CC_SetIntValueEx(Handle, strKey, nValue);
}

int HIKCamera::MV_CC_GetEnumValue(const char* strKey, MVCC_ENUMVALUE* pstEnumValue)
{
    return ::MV_CC_GetEnumValue(Handle, strKey, pstEnumValue);
}

int HIKCamera::MV_CC_GetEnumValueEx(const char* strKey, MVCC_ENUMVALUE_EX* pstEnumValue)
{
    return ::MV_CC_GetEnumValueEx(Handle, strKey, pstEnumValue);
}

int HIKCamera::MV_CC_SetEnumValue(const char* strKey, unsigned int nValue)
{
    return ::MV_CC_SetEnumValue(Handle, strKey, nValue);
}

int HIKCamera::MV_CC_GetFloatValue(const char* strKey, MVCC_FLOATVALUE* pstFloatValue)
{
    return ::MV_CC_GetFloatValue(Handle, strKey, pstFloatValue);
}

int HIKCamera::MV_CC_SetFloatValue(const char* strKey, float fValue)
{
    return ::MV_CC_SetFloatValue(Handle, strKey, fValue);
}

int HIKCamera::MV_CC_GetBoolValue(const char* strKey, bool* pbValue)
{
    return ::MV_CC_GetBoolValue(Handle, strKey, pbValue);
}

int HIKCamera::MV_CC_SetBoolValue(const char* strKey, bool bValue)
{
    return ::MV_CC_SetBoolValue(Handle, strKey, bValue);
}

int HIKCamera::MV_CC_GetStringValue(const char* strKey, MVCC_STRINGVALUE* pstStringValue)
{
    return ::MV_CC_GetStringValue(Handle, strKey, pstStringValue);
}

int HIKCamera::MV_CC_SetStringValue(const char* strKey, const char* strValue)
{
    return ::MV_CC_SetStringValue(Handle, strKey, strValue);
}

int HIKCamera::MV_CC_SetCommandValue(const char* strKey)
{
    return ::MV_CC_SetCommandValue(Handle, strKey);
}