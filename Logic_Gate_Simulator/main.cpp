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

#include "inputsize.h"
#include "Simulation.h"

//External Global variable as to be used throughout program
Simulation * simulation;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Show QGraphicsView and start program
    simulation = new Simulation();
    simulation->show();

    return a.exec();
}
