#ifndef MODELTERMINALS_H
#define MODELTERMINALS_H

#include "FuelNameWizard/terminals.h"

#include <QObject>
#include <QAbstractTableModel>

class ModelTerminals : public QAbstractTableModel
{
    Q_OBJECT
    QVector<Terminals> term;
public:
    ModelTerminals(const QVector<Terminals> vek);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    // QAbstractItemModel interface
public:
    Qt::ItemFlags flags(const QModelIndex &index) const;

    // QAbstractItemModel interface
public:
    bool setData(const QModelIndex &index, const QVariant &value, int role);
};

#endif // MODELTERMINALS_H
