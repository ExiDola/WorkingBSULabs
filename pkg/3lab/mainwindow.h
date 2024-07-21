#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <QMainWindow>
#include<QListWidgetItem>
#include<QPixmap>
#include<QVector>

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

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_grayParts_clicked();

    void on_picList_currentRowChanged(int currentRow);


private:
    Ui::MainWindow *ui;
    cv::Mat originalImage;
    QString imagePath;
    QPixmap imagePixmap;
    int currItem;
    QVector<QString> vec;
};
#endif // MAINWINDOW_H
