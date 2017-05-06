#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_remaining(3)
{
    ui->setupUi(this);
    ui->pushButton_continue->setVisible(false);
    ui->label_4->setVisible(false);

    // check for existing apps

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

void MainWindow::on_pushButton_1_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() += ui->pushButton_1->text());
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() += ui->pushButton_2->text());
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() += ui->pushButton_3->text());
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() += ui->pushButton_4->text());
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() += ui->pushButton_6->text());
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() += ui->pushButton_5->text());
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() += ui->pushButton_7->text());
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() += ui->pushButton_9->text());
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() += ui->pushButton_8->text());
}

void MainWindow::on_pushButton_0_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() += ui->pushButton_0->text());
}

void MainWindow::on_pushButton_continue_clicked()
{
    ui->mainStack->setCurrentIndex(1);
}
