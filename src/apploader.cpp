#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include "include/apploader.h"
#include <QPushButton>
#include <QProcess>
#include <glog/logging.h>

AppLoader::AppLoader(QObject* parent): QObject(parent)
{
    m_nrInstalledApps = 0;
    m_daemon = new DBusDaemon();
    connect(m_daemon, SIGNAL(registerAppReceived(int,QString)),
            this, SLOT(registerAppReceivedSlot(int,QString)));
    connect(m_daemon, SIGNAL(unregisterAppReceived(int)),
            this, SLOT(unregisterAppReceivedSlot(int)));
}

AppLoader::~AppLoader()
{
    delete m_daemon;
}

QStringList AppLoader::getInstalledApps()
{
    DIR *d;
    struct dirent *dir;
    d = opendir(appPath.toStdString().c_str());
    if (d) {
        LOG (ERROR) << "Dir opened";
        while((dir=readdir(d)) != NULL) {
            if (!QString(dir->d_name).contains("."))
                m_installedApps << QString(dir->d_name);
        }
        closedir(d);
        m_nrInstalledApps = m_installedApps.size();
        return m_installedApps;
    } else {
        LOG (ERROR) << "Error: Could not open dir";
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
    QString fullPath = QString(appPath + "/" + app + "/" + app);
    DLOG (INFO) << "Launching app: " << fullPath.toStdString();
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
        LOG (ERROR) << "Error (return code was: " << e.toStdString() << ")";
    } else {
        LOG (ERROR) << "App is running!";
    }*/
    QProcess* p = new QProcess(this);
    p->start(fullPath);
    //and invalidate apploader
    emit appIsRunning();
}

void AppLoader::registerAppReceivedSlot(int pid, QString app)
{
    DLOG (INFO) << "Appending pair (pid,app) : (" << pid
                << "," << app.toStdString() << ")";
    m_appsAndPids << qMakePair<int,QString>(pid,app);
}

void AppLoader::unregisterAppReceivedSlot(int pid) {
    DLOG (INFO) << "Checking if pid exists ...";
    int index;
    if ((index=appIsRegistered(pid)) != -1) {
        DLOG (INFO) << "PID " << pid << " exists. Unregistering";
        m_appsAndPids.removeAt(index);
        //and reenable focus on main window
        emit getFocusBack();
    } else {
        LOG (ERROR) << "Error: PID " << pid << " does not exist";
    }
}

int AppLoader::appIsRegistered(int pid) {
    for (unsigned k=0; k<m_appsAndPids.size(); ++k) {
        if (m_appsAndPids.at(k).first == pid) {
            return k;
        }
    }
    return -1;
}
