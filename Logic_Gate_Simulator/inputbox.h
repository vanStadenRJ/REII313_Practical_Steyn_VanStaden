#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <QObject>
#include <QDialog>
#include <QSpinBox>

class QLineEdit;
class QLabel;

class InputBox : public QDialog
{
    Q_OBJECT
public:
    // Constructors
    InputBox(QWidget *parent = nullptr);

    // Public Methods
    static QList<int> getValues(QWidget *parent, bool *ok = nullptr);

private:
    // Private Attributes
    QList<QSpinBox*> val_field;                                                // QList of fields; 1 for high time; 1 for low time
};

#endif // INPUTBOX_H
