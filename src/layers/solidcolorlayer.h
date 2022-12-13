#ifndef SOLIDCOLORLAYER_H
#define SOLIDCOLORLAYER_H

#include "layer.h"

class SolidColorLayer : public Layer
{
public:
    SolidColorLayer();

    virtual QPixmap GetLayerOuput(int width, int height) override;
};

#endif // SOLIDCOLORLAYER_H
