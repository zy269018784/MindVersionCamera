// CVmParamsInterface.h : 由 Microsoft Visual C++ 创建的 ActiveX 控件包装器类的声明

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CVmParamsInterface
#pragma warning(disable:4819)
#include "VmControlBaseInfo.h"
#include "ErrorCodeDefine.h"
#include "VmException.h"
#include <string>

typedef struct GroupInputInfo_
{
	char strSolPath[780]; // 方案路径
	char strPassword[32]; // 方案密码
}GroupInputInfo;

typedef struct ParamCtrlInput__
{
	void * Handle;
	unsigned int ModuId;
} ParamCtrlInput;

class CVmParamsInterface : public CWnd
{
protected:
	DECLARE_DYNCREATE(CVmParamsInterface)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x10C9ADFD, 0xABB2, 0x4AB3, { 0xBA, 0xB4, 0x26, 0xE5, 0x68, 0xD1, 0x2F, 0x1F } };
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
     * 设置参数配置信息
	 * @param pParamData [in] 参数配置信息
	 * @param strXmlPath [in] XML路径
     */
	void SetParamsInfo(void * pParamData, const char * const strXmlPath)
	{
		if ((NULL == pParamData) || (NULL == strXmlPath))
		{
			throw CVmException(IMVS_EC_PARAM);
		}
		std::string strPath = strXmlPath;
		if (!UTF8Format(strPath.c_str(), strPath.length()))
		{
			strPath = MB2UTF8F(strXmlPath);
		}
		ParamCtrlInput * pParam = (ParamCtrlInput *)pParamData;
		ParamBaseEx stParamData = { 0 };
		stParamData.Handle = pParam->Handle;
		stParamData.ModuId = pParam->ModuId;
		stParamData.TimeOut = 5;
		_snprintf_s(stParamData.XmlPath, 780, 779, "%s", strPath.c_str());
		__int64 pData = _int64(&stParamData);
		static BYTE parms[] = VTS_I8 ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, pData);
	}
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
		InvokeHelper(0x2, DISPATCH_METHOD, VT_I8, (void*)&result, nullptr);
		return (void *)result;
	}
	/**
     * @par 说明
     * 导入独立Group
	 * @param strPath [in] 路径
	 * @param strPassword [in] 密码
	 * @deprecated 弃用,推荐(SetParamsInfo(void * pParamData, const char * const strXmlPath)),绑定已导入的独立Group
     */
	void * LoadIndependentGroup(const char * const strPath, const char * const strPassword)
	{
		if (NULL == strPath)
		{
			throw CVmException(IMVS_EC_PARAM);
		}
		std::string strPassw = "";
		if (NULL != strPassword)
		{
			strPassw = strPassword;
		}
		
		GroupInputInfo stInput = {0};		
		std::string strPaths = strPath;
		if (!UTF8Format(strPaths.c_str(), strPaths.length()))
		{
			strPaths = MB2UTF8F(strPath);
		}
		_snprintf_s(stInput.strSolPath, 780, 779, "%s", strPaths.c_str());
		_snprintf_s(stInput.strPassword, 32, 31, "%s", strPassw.c_str());
		
		__int64 pData = _int64(&stInput);	
		__int64 result;
		static BYTE parms[] = VTS_I8 ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_I8, (void*)&result, parms, pData);
		return (void *)result;
	}
	/**
	* @par 说明
	* 流程、Group参数页中的添加、删除、编辑按钮是否可见
	* @param isEditable [in] 是否可见   true 按钮可见
	*/
    void SetParamTabEditable(bool isEditable)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, isEditable);
	}
	
		/**
     * @par 说明
     * 获取所有Tab名称
	 * @param strTabNameArray [out] Tab名称列表
     */
    void GetParamTabNames(CStringArray& strTabNameArray)
    {
        CString result;
        InvokeHelper(0x6, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
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
		InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, tabName, isVisible);
	}

    /**
     * @brief 释放控件资源
	 * @remarks 控件销毁前调用一次
     */
	void Dispose()
	{
		InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
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
