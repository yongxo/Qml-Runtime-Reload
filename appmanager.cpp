#include "appmanager.h"
#include "qquickview.h"
#include "qqmlcontext.h"
#include "settingsmanager.h"
#include "qfileselector.h"
#include "qqmlfileselector.h"
#include "qdebug.h"
#include "qcoreapplication.h"
#include "qtimer.h"
#include "qfileselector.h"
#include "qqmlapplicationengine.h"
#include "qdir.h"
#include "qguiapplication.h"
AppManager::AppManager( QObject *parent) : QObject(parent),
    mSettings(new SettingsManager()),
    mb_startingUp(true),
    mSelector(0),
    mView(new QQuickView()),
    mWindowEngine(new QQmlApplicationEngine())
{

    if(restoreSettings()){

    }

    connect(this, &AppManager::usingWindowChanged, this, &AppManager::handleModeSwitch, Qt::QueuedConnection);


#ifdef RELOAD_ENABLED
    mLoadingMode=DISK;
#else
    mLoadingMode = QRC;
#endif

    if(m_usingWindow){
        mWindowEngine->rootContext()->setContextProperty("app", this);
        mWindowEngine->rootContext()->setContextProperty("appSettings", mSettings);
    } else {
        mView->rootContext()->setContextProperty("app", this);
        mView->rootContext()->setContextProperty("appSettings", mSettings);
        mView->setResizeMode(QQuickView::SizeRootObjectToView);
        mView->setBaseSize(QSize(1280, 720));
    }
    QDir d;
    switch (mLoadingMode) {
    case QRC:m_qmlPath = "qrc:/qml/"; break;
    case WEB:m_qmlPath = "http://wopr.local/qml"; break;
    case DISK:
        //ugly per os
#ifdef Q_OS_LINUX
        m_qmlPath = QCoreApplication::applicationDirPath()+"/qml/";
        qDebug() << "m_qmlPath:" << m_qmlPath;
        break;
#elif defined(Q_OS_OSX)

#elif defined(WIN32)
        m_qmlPath = "qml/";
#endif
    default:
        break;
    }

    if(m_usingWindow){

    } else {
        mView->setSource(QUrl(m_qmlPath+"Loading.qml"));
        mView->showNormal();
    }

    if(m_usingWindow){
        mSkinList.append("window");
    } else {
        mSkinList.append("controls");
        mSkinList.append("vanilla");
    }

    setupSelectors();   
}

void AppManager::reload()
{

    QTimer *delayTimer= new QTimer(this);
    delayTimer->setInterval(500);
    delayTimer->setSingleShot(true);
    connect(delayTimer, SIGNAL(timeout()), this, SLOT(delayReloadQml()), Qt::QueuedConnection);
    delayTimer->start();

}

void AppManager::setLanguage()
{

}

void AppManager::handleModeSwitch()
{
    qDebug() << Q_FUNC_INFO;
    //QGuiApplication::setQuitOnLastWindowClosed(false) is set before we close any QQuickWindows. This is because the application would exit otherwise.
    QGuiApplication::setQuitOnLastWindowClosed(false);
    mSkinList.clear();

    if(m_usingWindow){

        mSkinList.append("window");
        if(mWindowEngine){
            mWindowEngine->deleteLater();
        }
        mWindowEngine = new QQmlApplicationEngine();
        m_currentSkinEntry="window";
        mWindowEngine->rootContext()->setContextProperty("app", this);
        mWindowEngine->rootContext()->setContextProperty("appSettings", mSettings);

        mView->close();
    }else {
        if(mView){
            mView->deleteLater();
        }
        mView=new QQuickView();
        mView->rootContext()->setContextProperty("app", this);
        mView->rootContext()->setContextProperty("appSettings", mSettings);

        mSkinList.append("controls");
        mSkinList.append("vanilla");
        m_currentSkinEntry = "vanilla";
        emit started();
    }
    setupSelectors();
    //QGuiApplication::setQuitOnLastWindowClosed(true) is set so that the window will close normally if the close button is clicked.
    QGuiApplication::setQuitOnLastWindowClosed(true);
}


