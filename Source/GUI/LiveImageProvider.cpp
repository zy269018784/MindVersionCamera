#include "LiveImageProvider.h"
/*
    image://[provider_name]/[image_id]?[optional_parameters]
*/
LiveImageProvider::LiveImageProvider() 
    : QQuickImageProvider(QQuickImageProvider::Image)
{

}

QImage LiveImageProvider::requestImage(const QString& id, QSize* size, const QSize& requestedSize)
{
    return QImage("1.png");
}