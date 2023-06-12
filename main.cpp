#include <QApplication>
#include <QThread>
#include <QMessageBox>
#include <QIcon>
#include <QSplashScreen>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QPixmap img = QPixmap(":images/splash.jpg").scaled(500,250);
    QSplashScreen *splash = new QSplashScreen(img);
    splash->show();
    splash->showMessage("加载中......",Qt::AlignBottom,Qt::black);
    QApplication::processEvents();
    QApplication::setWindowIcon(QIcon(":/images/launchicon.png"));
    w.thread()->sleep(3);
    w.show();
    splash->finish(&w);
    return a.exec();
}
