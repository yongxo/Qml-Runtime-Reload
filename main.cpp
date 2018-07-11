#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "appmanager.h"
#include "qdebug.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("ICS");
    QCoreApplication::setOrganizationDomain("ICS.com");
    QCoreApplication::setApplicationName("Qml Runtime Reload Example");

    QGuiApplication app(argc, argv);
    AppManager *manager = new AppManager();
    qDebug() << Q_FUNC_INFO << manager->thread();
    return app.exec();
}
