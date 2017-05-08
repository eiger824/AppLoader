#ifndef DBUSDAEMON_H
#define DBUSDAEMON_H

#include <QObject>

class DBusDaemon : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "se.mydns.mysland.DBusDaemon")
public:
    DBusDaemon(QObject *parent = 0);

signals:
    void informPidReceived(int pid, QString app);
Q_SIGNALS:
    void sendShutdownSignal(QString appname);
public Q_SLOTS:
    void informPid(int pid, QString app);

public slots:
};

#endif // DBUSDAEMON_H
