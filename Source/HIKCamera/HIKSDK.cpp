#include "MvCameraControl.h"
#include "HIKSDK.h"
#include <stdio.h>
HIKSDK::HIKSDK()
{
    int Ret = MV_CC_Initialize();
    if (MV_OK != Ret)
    {
        printf("Initialize SDK fail! nRet [0x%x]\n", Ret);
    }
}

HIKSDK::~HIKSDK()
{
    int Ret = MV_CC_Finalize();
    if (MV_OK != Ret)
    {
        printf("Finalize SDK fail! nRet [0x%x]\n", Ret);
    }
}

int HIKSDK::MV_CC_EnumDevices(unsigned int nTLayerType, MV_CC_DEVICE_INFO_LIST* pstDevList)
{
    return ::MV_CC_EnumDevices(nTLayerType, pstDevList);
}
