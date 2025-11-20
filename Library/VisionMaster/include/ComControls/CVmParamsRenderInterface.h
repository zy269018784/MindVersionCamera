// CVmParamsRenderInterface.h : 由 Microsoft Visual C++ 创建的 ActiveX 控件包装器类的声明

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CVmParamsRenderInterface
#pragma warning(disable:4819)
#include "VmControlBaseInfo.h"
#include "VmModuleResultBase.h"
#include "ErrorCodeDefine.h"
#include "VmException.h"
#include <string>

using namespace VisionMasterSDK;

typedef struct GroupInputRenderInfo_
{
	char strSolPath[780]; // 方案路径
	char strPassword[32]; // 方案密码
}GroupInputRenderInfo;

typedef struct ParamRenderCtrlInput__
{
	void * Handle;
	unsigned int ModuId;
} ParamRenderCtrlInput;

class CVmParamsRenderInterface : public CWnd
{
protected:
	DECLARE_DYNCREATE(CVmParamsRenderInterface)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xC6961180, 0x1F47, 0x41A2, { 0x82, 0xA6, 0xD9, 0x81, 0x18, 0x87, 0xF4, 0xF6 } };
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
		ParamRenderCtrlInput * pParam = (ParamRenderCtrlInput *)pParamData;
		ParamBaseEx stParamData = { 0 };
		stParamData.Handle = pParam->Handle;
		stParamData.ModuId = pParam->ModuId;
		stParamData.TimeOut = 5;
		_snprintf_s(stParamData.XmlPath, 780, 779, "%s", strPath.c_str());
		__int64 pData = _int64(&stParamData);
		static BYTE parms[] = VTS_I8 ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, pData);
	}
	/**
     * @par 说明
     * 设置图像数据
	 * @param pImgData [in] 图像数据
	 * 需先设置参数配置信息
     */
	void SetImageSourceData(ImageBaseData * pImgData)
	{
		if (NULL == pImgData)
		{
			throw CVmException(IMVS_EC_PARAM);
		}
		__int64 pData = _int64(pImgData);
		static BYTE parms[] = VTS_I8 ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, pData);
	}
	/**
     * @par 说明
     * 设置点集数据
	 * @param pPointSet [in] 点集信息
	 * @param isAddShape [in] false 立即绘制  true 在下次刷新渲染时自动绘制
	 * 需先设置参数配置信息
     */
	void SetPointSet(PointSet * pPointSet, bool isAddShape = false)
	{
		if (NULL == pPointSet)
		{
			throw CVmException(IMVS_EC_PARAM);
		}
		if (NULL == pPointSet->pstPointList)
		{
			throw CVmException(IMVS_EC_PARAM);
		}
		__int64 pData = _int64(pPointSet);
		static BYTE parms[] = VTS_I8 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, pData, isAddShape);
	}
	/**
     * @par 说明
     * 设置多边形数据
	 * @param pPolygon [in] 多边形
	 * @param isAddShape [in] false 立即绘制  true 在下次刷新渲染时自动绘制
	 * 需先设置参数配置信息
     */
	void SetPolygon(PolygonEx * pPolygon, bool isAddShape = false)
	{
		if (NULL == pPolygon)
		{
			throw CVmException(IMVS_EC_PARAM);
		}
		if (NULL == pPolygon->PolygonPointListPtr)
		{
			throw CVmException(IMVS_EC_PARAM);
		}
		__int64 pData = _int64(pPolygon);
		static BYTE parms[] = VTS_I8 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, pData, isAddShape);
	}
	/**
     * @par 说明
     * 设置折线数据
	 * @param pPolyline [in] 折线信息
	 * @param isAddShape [in] false 立即绘制  true 在下次刷新渲染时自动绘制
	 * 需先设置参数配置信息
     */
	void SetPolyline(PolylineEx * pPolyline, bool isAddShape = false)
	{
		if (NULL == pPolyline)
		{
			throw CVmException(IMVS_EC_PARAM);
		}
		if (NULL == pPolyline->PolylinePointListPtr)
		{
			throw CVmException(IMVS_EC_PARAM);
		}
		__int64 pData = _int64(pPolyline);
		static BYTE parms[] = VTS_I8 ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, pData, isAddShape);
	}
	/**
     * @par 说明
     * 设置圆形数据
	 * @param pCircle [in] 圆形数据
	 * @param isAddShape [in] false 立即绘制  true 在下次刷新渲染时自动绘制
	 * 需先设置参数配置信息
     */
	void SetCircle(CircleEx * pCircle, bool isAddShape = false)
	{
		if (NULL == pCircle)
		{
			throw CVmException(IMVS_EC_PARAM);
		}
		__int64 pData = _int64(pCircle);
		static BYTE parms[] = VTS_I8 ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, pData, isAddShape);
	}
	/**
     * @par 说明
     * 设置扇环形数据
	 * @param pAnnularSector [in] 扇环信息
	 * @param pShape [in] 形状
	 * @param isAddShape [in] false 立即绘制  true 在下次刷新渲染时自动绘制
	 * 需先设置参数配置信息
     */
	void SetAnnularSector(Annulus * pAnnularSector, Shape * pShape, bool isAddShape = false)
	{		
		if ((NULL == pAnnularSector) || (NULL == pShape))
		{
			throw CVmException(IMVS_EC_PARAM);
		}
		AnnulusEx stAnnuInfo = { 0 };
		stAnnuInfo.CenterX = pAnnularSector->CenterPoint.X;
		stAnnuInfo.CenterY = pAnnularSector->CenterPoint.Y;
		stAnnuInfo.OuterRadius = pAnnularSector->OuterRadius;
		stAnnuInfo.InnerRadius = pAnnularSector->InnerRadius;
		stAnnuInfo.StartAngle = pAnnularSector->StartAngle;
		stAnnuInfo.AngleRange = pAnnularSector->AngleExtend;
		stAnnuInfo.Opacity = pShape->Opacity;
		stAnnuInfo.Color = pShape->Color;
		stAnnuInfo.FillColor = pShape->FillColor;
		stAnnuInfo.StrokeThickness = pShape->StrokeThickness;
		__int64 pData = _int64(&stAnnuInfo);
		static BYTE parms[] = VTS_I8 ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, pData, isAddShape);
	}
	/**
     * @par 说明
     * 设置直线数据
	 * @param pLine [in] 直线信息
	 * @param pShape [in] 形状
	 * @param isAddShape [in] false 立即绘制  true 在下次刷新渲染时自动绘制
	 * 需先设置参数配置信息
     */
	void SetLine(Line * pLine, Shape * pShape, bool isAddShape = false)
	{
		if ((NULL == pLine) || (NULL == pShape))
		{
			throw CVmException(IMVS_EC_PARAM);
		}
		LineEx stLine = { 0 };
		stLine.StartPointX = pLine->StartPoint.X;
		stLine.StartPointY = pLine->StartPoint.Y;
		stLine.EndPointX = pLine->EndPoint.X;
		stLine.EndPointY = pLine->EndPoint.Y;
		stLine.Opacity = pShape->Opacity;
		stLine.Color = pShape->Color;
		stLine.FillColor = pShape->FillColor;
		stLine.StrokeThickness = pShape->StrokeThickness;
		__int64 pData = _int64(&stLine);
		static BYTE parms[] = VTS_I8 ;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, pData, isAddShape);
	}
	/**
     * @par 说明
     * 设置矩形数据
	 * @param pRectangle [in] 矩形信息
	 * @param isAddShape [in] false 立即绘制  true 在下次刷新渲染时自动绘制
	 * 需先设置参数配置信息
     */
	void SetRectangle(RectangleEx * pRectangle, bool isAddShape = false)
	{
		if (NULL == pRectangle)
		{
			throw CVmException(IMVS_EC_PARAM);
		}
		__int64 pData = _int64(pRectangle);
		static BYTE parms[] = VTS_I8 ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, pData, isAddShape);
	}
	/**
     * @par 说明
     * 设置文本数据
	 * @param pText [in] 文本信息
	 * @param isAddShape [in] false 立即绘制  true 在下次刷新渲染时自动绘制
	 * 需先设置参数配置信息
     */
	void SetText(Text * pText, bool isAddShape = false)
	{
		if (NULL == pText)
		{
			throw CVmException(IMVS_EC_PARAM);
		}
		std::string strCons = pText->Content;
		if (!UTF8Format(strCons.c_str(), strCons.length()))
		{
			strCons = MB2UTF8F(pText->Content);
			memset(pText->Content, 0, 4096);
			_snprintf_s(pText->Content, 4096, 4095, "%s", strCons.c_str());
		}
		__int64 pData = _int64(pText);
		static BYTE parms[] = VTS_I8 ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, pData, isAddShape);
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
		
		GroupInputRenderInfo stInput = {0};		
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
		InvokeHelper(0xc, DISPATCH_METHOD, VT_I8, (void*)&result, parms, pData);
		return (void *)result;
	}
	/**
     * @par 说明
     * 显示坐标信息
     */
	void ShowCoordinateInfo()
	{
		InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	/**
     * @par 说明
     * 隐藏坐标信息
     */
	void HideCoordinateInfo()
	{
		InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	/**
     * @par 说明
     * 放大视图
     */
	void EnlargeView(int index = 1)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, index);
	}
	/**
     * @par 说明
     * 缩小视图
     */
	void ShrinkView(int index = 1)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, index);
	}
	/**
     * @par 说明
     * 还原视图
     */
	void InitView(int index = 1)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, index);
	}
	/**
    * @par 说明
    * 设置控件背景图
    * @param Value [in] 背景图(小于100*100)绝对路径或#十六进制颜色码
    */
	void SetBackground(LPCTSTR Value)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Value);
	}
    /**
    * @par 说明
    * 清空显示
    */
    void ClearDisplayView(int index = 1)
    {
		static BYTE parms[] = VTS_I4;
        InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, index);
    }
	/**
	* @par 说明
	* 流程、Group参数页中的添加、删除、编辑按钮是否可见
	* @param isEditable [in] 是否可见   true 按钮可见
	*/
    void SetParamTabEditable(bool isEditable)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, isEditable);
	}
	/**
	* @par 说明
	* 多画面切换按钮是否可见
	* @param isVisible [in] 是否按钮显示
	*/
	void SetMultiImageButtonVisible(bool isVisible)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, isVisible);
	}
    /**
    * @par 说明
    * 设置椭圆形数据
    * @param pEllipse [in] 椭圆形数据
    * @param isAddShape [in] false 立即绘制  true 在下次刷新渲染时自动绘制
    */
    void SetEllipse(EllipseEx * pEllipse, bool isAddShape = false)
    {
        if (NULL == pEllipse)
        {
            throw CVmException(IMVS_EC_PARAM);
        }
        __int64 pData = _int64(pEllipse);
        static BYTE parms[] = VTS_I8;
        InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, pData, isAddShape);
    }

    /**
    * @brief 保存原图
	* @param fileName	[IN] 图片路径
	* @param jpgQuality [IN] 图片质量，范围[1，100]，数值越大质量越高，默认值95
	* @param index 		[IN] 图片索引
    * @remarks 双画面显示时可指定操作某个画面，默认为右侧输出画面，index从左到右为0，1
    */
    void SaveOriginalImage(LPCTSTR fileName, long index = 1, long jpgQuality = 95)
    {
        if (jpgQuality > 100 || jpgQuality <= 0)
        {
            throw CVmException(IMVS_EC_PARAM);
        }
        static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4;
        InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, parms, fileName, index, jpgQuality);
    }

    /**
    * @par 说明
    * 保存渲染图，jpgQuality范围[1,100]，数值越大质量越高，默认值95
    */
    void SaveRenderedImage(LPCTSTR fileName, long jpgQuality = 95)
    {
        if (jpgQuality > 100 || jpgQuality <= 0)
        {
            throw CVmException(IMVS_EC_PARAM);
        }
        static BYTE parms[] = VTS_BSTR VTS_I4;
        InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, parms, fileName, jpgQuality);
    }

    /**
    * @par 说明
    * 设置渲染间隔(ms)，用于减低渲染频率。设置后，执行结束触发渲染时先校验距离上一次渲染的时间是否已超过设置的间隔时间，已超过则正常渲染，未超过则跳过此次渲染
	* @param pMillseconds [IN] 间隔时间(ms)
    */
    void SetRenderInterval(long pMillseconds)
    {
		if (pMillseconds < 0 || pMillseconds > 10000)
		{
			throw CVmException(IMVS_EC_PARAM);
		}
        static BYTE parms[] = VTS_I4;
        InvokeHelper(0x1a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pMillseconds);
    }

    /**
    * @par 说明
    * 控制图层选择控件显示隐藏
	* @param isImageComboBoxVisible [IN] 是否可视
    */
    void ChangeImageComboBoxVisibility(BOOL isImageComboBoxVisible)
    {
        static BYTE parms[] = VTS_BOOL;
        InvokeHelper(0x1b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, isImageComboBoxVisible);
    }

    
    /**
    * @par 说明
    * 获取当前选中图像名称，双画面显示时可指定获取某个画面，默认为右侧输出画面，index从左到右为0，1
    */
    CString GetSelectedImageDisplayName(long index = 1)
    {
        CString result;
        static BYTE parms[] = VTS_I4;
        InvokeHelper(0x1c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, index);
        return result;
    }
	

    /**
    * @par 说明
    * 设置渲染条件：当设置条件status和模块状态值一致时才刷新
    * @param status [in] 模块状态
    */
    void SetRenderCondition(RenderSatus status = RenderSatus_ALL)
    {
        static BYTE parms[] = VTS_I4;
        InvokeHelper(0x1d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, status);
    }
	
	/**
     * @par 说明
     * 获取所有Tab名称
	 * @param strTabNameArray [out] Tab名称列表
     */
    void GetParamTabNames(CStringArray& strTabNameArray)
    {
        CString result;
        InvokeHelper(0x1e, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
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
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, tabName, isVisible);
	}
	
	/**
     * @par 说明
     * 设置工具栏是否可见
	 * @param isVisible [in] 是否可见
     */
	void SetRenderToolbarVisible(BOOL isVisible)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x20, DISPATCH_METHOD, VT_EMPTY, NULL, parms, isVisible);
	}
	
	/**
     * @par 说明
     * 获取可显示的图像名称列表
	 * @param strImageViewList [out] 图像名称列表
     */
    void GetDisplayableImageNameList(CStringArray& strImageViewList)
	{
        CString result;
        InvokeHelper(0x21, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
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
		InvokeHelper(0x22, DISPATCH_METHOD, VT_EMPTY, NULL, parms, displayImageName);
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
		InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms, backgroundImageName);
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
		InvokeHelper(0x24, DISPATCH_METHOD, VT_EMPTY, NULL, parms, displayImageName);
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
		InvokeHelper(0x25, DISPATCH_METHOD, VT_EMPTY, NULL, parms, displayImageName);
	}	

    /**
     * @brief 释放控件资源
	 * @remarks 控件销毁前调用一次
     */
	void Dispose()
	{
		InvokeHelper(0x26, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
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
