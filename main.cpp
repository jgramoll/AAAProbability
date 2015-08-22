#include <QGuiApplication>
#include <QQmlContext>

#include "AAAProbability.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    AAAProbability aaaProbability;
    aaaProbability.rootContext()->setContextProperty("aaaProbability", &aaaProbability);


#ifdef Q_OS_WIN
    aaaProbability.setSource(QUrl("../AAAProbability/qml/main.qml"));
    aaaProbability.show();
    aaaProbability.setWidth(700);
    aaaProbability.setHeight(1000);
    aaaProbability.setPosition(10, 30);
#else
    aaaProbability.setSource(QUrl("qrc:/qml/main.qml"));
    aaaProbability.showMaximized();
#endif

    return app.exec();
}
