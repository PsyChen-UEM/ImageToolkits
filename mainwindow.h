#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>
#include <QDir>
#include <opencv2/opencv.hpp>
#include <QStringListModel>
#include <string>

const std::string PICBASE = "C:/standard_test_images/";

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

private:
    Ui::MainWindow *ui;
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
#endif // MAINWINDOW_H
