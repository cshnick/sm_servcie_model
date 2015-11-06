#include "skyproxymodel.h"
#include "skymodel.h"
#include <QtCore>
#include <QTextDocument>
#include <QFontMetrics>
#include <QRect>
#include <QtGui>

#include "../../include/class_ids.h"
#include "plugin/loader.h"
#include "common/string.h"
#include "common/string_helper.h"
#include "common/filewatcher.h"


std::string SkyProxyModel::s_dbPath = "/home/ilia/.Skype/sc.ryabokon.ilia/main.db";
BOSS_DECLARE_RUNTIME_EXCEPTION(HistoryUi);

using namespace Boss;
using namespace skype_sc;

struct UIObserver
		:public Boss::CoClass<skype_sc::service::id::DBObserver, IDBObserver> {

	Boss::RetCode BOSS_CALL ReactOnDbChanged(IDBEvent *event) override {
		ref_ptr<IMessage> mesg;
		auto ret = event->Message(mesg.GetPPtr());
		ref_ptr<IString> body;
		if (ret == Status::Ok) ret = mesg->Body(body.GetPPtr());
		int id;
		ret = mesg->Id(&id);
		std::cout << id << " - " << StringHelper(body).GetString<IString::AnsiString>() << std::endl;

		return Boss::Status::Ok;
	}
};

class SkyModelPrivate {
public:
	friend class SkyProxyModel;
	SkyModelPrivate(SkyProxyModel *p_q) : q(p_q) {
		m_pluginLoader.reset(new Loader("sc_reg.xml", MAKE_MODULE_PATH MAKE_MODULE_NAME("service_registry"),
				                                      MAKE_MODULE_PATH MAKE_MODULE_NAME("class_factory")));
		try {
			m_dbctrl = CreateObject<IDBController>(skype_sc::service::id::DBControler);

			qi_ptr<IDBWatcher> watcher(m_dbctrl);
			m_observer = Base<UIObserver>::Create().Get();
			watcher->AddObserver(m_observer.Get());
			watcher->SetWatchFile(Base<String>::Create(SkyProxyModel::s_dbPath).Get());
			qi_ptr<IService> serv(m_dbctrl);
			serv->Start();

		} catch (const std::exception &e) {
			qDebug() << e.what();
		}
	}
	~SkyModelPrivate() {
	}

private:
	SkyProxyModel *q;
	int m_progress = 0;
	ref_ptr<IDBController> m_dbctrl;
	ref_ptr<UIObserver> m_observer;
	std::unique_ptr<sm::filewatcher> m_fw;
	std::unique_ptr<Loader> m_pluginLoader;
};


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
    const QModelIndex ind = sourceModel()->index(source_row, 0, source_parent);

    QString name_data = ind.data(Qt::UserRole).toString();
    QString author = ind.data(Qt::UserRole + 3).toString();

    bool accept = name_data.contains(filterRegExp()) ||
            author.contains(filterRegExp());
    return accept;
}

bool SkyProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const {
    QString name_data_left = left.data(Qt::UserRole + 1).toString();
    QString name_data_right = right.data(Qt::UserRole + 1).toString();

    return name_data_left < name_data_right;
}

int SkyProxyModel::loadProgress() const {return d->m_progress;}
void SkyProxyModel::setLoadProgress(int val) {d->m_progress = val;}

//INVOKABLE
void SkyProxyModel::stringChanged(const QString &p_str) {
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
        model_impl()->append(m);
    }
}
void SkyProxyModel::loadSkypeTest() {
}
//INVOKABLE
