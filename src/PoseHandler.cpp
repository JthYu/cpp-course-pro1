#include "PoseHandler.hpp"

namespace adas
{

PoseHandler::PoseHandler(const Pose& pose) noexcept : pose(pose)
{
}

// 删掉 fast 判断，只做基础移动
void PoseHandler::Move() noexcept
{
    if (pose.heading == 'E')
        ++pose.x;
    else if (pose.heading == 'W')
        --pose.x;
    else if (pose.heading == 'N')
        ++pose.y;
    else if (pose.heading == 'S')
        --pose.y;
}

void PoseHandler::TurnLeft() noexcept
{
    // 删掉原本的 if (fast) 那些逻辑，只做左转
    if (pose.heading == 'N')
        pose.heading = 'W';
    else if (pose.heading == 'W')
        pose.heading = 'S';
    else if (pose.heading == 'S')
        pose.heading = 'E';
    else if (pose.heading == 'E')
        pose.heading = 'N';
}

void PoseHandler::TurnRight() noexcept
{
    // 删掉原本的 if (fast) 那些逻辑，只做右转
    if (pose.heading == 'N')
        pose.heading = 'E';
    else if (pose.heading == 'E')
        pose.heading = 'S';
    else if (pose.heading == 'S')
        pose.heading = 'W';
    else if (pose.heading == 'W')
        pose.heading = 'N';
}

void PoseHandler::Fast() noexcept
{
    fast = !fast;
}

bool PoseHandler::IsFast() const noexcept
{
    return fast;
}

Pose PoseHandler::Query() const noexcept
{
    return pose;
}

}  // namespace adas