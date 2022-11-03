#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QElapsedTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connect the resolution input boxes to the ResolutionChanged event/slot
    connect(ui->WidthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(ResolutionChanged()));
    connect(ui->HeightSpinBox, SIGNAL(valueChanged(int)), this, SLOT(ResolutionChanged()));

    //call ResolutionChanged at the start so that the output image is initilized at startup
    ResolutionChanged();
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*! \brief Changes the resolution of the output image(by creating a new one) and calls CalculateOutput()
 *
 */
void MainWindow::ResolutionChanged()
{           
    QSize size = {ui->WidthSpinBox->value(), ui->HeightSpinBox->value()};
    outputImage = std::make_unique<QImage>(size, OUTPUT_IMAGE_FORMAT);

    CalculateOutput();
}

/*! \brief Does all the calculations and produces the output image
 *
 */
void MainWindow::CalculateOutput()
{
    QElapsedTimer timer;
    timer.start();

    outputImage->fill(Qt::GlobalColor::blue);
    ui->OutputImage->setPixmap(QPixmap::fromImage(*outputImage));


    int64_t calculationTime = timer.elapsed();
    ui->StatusBar->showMessage(QString("Finished Calculating Output. Time taken %1 ms").arg(calculationTime), OUTPUT_STATUS_BAR_NORMAL_MESSAGE_TIMEOUT_MS);
}
