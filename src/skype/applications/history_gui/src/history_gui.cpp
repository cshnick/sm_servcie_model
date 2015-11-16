#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTextCodec>
#include <QtQml>

#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>

#include "unistd.h"

#include "skyproxymodel.h"
#include "skycontactstreemodel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));

    SkyProxyModel *model = new SkyProxyModel();
    SkyContactsTreeModel *contacts_model = new SkyContactsTreeModel;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("sky_model", model);
    engine.rootContext()->setContextProperty("sky_contacts_model", contacts_model);
    qmlRegisterType<ModelState>("Enums", 1, 0, "ModelState");
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    QObject *rect = engine.rootObjects().at(0)->findChild<QObject*>("SkylistRect");
    model->setQmlObject(rect);

    qDebug() << "Rect width" << rect->property("width").toInt();
    qDebug() << "Rect object name" << rect->objectName();


    if (QSystemTrayIcon::isSystemTrayAvailable()) {
        QApplication::setQuitOnLastWindowClosed(false);
        QObject *root = 0;
        if (engine.rootObjects().size() > 0)
        {
            root = engine.rootObjects().at(0);

            QAction *minimizeAction = new QAction(QObject::tr("Mi&nimize"), root);
            root->connect(minimizeAction, SIGNAL(triggered()), root, SLOT(hide()));
            QAction *maximizeAction = new QAction(QObject::tr("Ma&ximize"), root);
            root->connect(maximizeAction, SIGNAL(triggered()), root, SLOT(showMaximized()));
            QAction *restoreAction = new QAction(QObject::tr("&Restore"), root);
            root->connect(restoreAction, SIGNAL(triggered()), root, SLOT(showNormal()));
            QAction *quitAction = new QAction(QObject::tr("&Quit"), root);
            root->connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

            QMenu *trayIconMenu = new QMenu();
            trayIconMenu->addAction(minimizeAction);
            trayIconMenu->addAction(maximizeAction);
            trayIconMenu->addAction(restoreAction);
            trayIconMenu->addSeparator();
            trayIconMenu->addAction(quitAction);

            QSystemTrayIcon *trayIcon = new QSystemTrayIcon(root);
            root->connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), root, SLOT(showNormal()));
            trayIcon->setContextMenu(trayIconMenu);
            trayIcon->setIcon(QIcon(":images/logoskype.svg"));
            trayIcon->show();

            app.setWindowIcon(QIcon(":images/logoskype.svg"));
        }
    }

    return app.exec();
}
