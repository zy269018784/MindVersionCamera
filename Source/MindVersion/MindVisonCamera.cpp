#include "MindVisonCamera.h"
#include <stdio.h>
MindVisonCamera::MindVisonCamera()
{
	
}

MindVisonCamera::~MindVisonCamera()
{  
    printf("relase framebuffer\n");
    // 释放Framebuffer
    CameraAlignFree(pFrameBuffer);

    CameraStop();

    CameraUnInit();
}

CameraHandle MindVisonCamera::GetHandle()
{
    return Handle;
}

CameraSdkStatus MindVisonCamera::CameraGetCapability()
{
    CameraSdkStatus ret = CameraGetCapability(&CameraInfo);
    bMonoCamera =CameraInfo.sIspCapacity.bMonoSensor;
    FrameBufferSize = CameraInfo.sResolutionRange.iWidthMax * CameraInfo.sResolutionRange.iHeightMax * (bMonoCamera ? 1 : 3);
    return ret;
}

void MindVisonCamera::CreateFramebuffer()
{
    pFrameBuffer = (unsigned char*)CameraAlignMalloc(FrameBufferSize, 16);
}

// 相机初始化相关
CameraSdkStatus MindVisonCamera::CameraInit(tSdkCameraDevInfo* pCameraInfo, int emParamLoadMode, int emTeam)
{
    return ::CameraInit(pCameraInfo, emParamLoadMode, emTeam, &Handle);
}

CameraSdkStatus MindVisonCamera::CameraInitEx(int iDeviceIndex, int emParamLoadMode, int emTeam)
{
    return ::CameraInitEx(iDeviceIndex, emParamLoadMode, emTeam, &Handle);
}

CameraSdkStatus MindVisonCamera::CameraInitEx2(char* CameraName)
{
    return ::CameraInitEx2(CameraName, &Handle);
}

CameraSdkStatus MindVisonCamera::CameraUnInit()
{
    return ::CameraUnInit(Handle);
}

// 相机控制相关
CameraSdkStatus MindVisonCamera::CameraPlay()
{
    return ::CameraPlay(Handle);
}

CameraSdkStatus MindVisonCamera::CameraStop()
{
    return ::CameraStop(Handle);
}

CameraSdkStatus MindVisonCamera::CameraPause()
{
    return ::CameraPause(Handle);
}

// 图像缓冲区相关
CameraSdkStatus MindVisonCamera::CameraClearBuffer()
{
    return ::CameraClearBuffer(Handle);
}

CameraSdkStatus MindVisonCamera::CameraGetImageBuffer(tSdkFrameHead* pFrameInfo, unsigned char** pbyBuffer, unsigned int wTimes)
{
    return ::CameraGetImageBuffer(Handle, pFrameInfo, pbyBuffer, wTimes);
}

CameraSdkStatus MindVisonCamera::CameraGetImageBufferPriority(tSdkFrameHead* pFrameInfo, unsigned char** pbyBuffer, unsigned int wTimes, unsigned int Priority)
{
    return ::CameraGetImageBufferPriority(Handle, pFrameInfo, pbyBuffer, wTimes, Priority);
}

CameraSdkStatus MindVisonCamera::CameraReleaseImageBuffer(unsigned char* pbyBuffer)
{
    return ::CameraReleaseImageBuffer(Handle, pbyBuffer);
}

// 图像处理相关
CameraSdkStatus MindVisonCamera::CameraImageProcess(unsigned char* pbyIn, unsigned char* pbyOut, tSdkFrameHead* pFrInfo)
{
    return ::CameraImageProcess(Handle, pbyIn, pbyOut, pFrInfo);
}

CameraSdkStatus MindVisonCamera::CameraSnapJpegToFile(char const* lpszFileName, unsigned char byQuality, unsigned int wTimes)
{
    return ::CameraSnapJpegToFile(Handle, lpszFileName, byQuality, wTimes);
}

