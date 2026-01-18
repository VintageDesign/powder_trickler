#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QUrl>

#include "controller/control_manager.h"
#include "run_screen_view.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setApplicationName("Powder Trickler");
    app.setOrganizationName("PowderTrickler");
    app.setApplicationVersion("1.0.0");

    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.load(QUrl(QStringLiteral("qrc:/PowderTrickler/main.qml")));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    ControlManager controlManager(nullptr);

    auto *rootObject = engine.rootObjects().first();
    auto *view = rootObject->findChild<RunScreenView*>();

    if (view) {
        QObject::connect(view, &RunScreenView::incrementRequested, &controlManager, &ControlManager::increment);
        QObject::connect(view, &RunScreenView::decrementRequested, &controlManager, &ControlManager::decrement);
        QObject::connect(view, &RunScreenView::dispenseRequested, &controlManager, &ControlManager::dispense);
        QObject::connect(view, &RunScreenView::setpointInputRequested, &controlManager, &ControlManager::setSetpoint);

        QObject::connect(&controlManager, &ControlManager::setpointChanged, view, &RunScreenView::onSetpointChanged);
        QObject::connect(&controlManager, &ControlManager::actualValueChanged, view, &RunScreenView::onActualValueChanged);
    }

    return app.exec();
}
