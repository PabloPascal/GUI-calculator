#include <iostream>
#include <QApplication>
#include "mainwindow.hpp"



int main(int argc, char* argv[]){


    QApplication app(argc, argv);

    std::setlocale(LC_ALL, "C");
    std::locale::global(std::locale("C"));


    Window* w = new Window;
    w->show();


    return app.exec();

}