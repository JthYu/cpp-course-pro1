#include <gtest/gtest.h>

#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{
// 跑车 M: 前进 2 格
TEST(ExecutorSportsCarTest, should_move_2_steps_given_normal_M)
{
    auto executor = Executor::NewExecutor({0, 0, 'E'}, CarType::SPORTS_CAR);
    executor->Execute("M");
    EXPECT_EQ(Pose({2, 0, 'E'}), executor->Query());
}

// 跑车 L: 左转90度，前进1格
TEST(ExecutorSportsCarTest, should_turn_left_and_move_1_given_normal_L)
{
    auto executor = Executor::NewExecutor({0, 0, 'E'}, CarType::SPORTS_CAR);
    executor->Execute("L");
    // 左转后朝北，前进一格 y+1
    EXPECT_EQ(Pose({0, 1, 'N'}), executor->Query());
}

// 跑车 F 后 M: 前进 4 格
TEST(ExecutorSportsCarTest, should_move_4_steps_given_FM)
{
    auto executor = Executor::NewExecutor({0, 0, 'E'}, CarType::SPORTS_CAR);
    executor->Execute("FM");
    EXPECT_EQ(Pose({4, 0, 'E'}), executor->Query());
}
}  // namespace adas