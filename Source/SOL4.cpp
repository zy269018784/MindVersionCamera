#include "IVmSolution.h"
#include "VMException.h"
#include "IVmProcedure.h"
#include "IVmImageSource.h"
#include <iostream>

using namespace VisionMasterSDK;
using namespace VisionMasterSDK::VmSolution;
using namespace VisionMasterSDK::VmProcedure;
using namespace VisionMasterSDK::ImageSourceModule;

/*
    stb
*/
#define STBI_WINDOWS_UTF8
#include <stb_image.h>
#include <stb_image_write.h>

int SOL4(void)
{
    try
    {
        //创建方案单例，用于初始化资源，方案对象可用于注册回调函数/事件等操作
        IVmSolution* pVmSol = CreateSolutionInstance();

        //获取已存在的方案对象，用于跨类操作方案
        pVmSol = GetSolutionExistedInstance();

        //加载方案，仅支持绝对路径，编码格式UTF-8
        pVmSol = LoadSolution("C:\\Test1.sol", "");
        if (NULL == pVmSol) return IMVS_EC_NULL_PTR;

        ImageSourceModuleTool* imageModu = (ImageSourceModuleTool*)(*pVmSol)["流程1.图像源1"];
        if (NULL == imageModu) return -1;

        //获取方案版本号 
        string strVersion = pVmSol->GetSolutionVersion();

        //判断方案是否加密
        bool bPassword = pVmSol->HasPassword();

        //获取当前方案路径
        string strPath = pVmSol->GetSolutionPath();

        //使用流程名称获取流程对象
        IVmProcedure* pVmPrc = (IVmProcedure*)(*pVmSol)["流程1"];

        //获取方案所有流程对象
        ObjectList procedureObjList = pVmSol->GetAllProcedureObjects();

        //获取方案所有流程信息
        ProcessInfoList* procedureList = pVmSol->GetAllProcedureList();

        //获取方案所有模块信息
        ModuleInfoList* moduInfoList = pVmSol->GetAllModuleList();
        for (int i = 0; i < moduInfoList->nNum; i++)
        {
            // moduInfoList->astModuleInfo[i].strModuleName;
            std::cout << "name " << moduInfoList->astModuleInfo[i].strModuleName << std::endl;
        }

        std::cout << "moduInfoList->nNum " << moduInfoList->nNum << std::endl;

        //方案同步执行一次
        //pVmSol->Run();
        imageModu->Run();
        //IMVSProcedureResults *Result = pVmPrc->GetResult();
        ImageSourceResults* Result = imageModu->GetResult();
        if (Result)
        {
            std::cout << "error " << Result->GetErrorCode() << std::endl;
            std::cout << "FrameNum " << Result->GetFrameNum() << std::endl;
            std::cout << "GetModuRunTime " << Result->GetModuRunTime() << std::endl;
            ImageBaseData outputImage = Result->GetImageDataMono8();
            printf("%d %d, Pixelformat %d\n", outputImage.Width, outputImage.Height, outputImage.Pixelformat);
            if (outputImage.Width > 0)
            {
                stbi_write_png("C:\\imagesource.png", outputImage.Width, outputImage.Height, 3, outputImage.ImageData, 0);
            }
        }
        else
        {
            printf("result is NULL\n");
        }

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
