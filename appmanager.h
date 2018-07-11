#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QObject>
#include <QVector>
#include <qqmlengine.h>
class SettingsManager;
class QQuickView;
class QFileSelector;
class QQmlApplicationEngine;

/*!
 * \brief The AppManager class. Simple class that is an interface to the c++ backend.
 */
class AppManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentSkinEntry READ currentSkinEntry WRITE setCurrentSkinEntry NOTIFY currentSkinEntryChanged)
    Q_PROPERTY(QString currentTheme READ currentTheme WRITE setCurrentTheme NOTIFY currentThemeChanged)
    Q_PROPERTY(QString currentScreen READ currentScreen WRITE setCurrentScreen NOTIFY currentScreenChanged)
    Q_PROPERTY(bool usingWindow READ usingWindow WRITE setUsingWindow NOTIFY usingWindowChanged)

    Q_ENUMS(LoadingMode)
public:
    explicit AppManager( QObject *parent = 0);
    enum LoadingMode{QRC, DISK, WEB};
    SettingsManager *mSettings;

    //--------------Qml Getters and Setters------------------------//
    QString currentSkinEntry() const;
    void setCurrentSkinEntry(const QString &currentSkinEntry);

    QString currentTheme() const;
    void setCurrentTheme(const QString &currentTheme);

    QString currentScreen() const;
    void setCurrentScreen(const QString &currentScreen);

    Q_INVOKABLE QString adjustPath(QString qmlFile);
    Q_INVOKABLE QString dayOfWeek(int day);

    bool usingWindow() const;
    void setUsingWindow(bool usingWindow);
     //--------------Qml Getters and Setters End------------------------//

signals:
    void currentSkinEntryChanged();
    void currentThemeChanged();
    void currentScreenChanged();
    void started();
    void usingWindowChanged();

public slots:
    /*!
     * \brief reload
     * The Reload Slot of the application that eventually calls the private function: delayReloadQml()
     */
    void reload();
    /*!
     * \brief setLanguage
     * Sets the language for the application, the calls reload to refresh any components.
     */
    void setLanguage();


private:
    /*!
     * \brief handleModeSwitch
     * This function handles switching between the QQuickView and QQuickWindow based QML views. Normally, an application would have one or the other, not both.
     *
     */
    void handleModeSwitch();

    /*!
     * \brief restoreSettings. Restores the settings from a QSettings, otherwise sets default values.
     * \return QVariant()
     */
    bool restoreSettings();

    /*!
     * \brief setupSelectors. Sets up QQmlFileSelectors
     */
    void setupSelectors();

    /*!
     * \brief resetSelectors. Resets the selctors to the default.
     */
    void resetSelectors();

private slots:
    /*!
 * \brief delayReloadQml. This private slot is responsible for reloading the qml
 */
void delayReloadQml();

private:
    QString m_currentScreen;

    QVector<QString> mSkinList;
    QVector<QString>mThemeList;

    QString m_apiKey;
    QString m_selectedLanguage;

    QString m_currentTheme;
    QString m_currentSkinEntry;

    QString m_qmlPath;
    bool mb_startingUp;

    LoadingMode mLoadingMode;
    QFileSelector *mSelector;
    QQuickView *mView;
    QQmlApplicationEngine *mWindowEngine;

    bool m_usingWindow;

};

#endif // APPMANAGER_H
