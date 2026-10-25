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
        // 统一用父类指针接收
        std::unique_ptr<ICommand> cmdder;

        if (cmd == 'M') {
            cmdder = std::make_unique<MoveCommand>();
        } else if (cmd == 'L') {
            cmdder = std::make_unique<TurnLeftCommand>();
        } else if (cmd == 'R') {
            cmdder = std::make_unique<TurnRightCommand>();
        }

        // === 多态调用：统一执行 ===
        if (cmdder) {
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