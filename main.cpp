#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include <qqml.h>
#include "../database/database.h"
#include "../managers/taskmanager.h"
#include "../model/listModel.h"
#include "../proxyModel/proxyModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");
    QQmlApplicationEngine engine;

    Database db;
    ListModelCpp model(db);
    ProxyModel proxy;

    model.loadTask();

    proxy.setSourceModel(&model);

    engine.rootContext()->setContextProperty("ListModelCpp", &model);
    engine.rootContext()->setContextProperty("ProxyModel", &proxy);

    qDebug() << "ROWS: " << model.rowCount();

    engine.loadFromModule("TodoList", "Main");

    if(engine.rootObjects().isEmpty()) {
        return -1;
    }

    return QCoreApplication::exec();
}
