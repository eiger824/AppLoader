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
    void registerAppReceived(int pid, QString app);
    void unregisterAppReceived(int pid);
Q_SIGNALS:
    Q_SCRIPTABLE void sendShutdownSignal(QString appname);
public Q_SLOTS:
    void registerApp(int pid, QString app);
    void unregisterApp(int pid);

public slots:
};

#endif // DBUSDAEMON_H
