#include "ExecutorImpl.hpp"

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

// 表驱动实现
void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    // 1. 建立指令映射表（将字符映射到对应的指令对象）
    std::unordered_map<char, std::unique_ptr<ICommand>> cmderMap;
    cmderMap.emplace('M', std::make_unique<MoveCommand>());
    cmderMap.emplace('L', std::make_unique<TurnLeftCommand>());
    cmderMap.emplace('R', std::make_unique<TurnRightCommand>());
    cmderMap.emplace('F', std::make_unique<FastCommand>());

    // 2. 遍历指令字符串
    for (const auto cmd : commands) {
        // 3. 在表中查找当前字符
        const auto it = cmderMap.find(cmd);

        // 4. 如果找到了对应的指令，就执行
        if (it != cmderMap.end()) {
            it->second->DoOperate(poseHandler);
        }
    }
}

}  // namespace adas