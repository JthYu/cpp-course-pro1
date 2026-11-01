#include "ExecutorImpl.hpp"

#include <memory>
#include <new>  // 为了 std::nothrow

#include "Command.hpp"

namespace adas
{

// 🔴 补上这个！测试用例全靠它来创建 Executor 实例
Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}

// 构造初始化
ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : poseHandler(pose)
{
}

Pose ExecutorImpl::Query(void) const noexcept
{
    return poseHandler.Query();
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
        } else if (cmd == 'F') {
            cmdder = std::make_unique<FastCommand>();
        }

        if (cmdder) {
            cmdder->DoOperate(poseHandler);
        }
    }
}

}  // namespace adas