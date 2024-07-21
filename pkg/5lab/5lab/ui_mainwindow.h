
#include <QPalette>

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QRadioButton *segments;
    QRadioButton *poly;
    QLabel *clippingText;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        centralwidget = new QWidget(MainWindow);
        segments = new QRadioButton(centralwidget);
        poly = new QRadioButton(centralwidget);
        clippingText = new QLabel(centralwidget);
        menubar = new QMenuBar(MainWindow);
        statusbar = new QStatusBar(MainWindow);
        QFont font;
        QPalette pal = MainWindow->palette();
        QFont font1;

        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);

        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));

        segments->setObjectName(QString::fromUtf8("segments"));
        segments->setGeometry(QRect(470, 260, 133, 27));

        font.setFamily(QString::fromUtf8("Segoe UI"));
        font.setPointSize(12);
        segments->setFont(font);


        pal.setColor(QPalette::Window, QColor(240, 240, 240));
        pal.setColor(QPalette::WindowText, Qt::black);
        segments->setPalette(pal);


        poly->setObjectName(QString::fromUtf8("poly"));
        poly->setGeometry(QRect(470, 190, 291, 61));

        font1.setFamily(QString::fromUtf8("Segoe UI"));
        font1.setPointSize(12);
        font1.setUnderline(false);
        poly->setFont(font1);
        poly->setPalette(pal);


        clippingText->setObjectName(QString::fromUtf8("clippingText"));
        clippingText->setGeometry(QRect(470, 140, 221, 51));
        clippingText->setFont(font);
        clippingText->setPalette(pal);


        MainWindow->setCentralWidget(centralwidget);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        segments->setText("Отрезков Сазерленда-Коэна");
        poly->setText("Выпуклого многоугольника");
        clippingText->setText("Выберите алгоритм отсечения");
        QMetaObject::connectSlotsByName(MainWindow);
    }
};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
}
