// CVmComprehensiveConfigWithRenderInterface.h : 由 Microsoft Visual C++ 创建的 ActiveX 控件包装器类的声明

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CVmComprehensiveConfigWithRenderInterface
#include <string>
#include "VmException.h"
#include "VmControlBaseInfo.h"

class CVmComprehensiveConfigWithRenderInterface : public CWnd
{
protected:
	DECLARE_DYNCREATE(CVmComprehensiveConfigWithRenderInterface)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xD8909EA7, 0xEEEB, 0x4A5B, { 0xA5, 0x57, 0x38, 0x77, 0xCD, 0x9E, 0xAB, 0x60 } };
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
     * 初始化
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
     * 获取所有Tab名称
	 * @param strTabNameArray [out] Tab名称列表
     */
    void GetParamTabNames(CStringArray& strTabNameArray)
    {
        CString result;
        InvokeHelper(0x2, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
        SplitUnicodeCString(result, strTabNameArray);
    }
	
	/**
     * @par 说明
     * 设置Tab页是否可见，如果绑定同一个数据源，调用此接口会同步更新与tabName对应的参数配置tab页的显示或者隐藏
	 * @param strTabName [in] Tab页名称
	 * @param isVisible [in] 是否可见
     */
    void SetParamTabVisible( const char * const strTabName, bool isVisible)
	{
        if ((NULL == strTabName))
        {
            throw CVmException(IMVS_EC_PARAM);
        }
        ParamName stParamName;
        memset(&stParamName, 0, sizeof(ParamName));
        std::string strBackupTabName = strTabName;
        if (!UTF8Format(strBackupTabName.c_str(), strBackupTabName.length()))
        {
            strBackupTabName = MB2UTF8F(strTabName);
        }
        _snprintf_s(stParamName.ParamStringName, 256, 255, "%s", strBackupTabName.c_str());
        __int64 tabName = _int64(&stParamName);
		static BYTE parms[] = VTS_I8 VTS_BOOL ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, tabName, isVisible);
	}
	
	/**
     * @par 说明
     * 设置工具栏是否可见
	 * @param isVisible [in] 是否可见
     */
	void SetRenderToolbarVisible(BOOL isVisible)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, isVisible);
	}
	
	/**
     * @par 说明
     * 获取可显示的图像名称列表
	 * @param strImageViewList [out] 图像名称列表
     */
    void GetDisplayableImageNameList(CStringArray& strImageViewList)
	{
        CString result;
        InvokeHelper(0x5, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
        SplitUnicodeCString(result, strImageViewList);
	}
	
	/**
     * @par 说明
     * 设置图像显示
	 * @param strDisplayImageName [in]显示的图像名称
     */	
    void SetSelectedImage(const char * const strDisplayImageName)
	{
        if ((NULL == strDisplayImageName))
        {
            throw CVmException(IMVS_EC_PARAM);
        }
        ParamName stParamName;
        memset(&stParamName, 0, sizeof(ParamName));
        std::string strBackupName = strDisplayImageName;
        if (!UTF8Format(strBackupName.c_str(), strBackupName.length()))
        {
            strBackupName = MB2UTF8F(strDisplayImageName);
        }
        _snprintf_s(stParamName.ParamStringName, 256, 255, "%s", strBackupName.c_str());
        __int64 displayImageName = _int64(&stParamName);
		static BYTE parms[] = VTS_I8 ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, displayImageName);
	}
	
	/**
     * @par 说明
     * 当图像堆叠时，切换背景图像
	 * @param strBackgroundImageName [in]背景图像名称
     */	
    void SwitchBackgroundImage(const char * const strBackgroundImageName)
	{
        if ((NULL == strBackgroundImageName))
        {
            throw CVmException(IMVS_EC_PARAM);
        }
        ParamName stParamName;
        memset(&stParamName, 0, sizeof(ParamName));
        std::string strBackupName = strBackgroundImageName;
        if (!UTF8Format(strBackupName.c_str(), strBackupName.length()))
        {
            strBackupName = MB2UTF8F(strBackgroundImageName);
        }
        _snprintf_s(stParamName.ParamStringName, 256, 255, "%s", strBackupName.c_str());
        __int64 backgroundImageName = _int64(&stParamName);
		static BYTE parms[] = VTS_I8 ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, backgroundImageName);
	}
	
	/**
     * @par 说明
     * 设置堆叠显示的图像(单张)
	 * @param strDisplayImageName [in]显示的图像名称
     */	
    void AddStackImage(const char * const strDisplayImageName)
	{
        if ((NULL == strDisplayImageName))
        {
            throw CVmException(IMVS_EC_PARAM);
        }
        ParamName stParamName;
        memset(&stParamName, 0, sizeof(ParamName));
        std::string strBackupName = strDisplayImageName;
        if (!UTF8Format(strBackupName.c_str(), strBackupName.length()))
        {
            strBackupName = MB2UTF8F(strDisplayImageName);
        }
        _snprintf_s(stParamName.ParamStringName, 256, 255, "%s", strBackupName.c_str());
        __int64 displayImageName = _int64(&stParamName);
		static BYTE parms[] = VTS_I8 ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, displayImageName);
	}
	
	/**
     * @par 说明
     * 移除堆叠显示的图像
	 * @param strDisplayImageName [in]显示的图像名称
     */	
    void RemoveStackImage(const char * const strDisplayImageName)
	{
        if ((NULL == strDisplayImageName))
        {
            throw CVmException(IMVS_EC_PARAM);
        }
        ParamName stParamName;
        memset(&stParamName, 0, sizeof(ParamName));
        std::string strBackupName = strDisplayImageName;
        if (!UTF8Format(strBackupName.c_str(), strBackupName.length()))
        {
            strBackupName = MB2UTF8F(strDisplayImageName);
        }
        _snprintf_s(stParamName.ParamStringName, 256, 255, "%s", strBackupName.c_str());
        __int64 displayImageName = _int64(&stParamName);
		static BYTE parms[] = VTS_I8 ;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, displayImageName);
	}
	
	/**
     * @par 说明
     * 绑定方案里的综合配置界面，需要在方案加载后调用
     */	
	void BindSolutionSource()
	{
		InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

    /**
    * @par 说明
    * 控制图层选择控件显示隐藏
    * @param flag [in] 是否显示
    */
    void ChangeImageComboBoxVisibility(BOOL flag)
    {
        static BYTE parms[] = VTS_BOOL;
        InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, flag);
    }
	/**
     * @brief 释放控件资源
	 * @remarks 控件销毁前调用一次
     */
    void Dispose()
	{
		InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

private:
    bool UTF8Format(const char * const strInput, const unsigned int nLen)
    {
        bool bRet = false;
        try
        {
            if ((NULL == strInput) || (0 == nLen))
            {
                throw false;
            }
            unsigned int nBytes = 0;
            unsigned char chIn = *strInput;
            bool bAllAscii = true;
            for (unsigned int i = 0; i < nLen; ++i)
            {
                chIn = *(strInput + i);
                if (nBytes == 0 && (chIn & 0x80) != 0)
                {
                    bAllAscii = false;
                }
                if (nBytes == 0)
                {
                    if (chIn >= 0x80)
                    {
                        if (chIn >= 0xFC && chIn <= 0xFD)
                        {
                            nBytes = 6;
                        }
                        else if (chIn >= 0xF8)
                        {
                            nBytes = 5;
                        }
                        else if (chIn >= 0xF0) {
                            nBytes = 4;
                        }
                        else if (chIn >= 0xE0)
                        {
                            nBytes = 3;
                        }
                        else if (chIn >= 0xC0)
                        {
                            nBytes = 2;
                        }
                        else
                        {
                            return false;
                        }
                        nBytes--;
                    }
                }
                else
                {
                    if ((chIn & 0xC0) != 0x80) {
                        return false;
                    }
                    nBytes--;
                }
            }
            if (nBytes != 0)
            {
                return false;
            }
            if (bAllAscii)
            {
                return true;
            }
        }
        catch (...)
        {
            return false;
        }
        return true;
    }

    std::string MB2UTF8F(LPCSTR pChar)
    {
        if (NULL == pChar)
        {
            return "";
        }

        wchar_t* buffw = NULL;
        char* lpsz = NULL;
        std::string strRtn;
        do
        {
            int num = MultiByteToWideChar(CP_ACP, NULL, pChar, -1, NULL, NULL);
            buffw = new(std::nothrow) wchar_t[num];
            if (NULL == buffw)
            {
                break;
            }
            MultiByteToWideChar(CP_ACP, NULL, pChar, -1, buffw, num);

            int len = WideCharToMultiByte(CP_UTF8, 0, buffw, num - 1, NULL, NULL, NULL, NULL);
            lpsz = new(std::nothrow) char[len + 1];
            if (NULL == lpsz)
            {
                break;
            }
            WideCharToMultiByte(CP_UTF8, 0, buffw, num - 1, lpsz, len, NULL, NULL);
            lpsz[len] = '\0';
            strRtn = lpsz;
        } while (0);

        if (NULL != buffw)
        {
            delete[] buffw;
            buffw = NULL;
        }
        if (NULL != lpsz)
        {
            delete[] lpsz;
            lpsz = NULL;
        }
        return strRtn;
    }

    void SplitUnicodeCString(const CString& strInput, CStringArray& arrResults)
    {
        arrResults.RemoveAll();
        if (strInput.GetLength() == 0)
        {
            return;
        }
        int nStartPos = 0;
        int nSplitPos = 0;

        while ((nSplitPos = strInput.Find(L'\r', nStartPos)) != -1)
        {
            arrResults.Add(strInput.Mid(nStartPos, nSplitPos - nStartPos));
            nStartPos = nSplitPos + 1;
        }

        if (nStartPos <= strInput.GetLength())
        {
            arrResults.Add(strInput.Mid(nStartPos));
        }
    }


};
