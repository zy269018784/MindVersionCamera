// CVmGlobalToolInterface.h : 由 Microsoft Visual C++ 创建的 ActiveX 控件包装器类的声明

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CVmGlobalToolInterface

class CVmGlobalToolInterface : public CWnd
{
protected:
	DECLARE_DYNCREATE(CVmGlobalToolInterface)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xB60D44E7, 0x1726, 0x42AA, { 0x9E, 0xD5, 0xD5, 0xD5, 0x12, 0xA6, 0xC1, 0xF2 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID,
						CCreateContext* pContext = nullptr)
	{
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID);
	}

	BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd,
				UINT nID, CFile* pPersist = nullptr, BOOL bStorage = FALSE,
				BSTR bstrLicKey = nullptr)
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
     * 初始化
	 * @return 内部信息
     * @par 权限
     * 只读
     */
	void * GetObjectPointer()
	{
		__int64 result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I8, (void*)&result, nullptr);
		return (void *)result;
	}

    /**
     * @brief 释放控件资源
	 * @remarks 控件销毁前调用一次
     */
	void Dispose()
	{
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	
	/**
     * @par 说明
     * 打开全局变量
     */	
	void OpenGlobalVariable()
	{
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	
	/**
     * @par 说明
     * 打开全局脚本
     */	
	void OpenGlobalScript()
	{
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	
	/**
     * @par 说明
     * 打开相机管理
     */
	void OpenGlobalCamera()
	{
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	
	/**
     * @par 说明
     * 打开全局触发
     */	
	void OpenGlobalTrigger()
	{
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	
	/**
     * @par 说明
     * 打开通信管理
     */	
	void OpenCommunicationManager()
	{
		InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}


};
