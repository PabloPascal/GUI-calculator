#include <iostream>
#include <QApplication>

#include "mainwindow.hpp"

int main(int argc, char* argv[]){

    QApplication app(argc, argv);

    Window* w = new Window;
    w->show();

    return app.exec();

}