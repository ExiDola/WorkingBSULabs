#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QListWidgetItem>
#include<opencv2/core.hpp>
#include <QLabel>
#include <QPixmap>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(850,600);
    this->imagePath = "C:/Users/Zephyrus/Downloads/82dfe1cc5ad678bac112915811c750b6.jpeg";
    QString FirstPath = "C:/Users/Zephyrus/Downloads/82dfe1cc5ad678bac112915811c750b6.jpeg";
    QPixmap image1(FirstPath);
    vec.push_back(FirstPath);
    this->currItem = 0;
    QString SecPath = "C:/Users/Zephyrus/Downloads/1645058652_27-fikiwiki-com-p-kartinki-pshenichnoe-pole-34.jpg";
    QPixmap image2(SecPath);
    vec.push_back(SecPath);
    QString thirdPath = "C:/Users/Zephyrus/Downloads/1676000128_gagaru-club-p-oboi-krasochnie-instagram-6.jpg";
    QPixmap image3(thirdPath);
    vec.push_back(thirdPath);
    QListWidgetItem *item1 = new QListWidgetItem("asus rog");
    item1->setIcon(image1);
    ui->picList->addItem(item1);

    QListWidgetItem *item2 = new QListWidgetItem("Kolosya");
    item2->setIcon(image2);
    ui->picList->addItem(item2);

    QListWidgetItem *item3 = new QListWidgetItem("Gradient");
    item3->setIcon(image3);
    ui->picList->addItem(item3);

    imagePixmap.load(this->imagePath);
    if(imagePixmap.isNull())
    {
        qDebug()<<"Картинка была не найдена";
    }
    else
    {
        ui->OrigLabel->setPixmap(imagePixmap);
        ui->OrigLabel->setScaledContents(true);
        ui->renderingLabel->setPixmap(imagePixmap);
        ui->renderingLabel->setScaledContents(true);
        originalImage = cv::imread(imagePath.toStdString());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    originalImage = cv::imread(imagePath.toStdString());
    cv::Mat filteredImage;
    cv::GaussianBlur(originalImage, filteredImage, cv::Size(5, 5), 0);
    QImage img(filteredImage.data, filteredImage.cols, filteredImage.rows, filteredImage.step, QImage::Format_RGB888);
    QPixmap pixmap = QPixmap::fromImage(img);
     ui->renderingLabel->setPixmap(pixmap);
     ui->renderingLabel->setScaledContents(true);
}


void MainWindow::on_pushButton_4_clicked()
{
    this->imagePath = this->vec[this->currItem];
    imagePixmap.load(this->imagePath);
    ui->OrigLabel->setPixmap(this->imagePixmap);
    ui->OrigLabel->setScaledContents(true);
    ui->renderingLabel->setPixmap(this->imagePixmap);
    ui->renderingLabel->setScaledContents(true);
}


void MainWindow::on_pushButton_2_clicked()
{
    if (!ui->renderingLabel->pixmap()) {
        qWarning("No image to process");
        return;
    }
    QPixmap originalPixmap = ui->renderingLabel->pixmap();
    QImage originalImage = originalPixmap.toImage();

    cv::Mat inputImage(originalImage.height(), originalImage.width(), CV_8UC4, originalImage.bits(), originalImage.bytesPerLine());
    cv::Mat processedImage;

    cv::cvtColor(inputImage, processedImage, cv::COLOR_BGR2GRAY);
    cv::threshold(processedImage, processedImage, 128, 255, cv::THRESH_BINARY);

    QImage processedQImage(processedImage.data, processedImage.cols, processedImage.rows, processedImage.step, QImage::Format_Grayscale8);

    QPixmap processedPixmap = QPixmap::fromImage(processedQImage);
    ui->renderingLabel->setPixmap(processedPixmap);
    ui->renderingLabel->setScaledContents(true);

}



void MainWindow::on_pushButton_3_clicked()
{
    if (!ui->renderingLabel->pixmap()) {
        qWarning("No image to process");
        return;
    }
    QPixmap originalPixmap = ui->renderingLabel->pixmap();
    QImage originalImage = originalPixmap.toImage();
    cv::Mat inputImage(originalImage.height(), originalImage.width(), CV_8UC4, originalImage.bits(), originalImage.bytesPerLine());
    cv::Mat processedImage;

    cv::cvtColor(inputImage, processedImage, cv::COLOR_BGR2GRAY);
    cv::adaptiveThreshold(processedImage, processedImage, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 11, 2);

    QImage processedQImage(processedImage.data, processedImage.cols, processedImage.rows, processedImage.step, QImage::Format_Grayscale8);

    QPixmap processedPixmap = QPixmap::fromImage(processedQImage);

    ui->renderingLabel->setPixmap(processedPixmap);
    ui->renderingLabel->setScaledContents(true);
}



void MainWindow::on_pushButton_5_clicked()
{

    if (!ui->renderingLabel->pixmap()) {
        qWarning("No image to process");
        return;
    }


    QPixmap originalPixmap = ui->renderingLabel->pixmap();

    QImage originalImage = originalPixmap.toImage();


    cv::Mat inputImage(originalImage.height(), originalImage.width(), CV_8UC4, originalImage.bits(), originalImage.bytesPerLine());
    cv::Mat processedImage;


    cv::cvtColor(inputImage, processedImage, cv::COLOR_BGR2GRAY);

    cv::equalizeHist(processedImage, processedImage);

    QImage processedQImage(processedImage.data, processedImage.cols, processedImage.rows, processedImage.step, QImage::Format_Grayscale8);

    QPixmap processedPixmap = QPixmap::fromImage(processedQImage);

    ui->renderingLabel->setPixmap(processedPixmap);
    ui->renderingLabel->setScaledContents(true);
}



void MainWindow::on_grayParts_clicked()
{

    if (!ui->renderingLabel->pixmap()) {
        qWarning("No image to process");
        return;
    }

    QPixmap originalPixmap = ui->renderingLabel->pixmap();

    QImage originalImage = originalPixmap.toImage();


    cv::Mat inputImage(originalImage.height(), originalImage.width(), CV_8UC4, originalImage.bits(), originalImage.bytesPerLine());
    cv::Mat processedImage;


    cv::cvtColor(inputImage, processedImage, cv::COLOR_BGR2GRAY);

    QImage processedQImage(processedImage.data, processedImage.cols, processedImage.rows, processedImage.step, QImage::Format_Grayscale8);

    QPixmap processedPixmap = QPixmap::fromImage(processedQImage);

    ui->renderingLabel->setPixmap(processedPixmap);
    ui->renderingLabel->setScaledContents(true);
}



void MainWindow::on_picList_currentRowChanged(int currentRow)
{
    if (currentRow >= 0 && currentRow < ui->picList->count()) {
        this->currItem = currentRow;
        QListWidgetItem *selectedItem = ui->picList->item(currentRow);

        QIcon itemIcon = selectedItem->icon();
        QPixmap selectedImage = itemIcon.pixmap(itemIcon.availableSizes().first());


        this->imagePath = this->vec[this->currItem];
        imagePixmap.load(this->imagePath);
        ui->OrigLabel->setPixmap(this->imagePixmap);
        ui->OrigLabel->setScaledContents(true);
        ui->renderingLabel->setPixmap(this->imagePixmap);
        ui->renderingLabel->setScaledContents(true);
    }
}


