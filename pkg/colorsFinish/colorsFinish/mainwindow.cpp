
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800,600);
    this->MainColor = QColor(Qt::gray);
    ui->ColorFrame->setStyleSheet("background-color:"+this->MainColor.name()+";");
    ui->ColorLineEdit->setText(this->MainColor.name());
    this->R = this->MainColor.red();
    this->G = this->MainColor.green();
    this->B = this->MainColor.blue();
    RgbToXyz();
    ui->RSlider->setMaximum(255);
    ui->RSlider->setMinimum(0);
    ui->GSlider->setMaximum(255);
    ui->GSlider->setMinimum(0);
    ui->BSlider->setMaximum(255);
    ui->BSlider->setMinimum(0);

    ui->XSlider->setMaximum(95.05);
    ui->XSlider->setMinimum(0);
    ui->YSlider->setMaximum(100);
    ui->YSlider->setMinimum(0);
    ui->ZSlider->setMaximum(108.88);
    ui->ZSlider->setMinimum(0);

    ui->HSlider->setMaximum(300);
    ui->HSlider->setMinimum(0);
    ui->SSlider->setMaximum(255);
    ui->SSlider->setMinimum(0);
    ui->LSlider->setMaximum(255);
    ui->LSlider->setMinimum(0);

    ui->RSlider->setValue(this->R);
    ui->GSlider->setValue(this->G);
    ui->BSlider->setValue(this->B);
    Regenerator();
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ChangeColor_clicked()
{
    QColor selectedColor=QColorDialog::getColor();
    if(selectedColor.isValid())
    {
        this->MainColor = selectedColor;
        ui->ColorLineEdit->setText(this->MainColor.name());
        ui->ColorFrame->setStyleSheet("background-color:"+this->MainColor.name()+";");
        Regenerator();
    }
}


void MainWindow::on_ColorLineEdit_textChanged(const QString &arg1)
{
    QColor newColor(arg1);
    ui->ColorFrame->setStyleSheet("background-color:"+newColor.name()+";");
    this->MainColor = newColor;
    RgbToXyz();
    Regenerator();
}

void MainWindow::Regenerator()
{
    ui->ColorFrame->setStyleSheet("background-color:"+this->MainColor.name()+";");
    ui->ColorLineEdit->setText(this->MainColor.name());

    this->R = this->MainColor.red();
    this->G = this->MainColor.green();
    this->B = this->MainColor.blue();
    SliderBlocker();
    ui->RSlider->setValue(this->R);
    ui->GSlider->setValue(this->G);
    ui->BSlider->setValue(this->B);
    SliderUdBlocker();
    ui->RLineEdit->setText(QString::number(this->R));
    ui->GLineEdit->setText(QString::number(this->G));
    ui->BLineEdit->setText(QString::number(this->B));

    this->MainColor.getHsl(&this->H, &this->S, &this->L);
    SliderBlocker();
    ui->HSlider->setValue(this->H);
    ui->SSlider->setValue(this->S);
    ui->LSlider->setValue(this->L);
    SliderUdBlocker();
    ui->HLineEdit->setText(QString::number(this->H));
    ui->SLineEdit->setText(QString::number(this->S));
    ui->LLineEdit->setText(QString::number(this->L));


    SliderBlocker();
    ui->XSlider->setValue(this->X);
    ui->YSlider->setValue(this->Y);
    ui->ZSlider->setValue(this->Z);
    SliderUdBlocker();
    ui->XLineEdit->setText(QString::number(this->X));
    ui->YLineEdit->setText(QString::number(this->Y));
    ui->ZLineEdit->setText(QString::number(this->Z));
}


void MainWindow::RgbToXyz()
{
    double r = this->MainColor.red();
    double g = this->MainColor.green();
    double b = this->MainColor.blue();
    r/=255;
    b/=255;
    g/=255;
    if(r>0.04045){
        r = pow((r+0.055)/1.055, 2.4);
    }else{
        r/=12.92;
    }
    if(g>0.04045){
        g = pow((g+0.055)/1.055, 2.4);
    }else{
        g/=12.92;
    }
    if(b>0.04045){
        b = pow((b+0.055)/1.055, 2.4);
    }else{
        b/=12.92;
    }
    r*=100;
    g*=100;
    b*=100;
    this->X =(int)(r * 0.4124 + g * 0.3576 + b * 0.1805);
    this->Y = (int)(r * 0.2126 + g * 0.7152 + b * 0.0722);
    this->Z = (int)(r * 0.0193 + g * 0.1192 + b * 0.9505);
}

