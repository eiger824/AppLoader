#include <QDebug>
#include "dbusdaemon.h"
#include "dbusdaemon_adaptor.h"

DBusDaemon::DBusDaemon(QObject *parent) : QObject(parent)
{
    new DBusDaemonAdaptor(this);
    QDBusConnection connection = QDBusConnection::sessionBus();
    bool obj,serv;
    if (!(obj=connection.registerObject("/DBusDaemon", this))) {
        qDebug() << "Error registering object: " << connection.lastError().message();
    }
    if (!(serv=connection.registerService("se.mydns.mysland.DBusDaemon")))  {
        qDebug() << "Error registering service: " << connection.lastError().message();
    }
    // If both successful
    if (obj && serv)
        qDebug() << "Started AppLoader D-Bus daemon";
}

void DBusDaemon::informPid(int pid, QString app)
{
    qDebug() << "Registering pid " << pid << " from app " << app;
    emit informPidReceived(pid,app);
}
