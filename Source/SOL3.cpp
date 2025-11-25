#include "IVmSolution.h"
#include "VMException.h"
#include "IVmImageSource.h"
#include "IVmFastFeatureMatch.h"
using namespace VisionMasterSDK;
using namespace VisionMasterSDK::VmSolution;
using namespace VisionMasterSDK::ImageSourceModule;
using namespace VisionMasterSDK::IMVSFastFeatureMatchModu;


/*
    stb
*/
#define STBI_WINDOWS_UTF8
#include <stb_image.h>
#include <stb_image_write.h>

int SOL3(void)
{
    try
    {
        //加载方案，仅支持绝对路径，编码格式UTF-8
        IVmSolution* pVmSol = LoadSolution("C:\\Test1.sol", "");
        if (NULL == pVmSol) return -1;
        //使用模块全名称获取模块对象
        ImageSourceModuleTool* imageModu = (ImageSourceModuleTool*)(*pVmSol)["流程1.图像源1"];
        if (NULL == imageModu) return -1;
#if 0
        //通过模块对象接口获取模块参数对象，用于设置/获取模块参数
        imageModu->GetParamObj()->SetImageSourceType(ImageSourceTypeEnum::ImageSourceType_SDK);
        //图像源模块选择SDK模式，可使用接口设置图像数据
        //注意设置后图像数据仅当次执行有效，执行完成后清空，再次执行需再次设置
        imageModu->SetImagePath("C:\\grab2.png");
        unsigned char *image = new unsigned char[4000 * 3000 * 3];
        ImageBaseData inputImage = { 0 };
        inputImage.Width = 4000;
        inputImage.Height = 3000;
        inputImage.DataLen = inputImage.Width * inputImage.Height * 3;
        inputImage.Pixelformat = MVD_PIXEL_RGB_RGB24_C3;
        inputImage.ImageData = image;
        if (NULL != imageModu)
        {
            imageModu->SetImageData(&inputImage);
        }
#else
        //unsigned char* image = new unsigned char[4000 * 3000];
        //ImageBaseData inputImage = { 0 };
        //inputImage.Width = 4000;
        //inputImage.Height = 3000;
        //inputImage.DataLen = inputImage.Width * inputImage.Height;
        //inputImage.Pixelformat = MVD_PIXEL_MONO_08;
        //inputImage.ImageData = image;
        //if (NULL != imageModu)
        //{
        //    imageModu->SetImageData(&inputImage);
        //}

        ImageSourceParams* Params = imageModu->GetParamObj();
        Params->SetImageSourceType(ImageSourceTypeEnum::ImageSourceType_Camera);
        Params->SetPixelFormat(PixelFormat_RGB24);
        char CameraName[100];
        Params->GetCameraName(CameraName);
        printf("CameraName %s\n", CameraName);
        printf("PixelFormat %d\n", Params->GetPixelFormat());
#endif
        printf("debug 6\n");

        //方案同步执行一次
        pVmSol->Run();
        imageModu->Run();
        printf("debug 7\n");
        //通过模块对象接口获取模块结果对象，用于获取模块输出
        //注意每次方案执行后，通过重新获取结果对象刷新其中输出数据
        //该操作存在耗时，建议获取结果对象后，直接使用对象获取具体输出数据
        ImageSourceResults* pRes = imageModu->GetResult();
        ImageBaseData outputImage = { 0 };
        if (NULL != pRes)
        {
            outputImage = pRes->GetImageData();
        }  
        
        printf("%d %d, Pixelformat %d\n", outputImage.Width, outputImage.Height, outputImage.Pixelformat);
        if (outputImage.Width > 0)
        {

            stbi_write_png("C:\\imagesource.png", outputImage.Width, outputImage.Height, 3, outputImage.ImageData, 0);
        }
        
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
