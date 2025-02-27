#ifndef QRCODEPAGE_H
#define QRCODEPAGE_H

#include <vector>
#include <string>
#include <QWidget>
#include <opencv2/opencv.hpp>
#include <qrcodegen.hpp>

using qrcodegen::QrCode;

namespace Ui {
class qrcodepage;
}

class qrcodepage : public QWidget
{
    Q_OBJECT

public:
    explicit qrcodepage(QWidget *parent = nullptr);
    ~qrcodepage();

private slots:
    void on_QRcodeSize_valueChanged(int arg1);

    void on_GenerateButton_clicked();

    void on_ExportButton_clicked();

private:
    cv::Mat QRcodeImage;
    QString DIB_LOC;
    Ui::qrcodepage *ui;
};

#endif // QRCODEPAGE_H
