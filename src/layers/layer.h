#ifndef LAYER_H
#define LAYER_H

#include <QPixmap>

class Layer
{
public:
    Layer();
    virtual ~Layer() {};

public:
    virtual QPixmap GetLayerOuput(int width, int height) = 0;

public:
    QString Name;
};

#endif // LAYER_H
