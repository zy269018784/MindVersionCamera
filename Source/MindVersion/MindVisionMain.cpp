#include "MindVisonCamera.h"
#include "MindVisionSDK.h"
#include <stdio.h>
#include <vector>
#include <memory>
#include <QImage>

int MindVisionMain1(int argc, char** argv)
{
    MindVisonCamera Camera;

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
    printf("CameraNums %d\n", CameraNums);
    // 该示例中，我们只初始化第一个相机。
    // (-1,-1)表示加载上次退出前保存的参数，如果是第一次使用该相机，则加载默认参数。
    // In this example, we only initialize the first camera.
    // (-1,-1) means to load the parameters saved before the last exit. If it is the first time to use the camera, then load the default parameters.
    status = Camera.CameraInit(&CameraList[0], -1, -1);
    //status = CameraInit(&CameraList[0], -1, -1, &hCamera);
    if (status != CAMERA_STATUS_SUCCESS)
    {
        printf("CameraInit Error code: %d", status);
        return -1;
    }

    // 获得该相机的特性描述
    // Get the camera's feature description
    tSdkCameraCapbility CameraInfo;
    status = Camera.CameraGetCapability(&CameraInfo);
    if (status != CAMERA_STATUS_SUCCESS)
    {
        printf("CameraGetCapability Error code: %d", status);
        return -1;
    }
    // 判断是黑白相机还是彩色相机
    // Judging whether it is a mono camera or a color camera
    BOOL bMonoCamera = CameraInfo.sIspCapacity.bMonoSensor;
    printf("bMonoCamera %d\n", bMonoCamera);
    // 黑白相机让ISP直接输出MONO数据，而不是扩展成R=G=B的24位灰度
    // Mono cameras allow the ISP to directly output MONO data instead of the 24-bit grayscale expanded to R=G=B
    if (bMonoCamera)
    {
        Camera.CameraSetIspOutFormat(CAMERA_MEDIA_TYPE_MONO8);
    }
    // 相机模式切换成连续采集
    // Switch camera mode to continuous acquisition
    Camera.CameraSetTriggerMode(0);

    // 手动曝光，曝光时间30ms
    // Manual exposure, exposure time 30ms
    /*
        手动曝光
    */
    Camera.CameraSetAeState(FALSE);
    Camera.CameraSetExposureTime(30 * 1000);

    // 让SDK内部取图线程开始工作
    // Let the SDK internal grab thread start working
    Camera.CameraPlay();
    printf("channels %d\n", (bMonoCamera ? 1 : 3));
    // 计算RGB buffer所需的大小，这里直接按照相机的最大分辨率来分配
    UINT FrameBufferSize = CameraInfo.sResolutionRange.iWidthMax * CameraInfo.sResolutionRange.iHeightMax * (bMonoCamera ? 1 : 3);
    printf("iWidthMax %u\n", CameraInfo.sResolutionRange.iWidthMax);
    printf("iHeightMax %u\n", CameraInfo.sResolutionRange.iHeightMax);
    printf("FrameBufferSize %u MB\n", FrameBufferSize / 1024 / 1024);
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
    status = Camera.CameraGetImageBuffer(&FrameHead, &pRawData, 2000);
    printf("CameraGetImageBuffer status  %d\n", status);
    if (status == CAMERA_STATUS_SUCCESS)
    {
        printf("debug 6\n");
        Camera.CameraImageProcess(pRawData, pFrameBuffer, &FrameHead);
        Camera.CameraReleaseImageBuffer(pRawData);
        char* str = (char*)"c:/grab2.png";

        QImage img(pFrameBuffer, CameraInfo.sResolutionRange.iWidthMax, CameraInfo.sResolutionRange.iHeightMax, QImage::Format_BGR888);
        img.save("c:/grab.png");
        // 此时图片已经存储在pFrameBuffer中，对于彩色相机pFrameBuffer=RGB数据，黑白相机pFrameBuffer=8位灰度数据
        // 该示例中我们只是把图片保存到硬盘文件中
        // At this point, the picture has been stored in pFrameBuffer. For pFrameBuffer=RGB data in color camera, pFrameBuffer=8bit gray data in mono camera.
        // In this example we just saved the image to a hard disk file
       // status = CameraSaveImage(hCamera, str, pFrameBuffer, &FrameHead, bMonoCamera ? FILE_BMP_8BIT : FILE_BMP, 100);
        status = Camera.CameraSaveImage(str, pFrameBuffer, &FrameHead, bMonoCamera ? FILE_PNG_8BIT : FILE_PNG, 100);
        if (status == CAMERA_STATUS_SUCCESS)
            printf("Save image successfully. image_size = %dX%d\n", FrameHead.iWidth, FrameHead.iHeight);
        else
            printf("Save image failed. err=%d\n", status);
    }
    printf("debug 7\n");
    // 关闭相机
    // close camera
    Camera.CameraUnInit();

    // release RGB buffer
    CameraAlignFree(pFrameBuffer);

    return 0;
}

int MindVisionMain(int argc, char** argv)
{
    MindVisionSDK SDK;
    MindVisonCamera& Camera = SDK.Camera;

    CameraSdkStatus status;

    // 让SDK内部取图线程开始工作
    Camera.CameraPlay();

    BYTE* pFrameBuffer = SDK.Camera.pFrameBuffer;


    // 从相机取一帧图片
    // Take a frame from the camera
    tSdkFrameHead FrameHead;
    BYTE* pRawData;
    status = Camera.CameraGetImageBuffer(&FrameHead, &pRawData, 2000);
    printf("CameraGetImageBuffer status  %d\n", status);
    if (status == CAMERA_STATUS_SUCCESS)
    {
        printf("debug 6\n");
        Camera.CameraImageProcess(pRawData, pFrameBuffer, &FrameHead);
        Camera.CameraReleaseImageBuffer(pRawData);
        char* str = (char*)"c:/grab2.png";

        QImage img(pFrameBuffer, SDK.Camera.CameraInfo.sResolutionRange.iWidthMax, SDK.Camera.CameraInfo.sResolutionRange.iHeightMax, QImage::Format_BGR888);
        img.save("c:/grab.png");

        // 此时图片已经存储在pFrameBuffer中，对于彩色相机pFrameBuffer=RGB数据，黑白相机pFrameBuffer=8位灰度数据
        status = Camera.CameraSaveImage(str, pFrameBuffer, &FrameHead, SDK.Camera.bMonoCamera ? FILE_PNG_8BIT : FILE_PNG, 100);
        if (status == CAMERA_STATUS_SUCCESS)
            printf("Save image successfully. image_size = %dX%d\n", FrameHead.iWidth, FrameHead.iHeight);
        else
            printf("Save image failed. err=%d\n", status);
    }

    return 0;
}
