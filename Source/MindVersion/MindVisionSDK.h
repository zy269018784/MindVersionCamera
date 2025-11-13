#pragma once
#include <Windows.h>
#include "CameraApi.h"

class MindVisionSDK
{
public:
	MindVisionSDK();
	~MindVisionSDK();
public:
	CameraSdkStatus CameraEnumerateDevice(tSdkCameraDevInfo* pCameraList, int* piNums);
	int  CameraEnumerateDeviceEx();


};