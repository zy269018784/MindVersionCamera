#include "IVmSolution.h"
#include "VMException.h"
#include "IVmProcedure.h"
#include <iostream>

/*
    stb
*/
#define STBI_WINDOWS_UTF8
#include <stb_image.h>
#include <stb_image_write.h>
using namespace VisionMasterSDK;
using namespace VisionMasterSDK::VmSolution;
using namespace VisionMasterSDK::VmProcedure;
int __stdcall CallBackFunc(OUT OutputPlatformInfo* const pstOutputInfo, IN void* const pUser)
{
    std::cout << "CallBackFunc " << pstOutputInfo->nInfoType << std::endl;
    if (IMVS_ENUM_CTRLC_OUTPUT_PLATFORM_INFO_MODULE_RESULT == pstOutputInfo->nInfoType)
    {
        
        IMVS_PF_MODULE_RESULT_INFO_LIST* pstPFModuResInfoList = (IMVS_PF_MODULE_RESULT_INFO_LIST*)pstOutputInfo->pData;
        if (pstPFModuResInfoList == NULL)
            return IMVS_EC_NULL_PTR;

        // 获取流程/Group/模块运行结果数据
        IMVS_PF_MODULE_RESULT_INFO* pstPFModuResInfo = pstPFModuResInfoList->pModuResInfo;
        if (pstPFModuResInfo == NULL)
            return IMVS_EC_NULL_PTR;

        // 获取结果名称
        char    strParamName[IMVS_PF_MAX_MODULE_PARAMNAME_LENGTH];
        memcpy_s(strParamName, sizeof(strParamName), pstPFModuResInfo->strParamName, sizeof(pstPFModuResInfo->strParamName));

       std::cout << "\tnParamType " << pstPFModuResInfo->nParamType << std::endl;
       std::cout << "\tstrParamName " << pstPFModuResInfo->strParamName << std::endl;
       if (3 == pstPFModuResInfo->nParamType)
           std::cout << "\tpstStringValue " << pstPFModuResInfo->pstStringValue->strValue << std::endl;
    }
    else if (IMVS_ENUM_CTRLC_OUTPUT_PLATFORM_INFO_STOP == pstOutputInfo->nInfoType)
    {

    }
    else if (IMVS_ENUM_CTRLC_OUTPUT_PLATFORM_INFO_WORK_STATE == pstOutputInfo->nInfoType)
    {

    }
    else if (IMVS_ENUM_CTRLC_OUTPUT_PLATFORM_INFO_SOLUTION_RUN_END == pstOutputInfo->nInfoType)
    {

    }

    return IMVS_EC_OK;
}

class ProEvent :public IVmProcedureEvent
{
public:
    // 流程开始执行状态回调
    virtual void OnWorkBeginStatusCallBack(IN const IMVS_PF_MODULE_WORK_STAUS* const pstWorkStatus, IN void* const pUser)
    {
        // 获取流程ID
        int processID = pstWorkStatus->nProcessID;

        std::cout << "WorkBegin " << processID << std::endl;
    }

    // 流程结束执行状态回调
    virtual void OnWorkEndStatusCallBack(IN const IMVS_PF_MODULE_WORK_STAUS* const pstWorkStatus, IN void* const pUser)
    {
        // 获取流程ID
        int processID = pstWorkStatus->nProcessID;

        // 获取流程耗时
        float processTime = pstWorkStatus->fProcessTime;

        std::cout << "WorkEnd " << processID << std::endl;

    }
};

