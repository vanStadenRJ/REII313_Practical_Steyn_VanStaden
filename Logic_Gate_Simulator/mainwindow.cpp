#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Simulation.h"
#include "Gate.h"
#include "Wire.h"

#include <QJsonDocument>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QJsonObject>

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
    // Warning message desplayed to warn user that starting a new schematic will delete any unsaved progress
    // User can press cancel to save schematic
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, "New File?",
            "Are you sure you want to start a new project? \nAny unsaved schematics will be lost!",
            QMessageBox::Yes | QMessageBox::Cancel);

    if(reply == QMessageBox::Yes)
    {
        // Clears and deletes all gates and wires
        this->clearScene();
    }
}

void MainWindow::on_actionOpen_triggered()
{
    // Warning message desplayed to warn user that opening a previously saved schematic will delete any unsaved progress
    // User can press cancel to save schematic
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, "Open File?",
            "Are you sure you want to open a saved schematic? \nAny unsaved schematics will be lost!",
            QMessageBox::Yes | QMessageBox::Cancel);

    if(reply == QMessageBox::Yes)
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
            // Clears gates and wires first before
            this->clearScene();

            // Load file chosen into QFile
            QFile input(fileName);
            if(input.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                // Generate TextStream from data in .json file
                QTextStream file_text(&input);
                QString json_string;
                json_string = file_text.readAll();
                input.close();
                QByteArray json_bytes = json_string.toLocal8Bit();
                auto json_doc = QJsonDocument::fromJson(json_bytes);

                // Read Gate data and generate Gates
                QJsonArray arr_Gates = json_doc["Gates"].toArray();
                simulation->nr_Gates = 0;
                for(int i = 0; i < arr_Gates.count(); i++)
                {
                    QJsonObject obj_Gates;
                    obj_Gates = arr_Gates.at(i).toObject();
                    if(obj_Gates["Nr"].toInt() > simulation->nr_Gates)
                    {
                        simulation->nr_Gates = obj_Gates["Nr"].toInt();
                    }
                    Gate * gate = new Gate(obj_Gates["Nr"].toInt(), obj_Gates["Type"].toInt(), obj_Gates["nr_Inputs"].toInt());
                    gate->setPos(obj_Gates["x_Pos"].toDouble(), obj_Gates["y_Pos"].toDouble());
                    simulation->scene->addItem(gate);
                    gate->pos_Gate = gate->pos();
                    gate->lowTime = obj_Gates["low"].toInt();
                    gate->highTime = obj_Gates["high"].toInt();

                    simulation->list_Gates << gate;
                    for(int j = 0; j < simulation->list_Gates.size(); j++)
                    {
                        simulation->list_Gates.at(j)->setCenterPos();
                    }
                }

                // Read Wires data and generate Wires
                QJsonArray arr_Wires = json_doc["Wires"].toArray();
                simulation->nr_Wires = 0;
                for(int i = 0; i < arr_Wires.count(); i++)
                {
                    // Create new Wire() and load data from object to populate Wire
                    QJsonObject obj_Wires;
                    obj_Wires = arr_Wires.at(i).toObject();
                    Wire * wire = new Wire();
                    wire->dest = QPointF(obj_Wires["Dest_X"].toDouble(), obj_Wires["Dest_Y"].toDouble());
                    wire->source = QPointF(obj_Wires["Src_X"].toDouble(), obj_Wires["Src_Y"].toDouble());
                    wire->dest_Gate = obj_Wires["Dest_Gate"].toInt();
                    simulation->dest_Gate = wire->dest_Gate;
                    simulation->src_Gate = wire->src_Gate;
                    wire->src_Gate = obj_Wires["Src_Gate"].toInt();
                    wire->src_NodeNr = obj_Wires["Src_Node"].toInt();
                    wire->dest_NodeNr = obj_Wires["Dest_Node"].toInt();

                    // Draw wire on scene
                    QLineF line;
                    line.setPoints(wire->source, wire->dest);
                    wire->setLine(line);
                    simulation->scene->addItem(wire);
                    simulation->list_Wires << wire;
                    simulation->nr_Wires++;

                    // Needs to connect each wire and update logic
                    for(int g = 0; g < simulation->list_Gates.size(); g++)
                    {
                        if(simulation->list_Gates.at(g)->gate_Nr == wire->src_Gate)
                        {
                            if(simulation->list_Gates.at(g)->gateType == 0)
                            {
                                simulation->list_Gates.at(g)->lowTimer->stop();
                                simulation->list_Gates.at(g)->highTimer->stop();
                                simulation->list_Gates.at(g)->LogicalOutput = 0;
                                simulation->list_Gates.at(g)->lowTimer->start(simulation->list_Gates.at(g)->lowTime);
                            }
                            else
                            {
                                wire->Logic_Wire = simulation->list_Gates.at(g)->LogicalOutput;
                            }
                            simulation->updateMWLogic(wire->Logic_Wire, wire->src_Gate);
                        }

                        // Need to updata gate input nodes as well!
                        for(int h = 0; h < simulation->list_Wires.size(); h++)
                        {
                            for(int k = 0; k < simulation->list_Gates.at(g)->list_Inputs.size(); k++)
                            {
                                if(simulation->list_Wires.at(h)->dest_Gate == simulation->list_Gates.at(g)->list_Inputs.at(k)->parent_Gate &&
                                        simulation->list_Wires.at(h)->dest_NodeNr == simulation->list_Gates.at(g)->list_Inputs.at(k)->posGate)
                                {
                                    simulation->list_Gates.at(g)->list_Inputs.at(k)->test = true;
                                    break;
                                }
                            }
                        }
                        simulation->updateMWLogic(wire->Logic_Wire, wire->src_Gate);
                    }
                }

                // Display Message when data was loaded successfully
                QMessageBox::information(this, tr("Message"), tr("Document Loaded Successfully"));
            }
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    // Get filename to svae file to
    // User must input .json at the end of their filename
    QString json_filter = "JSON (*.json)";
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "/",
                                                          tr("Any File (*);;%1").arg(json_filter),
                                                          &json_filter, QFileDialog::DontUseNativeDialog);

    if(fileName.isEmpty())
    {

    }
    else
    {
        // Populate Gate portion of JSON document
        QJsonArray arr_Gates;
        for(int i = 0; i < simulation->list_Gates.size(); i++)
        {
            // Each gate treated as own object
            QJsonObject obj_Gates;
            obj_Gates["Type"] = simulation->list_Gates.at(i)->gateType;
            obj_Gates["Nr"] = simulation->list_Gates.at(i)->gate_Nr;
            obj_Gates["x_Pos"] = simulation->list_Gates.at(i)->x();
            obj_Gates["y_Pos"] = simulation->list_Gates.at(i)->y();
            obj_Gates["Logic"] = simulation->list_Gates.at(i)->LogicalOutput;
            obj_Gates["nr_Inputs"] = simulation->list_Gates.at(i)->input_size;
            obj_Gates["low"] = simulation->list_Gates.at(i)->lowTime;
            obj_Gates["high"] = simulation->list_Gates.at(i)->highTime;

            // Add object to array of gate objects
            arr_Gates << obj_Gates;
        }

        // Populate Wire portion of JSON document
        QJsonArray arr_Wires;
        for(int i = 0; i < simulation->list_Wires.size(); i++)
        {
            // Each wire is represented by object
            QJsonObject obj_Wires;
            obj_Wires["Dest_X"] = simulation->list_Wires.at(i)->dest.x();
            obj_Wires["Dest_Y"] = simulation->list_Wires.at(i)->dest.y();
            obj_Wires["Src_X"] = simulation->list_Wires.at(i)->source.x();
            obj_Wires["Src_Y"] = simulation->list_Wires.at(i)->source.y();
            obj_Wires["Dest_Node"] = simulation->list_Wires.at(i)->dest_NodeNr;
            obj_Wires["Src_Node"] = simulation->list_Wires.at(i)->src_NodeNr;
            obj_Wires["Src_Gate"] = simulation->list_Wires.at(i)->src_Gate;
            obj_Wires["Dest_Gate"] = simulation->list_Wires.at(i)->dest_Gate;

            // Add object to array of wire objects
            arr_Wires << obj_Wires;
        }

        // Generate new QJsonObject that will house our 2 generated arrays of objects
        QJsonObject obj_Save;
        obj_Save.insert("Gates", arr_Gates);    // Add array of Gate Objects
        obj_Save.insert("Wires", arr_Wires);    // Add array of Wire Objects

        // Generate QJsonDocument from the newly created object housing the 2 arrays
        QJsonDocument json_save(obj_Save);
        QString json_string = json_save.toJson();

        // Output the QJsonDocument to a file and save to hardrive
        QFile output(fileName);
        if(output.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            output.write(json_string.toLocal8Bit());
            output.close();
            QMessageBox::information(this, tr("Message"), tr("Document Saved Successfully"));
        }
        else
        {
            // Error message displayed if something not right
            QMessageBox::critical(this, tr("Error"), output.errorString());
        }
    }
}

void MainWindow::clearScene()
{
    // Delete all placed gates and clear the QList<Gates *>
    for(int i = 0; i < simulation->list_Gates.size(); i++)
    {
        delete simulation->list_Gates.at(i);
    }
    simulation->list_Gates.clear();

    // Delete all places wires and clear the QList<Wires *>
    for(int i = 0; i < simulation->list_Wires.size(); i++)
    {
        delete simulation->list_Wires.at(i);
    }
    simulation->list_Wires.clear();

    // Reset the number of gates and wires counters
    simulation->nr_Gates = 0;
    simulation->nr_Wires = 0;
}
