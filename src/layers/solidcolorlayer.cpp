#include "solidcolorlayer.h"

SolidColorLayer::SolidColorLayer()
{

}

QPixmap SolidColorLayer::GetLayerOuput(int width, int height)
{
    QPixmap pixels(width, height);

    pixels.fill(QColor("red"));

    return pixels;
}
