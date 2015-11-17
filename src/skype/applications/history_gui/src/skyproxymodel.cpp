#include "skyproxymodel.h"
#include "skymodel.h"
#include <QtCore>
#include <QTextDocument>
#include <QFontMetrics>
#include <QRect>
#include <QtGui>
#include <QTextDocument>

#include "../../include/class_ids.h"
#include "plugin/loader.h"
#include "common/string.h"
#include "common/string_helper.h"
#include "common/filewatcher.h"
#include "common/enum_helper.h"

#include "../../include/skype_helpers.h"


std::string SkyProxyModel::s_dbPath = "/home/ilia/.Skype/luxa_ryabic/main.db";
BOSS_DECLARE_RUNTIME_EXCEPTION(HistoryUi)

using namespace Boss;
using namespace skype_sc;

class SkyModelPrivate {
public:
	friend class SkyProxyModel;
	SkyModelPrivate(SkyProxyModel *p_q) : q(p_q) {
		m_pluginLoader.reset(new Loader("sc_reg.xml", MAKE_MODULE_PATH MAKE_MODULE_NAME("service_registry"),
				                                      MAKE_MODULE_PATH MAKE_MODULE_NAME("class_factory")));
		try {
			m_dbctrl = CreateObject<IDBController>(skype_sc::service::id::DBControler);

			qi_ptr<IDBWatcher> watcher(m_dbctrl);
			m_observer = Base<UIObserver>::Create(this).Get();
			watcher->AddObserver(m_observer.Get());
			watcher->SetWatchFile(Base<String>::Create(SkyProxyModel::s_dbPath).Get());
			qi_ptr<IService> serv(m_dbctrl);
            serv->Start();

		} catch (const std::exception &e) {
			qDebug() << e.what();
		}
	}
	Boss::RetCode ReactOnDbChanged(skype_sc::IDBEvent *event) {
		Boss::ref_ptr<skype_sc::IMessage> mesg;
		auto ret = event->Message(mesg.GetPPtr());
        assert(!ret);
        QVariantMap m(convert(Message_hlpr(mesg)));
        if (model_impl()) {
            model_impl()->insert(0, m);
        }

		return Boss::Status::Ok;
	}

    void loadRecent() {
        qi_ptr<IEnum> recent;
        m_dbctrl->Recent(recent.GetPPtr());
        EnumHelper<IMessage> recent_hlpr(recent);
        for (auto iter = recent_hlpr.First(); iter.Get(); iter = recent_hlpr.Next()) {
            Message_hlpr mh(iter);
            QVariantMap m(convert(mh));
            if (model_impl()) {
                model_impl()->append(m);
            }
        }
    }

    QVariantMap convert(const Message_hlpr &h) {
        int width = 1115;
        QString body = QString::fromStdString(h.Body());
        if (qml_object) {
            width = qml_object->property("width").toInt();
        }
        QTextDocument doc(body);
        doc.setTextWidth(width);
        int height = doc.size().height();
        QVariantMap m;
        m["Name"] = body;
        m["Height"] = height + 30;
        m["Author"] = QString::fromStdString(h.Author());
        m["Timestamp"] = QDateTime::fromTime_t(h.SkypeTimestamp());
        m["Chatname"] = QString::fromStdString(h.Conversation().Name());

        return m;
    }

	~SkyModelPrivate() {
	}

    SkyModel *model_impl() {
        return reinterpret_cast<SkyModel*> (q->sourceModel());
    }
    SkyModel *model_impl() const {
        return reinterpret_cast<SkyModel*> (q->sourceModel());
    }

private:
	SkyProxyModel *q;
    int m_progress = 0, m_state = 0;

	ref_ptr<IDBController> m_dbctrl;
	ref_ptr<UIObserver> m_observer;
	std::unique_ptr<sm::filewatcher> m_fw;
	std::unique_ptr<Loader> m_pluginLoader = nullptr;
    QObject *qml_object = nullptr;
};

UIObserver::UIObserver(SkyModelPrivate *p_q)
	: q(p_q) {
}
Boss::RetCode UIObserver::ReactOnDbChanged(IDBEvent *event) {
	return q->ReactOnDbChanged(event);
}

QVariantMap fromMessage() {
    return QVariantMap();
}

int calcPercent(int cnt, int i) {
    int offset = 9;
    double status_move = (cnt - i) << offset;
    double percentage = status_move / cnt;
    int status_res = static_cast<int>(percentage * 100) >> offset;

    return status_res;
}

SkyProxyModel::SkyProxyModel(QObject *parent)
    :QSortFilterProxyModel(parent) ,
	 d(new SkyModelPrivate(this))
{
	setSourceModel(new SkyModel);
//    sort(0);
    setFilterCaseSensitivity(Qt::CaseInsensitive);
}

SkyProxyModel::~SkyProxyModel() {
}

bool SkyProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    Q_UNUSED(source_row)
    Q_UNUSED(source_parent)

    bool accept = false;
    switch (d->m_state) {
    case ModelState::STATE_EDIT : {
        const QModelIndex ind = sourceModel()->index(source_row, 0, source_parent);

        QString name_data = ind.data(Qt::UserRole).toString();
        QString author = ind.data(Qt::UserRole + 3).toString();

        accept = name_data.contains(filterRegExp()) ||
                author.contains(filterRegExp());
    } break;
    case ModelState::STATE_RECENT_TREE : {

    } break;
    default:
        accept = false;
    }

    return accept;
}

bool SkyProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const {
    QString name_data_left = left.data(Qt::UserRole + 1).toString();
    QString name_data_right = right.data(Qt::UserRole + 1).toString();

    return name_data_left < name_data_right;
}

int SkyProxyModel::loadProgress() const {return d->m_progress;}
void SkyProxyModel::setLoadProgress(int val) {d->m_progress = val;}
int SkyProxyModel::state() const {return d->m_state;}
void SkyProxyModel::setState(int val) {
    if (val != d->m_state) {
        d->m_state = val;
        emitStateChanged(val);
    }
}

void SkyProxyModel::setQmlObject(QObject *o) {
    qDebug() << "New qml object" << o;
    d->qml_object = o;
}

//INVOKABLE
void SkyProxyModel::stringChanged(const QString &p_str) {
    setState(ModelState::STATE_EDIT);
    setFilterFixedString(p_str);
}
QVariant SkyProxyModel::get(int p_index, int role) {
    return sourceModel()->data(mapToSource(index(p_index, 0)), role);
}
QString SkyProxyModel::get_name(int p_index) {
    return sourceModel()->data(mapToSource(index(p_index, 0)), Qt::UserRole + 1).toString();
}
void SkyProxyModel::refresh() {
}
void SkyProxyModel::loadTest() {
    QStringList l = QString("Psycho,Lever,Mace,Green").split(",");
    for (int i = 0; i < 4; i++) {
        QVariantMap m;
        m["Name"] = l.at(i);
        m["Height"] = 50;
        m["Author"] = "Luxa Ryabic";
        m["Timestamp"] = QDateTime::currentDateTime();
        d->model_impl()->append(m);
    }
}
void SkyProxyModel::loadSkypeTest() {
}
void SkyProxyModel::loadRecent() {
    d->loadRecent();
}

//INVOKABLE