bool AppManager::restoreSettings()
{
    qDebug() << Q_FUNC_INFO;
    m_usingWindow = mSettings->getSetting("usingWindow").toBool();
    qDebug() << "m_usingWindow:" << m_usingWindow;

    m_currentSkinEntry = mSettings->getSetting("skin").toString();
    qDebug() << "m_currentSkinEntry:" << m_currentSkinEntry;

    if(m_usingWindow){
        if(!mSkinList.contains(m_currentSkinEntry)){
            m_currentSkinEntry = "window";
        }
    }

    m_currentTheme = mSettings->getSetting("theme").toString();
    if(m_currentTheme.isEmpty()){
        m_currentTheme="morning";
    }

    m_currentScreen=mSettings->getSetting("screen").toString();
    qDebug() << "m_currentScreen :" << m_currentScreen ;
    qDebug() << "m_currentTheme :" << m_currentTheme ;
    return true;
}

void AppManager::delayReloadQml(){
    qDebug() << Q_FUNC_INFO;
    if(m_usingWindow){
        emit started();
        mWindowEngine->clearComponentCache();
        mWindowEngine->load(adjustPath("main.qml"));

    } else {

        mView->engine()->clearComponentCache();
        mView->setSource(QUrl(adjustPath("main.qml")));
    }

}
bool AppManager::usingWindow() const
{
    return m_usingWindow;
}

void AppManager::setUsingWindow(bool usingWindow)
{
    if(usingWindow == m_usingWindow) return;
    m_usingWindow = usingWindow;
    mSettings->writeSetting("usingWindow", QVariant(m_usingWindow));
    emit usingWindowChanged();
}


QString AppManager::currentScreen() const
{
    return m_currentScreen;
}

void AppManager::setCurrentScreen(const QString &currentScreen)
{
    m_currentScreen = currentScreen;
    mSettings->writeSetting("screen", QVariant(m_currentScreen));
    emit currentScreenChanged();
}

QString AppManager::adjustPath(QString qmlFile)
{


    QString returnPath =  mSelector->select(m_qmlPath+qmlFile);
    qDebug() << "Selected Path" << returnPath;
    return returnPath;
}

QString AppManager::dayOfWeek(int day)
{
    switch (day) {
    case 0: return tr("Sunday"); break;
    case 1: return tr("Monday"); break;
    case 2: return tr("Tuesday"); break;
    case 3: return tr("Wednesday"); break;
    case 4: return tr("Thursday"); break;
    case 5: return tr("Friday"); break;
    case 6: return tr("Saturday"); break;
    default: return tr("Caturday"); break;
    }
}


void AppManager::setupSelectors()
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << "m_currentSkinEntry: " << m_currentSkinEntry;
    qDebug() << "m_currentTheme: " << m_currentTheme;
    mSelector = new QFileSelector();
    mSelector->setExtraSelectors( QStringList() << m_currentSkinEntry << m_currentTheme);
    QQmlFileSelector *qmlSelector = new QQmlFileSelector(m_usingWindow ? mWindowEngine : mView->engine());
    qmlSelector->setSelector(mSelector);
    qDebug() << Q_FUNC_INFO << "Current Selectors::\n" << mSelector->allSelectors();

    if(mb_startingUp==true){
        if(m_currentScreen.isEmpty()){
            setCurrentScreen("Home.qml");
            mb_startingUp =false;
            emit started();
        }
    }

    if(m_usingWindow){
        mWindowEngine->clearComponentCache();
        mWindowEngine->load(QUrl(adjustPath("main.qml")));
    } else {
        mView->engine()->clearComponentCache();
        mView->setSource(QUrl(adjustPath("main.qml")));
        mView->show();
    }
}

void AppManager::resetSelectors()
{
    mSelector->setExtraSelectors( QStringList() << m_currentSkinEntry << m_currentTheme);
    QQmlFileSelector *qmlSelector = new QQmlFileSelector(m_usingWindow ? mWindowEngine : mView->engine());
    qmlSelector->setSelector(mSelector);
    reload();
}

QString AppManager::currentTheme() const
{
    return m_currentTheme;
}

void AppManager::setCurrentTheme(const QString &currentTheme)
{

    m_currentTheme = currentTheme;
    mSettings->writeSetting("theme", QVariant(m_currentTheme));
    emit currentThemeChanged();
    resetSelectors();
}

QString AppManager::currentSkinEntry() const
{
    return m_currentSkinEntry;
}

void AppManager::setCurrentSkinEntry(const QString &currentSkinEntry)
{
    qDebug() << Q_FUNC_INFO;
    m_currentSkinEntry = currentSkinEntry;
    mSettings->writeSetting("skin", QVariant(m_currentSkinEntry));
    emit currentSkinEntryChanged();
    resetSelectors();
}