CameraSdkStatus MindVisonCamera::CameraSnapToBuffer(tSdkFrameHead* pFrameInfo, unsigned char** pbyBuffer, unsigned int wTimes)
{
    return ::CameraSnapToBuffer(Handle, pFrameInfo, pbyBuffer, wTimes);
}

CameraSdkStatus MindVisonCamera::CameraSaveImage(char* lpszFileName, unsigned char* pbyImageBuffer, tSdkFrameHead* pFrInfo, unsigned int byFileType, unsigned char byQuality)
{
    return ::CameraSaveImage(Handle, lpszFileName, pbyImageBuffer, pFrInfo, byFileType, byQuality);
}

CameraSdkStatus MindVisonCamera::CameraSaveImageEx(char* lpszFileName, unsigned char* pbyImageBuffer, unsigned int uImageFormat, int iWidth, int iHeight, unsigned int byFileType, unsigned char byQuality)
{
    return ::CameraSaveImageEx(Handle, lpszFileName, pbyImageBuffer, uImageFormat, iWidth, iHeight, byFileType, byQuality);
}

CameraSdkStatus MindVisonCamera::CameraGetCapability(tSdkCameraCapbility* pCameraInfo)
{
    return ::CameraGetCapability(Handle, pCameraInfo);
}

// 图像参数设置
CameraSdkStatus MindVisonCamera::CameraSetBlackLevel(int iBlackLevel)
{
    return ::CameraSetBlackLevel(Handle, iBlackLevel);
}

CameraSdkStatus MindVisonCamera::CameraSetWhiteLevel(int iWhiteLevel)
{
    return ::CameraSetWhiteLevel(Handle, iWhiteLevel);
}

CameraSdkStatus MindVisonCamera::CameraSetIspOutFormat(unsigned int uFormat)
{
    return ::CameraSetIspOutFormat(Handle, uFormat);
}

CameraSdkStatus MindVisonCamera::CameraSetBayerDecAlgorithm(int iIspProcessor, int iAlgorithmSel)
{
    return ::CameraSetBayerDecAlgorithm(Handle, iIspProcessor, iAlgorithmSel);
}

// 回调函数设置
CameraSdkStatus MindVisonCamera::CameraSetCallbackFunction(CAMERA_SNAP_PROC pCallBack, PVOID pContext, CAMERA_SNAP_PROC* pCallbackOld)
{
    return ::CameraSetCallbackFunction(Handle, pCallBack, pContext, pCallbackOld);
}

CameraSdkStatus MindVisonCamera::CameraSetCallbackFunctionEx(CAMERA_SNAP_PROC pCallBack, PVOID pContext, CAMERA_SNAP_PROC* pCallbackOld, unsigned int uFlags)
{
    return ::CameraSetCallbackFunctionEx(Handle, pCallBack, pContext, pCallbackOld, uFlags);
}

// 显示设置
CameraSdkStatus MindVisonCamera::CameraSetDisplayMode(int iMode)
{
    return ::CameraSetDisplayMode(Handle, iMode);
}

CameraSdkStatus MindVisonCamera::CameraSetDisplayOffset(int iOffsetX, int iOffsetY)
{
    return ::CameraSetDisplayOffset(Handle, iOffsetX, iOffsetY);
}

CameraSdkStatus MindVisonCamera::CameraSetDisplaySize(int iWidth, int iHeight)
{
    return ::CameraSetDisplaySize(Handle, iWidth, iHeight);
}

// 曝光增益API
CameraSdkStatus MindVisonCamera::CameraSetAeState(bool bAeState)
{
    return ::CameraSetAeState(Handle, bAeState);
}

CameraSdkStatus MindVisonCamera::CameraSetExposureTime(double fExposureTime)
{
    return ::CameraSetExposureTime(Handle, fExposureTime);
}

