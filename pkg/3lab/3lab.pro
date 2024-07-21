QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH +=C:\Users\Zephyrus\Downloads\opencv\release\install\include

LIBS +=C:\Users\Zephyrus\Downloads\opencv\release\bin\libopencv_calib3d480.dll
LIBS +=C:\Users\Zephyrus\Downloads\opencv\release\bin\libopencv_core480.dll
LIBS +=C:\Users\Zephyrus\Downloads\opencv\release\bin\libopencv_dnn480.dll
LIBS +=C:\Users\Zephyrus\Downloads\opencv\release\bin\libopencv_features2d480.dll
LIBS +=C:\Users\Zephyrus\Downloads\opencv\release\bin\libopencv_flann480.dll
LIBS +=C:\Users\Zephyrus\Downloads\opencv\release\bin\libopencv_gapi480.dll
LIBS +=C:\Users\Zephyrus\Downloads\opencv\release\bin\libopencv_highgui480.dll
LIBS +=C:\Users\Zephyrus\Downloads\opencv\release\bin\libopencv_imgcodecs480.dll
LIBS +=C:\Users\Zephyrus\Downloads\opencv\release\bin\libopencv_imgproc480.dll
LIBS +=C:\Users\Zephyrus\Downloads\opencv\release\bin\libopencv_ml480.dll
LIBS +=C:\Users\Zephyrus\Downloads\opencv\release\bin\libopencv_objdetect480.dll
LIBS +=C:\Users\Zephyrus\Downloads\opencv\release\bin\libopencv_photo480.dll
LIBS +=C:\Users\Zephyrus\Downloads\opencv\release\bin\libopencv_stitching480.dll
LIBS +=C:\Users\Zephyrus\Downloads\opencv\release\bin\libopencv_video480.dll
LIBS +=C:\Users\Zephyrus\Downloads\opencv\release\bin\libopencv_videoio480.dll
LIBS +=C:\Users\Zephyrus\Downloads\opencv\release\bin\opencv_videoio_ffmpeg480_64.dll


SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
