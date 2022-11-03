#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

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
    void ResolutionChanged();
    void CalculateOutput();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<QImage> outputImage;
};
#endif // MAINWINDOW_H
