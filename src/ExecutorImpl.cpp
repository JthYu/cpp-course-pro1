#include "ExecutorImpl.hpp"

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
        std::unique_ptr<ICommand> cmdder;

        if (cmd == 'M') {
            cmdder = std::make_unique<MoveCommand>();
        } else if (cmd == 'L') {
            cmdder = std::make_unique<TurnLeftCommand>();
        } else if (cmd == 'R') {
            cmdder = std::make_unique<TurnRightCommand>();
        } else if (cmd == 'F') {  // 新增 F 指令
            cmdder = std::make_unique<FastCommand>();
        }

        if (cmdder) {
            cmdder->DoOperate(*this);
        }
    }
}

// 切换加速状态
void ExecutorImpl::Fast() noexcept
{
    fast = !fast;
}

void ExecutorImpl::Move() noexcept
{
    // 如果处于加速状态，走2步，否则走1步
    int steps = fast ? 2 : 1;
    for (int i = 0; i < steps; ++i) {
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
}

void ExecutorImpl::TurnLeft() noexcept
{
    // 加速状态下，先往前走一步（不管朝向怎么转，转向之前的位置是固定的）
    if (fast) {
        fast = false;  // 暂时关闭加速，借用 Move 走1步
        Move();
        fast = true;  // 恢复加速状态
    }

    // 执行左转
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

void ExecutorImpl::TurnRight() noexcept
{
    // 加速状态下，先往前走一步
    if (fast) {
        fast = false;
        Move();
        fast = true;
    }

    // 执行右转
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