#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar->addAction(ui->actionHome);
    ui->toolBar->addAction(ui->actionQrCode);
    homepageinstance =new homepage(this);
    homepageinstance->close();
    qrcodepageinstance =new qrcodepage(this);
    qrcodepageinstance->close();
    currentpage=homepageinstance;
    currentpage->move(50,0);
    currentpage->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionHome_triggered()
{
    currentpage->close();
    currentpage=homepageinstance;
    currentpage->move(50,0);
    currentpage->show();
    return;
}


void MainWindow::on_actionQrCode_triggered()
{
    currentpage->close();
    currentpage=qrcodepageinstance;
    currentpage->move(50,0);
    currentpage->show();
    return;
}

