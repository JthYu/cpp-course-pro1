#pragma once
#include "Executor.hpp"

namespace adas
{
class ExecutorImpl final : public Executor
{
public:
    explicit ExecutorImpl(const Pose& pose) noexcept;
    ~ExecutorImpl() noexcept = default;

    ExecutorImpl(const ExecutorImpl&) = delete;
    ExecutorImpl& operator=(const ExecutorImpl&) = delete;

public:
    void Execute(const std::string& command) noexcept override;
    Pose Query(void) const noexcept override;
    void Move() noexcept;
    void TurnLeft() noexcept;
    void TurnRight() noexcept;

private:
    // 类实现，将指令封装成类 ===
    // 定义移动指令类
    class MoveCommand final
    {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept
        {
            executor.Move();
        }
    };

    // 定义左转指令类
    class TurnLeftCommand final
    {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept
        {
            executor.TurnLeft();
        }
    };

    // 定义右转指令类
    class TurnRightCommand final
    {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept
        {
            executor.TurnRight();
        }
    };

private:
    Pose pose;
};
}  // namespace adas