#ifndef APPLOADER_H
#define APPLOADER_H

#include <QObject>
#include <QStringList>
#include <QPair>

#include "dbusdaemon.h"

class AppLoader : public QObject
{
    Q_OBJECT
public:
    AppLoader(QObject* parent=0);
    ~AppLoader();
public:
    QStringList getInstalledApps();
    int getNrInstalledApps();
private:
    int appIsRegistered(int pid);
signals:
    void appIsRunning();
    void getFocusBack();
private slots:
    void launchApp();
    void registerAppReceivedSlot(int pid, QString app);
    void unregisterAppReceivedSlot(int pid);
private:
    QStringList m_installedApps;
    QList<QPair<int,QString>> m_appsAndPids;
    QString appPath = "/usr/bin/apps";
    QString TappPath = "./bin/apps";
    int m_nrInstalledApps;
    DBusDaemon* m_daemon;
};

#endif // APPLOADER_H
