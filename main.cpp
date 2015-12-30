#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <QDate>

#include "manager.h"
#include "trainer.h"
#include "training_type.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    auto root_context = engine.rootContext();

    Manager manager; //manager instance on stack

    root_context->setContextProperty("cpManager", &manager);


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
