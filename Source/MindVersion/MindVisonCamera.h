#pragma once
#include <Windows.h>
#include "CameraApi.h"

class MindVisonCamera
{
public:
	MindVisonCamera();
	~MindVisonCamera();
	CameraHandle GetHandle();
	CameraSdkStatus CameraGetCapability();
	void CreateFramebuffer();
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


	CameraSdkStatus CameraImageProcess(unsigned char* pbyIn, unsigned char* pbyOut, tSdkFrameHead* pFrInfo);

	CameraSdkStatus CameraSnapJpegToFile(char const* lpszFileName, unsigned char byQuality, unsigned int wTimes);

	CameraSdkStatus CameraSnapToBuffer(tSdkFrameHead* pFrameInfo, unsigned char** pbyBuffer, unsigned int wTimes);

	CameraSdkStatus CameraSaveImage(char* lpszFileName, unsigned char* pbyImageBuffer, tSdkFrameHead* pFrInfo, unsigned int byFileType, unsigned char byQuality);

	CameraSdkStatus CameraSaveImageEx(char* lpszFileName, unsigned char* pbyImageBuffer, unsigned int uImageFormat, int iWidth, int iHeight, unsigned int byFileType, unsigned char byQuality);

	CameraSdkStatus CameraGetCapability(tSdkCameraCapbility* pCameraInfo);



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

public:
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


public:
	// 触发功能
	CameraSdkStatus CameraSetTriggerMode(int iModeSel);

	/*
		设置触发模式下的触发帧数。对软件触发和硬件触发模式都有效。默认为1帧，即一次触发信号采集一帧图像。 
	*/
	CameraSdkStatus CameraSetTriggerCount(int iCount);

	/*
		设置外触发信号间隔时间，默认为0，单位为微秒。
	*/
	CameraSdkStatus CameraSetExtTrigIntervalTime(unsigned int uTimeUs);

	/*
		设置相机外触发信号的消抖时间。默认为0，单位为微秒。
	*/
	CameraSdkStatus CameraSetExtTrigJitterTime(unsigned int uTimeUs);


	/*
		执行一次软触发。执行后，会触发由CameraSetTriggerCount指定的帧数。
	*/
	CameraSdkStatus CameraSoftTrigger();
	/*
		设置IO引脚端子上的STROBE信号。该信号可以做闪光灯控制，也可以做外部机械快门控制。
	*/
	CameraSdkStatus CameraSetStrobeMode(int iMode);

	/*
		当STROBE信号处于STROBE_SYNC_WITH_TRIG时，通过该函数设置其相对触发信号延时时间。 
	*/
	CameraSdkStatus CameraSetStrobeDelayTime(unsigned int uDelayTimeUs);

	/*
		当STROBE信号处于STROBE_SYNC_WITH_TRIG时，通过该函数设置其脉冲宽度。 
	*/
	CameraSdkStatus CameraSetStrobePulseWidth(unsigned int uTimeUs);


private:
	CameraHandle Handle = -1; 
public:
	tSdkCameraCapbility CameraInfo;
	unsigned int FrameBufferSize;
	unsigned char* pFrameBuffer;
	bool bMonoCamera;
};

#define CHECK_STATUS(status, str) if (status != CAMERA_STATUS_SUCCESS)		\
	{																	\
		printf("%s %d", str, status);	\
		return -1;														\
	}