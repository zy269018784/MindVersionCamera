#include "MindVisionSDK.h"
#include "CameraApi.h"
#include <stdio.h>
MindVisionSDK::MindVisionSDK()
{
    CameraSdkStatus status;

    // 1. 初始化SDK
    status = CameraSdkInit(0);
	if (status != CAMERA_STATUS_SUCCESS)
	{
		printf("CameraSdkInit failed\n");
	}


    // 2. 枚举设备，获得设备列表
    tSdkCameraDevInfo CameraList[16];
    int CameraNums = 1;
    status = CameraEnumerateDevice(CameraList, &CameraNums);
    if (status != CAMERA_STATUS_SUCCESS)
    {
        printf("No camera was found!");
        return;
    }

    // 3. 初始化相机
    status = Camera.CameraInit(&CameraList[0], -1, -1);
    if (status != CAMERA_STATUS_SUCCESS)
    {
        printf("CameraInit Error code: %d", status);
        return;
    }

    // 获得该相机的特性描述
    status = Camera.CameraGetCapability();
    if (status != CAMERA_STATUS_SUCCESS)
    {
        printf("CameraGetCapability Error code: %d", status);
        return ;
    }


    // 判断是黑白相机还是彩色相机, 黑白相机让ISP直接输出MONO数据，而不是扩展成R=G=B的24位灰度.
    bool bMonoCamera = Camera.CameraInfo.sIspCapacity.bMonoSensor;
    printf("bMonoCamera %d\n", bMonoCamera);
    if (bMonoCamera)
    {
        Camera.CameraSetIspOutFormat(CAMERA_MEDIA_TYPE_MONO8);
    }

    // 相机模式切换成连续采集
    Camera.CameraSetTriggerMode(0);

    // 手动曝光
    Camera.CameraSetAeState(FALSE);
    
    // 曝光时间
    Camera.CameraSetExposureTime(30000);

    // 创建Framebuffer
    Camera.CreateFramebuffer();
}

MindVisionSDK::~MindVisionSDK()
{
    printf("relase SDK\n");
}

CameraSdkStatus MindVisionSDK::CameraEnumerateDevice(tSdkCameraDevInfo* pCameraList, int* piNums)
{
	return ::CameraEnumerateDevice(pCameraList, piNums);
}

int MindVisionSDK::CameraEnumerateDeviceEx()
{
	return ::CameraEnumerateDeviceEx();
}