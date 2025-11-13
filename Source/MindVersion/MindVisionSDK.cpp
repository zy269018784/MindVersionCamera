#include "MindVisionSDK.h"
#include "CameraApi.h"
#include <stdio.h>
MindVisionSDK::MindVisionSDK()
{
	int ret = CameraSdkInit(0);
	if (ret != CAMERA_STATUS_SUCCESS)
	{
		printf("CameraSdkInit failed\n");
	}
}

MindVisionSDK::~MindVisionSDK()
{

}

CameraSdkStatus MindVisionSDK::CameraEnumerateDevice(tSdkCameraDevInfo* pCameraList, int* piNums)
{
	return ::CameraEnumerateDevice(pCameraList, piNums);
}

int MindVisionSDK::CameraEnumerateDeviceEx()
{
	return ::CameraEnumerateDeviceEx();
}