#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();                  // Trigger when user wants to start a new simulation
    void on_actionOpen_triggered();                 // Trigger when user wants to open a previously saved schematic
    void on_actionSave_triggered();                 // Trigger when user wants to save a schematic

private:
    Ui::MainWindow *ui;

    void clearScene();                              // Function to remove and delete all placed gates and wires
};

#endif // MAINWINDOW_H