CameraSdkStatus MindVisonCamera::CameraSetAeTarget(int iAeTarget)
{
    return ::CameraSetAeTarget(Handle, iAeTarget);
}

CameraSdkStatus MindVisonCamera::CameraSetAeAnalogGainRange(int iMinAnalogGain, int iMaxAnalogGain)
{
    return ::CameraSetAeAnalogGainRange(Handle, iMinAnalogGain, iMaxAnalogGain);
}

CameraSdkStatus MindVisonCamera::CameraSetAeExposureRange(double fMinExposureTime, double fMaxExposureTime)
{
    return ::CameraSetAeExposureRange(Handle, fMinExposureTime, fMaxExposureTime);
}

CameraSdkStatus MindVisonCamera::CameraSetAeThreshold(int iThreshold)
{
    return ::CameraSetAeThreshold(Handle, iThreshold);
}

CameraSdkStatus MindVisonCamera::CameraSetAeWindow(int iHOff, int iVOff, int iWidth, int iHeight)
{
    return ::CameraSetAeWindow(Handle, iHOff, iVOff, iWidth, iHeight);
}

CameraSdkStatus MindVisonCamera::CameraSetAnalogGain(int iAnalogGain)
{
    return ::CameraSetAnalogGain(Handle, iAnalogGain);
}

CameraSdkStatus MindVisonCamera::CameraSetAnalogGainX(float fGain)
{
    return ::CameraSetAnalogGainX(Handle, fGain);
}

CameraSdkStatus MindVisonCamera::CameraSetLightFrequency(int iFrequencySel)
{
    return ::CameraSetLightFrequency(Handle, iFrequencySel);
}

CameraSdkStatus MindVisonCamera::CameraSetTriggerMode(int iModeSel)
{
    return ::CameraSetTriggerMode(Handle, iModeSel);
}

/*
    设置触发模式下的触发帧数。对软件触发和硬件触发模式都有效。默认为1帧，即一次触发信号采集一帧图像。
*/
CameraSdkStatus MindVisonCamera::CameraSetTriggerCount(int iCount)
{
    return ::CameraSetTriggerCount(Handle, iCount);
}

/*
    设置外触发信号间隔时间，默认为0，单位为微秒。
*/
CameraSdkStatus MindVisonCamera::CameraSetExtTrigIntervalTime(unsigned int uTimeUs)
{
    return ::CameraSetExtTrigIntervalTime(Handle, uTimeUs);
}

/*
    设置相机外触发信号的消抖时间。默认为0，单位为微秒。
*/
CameraSdkStatus MindVisonCamera::CameraSetExtTrigJitterTime(unsigned int uTimeUs)
{
    return ::CameraSetExtTrigJitterTime(Handle, uTimeUs);
}

/*
    执行一次软触发。执行后，会触发由CameraSetTriggerCount指定的帧数。
*/
CameraSdkStatus MindVisonCamera::CameraSoftTrigger()
{
    return ::CameraSoftTrigger(Handle);
}

/*
    设置IO引脚端子上的STROBE信号。该信号可以做闪光灯控制，也可以做外部机械快门控制。
*/
CameraSdkStatus MindVisonCamera::CameraSetStrobeMode(int iMode)
{
    return ::CameraSetStrobeMode(Handle, iMode);
}

/*
    当STROBE信号处于STROBE_SYNC_WITH_TRIG时，通过该函数设置其相对触发信号延时时间。
*/
CameraSdkStatus MindVisonCamera::CameraSetStrobeDelayTime(unsigned int uDelayTimeUs)
{
    return ::CameraSetStrobeDelayTime(Handle, uDelayTimeUs);
}

/*
    当STROBE信号处于STROBE_SYNC_WITH_TRIG时，通过该函数设置其脉冲宽度。
*/
CameraSdkStatus MindVisonCamera::CameraSetStrobePulseWidth(unsigned int uTimeUs)
{
    return ::CameraSetStrobePulseWidth(Handle, uTimeUs);
}