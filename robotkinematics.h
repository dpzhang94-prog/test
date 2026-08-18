#pragma once

#include <QString>

#include <array>

struct HK_Context;

// 表示五轴正解得到的TCP位置和姿态。
struct RobotTcpPose
{
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    double rx = 0.0;
    double ry = 0.0;
};

// 统一管理机器人机构参数和五轴正解上下文。
class RobotKinematics final
{
public:
    RobotKinematics();
    ~RobotKinematics();

    RobotKinematics(const RobotKinematics &) = delete;
    RobotKinematics &operator=(const RobotKinematics &) = delete;

    // 使用公共机构参数将五个关节值正解为TCP位姿。
    bool forward5Axis(const std::array<double, 5> &joints,
                      RobotTcpPose &pose,
                      QString &errorMessage) const;

private:
    HK_Context *m_context = nullptr;
    QString m_initializationError;
};
