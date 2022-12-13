#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include <QShortcut>
#include <QList>
//#include "layers/layer.h"

#define OUTPUT_IMAGE_FORMAT (QImage::Format_ARGB32)

#define OUTPUT_STATUS_BAR_NORMAL_MESSAGE_TIMEOUT_MS (1000)

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void CapitalizeHexInput();
    void ResolutionChanged();
    void CalculateOutput();
    void SaveOutput();
    void OpenAddLayerDialogWindow();
    void AddLayer();
    void RemoveLayer();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<QImage> outputImage;
    QShortcut saveOutputShortcut;
    //std::vector<std::unique_ptr<Layer>> layers;
};
#endif // MAINWINDOW_H