int SOL2(void)
{
    try
    {
        //创建方案单例，用于初始化资源，方案对象可用于注册回调函数/事件等操作
        IVmSolution* pVmSol;// = CreateSolutionInstance();

        //获取已存在的方案对象，用于跨类操作方案
        //pVmSol = GetSolutionExistedInstance();

        //加载方案，仅支持绝对路径，编码格式UTF-8
        pVmSol = LoadSolution("C:\\Test1.sol", "");

        if (NULL == pVmSol) 
            return IMVS_EC_NULL_PTR;


        //获取方案所有流程对象
        ObjectList procedureObjList = pVmSol->GetAllProcedureObjects();
        std::cout << "procedureObjList.nNum " << procedureObjList.nNum << std::endl;
        for (int i = 0; i < procedureObjList.nNum; i++)
        {
            std::cout << "\t" << procedureObjList.pObjects[i] << std::endl;
        }

        //获取方案所有流程信息
        ProcessInfoList* procedureList = pVmSol->GetAllProcedureList();
        std::cout << "procedureList->nNum " << procedureList->nNum << std::endl;
        for (int i = 0; i < procedureList->nNum; i++)
        {
            std::cout << "\t" << procedureList->astProcessInfo[i].strProcessName << std::endl;
        }

        //获取方案所有模块信息
        ModuleInfoList* moduInfoList = pVmSol->GetAllModuleList();
        std::cout << "moduInfoList->nNum " << moduInfoList->nNum << std::endl;
        for (int i = 0; i < moduInfoList->nNum; i++)
        {
            std::cout << "\t" << moduInfoList->astModuleInfo[i].strModuleName << std::endl;
        }

        /*
            方案回调
        */
        pVmSol->DisableModulesCallback(); 
        pVmSol->EnableModulesCallback();
        pVmSol->RegisterCallBack(CallBackFunc, nullptr);

        /*
            流程
        */
        IVmProcedure* pVmPrc = (IVmProcedure*)(*pVmSol)["流程1"];
        /*
            流程回调
        */
        //ProEvent *m_pPrcEvent = new ProEvent();
        
        //pVmPrc->RegisterCallBackEvent(m_pPrcEvent, nullptr);

        std::cout << "debug 1" << std::endl;
        unsigned char *image = new unsigned char[3 * 4000 * 3000];
       
        ImageBaseData imageBaseData = { 0 };
        imageBaseData.Width  = 4000;
        imageBaseData.Height = 3000;
        imageBaseData.DataLen = imageBaseData.Width * imageBaseData.Height;
        imageBaseData.Pixelformat = MVD_PIXEL_RGB_RGB24_C3;
        imageBaseData.ImageData = image;
        
        VisionMasterSDK::IoImage inputImage;
        inputImage.stImage = imageBaseData;
        //std::cout << "debug 2" << std::endl;

        IMVSProcedureParams* pParam = pVmPrc->GetParamObj();
        if (NULL != pParam)
        {
            std::cout << "debug 2" << std::endl;
            pParam->SetInputImageV2("ImageData", &inputImage);
            std::cout << "debug 3" << std::endl;
        }

        std::cout << "debug 3" << std::endl;
        //方案同步执行一次
        pVmSol->Run();
        std::cout << "debug 4" << std::endl;
        //通过流程对象接口获取流程结果对象，用于获取流程输出
       //注意每次流程执行后，通过重新获取结果对象刷新其中输出数据
       //该操作存在耗时，建议获取结果对象后，直接使用对象获取具体输出数据
        IMVSProcedureResults* pRes = pVmPrc->GetResult();
        if (NULL != pRes)
        {
            IoImage outputImage = pRes->GetOutputImageV2("ImageData0");
            std::cout << "Width " << outputImage.stImage.Width << " Height " <<  outputImage.stImage.Height << std::endl;
            stbi_write_png("sol.png", outputImage.stImage.Width, outputImage.stImage.Height, 3, outputImage.stImage.ImageData, 0);
        }
        std::cout << "debug 5" << std::endl;
   
        //关闭当前方案
        DestroySolutionInstance(pVmSol);

        //退出程序前释放所有资源，注意避免在析构函数中调用
        DisposeResource();
    }
    catch (CVmException vmex)
    {
        return vmex.GetErrorCode();
    }
    catch (...)
    {
        return IMVS_EC_UNKNOWN;
    }

    return IMVS_EC_OK;
}
