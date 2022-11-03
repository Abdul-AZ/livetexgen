#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->WidthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(ResolutionChanged()));
    connect(ui->HeightSpinBox, SIGNAL(valueChanged(int)), this, SLOT(ResolutionChanged()));

    ResolutionChanged();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ResolutionChanged()
{           
    QSize size = {ui->WidthSpinBox->value(), ui->HeightSpinBox->value()};
    outputImage = std::make_unique<QImage>(size, OUTPUT_IMAGE_FORMAT);

    CalculateOutput();
}

void MainWindow::CalculateOutput()
{
    outputImage->fill(Qt::GlobalColor::blue);
    ui->OutputImage->setPixmap(QPixmap::fromImage(*outputImage));
}
