#pragma once
#include "MvCameraControl.h"

class HIKSDK
{
public:
	HIKSDK();
	~HIKSDK();
public:
	int MV_CC_EnumDevices(unsigned int nTLayerType, MV_CC_DEVICE_INFO_LIST* pstDevList);
};