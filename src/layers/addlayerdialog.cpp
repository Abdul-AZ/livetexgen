#include "addlayerdialog.h"
#include "ui_addlayerdialog.h"

AddLayerDialog::AddLayerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLayerDialog)
{
    ui->setupUi(this);
}

AddLayerDialog::~AddLayerDialog()
{
    delete ui;
}
