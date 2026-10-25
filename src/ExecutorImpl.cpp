#include "ExecutorImpl.hpp"

#include <memory>

namespace adas
{
Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}

ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : pose(pose)
{
}

void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    for (const auto cmd : commands) {
        // === 17页：面向对象封装 ===
        if (cmd == 'M') {
            // Move(); // 注释掉原来的直接调用
            std::unique_ptr<MoveCommand> cmdder = std::make_unique<MoveCommand>();
            cmdder->DoOperate(*this);
        } else if (cmd == 'L') {
            // TurnLeft();
            std::unique_ptr<TurnLeftCommand> cmdder = std::make_unique<TurnLeftCommand>();
            cmdder->DoOperate(*this);
        } else if (cmd == 'R') {
            // TurnRight();
            std::unique_ptr<TurnRightCommand> cmdder = std::make_unique<TurnRightCommand>();
            cmdder->DoOperate(*this);
        }
    }
}

// 抽取出的移动逻辑
void ExecutorImpl::Move() noexcept
{
    if (pose.heading == 'E') {
        ++pose.x;
    } else if (pose.heading == 'W') {
        --pose.x;
    } else if (pose.heading == 'N') {
        ++pose.y;
    } else if (pose.heading == 'S') {
        --pose.y;
    }
}

// 抽取出的左转逻辑
void ExecutorImpl::TurnLeft() noexcept
{
    if (pose.heading == 'N') {
        pose.heading = 'W';
    } else if (pose.heading == 'W') {
        pose.heading = 'S';
    } else if (pose.heading == 'S') {
        pose.heading = 'E';
    } else if (pose.heading == 'E') {
        pose.heading = 'N';
    }
}

// 抽取出的右转逻辑
void ExecutorImpl::TurnRight() noexcept
{
    if (pose.heading == 'N') {
        pose.heading = 'E';
    } else if (pose.heading == 'E') {
        pose.heading = 'S';
    } else if (pose.heading == 'S') {
        pose.heading = 'W';
    } else if (pose.heading == 'W') {
        pose.heading = 'N';
    }
}

Pose ExecutorImpl::Query() const noexcept
{
    return pose;
}
}  // namespace adas