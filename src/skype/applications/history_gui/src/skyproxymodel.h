#ifndef SKYPROXYMODEL_H
#define SKYPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QThread>
#include <QMutex>
#include <atomic>
#include <memory>

#include "../../include/ifaces.h"
#include "core/ref_obj_ptr.h"
#include "core/co_class.h"

class SkyModel;

template <class T> class VPtr
{
public:
    static T* asPtr(QVariant v) {
    	return  (T *) v.value<void *>();
    }

    static QVariant asQVariant(T* ptr) {
    	return qVariantFromValue((void *) ptr);
    }
};

class SkyModelPrivate;
class SkyProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(int loadProgress READ loadProgress WRITE setLoadProgress NOTIFY loadProgressChanged)

public:
    explicit SkyProxyModel(QObject *parent = 0);
    virtual ~SkyProxyModel();

    static std::string s_dbPath;

    int loadProgress() const;
    void setLoadProgress(int val);
    Q_SIGNAL void loadProgressChanged(int progress);

    Q_INVOKABLE void stringChanged(const QString &p_str);
    Q_INVOKABLE QVariant get(int p_index, int role);
    Q_INVOKABLE QString get_name(int p_index);
    Q_INVOKABLE void refresh();
    Q_INVOKABLE void loadTest();
    Q_INVOKABLE void loadSkypeTest();

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;

private:
    void prependNewMesages();

private:
    std::unique_ptr<SkyModelPrivate> d;

    SkyModel *model_impl() {
        return reinterpret_cast<SkyModel*> (this->sourceModel());
    }
    SkyModel *model_impl() const {
        return reinterpret_cast<SkyModel*> (this->sourceModel());
    }
};

#endif // SKYPROXYMODEL_H
