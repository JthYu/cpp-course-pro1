#include "PoseHandler.hpp"

namespace adas
{
PoseHandler::PoseHandler(const Pose& pose) noexcept : pose(pose)
{
}

void PoseHandler::Move() noexcept
{
    // 如果处于倒车状态，移动方向与正常相反
    if (reverse) {
        if (pose.heading == 'E')
            --pose.x;
        else if (pose.heading == 'W')
            ++pose.x;
        else if (pose.heading == 'N')
            --pose.y;
        else if (pose.heading == 'S')
            ++pose.y;
    } else {
        if (pose.heading == 'E')
            ++pose.x;
        else if (pose.heading == 'W')
            --pose.x;
        else if (pose.heading == 'N')
            ++pose.y;
        else if (pose.heading == 'S')
            --pose.y;
    }
}

void PoseHandler::TurnLeft() noexcept
{
    // 倒车时，L 变成右转
    if (reverse) {
        if (pose.heading == 'N')
            pose.heading = 'E';
        else if (pose.heading == 'E')
            pose.heading = 'S';
        else if (pose.heading == 'S')
            pose.heading = 'W';
        else if (pose.heading == 'W')
            pose.heading = 'N';
    } else {
        if (pose.heading == 'N')
            pose.heading = 'W';
        else if (pose.heading == 'W')
            pose.heading = 'S';
        else if (pose.heading == 'S')
            pose.heading = 'E';
        else if (pose.heading == 'E')
            pose.heading = 'N';
    }
}

void PoseHandler::TurnRight() noexcept
{
    // 倒车时，R 变成左转
    if (reverse) {
        if (pose.heading == 'N')
            pose.heading = 'W';
        else if (pose.heading == 'W')
            pose.heading = 'S';
        else if (pose.heading == 'S')
            pose.heading = 'E';
        else if (pose.heading == 'E')
            pose.heading = 'N';
    } else {
        if (pose.heading == 'N')
            pose.heading = 'E';
        else if (pose.heading == 'E')
            pose.heading = 'S';
        else if (pose.heading == 'S')
            pose.heading = 'W';
        else if (pose.heading == 'W')
            pose.heading = 'N';
    }
}

void PoseHandler::Fast() noexcept
{
    fast = !fast;
}

bool PoseHandler::IsFast() const noexcept
{
    return fast;
}

void PoseHandler::Reverse() noexcept
{
    reverse = !reverse;
}

bool PoseHandler::IsReverse() const noexcept
{
    return reverse;
}

Pose PoseHandler::Query() const noexcept
{
    return pose;
}
}  // namespace adas