#pragma once
#include <string>
namespace adas
{
struct Pose {
    int x;
    int y;
    char heading;
};

enum class CarType { CAR, SPORTS_CAR, BUS };

class Executor
{
public:
    // Caller should delete *executor when it is no longer needed.
    // static Executor* NewExecutor(const Pose& pose) noexcept;

    static Executor* NewExecutor(const Pose& pose, const CarType carType = CarType::CAR) noexcept;

public:
    Executor(void) = default;
    virtual ~Executor(void) = default;
    Executor(const Executor&) = delete;
    Executor& operator=(const Executor&) = delete;

public:
    virtual void Execute(const std::string& command) noexcept = 0;
    virtual Pose Query(void) const noexcept = 0;
};
}  // namespace adas