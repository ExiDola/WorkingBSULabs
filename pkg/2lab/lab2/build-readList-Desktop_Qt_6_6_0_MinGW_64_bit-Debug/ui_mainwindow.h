/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *chooseFileBut;
    QLabel *label;
    QLabel *InfLabel;
    QTableWidget *mainTable;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(978, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(200, 200, 200, 255), stop:1 rgba(100, 100, 100, 255));\n"
"}\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        chooseFileBut = new QPushButton(centralwidget);
        chooseFileBut->setObjectName("chooseFileBut");
        chooseFileBut->setGeometry(QRect(10, 10, 151, 71));
        chooseFileBut->setStyleSheet(QString::fromUtf8("font-weight: bold;\n"
"   padding: 5px;\n"
"   background: #00ffff;\n"
" border: 1px solid #dddddd;\n"
"border-radius: 10px;"));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(170, 0, 571, 31));
        label->setStyleSheet(QString::fromUtf8("font-weight: bold;\n"
"padding: 5px;\n"
"background: #ffff7f;\n"
"border: 1px solid #dddddd;\n"
"border-radius: 10px;"));
        InfLabel = new QLabel(centralwidget);
        InfLabel->setObjectName("InfLabel");
        InfLabel->setGeometry(QRect(170, 30, 571, 51));
        InfLabel->setStyleSheet(QString::fromUtf8("font-weight: bold;\n"
"padding: 5px;\n"
"background: #ffddfd;\n"
"border: 1px solid #dddddd;\n"
"border-radius: 10px;"));
        mainTable = new QTableWidget(centralwidget);
        mainTable->setObjectName("mainTable");
        mainTable->setGeometry(QRect(10, 90, 901, 431));
        mainTable->setStyleSheet(QString::fromUtf8("font-family: Arial, sans-serif;\n"
"font-size: 14px;\n"
"\n"
"background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #beffa0, stop:1 #f5f5f5);\n"
"border: 1px solid #dddddd;\n"
"color: #333333;\n"
"border-radius: 5px;"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(750, 10, 161, 71));
        pushButton->setStyleSheet(QString::fromUtf8("font-weight: bold;\n"
"   padding: 5px;\n"
"   background: #00ffff;\n"
" border: 1px solid #dddddd;\n"
"border-radius: 10px;"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 978, 21));
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
        chooseFileBut->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \320\237\320\260\320\277\320\272\321\203", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\230\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217:", nullptr));
        InfLabel->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \320\244\320\260\320\271\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
