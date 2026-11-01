#pragma once
#include "Executor.hpp"  // 为了使用 Pose

namespace adas
{
class PoseHandler final
{
public:
    explicit PoseHandler(const Pose& pose) noexcept;
    PoseHandler(const PoseHandler&) = delete;
    PoseHandler& operator=(const PoseHandler&) = delete;

public:
    // 提供对外的行为接口
    void Move(void) noexcept;
    void TurnLeft(void) noexcept;
    void TurnRight(void) noexcept;
    void Fast(void) noexcept;
    bool IsFast(void) const noexcept;
    Pose Query(void) const noexcept;

private:
    // 状态数据被封装在这里
    Pose pose;
    bool fast{false};
};
}  // namespace adas