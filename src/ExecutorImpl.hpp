#pragma once
#include "Executor.hpp"
#include "PoseHandler.hpp"

namespace adas
{

class ExecutorImpl final : public Executor
{
public:
    // 1. 修改构造函数，增加 CarType 参数
    explicit ExecutorImpl(const Pose& pose, CarType carType) noexcept;
    ~ExecutorImpl() noexcept = default;

    ExecutorImpl(const ExecutorImpl&) = delete;
    ExecutorImpl& operator=(const ExecutorImpl&) = delete;

public:
    void Execute(const std::string& command) noexcept override;
    Pose Query(void) const noexcept override;

private:
    PoseHandler poseHandler;

    // 2. 新增成员变量保存车辆类型
    CarType carType;
};

}  // namespace adas