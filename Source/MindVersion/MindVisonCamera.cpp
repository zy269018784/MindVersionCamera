#include "MindVisonCamera.h"
#include <stdio.h>
MindVisonCamera::MindVisonCamera()
{
	
}

MindVisonCamera::~MindVisonCamera()
{

}

CameraSdkStatus MindVisonCamera::CameraInit(tSdkCameraDevInfo* pCameraInfo, int emParamLoadMode, int emTeam)
{
	printf("Handle %d\n", Handle);
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

CameraSdkStatus MindVisonCamera::CameraSetCallbackFunction(CAMERA_SNAP_PROC pCallBack, PVOID pContext, CAMERA_SNAP_PROC* pCallbackOld)
{
	return ::CameraSetCallbackFunction(Handle, pCallBack, pContext, pCallbackOld);
}

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

// 清空相机缓冲区
CameraSdkStatus MindVisonCamera::CameraClearBuffer()
{
    return ::CameraClearBuffer(Handle);
}

// 获取图像缓冲区（标准版本）
CameraSdkStatus MindVisonCamera::CameraGetImageBuffer(
    tSdkFrameHead* pFrameInfo,
    unsigned char** pbyBuffer,
    unsigned int wTimes)
{
    return ::CameraGetImageBuffer(Handle, pFrameInfo, pbyBuffer, wTimes);
}

// 获取图像缓冲区（带优先级）
CameraSdkStatus MindVisonCamera::CameraGetImageBufferPriority(
    tSdkFrameHead* pFrameInfo,
    unsigned char** pbyBuffer,
    unsigned int wTimes,
    unsigned int Priority)
{
    return ::CameraGetImageBufferPriority(Handle, pFrameInfo, pbyBuffer, wTimes, Priority);
}

// 释放图像缓冲区
CameraSdkStatus MindVisonCamera::CameraReleaseImageBuffer(unsigned char* pbyBuffer)
{
    return ::CameraReleaseImageBuffer(Handle, pbyBuffer);
}

// 拍摄JPEG图像并保存到文件
CameraSdkStatus MindVisonCamera::CameraSnapJpegToFile(
    char const* lpszFileName,
    unsigned char byQuality,
    unsigned int wTimes)
{
    return ::CameraSnapJpegToFile(Handle, lpszFileName, byQuality, wTimes);  // 1 表示JPEG格式
}

// 拍摄图像到缓冲区
CameraSdkStatus MindVisonCamera::CameraSnapToBuffer(
    tSdkFrameHead* pFrameInfo,
    unsigned char** pbyBuffer,
    unsigned int wTimes)
{
    return ::CameraSnapToBuffer(Handle, pFrameInfo, pbyBuffer, wTimes);
}