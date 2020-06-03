#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Simulation.h"
#include "Gate.h"

#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
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
        this->clearScene();
    }
}

void MainWindow::on_actionOpen_triggered()
{    

    QString json_filter = "JSON (*.json)";
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/",
                                                          tr("Any File (*);;%1").arg(json_filter),
                                                          &json_filter, QFileDialog::DontUseNativeDialog);

    if(fileName.isEmpty())
    {

    }
    else
    {
        this->clearScene();
        QFile input(fileName);
        if(input.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream file_text(&input);
            QString json_string;
            json_string = file_text.readAll();
            input.close();
            QByteArray json_bytes = json_string.toLocal8Bit();

            auto json_doc = QJsonDocument::fromJson(json_bytes);

            if(json_doc["Gates"].isArray())
            {
                qDebug() << "Object";
            }

            //QJsonObject obj_Load = json_doc.object();
            QJsonArray arr_Gates = json_doc["Gates"].toArray();

            simulation->nr_Gates = 0;
            for(int i = 0; i < arr_Gates.count(); i++)
            {
                QJsonObject obj_Gates;
                obj_Gates = arr_Gates.at(i).toObject();
                Gate * gate = new Gate(i+1, obj_Gates["Type"].toInt(), obj_Gates["nr_Inputs"].toInt());
                simulation->nr_Gates = simulation->nr_Gates++;
                gate->setPos(obj_Gates["x_Pos"].toDouble(), obj_Gates["y_Pos"].toDouble());
                simulation->scene->addItem(gate);
                gate->pos_Gate = gate->pos();

                simulation->list_Gates << gate;
                for(int j = 0; j < simulation->list_Gates.size(); j++)
                {
                    simulation->list_Gates.at(j)->setCenterPos();
                }
            }
            QMessageBox::information(this, tr("Message"), tr("Document Loaded Successfully"));
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    QString json_filter = "JSON (*.json)";
    QString fileName = QFileDialog::getSaveFileName(this, tr("Open File"), "/",
                                                          tr("Any File (*);;%1").arg(json_filter),
                                                          &json_filter, QFileDialog::DontUseNativeDialog);

    if(fileName.isEmpty())
    {

    }
    else
    {
        QJsonArray arr_Gates;
        for(int i = 0; i < simulation->list_Gates.size(); i++)
        {
            QJsonObject obj_Gates;
            obj_Gates["Type"] = simulation->list_Gates.at(i)->gateType;
            obj_Gates["x_Pos"] = simulation->list_Gates.at(i)->x();
            obj_Gates["y_Pos"] = simulation->list_Gates.at(i)->y();
            obj_Gates["Logic"] = simulation->list_Gates.at(i)->LogicalOutput;
            obj_Gates["nr_Inputs"] = simulation->list_Gates.at(i)->input_size;
            arr_Gates << obj_Gates;
        }



        QJsonObject obj_Save;
        obj_Save.insert("Gates", arr_Gates);
        QJsonDocument json_save(obj_Save);
        QString json_string = json_save.toJson();

        QFile output(fileName);
        if(output.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            output.write(json_string.toLocal8Bit());
            output.close();
            QMessageBox::information(this, tr("Message"), tr("Document Saved Successfully"));
        }
        else
        {
            QMessageBox::critical(this, tr("Error"), output.errorString());
        }
    }
}

void MainWindow::clearScene()
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

void MainWindow::newGates()
{

}
