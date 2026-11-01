#pragma once
#include <functional>

#include "PoseHandler.hpp"

namespace adas
{

class MoveCommand final
{
public:
    const std::function<void(PoseHandler& poseHandler)> operate = [](PoseHandler& poseHandler) noexcept {
        if (poseHandler.IsFast()) {
            poseHandler.Move();
        }
        poseHandler.Move();
    };
};

class TurnLeftCommand final
{
public:
    const std::function<void(PoseHandler& poseHandler)> operate = [](PoseHandler& poseHandler) noexcept {
        // 需求：如果加速，先移动一格；如果倒车，L指令本身要求先倒退一格
        if (poseHandler.IsFast() || poseHandler.IsReverse()) {
            poseHandler.Move();
        }
        poseHandler.TurnLeft();
    };
};

class TurnRightCommand final
{
public:
    const std::function<void(PoseHandler& poseHandler)> operate = [](PoseHandler& poseHandler) noexcept {
        if (poseHandler.IsFast() || poseHandler.IsReverse()) {
            poseHandler.Move();
        }
        poseHandler.TurnRight();
    };
};

class FastCommand final
{
public:
    const std::function<void(PoseHandler& poseHandler)> operate = [](PoseHandler& poseHandler) noexcept {
        poseHandler.Fast();
    };
};

// 倒车指令
class ReverseCommand final
{
public:
    const std::function<void(PoseHandler& poseHandler)> operate = [](PoseHandler& poseHandler) noexcept {
        poseHandler.Reverse();
    };
};

}  // namespace adas