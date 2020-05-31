#include "inputbox.h"

#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QFormLayout>


InputBox::InputBox(QWidget *parent) : QDialog(parent)
{
    QFormLayout *lytMain = new QFormLayout(this);

    QLabel *lblLow = new QLabel(QString("Time Low (ms):"), this);
    QSpinBox * sLow = new QSpinBox(this);
    sLow->setRange(100, 10000);
    lytMain->addRow(lblLow, sLow);
    fields << sLow;

    QLabel *lblHigh = new QLabel(QString("Time High (ms):"), this);
    QSpinBox * sHigh = new QSpinBox(this);
    sHigh->setRange(100, 10000);
    lytMain->addRow(lblHigh, sHigh);
    fields << sHigh;

    QDialogButtonBox *buttonBox = new QDialogButtonBox
            ( QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
              Qt::Horizontal, this );
    lytMain->addWidget(buttonBox);

    bool conn = connect(buttonBox, &QDialogButtonBox::accepted,
                   this, &InputBox::accept);
    Q_ASSERT(conn);
    conn = connect(buttonBox, &QDialogButtonBox::rejected,
                   this, &InputBox::reject);
    Q_ASSERT(conn);

    setLayout(lytMain);


}

QList<int> InputBox::getStrings(QWidget *parent, bool *ok)
{
    InputBox *dialog = new InputBox(parent);

    QList<int> list;

    const int ret = dialog->exec();
    if (ok)
        *ok = !!ret;

    if (ret) {
        foreach (auto field, dialog->fields) {
            list << field->value();
        }
    }

    dialog->deleteLater();

    return list;
}
