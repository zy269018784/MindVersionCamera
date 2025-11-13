#include "HIKCamera.h"
#include "HIKSDK.h"
#include <stdio.h>
#include <vector>
#include <memory>
int HIKCameraMain(int argc, char** argv)
{
    HIKSDK SDK;

    MV_CC_DEVICE_INFO_LIST stDeviceList = { 0 };
    int nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDeviceList);
    if (MV_OK == nRet)
    { 
        std::vector<std::unique_ptr<HIKCamera>> Cameras(stDeviceList.nDeviceNum);
        for (unsigned int i = 0; i < stDeviceList.nDeviceNum; i++)
        {
            MV_CC_DEVICE_INFO* pDeviceInfo = stDeviceList.pDeviceInfo[i];
            Cameras[i].reset(new HIKCamera(pDeviceInfo));
            Cameras[i]->MV_CC_OpenDevice();
            if (pDeviceInfo->nTLayerType == MV_GIGE_DEVICE)
            {
                MV_GIGE_DEVICE_INFO* pGigEInfo = (MV_GIGE_DEVICE_INFO*)pDeviceInfo;
                printf("GigE device\n");
                printf("\tIP:\t%u.%u.%u.%u\n", ((pGigEInfo->nCurrentIp >> 0) & 0xFF), ((pGigEInfo->nCurrentIp >> 8) & 0xFF), ((pGigEInfo->nCurrentIp >> 16) & 0xFF), ((pGigEInfo->nCurrentIp >> 24) & 0xFF));
                printf("\tSubNetMask:\t%u\n", pGigEInfo->nCurrentSubNetMask);
                printf("\tManufacturerName:\t%s\n", pGigEInfo->chManufacturerName);
                printf("\tchModelName:\t%s\n", pGigEInfo->chModelName);
                printf("\tchDeviceVersion:\t%s\n", pGigEInfo->chDeviceVersion);
                printf("\tchSerialNumber:\t%s\n", pGigEInfo->chSerialNumber);
                printf("\tchUserDefinedName:\t%s\n", pGigEInfo->chUserDefinedName);
            }
            else if (pDeviceInfo->nTLayerType == MV_USB_DEVICE)
            {

            }
        }
        
        MVCC_INTVALUE_EX stIntEx  = {0}; 
        nRet = Cameras[0]->MV_CC_GetIntValueEx("Width", &stIntEx);
        printf("Width %d\n", stIntEx.nCurValue);
        nRet = Cameras[0]->MV_CC_GetIntValueEx("Height", &stIntEx);
        printf("Height %d\n", stIntEx.nCurValue);
        return 0;
        Cameras[0]->TriggerModeOn();
        Cameras[0]->MV_CC_StartGrabbing();
        Cameras[0]->MV_CC_StopGrabbing();
    }

    return 0;
}