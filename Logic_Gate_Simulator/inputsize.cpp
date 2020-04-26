#include "inputsize.h"
#include "Gate.h"
#include "ui_inputsize.h"
#include <QDebug>

InputSize::InputSize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputSize)
{
    ui->setupUi(this);
}

InputSize::~InputSize()
{
    delete ui;
}

void InputSize::on_pushButton_clicked()
{
    setSize();
}

void InputSize::setSize()
{
    size = ui->spinBox->value();
}
