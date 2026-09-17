//#include "mainwindow.h"
#include <QApplication>
#include "view.h"
#include "model.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    Model model;
        View window;
        Controller ctrl(&model);
        window.setController(&ctrl);
        window.show();
    return a.exec();
}
