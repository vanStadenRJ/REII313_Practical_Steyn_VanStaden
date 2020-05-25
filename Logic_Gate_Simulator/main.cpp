/* * * * * * * * * * * * * * * * * * * * * * * *
 * Project Title:       Logic Gate Simulator
 * Module:              REII 313
 * Assignment:          Practical
 * Contributors:        CE STEYN
 *                      30070147
 *                      RJ VAN STADEN
 *                      30026792
 * First Commit Date:   25/04/2020
 * Last Commit Date:    11/06/2020
 * Version:             v0.01
 * * * * * * * * * * * * * * * * * * * * * * * */

#include <QApplication>
#include <QMainWindow>
#include <QLayout>

#include "Simulation.h"
#include "mainwindow.h"

//External Global variable as to be used throughout program
Simulation * simulation;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Mainwindow start
    MainWindow mw;
    simulation = new Simulation(&mw);

    //Set GraphicsView as central widget
    mw.setCentralWidget(simulation);
    mw.setFixedSize(1600,900);
    mw.centralWidget()->setGeometry(0,0,1600,900);
    mw.show();

    return a.exec();
}
