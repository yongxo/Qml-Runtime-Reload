TEMPLATE = app

QT += qml quick

SOURCES += main.cpp \
    appmanager.cpp \
    settingsmanager.cpp


HEADERS += \
    appmanager.h \
    settingsmanager.h

RESOURCES += qml.qrc
CONFIG(debug):message("Debug Build!")

lessThan(QT_VERSION, 5.4.0): error(This project requires Qt 5.4.0 or later)


debug{
DEFINES += RELOAD_ENABLED
}


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)


