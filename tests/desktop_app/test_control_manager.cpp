#include <gtest/gtest.h>
#include <QSignalSpy>
#include <QCoreApplication>

#include "controller/control_manager.h"
#include "run_screen_view.h"

class ControlManagerTest : public ::testing::Test
{
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ControlManagerTest, Increment)
{
    ControlManager manager(nullptr);
    QSignalSpy spy(&manager, &ControlManager::setpointChanged);

    manager.increment();

    EXPECT_EQ(spy.count(), 1);
    EXPECT_EQ(spy.takeFirst().at(0).toString().toStdString(), "0.1");

    manager.increment();

    EXPECT_EQ(spy.count(), 1);
    EXPECT_EQ(spy.takeFirst().at(0).toString().toStdString(), "0.2");
}

TEST_F(ControlManagerTest, Decrement)
{
    ControlManager manager(nullptr);
    QSignalSpy spy(&manager, &ControlManager::setpointChanged);

    manager.increment();
    manager.increment();
    spy.clear();

    manager.decrement();

    EXPECT_EQ(spy.count(), 1);
    EXPECT_EQ(spy.takeFirst().at(0).toString().toStdString(), "0.1");
}

TEST_F(ControlManagerTest, DecrementDoesNotGoBelowZero)
{
    ControlManager manager(nullptr);
    QSignalSpy spy(&manager, &ControlManager::setpointChanged);

    manager.decrement();

    EXPECT_EQ(spy.count(), 1);
    EXPECT_EQ(spy.takeFirst().at(0).toString().toStdString(), "0.0");

    manager.decrement();

    EXPECT_EQ(spy.count(), 1);
    EXPECT_EQ(spy.takeFirst().at(0).toString().toStdString(), "0.0");
}

TEST_F(ControlManagerTest, ViewConnection)
{
    ControlManager manager(nullptr);
    RunScreenView view;

    manager.connectView(&view);

    QSignalSpy viewSpy(&view, &RunScreenView::setpointChanged);

    view.increment();

    EXPECT_EQ(viewSpy.count(), 1);
    EXPECT_EQ(view.setpoint().toStdString(), "0.1");

    view.decrement();

    EXPECT_EQ(viewSpy.count(), 2);
    EXPECT_EQ(view.setpoint().toStdString(), "0.0");
}
