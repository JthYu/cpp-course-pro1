#include "ExecutorImpl.hpp"

#include <functional>
#include <memory>
#include <new>
#include <unordered_map>

#include "Command.hpp"

namespace adas
{

// 修改工厂方法
Executor* Executor::NewExecutor(const Pose& pose, const CarType carType) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose, carType);
}

ExecutorImpl::ExecutorImpl(const Pose& pose, CarType carType) noexcept : poseHandler(pose), carType(carType)
{
}

// 由于现在是指令返回动作列表，我们用 std::unordered_map 存命令对象指针
void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    // 这里为了支持 'TR'，我们需要简单替换一下字符串
    std::string parsedCommands;
    for (size_t i = 0; i < commands.length(); ++i) {
        if (commands[i] == 'T' && i + 1 < commands.length() && commands[i + 1] == 'R') {
            parsedCommands += 'Z';  // 把 TR 替换成 Z
            i++;                    // 跳过 R
        } else {
            parsedCommands += commands[i];
        }
    }

    // 静态指令表（只初始化一次，提高效率）
    static const std::unordered_map<char, std::shared_ptr<ICommand>> cmdMap = {
        {'M', std::make_shared<MoveCommand>()},      {'L', std::make_shared<TurnLeftCommand>()},
        {'R', std::make_shared<TurnRightCommand>()}, {'F', std::make_shared<FastCommand>()},
        {'B', std::make_shared<ReverseCommand>()},   {'Z', std::make_shared<TurnRoundCommand>()}};

    for (const auto cmd : parsedCommands) {
        auto it = cmdMap.find(cmd);
        if (it != cmdMap.end()) {
            // 获取动作列表，然后依次执行
            ActionGroup actions = it->second->GetActions(poseHandler, carType);
            for (const auto& action : actions) {
                action(poseHandler);
            }
        }
    }
}

Pose ExecutorImpl::Query(void) const noexcept
{
    return poseHandler.Query();
}

}  // namespace adas