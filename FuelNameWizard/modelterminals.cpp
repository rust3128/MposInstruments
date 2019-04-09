#include "modelterminals.h"

ModelTerminals::ModelTerminals(const QVector<Terminals> vek)
{
    term = vek;
}


int ModelTerminals::rowCount(const QModelIndex &parent) const
{
    return term.size();
}

int ModelTerminals::columnCount(const QModelIndex &parent) const
{
    Terminals *terminal = new Terminals();
    return terminal->colParam();
}

QVariant ModelTerminals::data(const QModelIndex &index, int role) const
{
    if ( !index.isValid() ) { return QVariant(); }
    Terminals t = term[index.row()];
    switch (role) {
    case Qt::DisplayRole:
        switch (index.column()) {
        case 0: return t.isCheked();
        case 1: return t.terminal();
        case 2: return t.name();
        case 3: return t.serverName();
        case 4: return t.database();
        case 5: return t.password();
        default: break;
        }
      break;
    case Qt::CheckStateRole:
        if(index.column() == 0)
            return (t.isCheked() != 0) ? Qt::Checked : Qt::Unchecked;
    break;

    default:
        break;
    }

    return QVariant();
}

QVariant ModelTerminals::headerData(int section, Qt::Orientation orientation, int role) const
{
    //Cоздаем заголовки столбцов модели
    if( role != Qt::DisplayRole ) {
        return QVariant();
    }

    if( orientation == Qt::Vertical ) {
        return section;
    }
    switch( section ) {
    case 0:
        return tr( "" );
    case 1:
        return tr( "АЗС" );
    case 2:
        return tr( "Адрес" );
    case 3:
        return tr( "Сервер" );
    case 4:
        return tr( "Файл БД" );
    case 5:
        return tr( "Пароль" );
    }

    return QVariant();
}


Qt::ItemFlags ModelTerminals::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if (index.column() == 0)
    {
        flags |= Qt::ItemIsUserCheckable;
        flags |= Qt::ItemIsSelectable;
    }
    else
    {
        flags |= Qt::ItemIsEditable;
        flags |= Qt::ItemIsSelectable;
    }
    return flags;

}

bool ModelTerminals::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Terminals t = term[index.row()];
    if(!index.isValid())
        return false;
    if(role == Qt::CheckStateRole)
    {
        if(value.toInt() == Qt::Checked)
        {
            t.setIsCheked(1);
            return true;
        }
        else
        {
            t.setIsCheked(0);
            return true;
        }
    }
    return  false;
}
