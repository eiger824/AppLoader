#include <glog/logging.h>
#include "include/dbusdaemon.h"
#include "dbusdaemon_adaptor.h"

DBusDaemon::DBusDaemon(QObject *parent) : QObject(parent)
{
    new DBusDaemonAdaptor(this);
    QDBusConnection connection = QDBusConnection::sessionBus();

    bool obj,serv;
    if (!(obj=connection.registerObject("/DBusDaemon", this))) {
        LOG (ERROR) << "Error registering object: " << connection.lastError().message().toStdString();
    }
    if (!(serv=connection.registerService("se.mydns.mysland.DBusDaemon")))  {
        LOG (ERROR) << "Error registering service: " << connection.lastError().message().toStdString();
    }
    // If both successful
    if (obj && serv)
        DLOG (INFO) << "Started AppLoader D-Bus daemon";
}

void DBusDaemon::registerApp(int pid, QString app)
{
    DLOG (INFO) << "PID register request received: " << pid
                << ", from app: " << app.toStdString();
    emit registerAppReceived(pid,app);
}

void DBusDaemon::unregisterApp(int pid)
{
    DLOG (INFO) << "PID unregister request received: " << pid;
    emit unregisterAppReceived(pid);
}
