#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include "qsettings.h"

class SettingsManager : public QObject
{
    Q_OBJECT
public:
    explicit SettingsManager(QObject *parent = 0);  

signals:
    void settingsError(QString err);

public slots:
    bool writeSetting(QString key, QVariant val);
    QVariant getSetting(QString key);

private:

    QSettings *mSettings;
};

#endif // SETTINGSMANAGER_H
