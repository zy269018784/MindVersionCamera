// CVmMainViewControlInterface.h : 由 Microsoft Visual C++ 创建的 ActiveX 控件包装器类的声明

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CVmMainViewControlInterface

class CVmMainViewControlInterface : public CWnd
{
protected:
	DECLARE_DYNCREATE(CVmMainViewControlInterface)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x650FFBDC, 0x5E28, 0x4314, { 0x89, 0x1, 0x7F, 0x2, 0xE6, 0x14, 0x54, 0x14 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
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
     * 初始化（加载方案前调用）
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
     * @par 说明
     * 绑定单流程
	 * @param name [in] 流程名称
	 * 绑定单流程后不支持加载方案，导入流程
     */	
	void BindSingleProcedure(LPCTSTR name)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, name);
	}
	/**
     * @par 说明
     * 绑定多流程
     */
	void BindMultiProcedure()
	{
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	/**
     * @par 说明
     * 锁定工作区
     */
	void LockWorkArea()
	{
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	/**
     * @par 说明
     * 解锁工作区
     */
	void UnlockWorkArea()
	{
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	/**
	* @par 说明
	* 流程、Group参数页中的添加、删除、编辑按钮是否可见
	* @param isEditable [in] 是否可见   true 按钮可见
	*/
    void SetParamTabEditable(bool isEditable)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, isEditable);
	}

    /**
     * @brief 释放控件资源
	 * @remarks 控件销毁前调用一次
     */
	void Dispose()
	{
		InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}	
};
