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
struct UIObserver
		:public Boss::SimpleCoClass<skype_sc::IDBObserver> {

	UIObserver(SkyModelPrivate *q);
	Boss::RetCode BOSS_CALL ReactOnDbChanged(skype_sc::IDBEvent *event) override;

private:
	SkyModelPrivate *q;
};

class ModelState : public QObject {
    Q_OBJECT

public:
    enum en {
        STATE_UNDEFINED,
        STATE_EDIT,
        STATE_RECENT_TREE
    };
    Q_ENUMS(en)
};

class SkyProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_ENUMS(en_state)
    Q_PROPERTY(int loadProgress READ loadProgress WRITE setLoadProgress NOTIFY loadProgressChanged)
    Q_PROPERTY(int state READ loadProgress WRITE setState NOTIFY stateChanged)

public:
    explicit SkyProxyModel(QObject *parent = 0);
    virtual ~SkyProxyModel();

    static std::string s_dbPath;

    int loadProgress() const;
    void setLoadProgress(int val);
    int state() const;
    void setState(int val);
    void emitStateChanged(int new_val) {Q_EMIT stateChanged(new_val);}
    void setQmlObject(QObject *o);

    Q_SIGNAL void loadProgressChanged(int progress);
    Q_SIGNAL void loadFinished();
    Q_SIGNAL void stateChanged(int);

    Q_INVOKABLE void stringChanged(const QString &p_str);
    Q_INVOKABLE QVariant get(int p_index, int role);
    Q_INVOKABLE QString get_name(int p_index);
    Q_INVOKABLE void refresh();
    Q_INVOKABLE void loadTest();
    Q_INVOKABLE void loadSkypeTest();
    Q_INVOKABLE void loadRecent();

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;

private:
    void prependNewMesages();

private:
    std::unique_ptr<SkyModelPrivate> d;
};

#endif // SKYPROXYMODEL_H
