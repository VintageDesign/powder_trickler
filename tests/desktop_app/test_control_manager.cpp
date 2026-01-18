#include <gtest/gtest.h>
#include <QSignalSpy>
#include <QCoreApplication>

#include "controller/control_manager.h"

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
    EXPECT_DOUBLE_EQ(spy.takeFirst().at(0).toDouble(), 0.1);

    manager.increment();

    EXPECT_EQ(spy.count(), 1);
    EXPECT_DOUBLE_EQ(spy.takeFirst().at(0).toDouble(), 0.2);
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
    EXPECT_DOUBLE_EQ(spy.takeFirst().at(0).toDouble(), 0.1);
}

TEST_F(ControlManagerTest, DecrementDoesNotGoBelowZero)
{
    ControlManager manager(nullptr);
    QSignalSpy spy(&manager, &ControlManager::setpointChanged);

    manager.decrement();

    EXPECT_EQ(spy.count(), 1);
    EXPECT_DOUBLE_EQ(spy.takeFirst().at(0).toDouble(), 0.0);

    manager.decrement();

    EXPECT_EQ(spy.count(), 1);
    EXPECT_DOUBLE_EQ(spy.takeFirst().at(0).toDouble(), 0.0);
}

TEST_F(ControlManagerTest, SetSetpointValidInput)
{
    ControlManager manager(nullptr);
    QSignalSpy spy(&manager, &ControlManager::setpointChanged);

    manager.setSetpoint(5.5);

    EXPECT_EQ(spy.count(), 1);
    EXPECT_DOUBLE_EQ(spy.takeFirst().at(0).toDouble(), 5.5);
}

TEST_F(ControlManagerTest, SetSetpointNegativeClampedToZero)
{
    ControlManager manager(nullptr);
    QSignalSpy spy(&manager, &ControlManager::setpointChanged);

    manager.setSetpoint(-3.0);

    EXPECT_EQ(spy.count(), 1);
    EXPECT_DOUBLE_EQ(spy.takeFirst().at(0).toDouble(), 0.0);
}

TEST_F(ControlManagerTest, SetSetpointThenIncrement)
{
    ControlManager manager(nullptr);
    QSignalSpy spy(&manager, &ControlManager::setpointChanged);

    manager.setSetpoint(10.0);
    spy.clear();

    manager.increment();

    EXPECT_EQ(spy.count(), 1);
    EXPECT_DOUBLE_EQ(spy.takeFirst().at(0).toDouble(), 10.1);
}

