#ifndef ADDLAYERDIALOG_H
#define ADDLAYERDIALOG_H

#include <QDialog>

namespace Ui {
class AddLayerDialog;
}

class AddLayerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddLayerDialog(QWidget *parent = nullptr);
    ~AddLayerDialog();

private:
    Ui::AddLayerDialog *ui;
};

#endif // ADDLAYERDIALOG_H
