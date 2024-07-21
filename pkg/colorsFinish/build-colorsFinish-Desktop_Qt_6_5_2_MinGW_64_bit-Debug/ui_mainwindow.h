/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *ColorFrame;
    QPushButton *ChangeColor;
    QLineEdit *ColorLineEdit;
    QLabel *label;
    QGroupBox *groupBox;
    QLineEdit *RLineEdit;
    QLineEdit *GLineEdit;
    QLineEdit *BLineEdit;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QSlider *RSlider;
    QSlider *GSlider;
    QSlider *BSlider;
    QGroupBox *groupBox_2;
    QLineEdit *XLineEdit;
    QLineEdit *YLineEdit;
    QLineEdit *ZLineEdit;
    QLabel *Xlabel;
    QLabel *YLabel;
    QLabel *ZLabel;
    QSlider *XSlider;
    QSlider *YSlider;
    QSlider *ZSlider;
    QGroupBox *groupBox_3;
    QLineEdit *HLineEdit;
    QLineEdit *SLineEdit;
    QLineEdit *LLineEdit;
    QLabel *HLabel;
    QLabel *LLabel;
    QLabel *SLabel;
    QSlider *HSlider;
    QSlider *SSlider;
    QSlider *LSlider;
    QLabel *ErrorsLine;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(200, 200, 200, 255), stop:1 rgba(100, 100, 100, 255));\n"
