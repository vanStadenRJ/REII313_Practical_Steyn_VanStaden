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
    explicit InputBox(QWidget *parent = nullptr);
    static QList<int> getStrings(QWidget *parent, bool *ok = nullptr);

private:
    QList<QSpinBox*> fields;
};

#endif // INPUTBOX_H
