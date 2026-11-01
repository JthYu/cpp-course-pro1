#pragma once
#include <functional>
#include <list>

#include "PoseHandler.hpp"

namespace adas
{

// 1. 定义基础动作（原子操作）
using Action = std::function<void(PoseHandler&)>;

// 2. 动作组：组合多个原子动作
using ActionGroup = std::list<Action>;

// 3. 定义标准动作的具体实现（供不同类型的车复用）
inline const Action Forward = [](PoseHandler& p) { p.Move(); };
inline const Action Backward = [](PoseHandler& p) { p.Move(); };  // Move 内部已处理方向
inline const Action TurnLeft = [](PoseHandler& p) { p.TurnLeft(); };
inline const Action TurnRight = [](PoseHandler& p) { p.TurnRight(); };
inline const Action BeFast = [](PoseHandler& p) { p.Fast(); };
inline const Action BeReverse = [](PoseHandler& p) { p.Reverse(); };

// 4. 定义指令基类（接口），接收 carType 以便在内部判断
class ICommand
{
public:
    virtual ~ICommand() = default;
    // 根据车辆类型和当前状态，返回该指令需要执行的动作列表
    virtual ActionGroup GetActions(PoseHandler& poseHandler, CarType carType) const noexcept = 0;
};

// ---------------- 具体指令实现 ----------------

class MoveCommand final : public ICommand
{
public:
    ActionGroup GetActions(PoseHandler& poseHandler, CarType carType) const noexcept override
    {
        ActionGroup actions;
        int steps = 1;

        // 跑车：每次移动 2 格；普通车/Bus：1 格
        if (carType == CarType::SPORTS_CAR)
            steps = 2;

        // 加速状态下，移动次数翻倍
        if (poseHandler.IsFast())
            steps *= 2;

        // 倒车状态下，也是一样的逻辑（PoseHandler 内部会处理反向）
        for (int i = 0; i < steps; ++i) {
            actions.push_back(Forward);
        }
        return actions;
    }
};

class TurnLeftCommand final : public ICommand
{
public:
    ActionGroup GetActions(PoseHandler& poseHandler, CarType carType) const noexcept override
    {
        ActionGroup actions;

        // 跑车需求：先左转，再前进 1 格
        if (carType == CarType::SPORTS_CAR) {
            actions.push_back(TurnLeft);
            actions.push_back(Forward);
        }
        // Bus 需求：前进 1 格，再左转
        else if (carType == CarType::BUS) {
            actions.push_back(Forward);
            actions.push_back(TurnLeft);
        }
        // 普通车需求
        else {
            if (poseHandler.IsFast() || poseHandler.IsReverse()) {
                actions.push_back(Forward);
            }
            actions.push_back(TurnLeft);
        }

        return actions;
    }
};

class TurnRightCommand final : public ICommand
{
public:
    ActionGroup GetActions(PoseHandler& poseHandler, CarType carType) const noexcept override
    {
        ActionGroup actions;

        if (carType == CarType::SPORTS_CAR) {
            actions.push_back(TurnRight);
            actions.push_back(Forward);
        }
        // Bus 需求：前进 1 格，再右转
        else if (carType == CarType::BUS) {
            actions.push_back(Forward);
            actions.push_back(TurnRight);
        } else {
            if (poseHandler.IsFast() || poseHandler.IsReverse()) {
                actions.push_back(Forward);
            }
            actions.push_back(TurnRight);
        }

        return actions;
    }
};

class FastCommand final : public ICommand
{
public:
    ActionGroup GetActions(PoseHandler& poseHandler, CarType carType) const noexcept override
    {
        return {BeFast};
    }
};

class ReverseCommand final : public ICommand
{
public:
    ActionGroup GetActions(PoseHandler& poseHandler, CarType carType) const noexcept override
    {
        return {BeReverse};
    }
};

// 任务编排指令 TR (掉头)
class TurnRoundCommand final : public ICommand
{
public:
    ActionGroup GetActions(PoseHandler& poseHandler, CarType carType) const noexcept override
    {
        if (poseHandler.IsReverse())
            return {};  // 倒车状态下 TR 无效

        if (poseHandler.IsFast()) {
            return {Forward, TurnLeft, Forward, TurnLeft};
        }
        return {TurnLeft, Forward, TurnLeft};
    }
};

}  // namespace adas