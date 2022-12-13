#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QElapsedTimer>
#include <QFileDialog>
#include <QStandardItem>

#include "layers/addlayerdialog.h"
#include "layers/solidcolorlayer.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , saveOutputShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(SaveOutput()))
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

    //connect buttons to add and remove layers
    connect(ui->AddLayerButton, SIGNAL(clicked()), this, SLOT(OpenAddLayerDialogWindow()));
    connect(ui->DeleteLayerButton, SIGNAL(clicked()), this, SLOT(RemoveLayer()));
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


/*! \brief Opens a blocking file dialog to save the generated image
 *
 */
void MainWindow::SaveOutput()
{
    QString selectedFilter;
    QString path = QFileDialog::getSaveFileName(
        this,
        tr("Choose image export location"),
        nullptr,
        "PNG(*.png);;JPEG(*.jpg *.jpeg)",
        &selectedFilter
    );

    //for when the user does not put in an extension
    const QString defaultExtension = ".png";
    if(selectedFilter.isEmpty())
    {
        path.append(defaultExtension);
    }

    outputImage->save(path);
}

void MainWindow::OpenAddLayerDialogWindow()
{
    AddLayerDialog* dialog = new AddLayerDialog(this);
    connect(dialog, SIGNAL(accepted()), this, SLOT(AddLayer()));
    dialog->show();
}

void MainWindow::AddLayer()
{
    Layer* layer = new SolidColorLayer();

    ui->LayersView->AddLayer(layer);
}

void MainWindow::RemoveLayer()
{
    int index = ui->LayersView->currentIndex().row();
    ui->LayersView->DeleteLayer(index);
}
