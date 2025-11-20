// CVmSingleModuleSetControlInterface.h : 由 Microsoft Visual C++ 创建的 ActiveX 控件包装器类的声明

#pragma once
#pragma warning(disable:4819)
#include "VmException.h"
#include <string>

/////////////////////////////////////////////////////////////////////////////
// CVmSingleModuleSetControlInterface

using namespace VisionMasterSDK;

typedef struct SingleGroupInputRenderInfo_
{
	char strSolPath[780]; // Group路径
	char strPassword[32]; // Group密码
}SingleGroupInputRenderInfo;

class CVmSingleModuleSetControlInterface : public CWnd
{
protected:
	DECLARE_DYNCREATE(CVmSingleModuleSetControlInterface)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x611E76E, 0x3E97, 0x42C7, { 0x8D, 0x2D, 0xA8, 0xA4, 0x2E, 0x92, 0x8A, 0x7A } };
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
     * @brief 导入独立Group
	 * @param strPath [in] 路径
	 * @param strPassword [in] 密码
	 * @remarks 与DestroyIndependentGroup()配对使用
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
		
		SingleGroupInputRenderInfo stInput = {0};		
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
		InvokeHelper(0x2, DISPATCH_METHOD, VT_I8, (void*)&result, parms, pData);
        if (result == NULL)
        {
            throw CVmException(IMVS_EC_PARAM);
        }

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
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, isEditable);
	}

    /**
     * @brief 销毁独立Group
	 * @remarks 与LoadIndependentGroup(const char * const strPath, const char * const strPassword)配对使用
     */
	void DestroyIndependentGroup()
	{
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	
    /**
     * @brief 释放控件资源
	 * @remarks 控件销毁前调用一次
     */
	void Dispose()
	{
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
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
};
