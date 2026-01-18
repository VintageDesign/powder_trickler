#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QUrl>

#include "controller/control_manager.h"
#include "settings/settings_manager.h"
#include "qml/run_screen_view.h"
#include "qml/settings_view.h"

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
    SettingsManager settingsManager;

    auto *rootObject = engine.rootObjects().first();
    auto *runView = rootObject->findChild<RunScreenView*>();
    auto *settingsView = rootObject->findChild<SettingsView*>();

    if (runView) {
        QObject::connect(runView, &RunScreenView::incrementRequested, &controlManager, &ControlManager::increment);
        QObject::connect(runView, &RunScreenView::decrementRequested, &controlManager, &ControlManager::decrement);
        QObject::connect(runView, &RunScreenView::dispenseRequested, &controlManager, &ControlManager::dispense);
        QObject::connect(runView, &RunScreenView::setpointInputRequested, &controlManager, &ControlManager::setSetpoint);

        QObject::connect(&controlManager, &ControlManager::setpointChanged, runView, &RunScreenView::onSetpointChanged);
        QObject::connect(&controlManager, &ControlManager::actualValueChanged, runView, &RunScreenView::onActualValueChanged);
    }

    if (settingsView) {
        QObject::connect(settingsView, &SettingsView::refreshPortsRequested, &settingsManager, &SettingsManager::refreshPorts);
        QObject::connect(settingsView, &SettingsView::portSelectionRequested, &settingsManager, &SettingsManager::selectPort);
        QObject::connect(settingsView, &SettingsView::connectRequested, &settingsManager, &SettingsManager::connectToSelectedPort);
        QObject::connect(settingsView, &SettingsView::disconnectRequested, &settingsManager, &SettingsManager::disconnectFromPort);

        QObject::connect(&settingsManager, &SettingsManager::availablePortsChanged, settingsView, &SettingsView::onAvailablePortsChanged);
        QObject::connect(&settingsManager, &SettingsManager::selectedPortChanged, settingsView, &SettingsView::onSelectedPortChanged);
        QObject::connect(&settingsManager, &SettingsManager::connectionStatusChanged, settingsView, &SettingsView::onConnectionStatusChanged);

        settingsManager.refreshPorts();
    }

    return app.exec();
}
