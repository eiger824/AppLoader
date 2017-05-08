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
signals:
    void appIsRunning();
private slots:
    void launchApp();
    void informPidReceived(int pid, QString app);
private:
    QStringList m_installedApps;
    QList<QPair<int,QString>> m_appsAndPids;
    QString appPath = "/usr/bin/apps";
    QString TappPath = "./bin/apps";
    int m_nrInstalledApps;
    DBusDaemon* m_daemon;
};

#endif // APPLOADER_H
