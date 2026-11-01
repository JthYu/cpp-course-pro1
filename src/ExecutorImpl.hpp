#pragma once
#include "Executor.hpp"
#include "PoseHandler.hpp"  // 必须有

namespace adas
{

class ExecutorImpl final : public Executor
{
public:
    explicit ExecutorImpl(const Pose& pose) noexcept;

    void Execute(const std::string& command) noexcept override;
    Pose Query(void) const noexcept override;

private:
    PoseHandler poseHandler;  // 替换掉原先的私有变量
};

}  // namespace adas