#include "layerview.h"

#include <QStringListModel>

LayerView::LayerView(QObject* parent)
{
    setModel(new QStringListModel());

    connect(this,SIGNAL(clicked(const QModelIndex&)), this, SLOT(TrySelectingLayerByIndex(const QModelIndex&)));
}

void LayerView::AddLayer(Layer* layer)
{
    m_Layers.append(layer);

    model()->insertRow(model()->rowCount());
    QModelIndex index = model()->index(model()->rowCount()-1, 0);
    model()->setData(index, layer->Name);
}

void LayerView::DeleteLayer(int index)
{
    if((index < 0) || (index >= m_Layers.size()))
        return;

    delete m_Layers[index];
    m_Layers.removeAt(index);
    model()->removeRow(index);
}

void LayerView::TrySelectingLayerByIndex(const QModelIndex& index)
{
    if((index.row() < 0) || (index.row() >= m_Layers.size()))
        return;

    emit LayerSelected(m_Layers[index.row()]);
}
