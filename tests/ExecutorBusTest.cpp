#include <gtest/gtest.h>

#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{
// Bus M: 前进 1 格
TEST(ExecutorBusTest, should_move_1_step_given_normal_M)
{
    auto executor = Executor::NewExecutor({0, 0, 'E'}, CarType::BUS);
    executor->Execute("M");
    EXPECT_EQ(Pose({1, 0, 'E'}), executor->Query());
}

// Bus L: 前进1格，左转90度
TEST(ExecutorBusTest, should_move_1_and_turn_left_given_normal_L)
{
    auto executor = Executor::NewExecutor({0, 0, 'E'}, CarType::BUS);
    executor->Execute("L");
    EXPECT_EQ(Pose({1, 0, 'N'}), executor->Query());
}

// Bus B&F: 后退2格
TEST(ExecutorBusTest, should_move_backward_2_steps_given_BFM)
{
    auto executor = Executor::NewExecutor({0, 0, 'E'}, CarType::BUS);
    executor->Execute("BFM");
    // Bus 加速 1 次移动 2 格，倒车退 2 格 -> x - 2
    EXPECT_EQ(Pose({-2, 0, 'E'}), executor->Query());
}
}  // namespace adas