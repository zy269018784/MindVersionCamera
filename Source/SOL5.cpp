#include "IVmSolution.h"
#include "VMException.h"
#include "IVmImageSource.h"
#include "IVmProcedure.h"
#include "IVmFastFeatureMatch.h"
#include "IVMAffineTransform.h"
using namespace VisionMasterSDK;
using namespace VisionMasterSDK::VmSolution;
using namespace VisionMasterSDK::VmProcedure;
using namespace VisionMasterSDK::ImageSourceModule;
using namespace VisionMasterSDK::IMVSAffineTransformModu;
using namespace VisionMasterSDK::IMVSFastFeatureMatchModu;

/*
    stb
*/
#define STBI_WINDOWS_UTF8
#include <stb_image.h>
#include <stb_image_write.h>
int __stdcall CallBackFunc1(OUT OutputPlatformInfo* const pstOutputInfo, IN void* const pUser)
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

int SOL5(void)
{
    try
    {
        //----------------------------------------------------------------------------------------------------
        /*
            加载方案
        */
        IVmSolution* pVmSol = LoadSolution("C:\\Test1.sol", "");
        if (NULL == pVmSol) return -1;
        pVmSol->EnableModulesCallback();
        //pVmSol->RegisterCallBack(CallBackFunc1, nullptr);

        /*
            运行方案
        */
        printf("Solution Run\n");
        pVmSol->Run();
        //----------------------------------------------------------------------------------------------------

        /*
            获取流程
        */
        IVmProcedure* pVmPrc = (IVmProcedure*)(*pVmSol)["流程1"];

        /*
           运行流程
       */
        printf("Procedure Run\n");
        pVmPrc->EnableProcedure();
        pVmPrc->Run();
        IMVSProcedureResults* ProcedureResult = pVmPrc->GetResult();
        if (ProcedureResult)
        {
            printf("error %d\n", ProcedureResult->GetErrorCode());
            IoNameInfoArray NameInfoArray = ProcedureResult->GetAllOutputNameInfo();
            for (int i = 0; i < NameInfoArray.nNameNum; i++)
            {
                printf("strIoName %s\n", NameInfoArray.pstIo[i].strIoName);
            }
            //IoImage image = ProcedureResult->GetOutputImageV2("ImageData0");
           //printf("eType %d\n", image.eType);
        }
        //----------------------------------------------------------------------------------------------------
        /*
            获取模块
        */
        IMVSAffineTransformModuTool * AffineTransformModule = (IMVSAffineTransformModuTool*)(*pVmSol)["流程1.仿射变换1"];
        AffineTransformParams * AffineTransformParams = AffineTransformModule->GetParamObj();
        printf("GetMirrorOrientation %d\n", AffineTransformParams->GetMirrorOrientation());
        AffineTransformParams->SetMirrorOrientation(MirrorOrientation_Horizontal);
        unsigned char *InputData = new unsigned char[32 * 32 * 3];
        ImageBaseData InputValue;
        InputValue.ImageData = InputData;
        InputValue.Width = 32;
        InputValue.Height = 32;
        InputValue.DataLen = 32 * 32 * 3;
        InputValue.Pixelformat = MVD_PIXEL_RGB_RGB24_C3;
        for (int i = 0; i < 32; i++)
        {
            for (int j = 0; j < 32; j++)
            {
                int offset = 3 * (i * 32 + j);
                InputData[offset + 0] = 0;
                InputData[offset + 1] = 255;
                InputData[offset + 2] = 0;
                if (j < 16)
                {
                    InputData[offset + 0] = 255;
                    InputData[offset + 1] = 0;
                    InputData[offset + 2] = 0;
                }
            }
        }
        AffineTransformParams->SetInputImage(&InputValue);

        AffineTransformModule->Run();
        auto AffineTransformModuleResult = AffineTransformModule->GetResult();
        if (AffineTransformModuleResult)
        {
            printf("AffineTransformModuleResult\n");
            auto OutputImage = AffineTransformModuleResult->GetOutputImage();
            printf("%d %d, Pixelformat %d\n", OutputImage.Width, OutputImage.Height, OutputImage.Pixelformat);
            if (OutputImage.Width > 0)
            {
                stbi_write_png("C:\\AffineTransform.png", OutputImage.Width, OutputImage.Height, 3, OutputImage.ImageData, 0);
                //stbi_write_jpg("C:\\imagesource.jpg", outputImage.Width, outputImage.Height, 3, outputImage.ImageData, 100);
            }
        }
        //----------------------------------------------------------------------------------------------------
        /*
            获取模块
        */
        ImageSourceModuleTool* ImageSourceModule = (ImageSourceModuleTool*)(*pVmSol)["流程1.图像源1"];
        if (NULL == ImageSourceModule) return -1;
        ImageSourceModule->SetImagePath("C:\\1.jpg");

        /*
            模块参数
        */
        ImageSourceParams *Params = ImageSourceModule->GetParamObj();
        printf("GetSolSaveImageData %d\n", Params->GetSolSaveImageData());
        printf("GetTriggerProcessRun %d\n", Params->GetTriggerProcessRun());

        Params->SetImageSourceType(ImageSourceTypeEnum::ImageSourceType_SDK);
        Params->SetTriggerProcessRun(true);
        Params->SetSolSaveImageData(true);

 
        unsigned char *image = new unsigned char[831 * 469 * 3];
        ImageBaseData inputImage = { 0 };
        inputImage.Width = 831;
        inputImage.Height = 469;
        inputImage.DataLen = inputImage.Width * inputImage.Height * 3;
        inputImage.Pixelformat = MVD_PIXEL_RGB_RGB24_C3;
        inputImage.ImageData = image;
        if (NULL != ImageSourceModule)
        {
            ImageSourceModule->SetImageData(&inputImage);
        }

        /*
            运行模块
        */
        printf("Module Run\n");
        ImageSourceModule->Run();
        ImageSourceResults* pRes = ImageSourceModule->GetResult();
        ImageBaseData outputImage = { 0 };
        if (NULL != pRes)
        {
        
            printf("Module Run 1\n");
            outputImage = pRes->GetImageData();
            printf("Module Run 2\n");
            printf("%d %d, Pixelformat %d\n", outputImage.Width, outputImage.Height, outputImage.Pixelformat);

            for (int i = 0; i < 30; i++)
                //printf("%d ", ((unsigned char*)outputImage.ImageData)[i]);
                 printf("%d ", image[i]);
            printf("\n");
            if (outputImage.Width > 0)
            {
                stbi_write_png("C:\\imagesource.png", outputImage.Width, outputImage.Height, 3, outputImage.ImageData, 0);
                //stbi_write_jpg("C:\\imagesource.jpg", outputImage.Width, outputImage.Height, 3, outputImage.ImageData, 100);
            }
            printf("Module Run 3\n");
        }


        //----------------------------------------------------------------------------------------------------

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
