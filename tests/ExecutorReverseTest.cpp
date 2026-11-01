#include <gtest/gtest.h>

#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{

// ==========================================
// 1. 基础倒车测试 (B 指令)
// ==========================================

TEST(ExecutorReverseTest, should_return_same_pose_given_command_is_B_and_facing_is_E)
{
    auto executor = Executor::NewExecutor({0, 0, 'E'});
    executor->Execute("B");
    EXPECT_EQ(Pose({0, 0, 'E'}), executor->Query());
}

TEST(ExecutorReverseTest, should_return_same_pose_given_command_is_BB_and_facing_is_E)
{
    auto executor = Executor::NewExecutor({0, 0, 'E'});
    executor->Execute("BB");
    EXPECT_EQ(Pose({0, 0, 'E'}), executor->Query());
}

// ==========================================
// 2. 倒车状态下的移动 (BM 指令)
// ==========================================

TEST(ExecutorReverseTest, should_return_x_minus_1_given_command_is_BM_and_facing_is_E)
{
    auto executor = Executor::NewExecutor({0, 0, 'E'});
    executor->Execute("BM");
    EXPECT_EQ(Pose({-1, 0, 'E'}), executor->Query());
}

TEST(ExecutorReverseTest, should_return_y_minus_1_given_command_is_BM_and_facing_is_N)
{
    auto executor = Executor::NewExecutor({0, 0, 'N'});
    executor->Execute("BM");
    EXPECT_EQ(Pose({0, -1, 'N'}), executor->Query());
}

// ==========================================
// 3. 倒车状态下的转向 (BL, BR 指令)
// ==========================================

TEST(ExecutorReverseTest, should_return_x_minus_1_and_facing_S_given_command_is_BL_and_facing_is_E)
{
    auto executor = Executor::NewExecutor({0, 0, 'E'});
    executor->Execute("BL");
    EXPECT_EQ(Pose({-1, 0, 'S'}), executor->Query());
}

TEST(ExecutorReverseTest, should_return_x_minus_1_and_facing_N_given_command_is_BR_and_facing_is_E)
{
    auto executor = Executor::NewExecutor({0, 0, 'E'});
    executor->Execute("BR");
    EXPECT_EQ(Pose({-1, 0, 'N'}), executor->Query());
}

// ==========================================
// 4. 倒车与加速叠加测试 (BF, BFM 指令)
// ==========================================

TEST(ExecutorReverseTest, should_return_x_minus_2_given_command_is_BFM_and_facing_is_E)
{
    auto executor = Executor::NewExecutor({0, 0, 'E'});
    executor->Execute("BFM");
    EXPECT_EQ(Pose({-2, 0, 'E'}), executor->Query());
}

}  // namespace adas