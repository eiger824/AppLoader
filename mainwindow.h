#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "apploader.h"

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
    void on_key_clicked();
    void on_pushButton_continue_clicked();
    void invalidateLoader();
private:
    Ui::MainWindow *ui;
    QString m_initPin = "1590";
    int m_remaining;
    AppLoader* m_appLoader;
};

#endif // MAINWINDOW_H
