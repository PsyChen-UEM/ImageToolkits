#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "homepage.h"
#include "qrcodepage.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionHome_triggered();

    void on_actionQrCode_triggered();

private:
    homepage* homepageinstance;
    qrcodepage* qrcodepageinstance;
    QWidget* currentpage;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
