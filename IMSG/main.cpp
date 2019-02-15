#include "mainwindow.h"
#include "loginwindow.h"
#include "talkwindow.h"
#include <QApplication>
#include "stackdlg.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font("Microsoft YaHei", 12);
    a.setFont(font);
    //MainWindow w;
    //w.show();

    //LoginWindow lw;
    //lw.show();

    TalkWindow tw;
    tw.show();

    return a.exec();
}
