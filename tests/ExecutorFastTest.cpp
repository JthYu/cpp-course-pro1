#include <gtest/gtest.h>

#include <memory>

#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{
// 1. 加速状态下执行 M，前进两格
TEST(ExecutorFastTest, should_return_x_plus_2_given_status_is_fast_command_is_M_and_facing_is_E)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    executor->Execute("FM");  // F开启加速，M走两步
    const Pose target({2, 0, 'E'});
    ASSERT_EQ(target, executor->Query());
}

// 2. 加速状态下执行 L，先前进一格，再左转
TEST(ExecutorFastTest, should_return_N_and_x_plus_1_given_status_is_fast_command_is_L_and_facing_is_E)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    executor->Execute("FL");  // F开启加速，L前进并左转
    const Pose target({1, 0, 'N'});
    ASSERT_EQ(target, executor->Query());
}

// 3. 加速状态下执行 R，先前进一格，再右转
TEST(ExecutorFastTest, should_return_S_and_x_plus_1_given_status_is_fast_command_is_R_and_facing_is_E)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    executor->Execute("FR");
    const Pose target({1, 0, 'S'});
    ASSERT_EQ(target, executor->Query());
}

// 4. 再次收到 F 指令，状态取消，回到普通模式 (N朝向走1步)
TEST(ExecutorFastTest, should_return_y_plus_1_given_command_is_FFM_and_facing_is_N)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    executor->Execute("FFM");  // F加速，F取消，M只走一步
    const Pose target({0, 1, 'N'});
    ASSERT_EQ(target, executor->Query());
}

}  // namespace adas