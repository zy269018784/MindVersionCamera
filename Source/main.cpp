#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "GUI/LiveImageProvider.h"
int MindVisionMain(int argc, char** argv);
int SOL(void);
int SOL2(void);
int SOL3(void);
int SOL4(void);
int SOL5(void);
int main(int argc, char* argv[])
{
    return SOL5();
   // return SOL();
   // return MindVisionMain(argc, argv);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.addImageProvider("live", new LiveImageProvider());
    engine.load(QUrl(QStringLiteral("MyQML/MyWindow.qml")));
    int ret = app.exec();
    return ret;
}