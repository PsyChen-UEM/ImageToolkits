#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QPalette>
#include <QStandardPaths>
#include <QStringListModel>
#include <opencv2/opencv.hpp>

namespace Ui {
class homepage;
}

class homepage : public QWidget
{
    Q_OBJECT

public:
    explicit homepage(QWidget *parent = nullptr);
    ~homepage();

private slots:

    void on_pushButton_clicked();

    void on_SaveBuf_clicked();

    void on_GaussNoise_clicked();

    void on_SaltNoise_clicked();

    void on_Cancel_clicked();

    void on_GaussianBlur_clicked();

    void on_Brightnes_sliderMoved(int position);

    void on_Contrast_sliderMoved(int position);

    void on_ConvertGary_clicked();

    void on_Threshold_clicked();

    void on_MeanBlur_clicked();

    void on_BoxFilter_clicked();

    void on_MedianBlur_clicked();

    void on_Erode_clicked();

    void on_Dilate_clicked();

    void on_Brightnes_sliderPressed();

    void on_Contrast_sliderPressed();

    void on_Export_clicked();

    void on_ExportHist_clicked();

private:
    Ui::homepage *ui;
    cv::Mat PrevImage,AfterImage;
    QString DIB_LOC;
    QStringList ActionList;
    double BrightRate=1.0,ContrastRate=1.0;
    void SetBufImg1(const cv::Mat& img);
    void SetBufImg2(const cv::Mat& img);
    void setzero();
    void drawHist();
    void ShowImg();
    void MyAddAction(const QString& str);
};

#endif // HOMEPAGE_H
