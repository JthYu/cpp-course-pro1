#include "ExecutorImpl.hpp"

#include <functional>  // 引入
#include <memory>
#include <new>
#include <unordered_map>

#include "Command.hpp"

namespace adas
{

Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}

ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : poseHandler(pose)
{
}

Pose ExecutorImpl::Query(void) const noexcept
{
    return poseHandler.Query();
}

void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    // PPT 第 13 页：将表里的类型改为 std::function
    std::unordered_map<char, std::function<void(PoseHandler & poseHandler)>> cmderMap;

    // 实例化指令对象，并取出它们的 operate 函数放进去
    MoveCommand moveCommand;
    cmderMap.emplace('M', moveCommand.operate);

    TurnLeftCommand turnLeftCommand;
    cmderMap.emplace('L', turnLeftCommand.operate);

    TurnRightCommand turnRightCommand;
    cmderMap.emplace('R', turnRightCommand.operate);

    FastCommand fastCommand;
    cmderMap.emplace('F', fastCommand.operate);

    ReverseCommand reverseCommand;
    cmderMap.emplace('B', reverseCommand.operate);

    for (const auto cmd : commands) {
        const auto it = cmderMap.find(cmd);
        if (it != cmderMap.end()) {
            // 直接像调用函数一样调用它，把状态处理器传进去
            it->second(poseHandler);
        }
    }
}

}  // namespace adas