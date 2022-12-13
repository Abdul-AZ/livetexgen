#ifndef LAYERVIEW_H
#define LAYERVIEW_H

#include <QListView>
#include <QObject>

#include "layer.h"

class LayerView : public QListView
{
    Q_OBJECT
public:
    LayerView(QObject *parent = 0);

    void AddLayer(Layer* layer);
    void DeleteLayer(int index);


private:
    QVector<Layer*> m_Layers;
};

#endif // LAYERVIEW_H