"}\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        ColorFrame = new QFrame(centralwidget);
        ColorFrame->setObjectName("ColorFrame");
        ColorFrame->setGeometry(QRect(60, 20, 191, 131));
        ColorFrame->setFrameShape(QFrame::StyledPanel);
        ColorFrame->setFrameShadow(QFrame::Raised);
        ChangeColor = new QPushButton(centralwidget);
        ChangeColor->setObjectName("ChangeColor");
        ChangeColor->setGeometry(QRect(300, 30, 191, 31));
        ChangeColor->setStyleSheet(QString::fromUtf8("font-weight: bold;\n"
"   padding: 5px;\n"
"   background: #00ffff;\n"
" border: 1px solid #dddddd;\n"
"border-radius: 10px;"));
        ColorLineEdit = new QLineEdit(centralwidget);
        ColorLineEdit->setObjectName("ColorLineEdit");
        ColorLineEdit->setGeometry(QRect(300, 100, 191, 31));
        ColorLineEdit->setStyleSheet(QString::fromUtf8("font-weight: bold;\n"
"padding: 5px;\n"
"background: #ddfdff;\n"
"border: 1px solid #dddddd;\n"
"border-radius: 10px;"));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(540, 30, 181, 31));
        label->setStyleSheet(QString::fromUtf8("font-weight: bold;\n"
"padding: 5px;\n"
"background: #ffddfd;\n"
"border: 1px solid #dddddd;\n"
"border-radius: 10px;"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(60, 160, 191, 231));
        groupBox->setStyleSheet(QString::fromUtf8("font-weight: bold;\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 0 5px;\n"
"    background: #a0a6ff;\n"
"    border-top-left-radius: 6px;\n"
"    border-top-right-radius: 6px;"));
        RLineEdit = new QLineEdit(groupBox);
        RLineEdit->setObjectName("RLineEdit");
        RLineEdit->setGeometry(QRect(10, 40, 171, 24));
        RLineEdit->setStyleSheet(QString::fromUtf8("font-weight: bold;\n"
"padding: 5px;\n"
"background: #ff898b;\n"
"border: 1px solid #dddddd;"));
        GLineEdit = new QLineEdit(groupBox);
        GLineEdit->setObjectName("GLineEdit");
        GLineEdit->setGeometry(QRect(10, 110, 171, 24));
        GLineEdit->setStyleSheet(QString::fromUtf8("font-weight: bold;\n"
"padding: 5px;\n"
"background: #ff898b;\n"
"border: 1px solid #dddddd;"));
        BLineEdit = new QLineEdit(groupBox);
        BLineEdit->setObjectName("BLineEdit");
        BLineEdit->setGeometry(QRect(10, 180, 171, 24));
        BLineEdit->setStyleSheet(QString::fromUtf8("font-weight: bold;\n"
"padding: 5px;\n"
"background: #ff898b;\n"
"border: 1px solid #dddddd;"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 20, 171, 16));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 90, 171, 16));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 160, 171, 16));
        RSlider = new QSlider(groupBox);
        RSlider->setObjectName("RSlider");
        RSlider->setGeometry(QRect(10, 70, 160, 16));
        RSlider->setOrientation(Qt::Horizontal);
        GSlider = new QSlider(groupBox);
        GSlider->setObjectName("GSlider");
        GSlider->setGeometry(QRect(10, 140, 160, 16));
        GSlider->setOrientation(Qt::Horizontal);
        BSlider = new QSlider(groupBox);
        BSlider->setObjectName("BSlider");
        BSlider->setGeometry(QRect(10, 210, 160, 16));
        BSlider->setOrientation(Qt::Horizontal);
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(300, 160, 191, 231));
        groupBox_2->setStyleSheet(QString::fromUtf8("font-weight: bold;\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 0 5px;\n"
"    background: #a0a6ff;\n"
"    border-top-left-radius: 6px;\n"
"    border-top-right-radius: 6px;"));
        XLineEdit = new QLineEdit(groupBox_2);
        XLineEdit->setObjectName("XLineEdit");
        XLineEdit->setGeometry(QRect(10, 40, 171, 24));
        XLineEdit->setStyleSheet(QString::fromUtf8("font-weight: bold;\n"
"padding: 5px;\n"
"background: #ffff7f;\n"
"border: 1px solid #dddddd;"));
        YLineEdit = new QLineEdit(groupBox_2);
        YLineEdit->setObjectName("YLineEdit");
        YLineEdit->setGeometry(QRect(10, 110, 171, 24));
        YLineEdit->setStyleSheet(QString::fromUtf8("font-weight: bold;\n"
"padding: 5px;\n"
"background: #ffff7f;\n"
"border: 1px solid #dddddd;"));
        ZLineEdit = new QLineEdit(groupBox_2);
        ZLineEdit->setObjectName("ZLineEdit");
        ZLineEdit->setGeometry(QRect(10, 180, 171, 24));
        ZLineEdit->setStyleSheet(QString::fromUtf8("font-weight: bold;\n"
"padding: 5px;\n"
"background: #ffff7f;\n"
"border: 1px solid #dddddd;"));
        Xlabel = new QLabel(groupBox_2);
        Xlabel->setObjectName("Xlabel");
        Xlabel->setGeometry(QRect(10, 20, 171, 16));
        YLabel = new QLabel(groupBox_2);
        YLabel->setObjectName("YLabel");
        YLabel->setGeometry(QRect(10, 90, 171, 16));
        ZLabel = new QLabel(groupBox_2);
        ZLabel->setObjectName("ZLabel");
        ZLabel->setGeometry(QRect(10, 160, 171, 16));
        XSlider = new QSlider(groupBox_2);
        XSlider->setObjectName("XSlider");
        XSlider->setGeometry(QRect(10, 70, 160, 16));
        XSlider->setOrientation(Qt::Horizontal);
        YSlider = new QSlider(groupBox_2);
        YSlider->setObjectName("YSlider");
        YSlider->setGeometry(QRect(10, 140, 160, 16));
        YSlider->setOrientation(Qt::Horizontal);
        ZSlider = new QSlider(groupBox_2);
        ZSlider->setObjectName("ZSlider");
        ZSlider->setGeometry(QRect(10, 210, 160, 16));
        ZSlider->setOrientation(Qt::Horizontal);
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(530, 160, 201, 231));
        groupBox_3->setStyleSheet(QString::fromUtf8("font-weight: bold;\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 0 5px;\n"
"    background: #a0a6ff;\n"
"    border-top-left-radius: 6px;\n"
"    border-top-right-radius: 6px;"));
        HLineEdit = new QLineEdit(groupBox_3);
        HLineEdit->setObjectName("HLineEdit");
        HLineEdit->setGeometry(QRect(10, 40, 181, 24));
        HLineEdit->setStyleSheet(QString::fromUtf8("font-weight: bold;\n"
"padding: 5px;\n"
"background: #55ff7f;\n"
"border: 1px solid #dddddd;"));
        SLineEdit = new QLineEdit(groupBox_3);
        SLineEdit->setObjectName("SLineEdit");
        SLineEdit->setGeometry(QRect(10, 110, 181, 24));
        SLineEdit->setStyleSheet(QString::fromUtf8("font-weight: bold;\n"
"padding: 5px;\n"
"background: #55ff7f;\n"
"border: 1px solid #dddddd;"));
        LLineEdit = new QLineEdit(groupBox_3);
        LLineEdit->setObjectName("LLineEdit");
        LLineEdit->setGeometry(QRect(10, 180, 181, 24));
        LLineEdit->setStyleSheet(QString::fromUtf8("font-weight: bold;\n"
"padding: 5px;\n"
"background: #55ff7f;\n"
"border: 1px solid #dddddd;"));
        HLabel = new QLabel(groupBox_3);
        HLabel->setObjectName("HLabel");
        HLabel->setGeometry(QRect(10, 20, 181, 16));
        LLabel = new QLabel(groupBox_3);
        LLabel->setObjectName("LLabel");
        LLabel->setGeometry(QRect(10, 90, 181, 16));
        SLabel = new QLabel(groupBox_3);
        SLabel->setObjectName("SLabel");
        SLabel->setGeometry(QRect(10, 160, 181, 16));
        HSlider = new QSlider(groupBox_3);
        HSlider->setObjectName("HSlider");
        HSlider->setGeometry(QRect(20, 70, 160, 16));
        HSlider->setOrientation(Qt::Horizontal);
        SSlider = new QSlider(groupBox_3);
        SSlider->setObjectName("SSlider");
        SSlider->setGeometry(QRect(20, 140, 160, 16));
        SSlider->setOrientation(Qt::Horizontal);
        LSlider = new QSlider(groupBox_3);
        LSlider->setObjectName("LSlider");
        LSlider->setGeometry(QRect(20, 210, 160, 16));
        LSlider->setOrientation(Qt::Horizontal);
        ErrorsLine = new QLabel(centralwidget);
        ErrorsLine->setObjectName("ErrorsLine");
        ErrorsLine->setGeometry(QRect(60, 400, 661, 161));
        ErrorsLine->setStyleSheet(QString::fromUtf8("font-family: Arial, sans-serif;\n"
"    font-size: 14px;\n"
"    padding: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #beffa0, stop:1 #f5f5f5);\n"
"    border: 1px solid #dddddd;\n"
"    border-radius: 5px;\n"
"    color: #333333;"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        ChangeColor->setText(QCoreApplication::translate("MainWindow", "Change Color", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "12:RGB \342\206\224 XYZ \342\206\224 HSL", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "RGB", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "R", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "G", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "XYZ", nullptr));
        Xlabel->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        YLabel->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        ZLabel->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "HLS", nullptr));
        HLabel->setText(QCoreApplication::translate("MainWindow", "H", nullptr));
        LLabel->setText(QCoreApplication::translate("MainWindow", "S", nullptr));
        SLabel->setText(QCoreApplication::translate("MainWindow", "L", nullptr));
        ErrorsLine->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
