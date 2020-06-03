#include "inputbox.h"

#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QFormLayout>

InputBox::InputBox(QWidget *parent) : QDialog(parent)
{
    // Initialize Layout of InputBox
    QFormLayout *lytMain = new QFormLayout(this);

    // SpinBox to input time LOW
    QLabel *lblLow = new QLabel(QString("Time Low (ms):"), this);
    QSpinBox * sLow = new QSpinBox(this);
    sLow->setRange(10, 10000);
    sLow->setValue(500);            // Set Default Low value of 500ms
    lytMain->addRow(lblLow, sLow);
    this->val_field << sLow;

    QLabel *lblHigh = new QLabel(QString("Time High (ms):"), this);
    QSpinBox * sHigh = new QSpinBox(this);
    sHigh->setRange(10, 10000);
    sHigh->setValue(1000);          // Set Default High value of 1000ms
    lytMain->addRow(lblHigh, sHigh);
    this->val_field << sHigh;

    // Add Buttons to InputDialog
    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this );
    lytMain->addWidget(buttons);
    bool conn = connect(buttons, &QDialogButtonBox::accepted, this, &InputBox::accept);
    Q_ASSERT(conn);
    conn = connect(buttons, &QDialogButtonBox::rejected, this, &InputBox::reject);
    Q_ASSERT(conn);

    // Set Layout of custom InputBox
    this->setLayout(lytMain);
}

QList<int> InputBox::getValues(QWidget *parent, bool *ok)
{
    // Get values from QInputBox
    InputBox *dialog = new InputBox(parent);
    QList<int> list;

    int ex_d = dialog->exec();
    if(ok)
    {
        *ok = !!ex_d;
    }
    if(ex_d)
    {
        foreach (auto field, dialog->val_field)
        {
            list << field->value();
        }
    }

    // When values gathered, Dialog can be deleted.
    dialog->deleteLater();
    return list;
}
