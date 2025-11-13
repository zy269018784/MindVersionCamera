#pragma once
#include <QQuickImageProvider>
#include "MindVersion/MindVisonCamera.h"
class LiveImageProvider : public QQuickImageProvider
{
public:
    LiveImageProvider();
    ~LiveImageProvider();
    QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize) override;

private:
    MindVisonCamera Camera;
};