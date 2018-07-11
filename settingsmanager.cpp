#include "settingsmanager.h"
#include "qdebug.h"
SettingsManager::SettingsManager(QObject *parent) : QObject(parent)
{
    mSettings = new QSettings("ICS", "Weather Explorer");
}

bool SettingsManager::writeSetting(QString key, QVariant val)
{
    if(mSettings!=NULL){
            mSettings->setValue(key, val);
            return true;
    }
    return false;

}

QVariant SettingsManager::getSetting(QString key)
{
    if(mSettings!=NULL){
          return mSettings->value(key);
    }
    return QVariant();
}




