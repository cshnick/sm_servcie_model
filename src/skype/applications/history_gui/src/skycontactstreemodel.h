#ifndef SKYCONTACTSTREEMODEL_H
#define SKYCONTACTSTREEMODEL_H

#include <QStandardItemModel>
#include <QStandardItem>

class SkyContactsItem : public QStandardItem {
public:
    SkyContactsItem(const QString &text, const QString &image);
};


class SkyContactsTreeModel : public QStandardItemModel
{
    Q_OBJECT
public:
    SkyContactsTreeModel(QObject *parent = 0);

    Q_INVOKABLE QString icon_path(const QModelIndex &ind);
    Q_INVOKABLE void dosmth() {}
};

#endif // SKYCONTACTSTREEMODEL_H
