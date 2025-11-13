#include "MindVisonCamera.h"
#include "MindVisionSDK.h"
#include <stdio.h>
#include <vector>
#include <memory>
int MindVisionMain2(int argc, char** argv)
{
    MindVisionSDK SDK;
    int n = SDK.CameraEnumerateDeviceEx();
    std::vector<tSdkCameraDevInfo> pCameraList(n);
    SDK.CameraEnumerateDevice(pCameraList.data(), &n);
    printf("device = %d\n", n);

    CameraSetSysOption("NumBuffers", "3");
    //int                     iCameraCounts = 4;
    //int                     iStatus = -1;
    //tSdkCameraDevInfo       tCameraEnumList[4];
    //CameraEnumerateDevice(tCameraEnumList, &iCameraCounts);
    //n = iCameraCounts;
    
    int ret = 0;
    std::vector<std::unique_ptr<MindVisonCamera>> Cameras(n);
    for (int i = 0; i < n; i++)
    {
        Cameras[i].reset(new MindVisonCamera());
        //strcpy(pCameraList[i].acFriendlyName, "Camera MV-GE1201C#A9FE460F0");
        printf("debug 1-1: %d, %s\n", i, pCameraList[i].acFriendlyName);
        ret = Cameras[i]->CameraInit(&pCameraList[i], 0, 0);
        if (ret != CAMERA_STATUS_SUCCESS)
        {
            printf("CameraInit failed : %d\n", i);
            return -1;
        }
    }
    for (int i = 0; i < n; i++)
    {
        ret = Cameras[i]->CameraUnInit();
        if (ret != CAMERA_STATUS_SUCCESS)
        {
            printf("CameraUnInit failed : %d\n", i);
            return -1;
        }
    }
    printf("debug 3\n");
    return 0;
}

int MindVisionMain(int argc, char** argv)
{
    CameraSdkStatus status;

    // 调用CameraEnumerateDevice前，先设置CameraNums = 16，表示最多只读取16个设备。
    // 如果需要枚举更多的设备，请更改CameraList数组的大小和CameraNums的值
    // Before calling CameraEnumerateDevice, set CameraNums = 16 to read only 16 devices at most.
    // If you need to enumerate more devices, change the size of the CameraList array and CameraNums
    tSdkCameraDevInfo CameraList[16];
    int CameraNums = 16;

    // 枚举设备，获得设备列表
    // Enumerate devices to get a list of devices
    status = CameraEnumerateDevice(CameraList, &CameraNums);
    if (status != CAMERA_STATUS_SUCCESS)
    {
        printf("No camera was found!");
        return -1;
    }
    printf("debug 1\n");
    // 该示例中，我们只初始化第一个相机。
    // (-1,-1)表示加载上次退出前保存的参数，如果是第一次使用该相机，则加载默认参数。
    // In this example, we only initialize the first camera.
    // (-1,-1) means to load the parameters saved before the last exit. If it is the first time to use the camera, then load the default parameters.
    int hCamera = 0;
    status = CameraInit(&CameraList[0], -1, -1, &hCamera);
    if (status != CAMERA_STATUS_SUCCESS)
    {
        printf("Failed to init the camera! Error code is %d", status);
        return -1;
    }
    printf("debug 2\n");
    // 获得该相机的特性描述
    // Get the camera's feature description
    tSdkCameraCapbility CameraInfo;
    CameraGetCapability(hCamera, &CameraInfo);

    // 判断是黑白相机还是彩色相机
    // Judging whether it is a mono camera or a color camera
    BOOL bMonoCamera = CameraInfo.sIspCapacity.bMonoSensor;

    // 黑白相机让ISP直接输出MONO数据，而不是扩展成R=G=B的24位灰度
    // Mono cameras allow the ISP to directly output MONO data instead of the 24-bit grayscale expanded to R=G=B
    if (bMonoCamera)
    {
        CameraSetIspOutFormat(hCamera, CAMERA_MEDIA_TYPE_MONO8);
    }
    printf("debug 3\n");
    // 相机模式切换成连续采集
    // Switch camera mode to continuous acquisition
    CameraSetTriggerMode(hCamera, 0);

    // 手动曝光，曝光时间30ms
    // Manual exposure, exposure time 30ms
    CameraSetAeState(hCamera, FALSE);
    CameraSetExposureTime(hCamera, 30 * 1000);

    // 让SDK内部取图线程开始工作
    // Let the SDK internal grab thread start working
    CameraPlay(hCamera);
    printf("debug 4\n");
    // 计算RGB buffer所需的大小，这里直接按照相机的最大分辨率来分配
    UINT FrameBufferSize = CameraInfo.sResolutionRange.iWidthMax * CameraInfo.sResolutionRange.iHeightMax * (bMonoCamera ? 1 : 3);
    printf("iWidthMax %u\n", CameraInfo.sResolutionRange.iWidthMax);
    printf("iHeightMax %u\n", CameraInfo.sResolutionRange.iHeightMax);
    printf("FrameBufferSize %u\n", FrameBufferSize);
    // 分配RGB buffer，用来存放ISP输出的图像
    // 备注：从相机传输到PC端的是RAW数据，在PC端通过软件ISP转为RGB数据（如果是黑白相机就不需要转换格式，但是ISP还有其它处理，所以也需要分配这个buffer）
    // allocate RGB buffer to store the image output by ISP
    // Note: RAW data is transferred from the camera to the PC and converted to RGB data via the software ISP on the PC (if it is a Mono camera, there is no need to convert the format, but the ISP has other processing, so we also need to allocate this buffer)
    BYTE* pFrameBuffer = (BYTE*)CameraAlignMalloc(FrameBufferSize, 16);
    printf("debug 5\n");
    // 从相机取一帧图片
    // Take a frame from the camera
    tSdkFrameHead FrameHead;
    BYTE* pRawData;
    status = CameraGetImageBuffer(hCamera, &FrameHead, &pRawData, 2000);
    printf("CameraGetImageBuffer status  %d\n", status);
    if (status == CAMERA_STATUS_SUCCESS)
    {
        printf("debug 6\n");
        CameraImageProcess(hCamera, pRawData, pFrameBuffer, &FrameHead);
        CameraReleaseImageBuffer(hCamera, pRawData);
        char* str = (char *)"c:/grab.bmp";
        // 此时图片已经存储在pFrameBuffer中，对于彩色相机pFrameBuffer=RGB数据，黑白相机pFrameBuffer=8位灰度数据
        // 该示例中我们只是把图片保存到硬盘文件中
        // At this point, the picture has been stored in pFrameBuffer. For pFrameBuffer=RGB data in color camera, pFrameBuffer=8bit gray data in mono camera.
        // In this example we just saved the image to a hard disk file
        status = CameraSaveImage(hCamera, str, pFrameBuffer, &FrameHead, bMonoCamera ? FILE_BMP_8BIT : FILE_BMP, 100);
        if (status == CAMERA_STATUS_SUCCESS)
            printf("Save image successfully. image_size = %dX%d\n", FrameHead.iWidth, FrameHead.iHeight);
        else
            printf("Save image failed. err=%d\n", status);
    }
    printf("debug 7\n");
    // 关闭相机
    // close camera
    CameraUnInit(hCamera);

    // release RGB buffer
    CameraAlignFree(pFrameBuffer);

    return 0;
}
