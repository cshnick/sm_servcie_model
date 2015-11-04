#include "skyproxymodel.h"
#include "skymodel.h"
#include <QtCore>
#include <QTextDocument>
#include <QFontMetrics>
#include <QRect>
#include <QtGui>

QString SkyProxyModel::s_dbPath = "/home/ilia/.Skype/sc.ryabokon.ilia/main.db";

SkyDataLoader::SkyDataLoader()
{
}

void SkyDataLoader::loadFromScratch(const QVariantMap &msg){
    allMessages(msg);
}

typedef QHash<QString, QString> string_hash;
QVariantMap fromMessage() {
//    QString body = QString::fromStdString(message.body_xml);
//    QTextDocument doc(body);
//    QFont fnt = doc.defaultFont();
//    fnt.setPointSize(10);
//    doc.setDefaultFont(fnt);
//    doc.adjustSize();
//    QFontMetrics metrx(fnt);
//    int ofs = metrx.boundingRect("H").height();

    QVariantMap m;
//    m["Name"] = doc.toPlainText();
//    m["Height"] = doc.size().height() + ofs;
//    m["Timestamp"] = QDateTime::fromTime_t(message.timestamp).toString();
//    m["Author"] = contacts_hash.value(QString::fromStdString(message.author));
//    m["Chatname"] = chats_hash.value(QString::fromStdString(message.chatname));

    return m;
}

int calcPercent(int cnt, int i) {
    int offset = 9;
    double status_move = (cnt - i) << offset;
    double percentage = status_move / cnt;
    int status_res = static_cast<int>(percentage * 100) >> offset;

    return status_res;
}

void SkyDataLoader::alternativeLoad() {
    qDebug() << "Calc chats, start";
    QVariantMap m;
    emit send_finished(m);
}

void SkyDataLoader::allMessages(const QVariantMap &) {
}

SkyProxyModel::SkyProxyModel(QObject *parent)
    :QSortFilterProxyModel(parent)
{
    setSourceModel(new SkyModel);
//    sort(0);
    setFilterCaseSensitivity(Qt::CaseInsensitive);

    SkyDataLoader *skLoader = new SkyDataLoader();
    skLoader->moveToThread(&m_worker);
    connect(&m_worker, &QThread::finished, skLoader, &QObject::deleteLater);
    connect(this,  &SkyProxyModel::instigateLoad, skLoader, &SkyDataLoader::loadFromScratch);
    connect(skLoader, &SkyDataLoader::send_row, this, &SkyProxyModel::handleLoadedRow);
    connect(skLoader, &SkyDataLoader::prepend_msg, this, &SkyProxyModel::handlePrependMsg);
    connect(skLoader, &SkyDataLoader::send_finished, this, &SkyProxyModel::loadFinished);
    m_worker.start();
}
SkyProxyModel::~SkyProxyModel() {
    m_worker.quit();
    m_worker.wait();
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

void SkyProxyModel::stringChanged(const QString &p_str)
{
    setFilterFixedString(p_str);
}

QVariant SkyProxyModel::get(int p_index, int role)
{
    return sourceModel()->data(mapToSource(index(p_index, 0)), role);
}
QString SkyProxyModel::get_name(int p_index)
{
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
    QVariantMap m;
    Q_EMIT instigateLoad(m);
}

void SkyProxyModel::handleLoadedRow(const QVariantMap &msg) {
    model_impl()->append(msg);
    m_progress = msg.value("Percent").toInt();
    emit loadProgressChanged();
}

void SkyProxyModel::handlePrependMsg(const QVariantMap &msg) {
    model_impl()->insert(0, msg);
}
