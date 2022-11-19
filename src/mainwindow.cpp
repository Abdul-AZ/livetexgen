#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QElapsedTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRegExp regex ("^[0-9A-Fa-f]{6}$");
    QRegExpValidator *hexValidator = new QRegExpValidator(regex, this);
    ui->BackgroundColorHex->setValidator(hexValidator);

    //connect the resolution input boxes to the ResolutionChanged event/slot
    connect(ui->WidthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(ResolutionChanged()));
    connect(ui->HeightSpinBox, SIGNAL(valueChanged(int)), this, SLOT(ResolutionChanged()));

    //connect the background color input box to calculate CalculateOutput signal
    connect(ui->BackgroundColorHex, SIGNAL(textChanged(QString)), this, SLOT(CalculateOutput()));

    connect(ui->BackgroundColorHex, SIGNAL(textChanged(QString)), this, SLOT(CapitalizeHexInput()));

    //call ResolutionChanged at the start so that the output image is initilized at startup
    ResolutionChanged();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::CapitalizeHexInput()
{
    ui->BackgroundColorHex->setText(ui->BackgroundColorHex->text().toUpper());
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


    QColor color = QColor::fromRgb(0,0,0);

    //try to get color from the input box
    static QRegularExpression hexMatcher("^[0-9A-Fa-f]{6}$",
                                  QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match = hexMatcher.match(ui->BackgroundColorHex->text());
    if (match.hasMatch())
    {
        bool conversionOk = false;
        int value = ui->BackgroundColorHex->text().toInt(&conversionOk, 16);

        if(conversionOk)
        {
            color = QColor::fromRgb(value);
        }
    }

    outputImage->fill(color);
    ui->OutputImage->setPixmap(QPixmap::fromImage(*outputImage));

    int64_t calculationTime = timer.elapsed();
    ui->StatusBar->showMessage(QString("Finished Calculating Output. Time taken %1 ms").arg(calculationTime), OUTPUT_STATUS_BAR_NORMAL_MESSAGE_TIMEOUT_MS);
}