void MainWindow::SliderBlocker()
{
    ui->RSlider->blockSignals(true);
    ui->GSlider->blockSignals(true);
    ui->BSlider->blockSignals(true);
    ui->XSlider->blockSignals(true);
    ui->YSlider->blockSignals(true);
    ui->ZSlider->blockSignals(true);
    ui->HSlider->blockSignals(true);
    ui->SSlider->blockSignals(true);
    ui->LSlider->blockSignals(true);
}

void MainWindow::SliderUdBlocker()
{
    ui->RSlider->blockSignals(false);
    ui->GSlider->blockSignals(false);
    ui->BSlider->blockSignals(false);
    ui->XSlider->blockSignals(false);
    ui->YSlider->blockSignals(false);
    ui->ZSlider->blockSignals(false);
    ui->HSlider->blockSignals(false);
    ui->SSlider->blockSignals(false);
    ui->LSlider->blockSignals(false);
}


void MainWindow::XyzToRgb()
{
    double x = this->X;
    double y_ = this->Y;
    double z = this->Z;
    double Rn = 0.032406 *x - 0.015372*y_ -0.004986* z;
    double Gn = -0.009689 *x + 0.018758 *y_ + 0.000415 * z;
    double Bn= 0.000557 *x - 0.002040 *y_ + 0.010570 * z;


    double R= qMin(qMax(0.0,From_XYZ_To_RGB(Rn)*255), 255.0);
    double G= qMin(qMax(0.0, From_XYZ_To_RGB(Gn)*255), 255.0);
    double B= qMin(qMax(0.0, From_XYZ_To_RGB(Bn)*255), 255.0);

    this->MainColor.setRed(R);
    this->MainColor.setGreen(G);
    this->MainColor.setBlue(B);
    Regenerator();
}

void MainWindow::RGBCheck()
{
    if (this->R > 255 || this->R < 0 || this->G > 255 || this->G < 0 || this->B > 255 || this->B < 0) {
        ui->ErrorsLine->setText("Значения Rgb вышли за пределы и были приравнены к возможным значениям");
    }
}

void MainWindow::XYZCheck()
{
    if(this->X>95.05)
    {
        this->X =95.05;
         ui->ErrorsLine->setText("Значения Xyz вышли за пределы и были приравнены к возможным значениям");
    }
    if(this->X<0)
    {
        this->X =0;
         ui->ErrorsLine->setText("Значения Xyz вышли за пределы и были приравнены к возможным значениям");
    }
    if(this->Y>100)
    {
        this->Y =100;
         ui->ErrorsLine->setText("Значения Xyz вышли за пределы и были приравнены к возможным значениям");
    }
    if(this->Y<0)
    {
        this->Y =0;
         ui->ErrorsLine->setText("Значения Xyz вышли за пределы и были приравнены к возможным значениям");
    }
    if(this->Z>108.88)
    {
        this->Z =108.88;
         ui->ErrorsLine->setText("Значения Xyz вышли за пределы и были приравнены к возможным значениям");
    }
    if(this->Z<0)
    {
        this->Z =0;
         ui->ErrorsLine->setText("Значения Xyz вышли за пределы и были приравнены к возможным значениям");
    }
}

void MainWindow::HSLCheck()
{
    if (this->H > 300 || this->H < 0 || this->S > 255 || this->S < 0 || this->B > 255 || this->B < 0) {
        ui->ErrorsLine->setText("Значения Hsl вышли за пределы и были приравнены к возможным значениям");
    }
}


void MainWindow::on_HLineEdit_textEdited(const QString &arg1)
{
    ui->ErrorsLine->setText("");
    this->H = arg1.toInt();
    HSLCheck();
    this->MainColor.setHsl(this->H,this->S,this->L);
    RgbToXyz();
    Regenerator();
}


