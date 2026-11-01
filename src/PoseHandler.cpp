#include "PoseHandler.hpp"

namespace adas
{
PoseHandler::PoseHandler(const Pose& pose) noexcept : pose(pose)
{
}

void PoseHandler::Move() noexcept
{
    int steps = fast ? 2 : 1;
    for (int i = 0; i < steps; ++i) {
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
    if (fast) {
        bool temp = fast;
        fast = false;
        Move();
        fast = temp;
    }
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
    if (fast) {
        bool temp = fast;
        fast = false;
        Move();
        fast = temp;
    }
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