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
#include "skycontactstreemodel.h"


std::string SkyProxyModel::s_dbPath = "/home/ilia/.Skype/luxa_ryabic/main.db";
BOSS_DECLARE_RUNTIME_EXCEPTION(HistoryUi)

using namespace Boss;
using namespace skype_sc;

class SkyModelPrivate {
public:
	friend class SkyProxyModel;
    SkyModelPrivate(SkyProxyModel *p_q, SkyContactsTreeModel *contacts) : q(p_q), m_contacts(contacts) {
		m_pluginLoader.reset(new Loader("sc_reg.xml", MAKE_MODULE_PATH MAKE_MODULE_NAME("service_registry"),
				                                      MAKE_MODULE_PATH MAKE_MODULE_NAME("class_factory")));
		try {
			m_dbctrl = CreateObject<IDBController>(skype_sc::service::id::DBControler);
            m_settings = CreateObject<ISettings>(skype_sc::service::id::Settings);
            Settings_hlpr s_h(m_settings);
            auto accs = s_h.Accounts();
            auto acc_default = accs.at(s_h.DefaultAccount());

            qi_ptr<IDBWatcher> watcher(m_dbctrl);
			m_observer = Base<UIObserver>::Create(this).Get();
			watcher->AddObserver(m_observer.Get());
            watcher->SetWatchFile(Base<String>::Create(acc_default.FilePath()).Get());
            m_dbctrl->SetDBPath(Base<String>::Create(acc_default.HistoryDBPath()).Get());
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
        Message_hlpr mh(mesg);
        QVariantMap m(convert(mh));
        if (model_impl()) {
            model_impl()->insert(0, m);
        }
        m_contacts->processMessage(mh);

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
            m_contacts->processMessage(mh);
        }
    }

    void loadAsync() {
        m_dbctrl->GetMessagesAsync([this](IMessage *message, int progress) {
            qi_ptr<IMessage> pm(message);
            Message_hlpr mh(pm);
            QVariantMap m(convert(mh));
            if (model_impl()) {
                model_impl()->append(m);
            }
            m_contacts->processMessage(mh);
            m_progress = progress;
            q->emitLoadProgressChanged(progress);
        } , [this] {
        	q->emitLoadFinished();
        });
    }

    void restart(const QJsonObject &o) {
        model_impl()->clear();
        QString skype_path = o.value(QString::fromStdString(IAccount::TFilePath)).toString();
        QString history_path = o.value(QString::fromStdString(IAccount::THistoryDBPath)).toString();
        qi_ptr<IService>(m_dbctrl)->Restart(Base<String>::Create(skype_path.toLocal8Bit().data()).Get(),
                        Base<String>::Create(history_path.toLocal8Bit().data()).Get());
        loadRecent();
    }

    QJsonObject settings() {
        Settings_hlpr shlpr(m_settings);
        QString json_str = QString::fromStdString(shlpr.AsJsonString());
        QJsonDocument jdoc = QJsonDocument::fromJson(json_str.toLocal8Bit());
        QJsonObject o = jdoc.object();
        return o;
    }
    void updateSettings(const QJsonObject &o) {
        Settings_hlpr shlpr(m_settings);
        QJsonDocument doc(o);
        shlpr.UpdateFromJson(doc.toJson().data());
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
        m["Chatid"] = h.Conversation().SkypeId();

        return m;
    }

	~SkyModelPrivate() {
		qDebug() << "~SkyModelPrivate";
	}

    SkyModel *model_impl() {
        return reinterpret_cast<SkyModel*> (q->sourceModel());
    }
    SkyModel *model_impl() const {
        return reinterpret_cast<SkyModel*> (q->sourceModel());
    }

private:
	SkyProxyModel *q;
    SkyContactsTreeModel *m_contacts;
    int m_progress = 0, m_state = 0;
    std::unique_ptr<Loader> m_pluginLoader = nullptr;

    ref_ptr<IDBController> m_dbctrl;
    ref_ptr<ISettings> m_settings;
    ref_ptr<UIObserver> m_observer;

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

SkyProxyModel::SkyProxyModel(SkyContactsTreeModel *contacts, QObject *parent)
    :QSortFilterProxyModel(parent) ,
     d(new SkyModelPrivate(this, contacts))
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
    case ModelState::STATE_CONTACTS_TREE : {
        const QModelIndex ind = sourceModel()->index(source_row, 0, source_parent);
        QString author = ind.data(Qt::UserRole + 3).toString();
        accept = author.contains(filterRegExp());
    } break;
    case ModelState::STATE_RECENT_TREE : {
        const QModelIndex ind = sourceModel()->index(source_row, 0, source_parent);
        QString chatid = ind.data(Qt::UserRole + 5).toString();
        accept = chatid.contains(filterRegExp());
//        qDebug() << "Filter regexp, chatid" << filterRegExp() << chatid;
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
void SkyProxyModel::contactTreeItemSelected(const QModelIndex &ind) {
    bool contacts = ind.parent().data() == "Contacts";
    bool recent = ind.parent().parent().data() == "Recent";

    if (contacts) {
        setState(ModelState::STATE_CONTACTS_TREE);
        setFilterFixedString(ind.data(SkyContactsTreeModel::SkypeNameRole).toString());
    } else if (recent) {
        setState(ModelState::STATE_RECENT_TREE);
        setFilterFixedString(ind.data(SkyContactsTreeModel::ConversationIdRole).toString());
    }
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
void SkyProxyModel::loadAsync() {
    d->loadAsync();
}

void SkyProxyModel::restart(const QJsonObject &o) {
    d->restart(o);
}

QJsonObject SkyProxyModel::settings() {
    return d->settings();
}

void SkyProxyModel::updateSettings(const QJsonObject &o) {
    d->updateSettings(o);
}

//INVOKABLE
