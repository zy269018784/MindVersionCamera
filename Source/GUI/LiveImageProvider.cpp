#include "LiveImageProvider.h"
#include <QDebug>
#include "MindVersion/MindVisonCamera.h"
/*
    image://[provider_name]/[image_id]?[optional_parameters]
*/
LiveImageProvider::LiveImageProvider() 
    : QQuickImageProvider(QQuickImageProvider::Image)
{
    SDK.Camera.CameraPlay();
}

LiveImageProvider::~LiveImageProvider()
{
    qDebug() << __FUNCTION__; 
    SDK.Camera.CameraStop();
}

QImage LiveImageProvider::requestImage(const QString& id, QSize* size, const QSize& requestedSize)
{
    tSdkFrameHead FrameHead;
    BYTE* pRawData;


   // SDK.Camera.CameraPlay();
    SDK.Camera.CameraGetImageBuffer(&FrameHead, &pRawData, 2000);
    SDK.Camera.CameraImageProcess(pRawData, SDK.Camera.pFrameBuffer, &FrameHead);
    SDK.Camera.CameraReleaseImageBuffer(pRawData);
   // SDK.Camera.CameraPause();
    qDebug() << "id " << id;

    return QImage(SDK.Camera.pFrameBuffer, SDK.Camera.CameraInfo.sResolutionRange.iWidthMax, SDK.Camera.CameraInfo.sResolutionRange.iHeightMax, QImage::Format_BGR888);

    
    return QImage("1.png");
}