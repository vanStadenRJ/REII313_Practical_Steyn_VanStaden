/* * * * * * * * * * * * * * * * * * * * * * * *
 * Project Title:       Logic Gate Simulator
 * Module:              REII 313
 * Assignment:          Practical
 * Contributors:        CE STEYN
 *                      30070147
 *                      RJ VAN STADEN
 *                      30026792
 * First Commit Date:   25/04/2020
 * Last Commit Date:    10/06/2020
 * Version:             v2.0
 * * * * * * * * * * * * * * * * * * * * * * * */

#include <QApplication>
#include <QMainWindow>

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
    mw.setFixedSize(1800,885);
    mw.centralWidget()->setGeometry(0,0,1800,885);
    mw.show();

    return a.exec();
}
