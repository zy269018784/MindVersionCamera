#pragma once
#include <QQuickImageProvider>

class LiveImageProvider : public QQuickImageProvider
{
public:
    LiveImageProvider();
    QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize) override;
};