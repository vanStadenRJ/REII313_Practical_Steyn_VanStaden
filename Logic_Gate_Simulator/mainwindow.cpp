#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Simulation.h"

#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>

extern Simulation * simulation;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, "New File?",
            "Are you sure you want to start a new project? \nAny unsaved schematics will be lost!",
            QMessageBox::Yes | QMessageBox::Cancel);

    if(reply == QMessageBox::Yes)
    {
        for(int i = 0; i < simulation->list_Gates.size(); i++)
        {
            delete simulation->list_Gates.at(i);
        }
        simulation->list_Gates.clear();

        for(int i = 0; i < simulation->list_Wires.size(); i++)
        {
            delete simulation->list_Wires.at(i);
        }
        simulation->list_Wires.clear();
    }
}
