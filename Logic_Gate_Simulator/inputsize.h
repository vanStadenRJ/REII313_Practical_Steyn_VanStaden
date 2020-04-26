#ifndef INPUTSIZE_H
#define INPUTSIZE_H

#include <QDialog>

namespace Ui {
class InputSize;
}

class InputSize : public QDialog
{
    Q_OBJECT

public:
    explicit InputSize(QWidget *parent = nullptr);
    ~InputSize();
    unsigned int size = 2;

private slots:
    void on_pushButton_clicked();

private:
    Ui::InputSize *ui;    
    void setSize();
};

#endif // INPUTSIZE_H
