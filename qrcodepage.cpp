#include "qrcodepage.h"
#include "ui_qrcodepage.h"

#include <QMessageBox>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QFileDialog>

qrcodepage::qrcodepage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::qrcodepage)
{
    ui->setupUi(this);
    QPalette pal=ui->QRcodeImg->palette();
    pal.setColor(QPalette::Window,Qt::white);
    ui->QRcodeImg->setPalette(pal);

    QString DocLoc=QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    DIB_LOC=DocLoc+"/ImageToolkits/QRcode";
    QDir dir;dir.mkpath(DIB_LOC);

    QRcodeImage=cv::Mat::zeros(177,177,CV_8UC3);

}

qrcodepage::~qrcodepage()
{
    delete ui;
}

void qrcodepage::on_QRcodeSize_valueChanged(int arg1)
{
    int QRcodesize=21+(arg1-1)*4;
    ui->QRcodeSizeText->setText("Size "+QString(std::to_string(QRcodesize).c_str())+"*"+QString(std::to_string(QRcodesize).c_str()));
    return;
}


void qrcodepage::on_GenerateButton_clicked()
{
    std::vector<qrcodegen::QrSegment> segs=qrcodegen::QrSegment::makeSegments(ui->StringInput->toPlainText().toStdString().c_str());
    int QRsizevalue=21+4*(ui->QRcodeSize->value()-1);
    int ECClevel=ui->ErrorCorrectionLevel->value();
    switch (ECClevel) {
    case 1:{
        qrcodegen::QrCode qr0=qrcodegen::QrCode::encodeSegments(segs,qrcodegen::QrCode::Ecc::LOW,ui->QRcodeSize->value());
        QRsizevalue=qr0.getSize();
        QRcodeImage=cv::Mat::zeros(qr0.getSize(),qr0.getSize(),CV_8UC3);
        for (int y = 0; y < qr0.getSize(); ++y) {
            for (int x = 0; x < qr0.getSize(); ++x) {
                if(qr0.getModule(x,y)==false){
                    auto& pix=QRcodeImage.at<cv::Vec3b>(x,y);
                    pix[0]=255;
                    pix[1]=255;
                    pix[2]=255;
                }
            }
        }
    }
        break;
    case 2:{
        qrcodegen::QrCode qr0=qrcodegen::QrCode::encodeSegments(segs,qrcodegen::QrCode::Ecc::MEDIUM,ui->QRcodeSize->value());
        QRsizevalue=qr0.getSize();
        QRcodeImage=cv::Mat::zeros(qr0.getSize(),qr0.getSize(),CV_8UC3);
        for (int y = 0; y < qr0.getSize(); ++y) {
            for (int x = 0; x < qr0.getSize(); ++x) {
                if(qr0.getModule(x,y)==false){
                    auto& pix=QRcodeImage.at<cv::Vec3b>(x,y);
                    pix[0]=255;
                    pix[1]=255;
                    pix[2]=255;
                }
            }
        }
    }

        break;
    case 3:{
        qrcodegen::QrCode qr0=qrcodegen::QrCode::encodeSegments(segs,qrcodegen::QrCode::Ecc::QUARTILE,ui->QRcodeSize->value());
        QRsizevalue=qr0.getSize();
        QRcodeImage=cv::Mat::zeros(qr0.getSize(),qr0.getSize(),CV_8UC3);
        for (int y = 0; y < qr0.getSize(); ++y) {
            for (int x = 0; x < qr0.getSize(); ++x) {
                if(qr0.getModule(x,y)==false){
                    auto& pix=QRcodeImage.at<cv::Vec3b>(x,y);
                    pix[0]=255;
                    pix[1]=255;
                    pix[2]=255;
                }
            }
        }
    }

        break;
    case 4:{
        qrcodegen::QrCode qr0=qrcodegen::QrCode::encodeSegments(segs,qrcodegen::QrCode::Ecc::HIGH,ui->QRcodeSize->value());
        QRsizevalue=qr0.getSize();
        QRcodeImage=cv::Mat::zeros(qr0.getSize(),qr0.getSize(),CV_8UC3);
        for (int y = 0; y < qr0.getSize(); ++y) {
            for (int x = 0; x < qr0.getSize(); ++x) {
                if(qr0.getModule(x,y)==false){
                    auto& pix=QRcodeImage.at<cv::Vec3b>(x,y);
                    pix[0]=255;
                    pix[1]=255;
                    pix[2]=255;
                }
            }
        }
    }
        break;
    }
    cv::Mat tempimg;
    cv::resize(QRcodeImage,tempimg,cv::Size(300,300),0,0,cv::INTER_NEAREST);
    cv::imwrite(DIB_LOC.toStdString()+"/qrcode.jpg",tempimg);
    ui->QRcodeImg->setPixmap(DIB_LOC+"/qrcode.jpg");
    ui->RealSizeNumberText->setText(QString::fromStdString(std::to_string(QRsizevalue)));
    return;
}


void qrcodepage::on_ExportButton_clicked()
{
    cv::Mat tempimg;
    tempimg=cv::imread(DIB_LOC.toStdString()+"/qrcode.jpg");
    QString filename=QFileDialog::getSaveFileName(nullptr, "Save Text File", QDir::homePath(), "Image Files (*)");
    if(!filename.isEmpty()){
        cv::imwrite(filename.toStdString(),tempimg);
    }else{
        QMessageBox::critical(nullptr,"Error!","Cant Save In A Correct Way");
        return;
    }
}

