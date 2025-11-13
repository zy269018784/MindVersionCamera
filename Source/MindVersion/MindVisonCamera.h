#pragma once
#include <Windows.h>
#include "CameraApi.h"

class MindVisonCamera
{
public:
	MindVisonCamera();
	~MindVisonCamera();
	CameraHandle GetHandle();
public:
	CameraSdkStatus CameraInit(tSdkCameraDevInfo* pCameraInfo, int emParamLoadMode, int emTeam);
	CameraSdkStatus CameraInitEx(int iDeviceIndex, int emParamLoadMode, int emTeam);
	CameraSdkStatus CameraInitEx2(char* CameraName);
	CameraSdkStatus  CameraUnInit();
	
	CameraSdkStatus CameraPlay();
	CameraSdkStatus CameraStop();
	CameraSdkStatus CameraPause();

	CameraSdkStatus CameraClearBuffer();
	CameraSdkStatus CameraGetImageBuffer(tSdkFrameHead* pFrameInfo, unsigned char** pbyBuffer, unsigned int wTimes);

	CameraSdkStatus CameraGetImageBufferPriority(tSdkFrameHead* pFrameInfo, unsigned char** pbyBuffer, unsigned int wTimes, unsigned int Priority);

	CameraSdkStatus CameraReleaseImageBuffer(unsigned char* pbyBuffer);

	CameraSdkStatus CameraSnapJpegToFile(char const* lpszFileName, unsigned char byQuality, unsigned int wTimes);

	CameraSdkStatus CameraSnapToBuffer(tSdkFrameHead* pFrameInfo, unsigned char** pbyBuffer, unsigned int wTimes);

	/*
		设置图像的黑电平基准，默认值为0 
	*/
	CameraSdkStatus CameraSetBlackLevel(int iBlackLevel);

	/*
		设置图像的白电平基准，默认值为255 
	*/
	CameraSdkStatus CameraSetWhiteLevel(int iWhiteLevel);

	/*
		设置CameraImageProcess函数的图像处理的输出格式。
	*/
	CameraSdkStatus CameraSetIspOutFormat(unsigned int uFormat);

	/*
		设置Bayer数据转彩色的算法。
	*/
	CameraSdkStatus CameraSetBayerDecAlgorithm(int iIspProcessor, int iAlgorithmSel);

	/*
		设置图像捕获的回调函数。当捕获到新的图像数据帧时，pCallBack所指向的回调函数就会被调用。
	*/
	CameraSdkStatus CameraSetCallbackFunction(CAMERA_SNAP_PROC pCallBack, PVOID pContext, CAMERA_SNAP_PROC* pCallbackOld);

	/*
		设置图像捕获的回调函数。当捕获到新的图像数据帧时，pCallBack所指向的回调函数就会被调用。
	*/
	CameraSdkStatus CameraSetCallbackFunctionEx(CAMERA_SNAP_PROC pCallBack, PVOID pContext, CAMERA_SNAP_PROC* pCallbackOld, unsigned int uFlags);

	/*
		设置显示的模式。
	*/
	CameraSdkStatus CameraSetDisplayMode(int iMode);

	/*
		设置显示的起始偏移值。
	*/
	CameraSdkStatus CameraSetDisplayOffset(int iOffsetX, int iOffsetY);

	/*
		设置显示控件的尺寸。
	*/
	CameraSdkStatus CameraSetDisplaySize(int iWidth, int iHeight);

	// 曝光增益API
	/*
		设置相机曝光的模式。自动或者手动。
	*/
	CameraSdkStatus CameraSetAeState(bool bAeState);

	/*
		设置曝光时间。单位为微秒。 
	*/
	CameraSdkStatus CameraSetExposureTime(double fExposureTime);

	/*
		设定自动曝光的亮度目标值。
	*/
	CameraSdkStatus CameraSetAeTarget(int iAeTarget);

	/*
		设定自动曝光模式的增益调节范围
	*/
	CameraSdkStatus CameraSetAeAnalogGainRange(int iMinAnalogGain, int iMaxAnalogGain);

	/*
		设定自动曝光模式的曝光时间调节范围 
	*/
	CameraSdkStatus CameraSetAeExposureRange(double fMinExposureTime, double fMaxExposureTime);

	/*
		设置自动曝光模式的调节阈值 
	*/
	CameraSdkStatus CameraSetAeThreshold(int iThreshold);

	/*
		设置自动曝光的参考窗口。 
	*/
	CameraSdkStatus CameraSetAeWindow(int iHOff, int iVOff, int iWidth, int iHeight);

	/*
		设置相机的图像模拟增益值。 
	*/
	CameraSdkStatus CameraSetAnalogGain(int iAnalogGain);

	/*
		设置相机的模拟增益放大倍数。
	*/
	CameraSdkStatus CameraSetAnalogGainX(float fGain);

	/*
		设置自动曝光时消频闪的频率。 
	*/
	CameraSdkStatus CameraSetLightFrequency(int iFrequencySel);


private:
	CameraHandle Handle = -1; 
};

#define CHECK_STATUS(status, str) if (status != CAMERA_STATUS_SUCCESS)		\
	{																	\
		printf("%s %d", str, status);	\
		return -1;														\
	}