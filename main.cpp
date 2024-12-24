#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // 设置应用程序信息
    QApplication::setApplicationName("图像标注工具");
    QApplication::setOrganizationName("YourCompany");
    QApplication::setApplicationVersion("1.0");

    MainWindow w;
    w.show();
    
    return a.exec();
} 