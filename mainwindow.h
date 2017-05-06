#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void updateLabel(bool success);

private slots:
    void on_lineEdit_textChanged(const QString &arg1);
    void clearLineEdit();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_0_clicked();
    void on_pushButton_continue_clicked();

private:
    Ui::MainWindow *ui;
    QString m_initPin = "1590";
    int m_remaining;
};

#endif // MAINWINDOW_H
