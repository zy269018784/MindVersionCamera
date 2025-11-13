#pragma once
#include <Windows.h>
#include "CameraApi.h"

class MindVisonCamera
{
public:
	MindVisonCamera();
	~MindVisonCamera();
public:
	CameraSdkStatus CameraInit(tSdkCameraDevInfo* pCameraInfo, int emParamLoadMode, int emTeam);
	CameraSdkStatus CameraInitEx(int iDeviceIndex, int emParamLoadMode, int emTeam);
	CameraSdkStatus CameraInitEx2(char* CameraName);
	CameraSdkStatus  CameraUnInit();
	CameraSdkStatus CameraSetCallbackFunction(CAMERA_SNAP_PROC pCallBack, PVOID pContext, CAMERA_SNAP_PROC* pCallbackOld);

	CameraSdkStatus CameraPlay();
	CameraSdkStatus CameraStop();
	CameraSdkStatus CameraPause();

	CameraSdkStatus CameraClearBuffer();
	CameraSdkStatus CameraGetImageBuffer(tSdkFrameHead* pFrameInfo, unsigned char** pbyBuffer, unsigned int wTimes);

	CameraSdkStatus CameraGetImageBufferPriority(tSdkFrameHead* pFrameInfo, unsigned char** pbyBuffer, unsigned int wTimes, unsigned int Priority);

	CameraSdkStatus CameraReleaseImageBuffer(unsigned char* pbyBuffer);

	CameraSdkStatus CameraSnapJpegToFile(char const* lpszFileName, unsigned char byQuality, unsigned int wTimes);

	CameraSdkStatus CameraSnapToBuffer(tSdkFrameHead* pFrameInfo, unsigned char** pbyBuffer, unsigned int wTimes);
private:
	CameraHandle Handle = -1; 
};