void MainWindow::on_SLineEdit_textEdited(const QString &arg1)
{
    ui->ErrorsLine->setText("");
    this->S = arg1.toInt();
    HSLCheck();
    this->MainColor.setHsl(this->H,this->S,this->L);
    RgbToXyz();
    Regenerator();
}


void MainWindow::on_LLineEdit_textEdited(const QString &arg1)
{
    ui->ErrorsLine->setText("");
    this->L = arg1.toInt();
    HSLCheck();
    this->MainColor.setHsl(this->H,this->S,this->L);
    RgbToXyz();
    Regenerator();
}


void MainWindow::on_XLineEdit_textEdited(const QString &arg1)
{
    ui->ErrorsLine->setText("");
    this->X =arg1.toInt();
    XYZCheck();
    XyzToRgb();
}


void MainWindow::on_YLineEdit_textEdited(const QString &arg1)
{
    ui->ErrorsLine->setText("");
    this->Y =arg1.toInt();
    XYZCheck();
    XyzToRgb();
}


void MainWindow::on_ZLineEdit_textEdited(const QString &arg1)
{
    ui->ErrorsLine->setText("");
    this->Z =arg1.toInt();
    XYZCheck();
    XyzToRgb();
}


void MainWindow::on_RLineEdit_textEdited(const QString &arg1)
{
    ui->ErrorsLine->setText("");
    this->R = arg1.toInt();
    RGBCheck();
    this->MainColor.setRed(this->R);
    RgbToXyz();
    Regenerator();
}


void MainWindow::on_GLineEdit_textEdited(const QString &arg1)
{
    ui->ErrorsLine->setText("");
    this->G = arg1.toInt();
    RGBCheck();
    this->MainColor.setGreen(arg1.toInt());
    RgbToXyz();
    Regenerator();
}


void MainWindow::on_BLineEdit_textEdited(const QString &arg1)
{
    ui->ErrorsLine->setText("");
    this->B = arg1.toInt();
    RGBCheck();
    this->MainColor.setBlue(arg1.toInt());
    RgbToXyz();
    Regenerator();
}



double MainWindow::From_XYZ_To_RGB(double a)
{
    double x=a;
    if(x >= 0.0031308)
    {
        return (1.055*pow(x,1.0/2.4)-0.055);
    }
    else return 12.92*x;
}

void MainWindow::on_RSlider_valueChanged(int value)
{
    this->R = value;
    RGBCheck();
    this->MainColor.setRed(this->R);
    RgbToXyz();
    Regenerator();
}


void MainWindow::on_GSlider_valueChanged(int value)
{
    this->G = value;
    RGBCheck();
    this->MainColor.setGreen(this->G);
    RgbToXyz();
    Regenerator();
}


void MainWindow::on_BSlider_valueChanged(int value)
{
    this->B = value;
    RGBCheck();
    this->MainColor.setBlue(this->B);
    RgbToXyz();
    Regenerator();
}


void MainWindow::on_HSlider_valueChanged(int value)
{
    this->H = value;
    HSLCheck();
    this->MainColor.setHsl(this->H,this->S,this->L);
    RgbToXyz();
    Regenerator();
}


void MainWindow::on_SSlider_valueChanged(int value)
{
    this->S = value;
    HSLCheck();
    this->MainColor.setHsl(this->H,this->S,this->L);
    RgbToXyz();
    Regenerator();
}


void MainWindow::on_LSlider_valueChanged(int value)
{
    this->L = value;
    HSLCheck();
    this->MainColor.setHsl(this->H,this->S,this->L);
    RgbToXyz();
    Regenerator();
}


void MainWindow::on_XSlider_valueChanged(int value)
{
    this->X =value;
    XYZCheck();
    XyzToRgb();
}


void MainWindow::on_YSlider_valueChanged(int value)
{
    this->Y =value;
    XYZCheck();
    XyzToRgb();
}


void MainWindow::on_ZSlider_valueChanged(int value)
{
    this->Z =value;
    XYZCheck();
    XyzToRgb();
}

