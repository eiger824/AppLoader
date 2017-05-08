#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_remaining(3)
{
    ui->setupUi(this);
    /*
     * Connect all buttons to the on_key_clicked() slot
    */
    connect(ui->pushButton_0, SIGNAL(pressed()), this, SLOT(on_key_clicked()));
    connect(ui->pushButton_1, SIGNAL(pressed()), this, SLOT(on_key_clicked()));
    connect(ui->pushButton_2, SIGNAL(pressed()), this, SLOT(on_key_clicked()));
    connect(ui->pushButton_3, SIGNAL(pressed()), this, SLOT(on_key_clicked()));
    connect(ui->pushButton_4, SIGNAL(pressed()), this, SLOT(on_key_clicked()));
    connect(ui->pushButton_5, SIGNAL(pressed()), this, SLOT(on_key_clicked()));
    connect(ui->pushButton_6, SIGNAL(pressed()), this, SLOT(on_key_clicked()));
    connect(ui->pushButton_7, SIGNAL(pressed()), this, SLOT(on_key_clicked()));
    connect(ui->pushButton_8, SIGNAL(pressed()), this, SLOT(on_key_clicked()));
    connect(ui->pushButton_9, SIGNAL(pressed()), this, SLOT(on_key_clicked()));

    ui->pushButton_continue->setVisible(false);
    ui->label_4->setVisible(false);

    // check for existing apps
    m_appLoader = new AppLoader(this);
    connect(m_appLoader, SIGNAL(appIsRunning()),
            this, SLOT(invalidateLoader()));
    QStringList apps = m_appLoader->getInstalledApps();
    int napps = m_appLoader->getNrInstalledApps();
    qDebug() << "Nr. of installed apps: " << napps;

    // dynamic ui design
    int c = napps;
    for (auto app: apps) {
        QPushButton *p = new QPushButton();
        p->setFixedWidth(90);
        p->setFixedHeight(90);
        p->setFocusPolicy(Qt::NoFocus);
        p->setStyleSheet("border-radius: 10px;background-image: url(:/images/" + app + ".png);");
        //important: object name property
        p->setObjectName(app);
        //put it in the grid
        ui->gridLayout->addWidget(p,
                                  (int)(napps - c) / 3,
                                  (napps - c) % 3,
                                  Qt::AlignHCenter | Qt::AlignVCenter);
        //connect it to the launcher function
        connect(p, SIGNAL(pressed()), m_appLoader, SLOT(launchApp()));
        --c;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    if (arg1.size() < 4) return;

    //Check if pin correct
    if (arg1 == m_initPin) {
        updateLabel(true);
        ui->pushButton_continue->setVisible(true);
        ui->label_4->setVisible(true);
    } else {
        updateLabel(false);
        --m_remaining;
        QTimer::singleShot(1000, this, SLOT(clearLineEdit()));
        if (m_remaining == 0) {
            // then kick user out of the program
            QMessageBox box;
            box.information(this, QString("Error"), QString("Unauthorized access. Exiting ..."));
            box.setStyleSheet("background-color: white; color: black;");
            QApplication::quit();
        }
    }
}

void MainWindow::updateLabel(bool success)
{
    if (success) {
        ui->label_2->setText("Login correct!");
        ui->label_2->setStyleSheet("color: green;");
    } else {
        ui->label_2->setText("Failed login");
        ui->label_2->setStyleSheet("color: red;");
    }
}

void MainWindow::clearLineEdit() {
    ui->lineEdit->clear();
    ui->label_2->clear();
}

void MainWindow::on_key_clicked() {
    QString n = qobject_cast<QPushButton*>(QObject::sender())->text();
    ui->lineEdit->setText(ui->lineEdit->text() += n);
}

void MainWindow::on_pushButton_continue_clicked()
{
    ui->mainStack->setCurrentIndex(1);
}

void MainWindow::invalidateLoader()
{
    ui->centralwidget->setEnabled(false);
}
