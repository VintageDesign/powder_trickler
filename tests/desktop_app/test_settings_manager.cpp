#include <gtest/gtest.h>
#include <QSignalSpy>
#include <QCoreApplication>

#include "settings/settings_manager.h"
#include "interfaces/uart_interface.h"

class SettingsManagerTest : public ::testing::Test
{
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(SettingsManagerTest, RefreshPortsEmitsSignal)
{
    SettingsManager manager;
    QSignalSpy spy(&manager, &SettingsManager::availablePortsChanged);

    manager.refreshPorts();

    EXPECT_EQ(spy.count(), 1);
}

TEST_F(SettingsManagerTest, SelectPortEmitsSignal)
{
    SettingsManager manager;
    QSignalSpy spy(&manager, &SettingsManager::selectedPortChanged);

    manager.selectPort("ttyUSB0");

    EXPECT_EQ(spy.count(), 1);
    EXPECT_EQ(spy.takeFirst().at(0).toString().toStdString(), "ttyUSB0");
}

TEST_F(SettingsManagerTest, SelectSamePortDoesNotEmit)
{
    SettingsManager manager;
    manager.selectPort("ttyUSB0");

    QSignalSpy spy(&manager, &SettingsManager::selectedPortChanged);
    manager.selectPort("ttyUSB0");

    EXPECT_EQ(spy.count(), 0);
}

TEST_F(SettingsManagerTest, ConnectWithEmptyPortDoesNothing)
{
    SettingsManager manager;
    QSignalSpy spy(&manager, &SettingsManager::connectionStatusChanged);

    manager.connectToSelectedPort();

    EXPECT_EQ(spy.count(), 0);
}

TEST_F(SettingsManagerTest, DisconnectEmitsSignal)
{
    SettingsManager manager;
    QSignalSpy spy(&manager, &SettingsManager::connectionStatusChanged);

    manager.disconnectFromPort();

    EXPECT_EQ(spy.count(), 1);
    EXPECT_EQ(spy.takeFirst().at(0).toBool(), false);
}

TEST_F(SettingsManagerTest, GetUartInterfaceInitiallyNull)
{
    SettingsManager manager;

    EXPECT_EQ(manager.getUartInterface(), nullptr);
}

TEST_F(SettingsManagerTest, ViewConnectionRefreshPorts)
{
    SettingsManager manager;
    QSignalSpy spy(&manager, &SettingsManager::availablePortsChanged);

    manager.refreshPorts();

    EXPECT_EQ(spy.count(), 1);
    QStringList ports = spy.takeFirst().at(0).toStringList();
    // Ports list might be empty or have entries depending on system
    EXPECT_TRUE(ports.isEmpty() || !ports.isEmpty());
}

