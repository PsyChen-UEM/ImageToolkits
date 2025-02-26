#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString DocLoc=QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QDir dir;dir.mkpath(DIB_LOC);
    PrevImage=AfterImage=cv::Mat::zeros(300,300,CV_8U);
    cv::namedWindow("CurrentImage",cv::WINDOW_NORMAL);
    cv::imshow("CurrentImage",AfterImage);
    DIB_LOC=DocLoc+"/ImageToolkits/Image";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString filename=QFileDialog::getOpenFileName(nullptr,"Choose Image",QDir::homePath(),"All Files(*)");
    PrevImage=cv::imread(filename.toStdString());
    PrevImage.copyTo(AfterImage);
    if(PrevImage.empty()){
        QMessageBox::critical(nullptr,"Error!","Can't Open Image!");
        return;
    }
    SetBufImg1(PrevImage);
    setzero();
    ui->ImagePass->setText(filename);
    ShowImg();
    // ui->ImagePass->setText(filename);
    return;
}

void MainWindow::on_SaveBuf_clicked()
{
    AfterImage.copyTo(PrevImage);
    SetBufImg1(PrevImage);
    setzero();
}
void MainWindow::setzero(){
    ui->GaussionNoiseLCDNumber->display(0);
    ui->SaltNoiseLCDNumber->display(0);
    ui->Contrast->setValue(50);
    ui->Brightnes->setValue(50);
    ActionList.clear();
    QStringListModel *listmodel = new QStringListModel(ActionList);
    ui->UserlistView->setModel(listmodel);
    return;
}

void MainWindow::SetBufImg1(const cv::Mat& img){
    double ImageWH=img.cols*1.0/img.rows;
    cv::Mat ImageBeShowed=cv::Mat::zeros(300, 300, PrevImage.type());
    cv::Mat ResizeImage;
    cv::Mat ROI1;
    if(ImageWH>=1){
        cv::resize(img,ResizeImage,cv::Size(300,300/ImageWH));
        ROI1=ImageBeShowed(cv::Rect(0,150-ResizeImage.rows/2.0,300,ResizeImage.rows));
        ResizeImage.copyTo(ROI1);
    }
    else{
        cv::resize(img,ResizeImage,cv::Size(300*ImageWH,300));
        ROI1=ImageBeShowed(cv::Rect(150-ResizeImage.cols/2.0,0,ResizeImage.cols,300));
        ResizeImage.copyTo(ROI1);
    }
    // imshow("resize",ImageBeShowed);
    cv::imwrite(DIB_LOC.toStdString()+"/bufferimg1.jpg",ImageBeShowed);
    ui->PictureArea->setPixmap(QPixmap(DIB_LOC+"/bufferimg1.jpg"));
}


void MainWindow::on_GaussNoise_clicked()
{
    cv::Mat img_noise=cv::Mat::zeros(AfterImage.rows,AfterImage.cols,AfterImage.type());
    cv::RNG rng;
    rng.fill(img_noise,cv::RNG::NORMAL,10,20);
    AfterImage+=img_noise;
    ui->GaussionNoiseLCDNumber->display(ui->GaussionNoiseLCDNumber->intValue()+1);
    ShowImg();
    MyAddAction("Gauss Noise");
    return;
}


void MainWindow::on_SaltNoise_clicked()
{
    for (int k = 0; k <=AfterImage.cols*AfterImage.rows/20; k++) {
        int i, j;
        i = cvflann::rand() % AfterImage.cols;
        j = cvflann::rand() % AfterImage.rows;
        int wb_color = cvflann::rand() % 2;
        if (AfterImage.type() == CV_8UC1) {
            AfterImage.at<uchar>(j, i) = (wb_color ? 255 : 0);
        }
        else {
            for (int x = 0; x < 3; x++) {
                AfterImage.at<cv::Vec3b>(j, i)[x] = (wb_color ? 255 : 0);
            }
        }
    }
    ui->SaltNoiseLCDNumber->display(ui->SaltNoiseLCDNumber->intValue()+1);
    ShowImg();
    MyAddAction("Salt Noise");
    return;
}

