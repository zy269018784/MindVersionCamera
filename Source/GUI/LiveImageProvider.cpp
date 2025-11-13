#include "LiveImageProvider.h"
#include <QDebug>
#include "MindVersion/MindVisonCamera.h"
/*
    image://[provider_name]/[image_id]?[optional_parameters]
*/
LiveImageProvider::LiveImageProvider() 
    : QQuickImageProvider(QQuickImageProvider::Image)
{
    CameraSdkStatus status;
    tSdkCameraDevInfo CameraList[16];
    int CameraNums = 1;

    status = CameraEnumerateDevice(CameraList, &CameraNums);
    if (status != CAMERA_STATUS_SUCCESS)
    {
        printf("No camera was found!");
        return;
    }


}

LiveImageProvider::~LiveImageProvider()
{
    qDebug() << __FUNCTION__;
}

QImage LiveImageProvider::requestImage(const QString& id, QSize* size, const QSize& requestedSize)
{
    return QImage("1.png");
}