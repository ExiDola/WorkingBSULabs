#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QColor>
#include <QMainWindow>
#include<QDialog>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void Regenerator();

    void RgbToXyz();


    void SliderBlocker();
    void SliderUdBlocker();

    void XyzToRgb();

    void RGBCheck();
    void XYZCheck();
    void HSLCheck();
    double From_XYZ_To_RGB(double a);
    ~MainWindow();

private slots:
    void on_ChangeColor_clicked();


    void on_ColorLineEdit_textChanged(const QString &arg1);

    void on_RLineEdit_textEdited(const QString &arg1);


    void on_HLineEdit_textEdited(const QString &arg1);

    void on_SLineEdit_textEdited(const QString &arg1);

    void on_LLineEdit_textEdited(const QString &arg1);


    void on_XLineEdit_textEdited(const QString &arg1);

    void on_YLineEdit_textEdited(const QString &arg1);

    void on_ZLineEdit_textEdited(const QString &arg1);



    void on_GLineEdit_textEdited(const QString &arg1);

    void on_BLineEdit_textEdited(const QString &arg1);


    void on_RSlider_valueChanged(int value);

    void on_GSlider_valueChanged(int value);

    void on_BSlider_valueChanged(int value);

    void on_HSlider_valueChanged(int value);

    void on_SSlider_valueChanged(int value);

    void on_LSlider_valueChanged(int value);

    void on_XSlider_valueChanged(int value);

    void on_YSlider_valueChanged(int value);

    void on_ZSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QColor MainColor;
    int R;
    int G;
    int B;

    int H;
    int S;
    int L;

    int X;
    int Y;
    int Z;

    double PI = 3.1415926535;
    QColor* conver;
};
#endif // MAINWINDOW_H
