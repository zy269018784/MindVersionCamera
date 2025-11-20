// CVmRealTimeAcqControlInterface.h : 由 Microsoft Visual C++ 创建的 ActiveX 控件包装器类的声明

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CVmRealTimeAcqControlInterface
#include "VmControlBaseInfo.h"
#include "VmModuleResultBase.h"
#include "ErrorCodeDefine.h"
#include "VmException.h"

class CVmRealTimeAcqControlInterface : public CWnd
{
protected:
	DECLARE_DYNCREATE(CVmRealTimeAcqControlInterface)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x4919FA4C, 0xF224, 0x4C1E, { 0x91, 0x7C, 0x89, 0xB7, 0xF3, 0x7A, 0xAE, 0x0 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 特性
public:

// 操作
public:
	/**
     * @par 说明
     * 初始化（实时取流前调用）
	 * @return 内部信息
     * @par 权限
     * 只读
     */
	__int64 GetObjectPointer()
	{
		__int64 result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I8, (void*)&result, NULL);
		return result;
	}
    /**
     * @par 说明
     * 设置实时取流配置信息
	 * @param pParamData [in] 实时取流配置信息
     */
	void SetParamsInfo(void * pParamData)
	{
		if (NULL == pParamData)
		{
			throw CVmException(IMVS_EC_PARAM);
		}

		__int64 pData = _int64(pParamData);

		static BYTE parms[] = VTS_I8 ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pData);
	}
	/**
     * @par 说明
     * 开始取图
     */
	void StartGrabbing()
	{
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	/**
     * @par 说明
     * 停止取图
     */
	void StopGrabbing()
	{
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
    /**
     * @par 说明
     * 显示取图控制按钮
	 * @param bFlag [in] false 隐藏按钮  true 显示按钮
     */
	void ShowButton(BOOL bFlag)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bFlag);
	}

    /**
     * @brief 释放控件资源
	 * @remarks 控件销毁前调用一次
     */
	void Dispose()
	{
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}

};
