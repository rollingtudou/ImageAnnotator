QT       += core gui xml network widgets

TARGET = ImageAnnotator
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    annotationscene.cpp \
    annotationitem.cpp \
    annotationtools.cpp \
    labeleditor.cpp \
    styledialog.cpp \
    zoomableview.cpp \
    commands.cpp

HEADERS += \
    mainwindow.h \
    annotationscene.h \
    annotationitem.h \
    annotationtools.h \
    labeleditor.h \
    styledialog.h \
    zoomableview.h \
    commands.h

FORMS += \
    mainwindow.ui \
    labeleditor.ui

# 添加资源文件
RESOURCES += \
    resources.qrc

# 添加图标和其他资源
RC_ICONS = icons/app.ico

# 添加Python支持
unix {
    LIBS += -lpython3.8
    INCLUDEPATH += /usr/include/python3.8
}

win32 {
    LIBS += -lpython38
    INCLUDEPATH += C:/Python38/include
} 