#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include "apploader.h"
#include <QPushButton>
#include <QDebug>
#include <QProcess>

AppLoader::AppLoader(QObject* parent): QObject(parent)
{
    m_nrInstalledApps = 0;
    m_daemon = new DBusDaemon();
    connect(m_daemon, SIGNAL(informPidReceived(int,QString)),
            this, SLOT(informPidReceived(int,QString)));
}

AppLoader::~AppLoader()
{
    delete m_daemon;
}

QStringList AppLoader::getInstalledApps()
{
    DIR *d, *subd;
    struct dirent *dir;
    d = opendir(TappPath.toStdString().c_str());
    if (d) {
        qDebug() << "Dir opened";
        while((dir=readdir(d)) != NULL) {
            if (!QString(dir->d_name).contains("."))
                m_installedApps << QString(dir->d_name);
        }
        closedir(d);
        m_nrInstalledApps = m_installedApps.size();
        return m_installedApps;
    } else {
        qDebug() << "Error: Could not open dir";
        return QStringList();
    }
}

int AppLoader::getNrInstalledApps()
{
    return m_installedApps.size();
}

void AppLoader::launchApp()
{
    QString app = qobject_cast<QPushButton*>(QObject::sender())->objectName();
    QString fullPath = QString(TappPath + "/" + app + "/" + app);
    qDebug() << "Launching app: " << fullPath;
    /*int e;
    char *execPath = new char[fullPath.size() + 1];
    strcpy(execPath, fullPath.toStdString().c_str());
    execPath[fullPath.size()] = '\0';
    printf("Launching: [%s]\n", execPath);
    char *argv[] = {execPath, 0};
    char *envp[] = {
        "USER=root",
        "LOGNAME=root",
        "HOME=/home/root",
        "QT_QPA_PLATFORM=eglfs",
        "QT_QPA_EGLFS_PHYSICAL_HEIGHT=86",
        "QT_QPA_EGLFS_PHYSICAL_WIDTH=155",
        0
    };

    if ((e=execve(argv[0], &argv[0], envp)) != 0) {
        qDebug() << "Error (return code was: " << e << ")";
    } else {
        qDebug() << "App is running!";
    }*/
    QProcess* p = new QProcess(this);
    p->start(fullPath);
    //and invalidate apploader
    emit appIsRunning();
}

void AppLoader::informPidReceived(int pid, QString app)
{
    qDebug() << "Appending pair (pid,app) : (" << pid << "," << app << ")";
    m_appsAndPids << qMakePair<int,QString>(pid,app);
}