void MainWindow::drawHist(){
    cv::Mat gray,hist,hist_INF;
    cv::cvtColor(AfterImage,gray,cv::COLOR_RGB2GRAY);
    const int channels[1] = { 0 };
    float inRanges[2] = { 0,255 };
    const float* ranges[1] = { inRanges };
    const int bins[1] = { 256 };
    cv::calcHist(&gray, 1, channels,cv::Mat(), hist, 1, bins, ranges);
    normalize(hist, hist_INF, 1.0, 0.0, cv::NORM_INF, -1, cv::Mat());
    const int hist_w=256,hist_h=200,width=1;
    cv::Mat histImage=cv::Mat(hist_h,hist_w,CV_8U,cv::Scalar(255,255,255));
    for (int i = 1; i <= hist_INF.rows; i++) {
        cv::rectangle(histImage, cv::Point(width * (i - 1), hist_h - 1), cv::Point(width * i - 1, hist_h - cvRound(hist_h * hist_INF.at<float>(i - 1)) - 1),
                  cv::Scalar( 0 , 0 , 0), -1);
    }
    cv::imwrite(DIB_LOC.toStdString()+"/hist.jpg",histImage);
    QPixmap Histgraph(DIB_LOC+"/hist.jpg");
    ui->Hist->setPixmap(Histgraph);
    return;
}

void MainWindow::on_Cancel_clicked()
{
    PrevImage.copyTo(AfterImage);
    ShowImg();
    setzero();
    return;
}


void MainWindow::on_GaussianBlur_clicked()
{
    cv::GaussianBlur(AfterImage,AfterImage,cv::Size(5,5),10,20);
    ShowImg();
    MyAddAction("Gaussian Blur");
    return;
}


void MainWindow::on_Brightnes_sliderMoved(int position)
{
    BrightRate=(position-50.0)/50.0*255.0;
    PrevImage.convertTo(AfterImage,-1,ContrastRate,BrightRate);
    ShowImg();
    return;
}


void MainWindow::on_Contrast_sliderMoved(int position)
{
    ContrastRate=position/50.0;
    PrevImage.convertTo(AfterImage,-1,ContrastRate,BrightRate);
    ShowImg();
    return;
}

void MainWindow::ShowImg(){
    cv::imshow("CurrentImage",AfterImage);
    drawHist();
    return;
}

void MainWindow::on_ConvertGary_clicked()
{
    cv::Mat gray;
    cv::cvtColor(AfterImage,gray,cv::COLOR_RGB2GRAY);
    cv::cvtColor(gray,AfterImage,cv::COLOR_GRAY2RGBA);
    ShowImg();
    MyAddAction("ConvertGary");
    return;
}


void MainWindow::on_Threshold_clicked()
{
    cv::Mat gray;
    cv::cvtColor(AfterImage,gray,cv::COLOR_RGB2GRAY);
    cv::adaptiveThreshold(gray,gray,255,cv::ADAPTIVE_THRESH_GAUSSIAN_C,cv::THRESH_BINARY,ui->KernelSize->value(),0);
    cv::cvtColor(gray,AfterImage,cv::COLOR_GRAY2RGBA);
    ShowImg();
    MyAddAction("Threshold");
    return;
}


void MainWindow::on_MeanBlur_clicked()
{
    cv::blur(AfterImage,AfterImage,cv::Size(ui->KernelSize->value(),ui->KernelSize->value()));
    ShowImg();
    MyAddAction("Mean Blur");
    return;
}


void MainWindow::on_BoxFilter_clicked()
{
    cv::boxFilter(AfterImage,AfterImage,-1,cv::Size(ui->KernelSize->value(),ui->KernelSize->value()));
    ShowImg();
    MyAddAction("Box Filter");
    return;
}


void MainWindow::on_MedianBlur_clicked()
{
    cv::medianBlur(AfterImage,AfterImage,ui->KernelSize->value());
    ShowImg();
    MyAddAction("Median Blur");
    return;
}


void MainWindow::on_Erode_clicked()
{
    cv::erode(AfterImage,AfterImage,cv::getStructuringElement(0,cv::Size(3,3)));
    ShowImg();
    MyAddAction("Erode");
    return;
}


void MainWindow::on_Dilate_clicked()
{
    cv::dilate(AfterImage,AfterImage,cv::getStructuringElement(0,cv::Size(3,3)));
    ShowImg();
    MyAddAction("Dilate");
    return;
}

void MainWindow::MyAddAction(const QString& str){
    if(ActionList.size()==13){
        ActionList.pop_front();
    }
    ActionList.push_back(str);
    QStringListModel *listmodel = new QStringListModel(ActionList);
    ui->UserlistView->setModel(listmodel);
    return;
}

void MainWindow::on_Brightnes_sliderPressed()
{
    MyAddAction("Change Brightness");
    return;
}

void MainWindow::on_Contrast_sliderPressed()
{
    MyAddAction("Change Contrast");
    return;
}


void MainWindow::on_Export_clicked()
{
    QString filename=QFileDialog::getSaveFileName(nullptr, "Save Text File", QDir::homePath(), "Image Files (*)");
    if(!filename.isEmpty()){
        cv::imwrite(filename.toStdString(),PrevImage);
    }else{
        QMessageBox::critical(nullptr,"Error!","Cant Save In A Correct Way");
        return;
    }
    return;
}

