#include "robotkinematics.h"

#include "HK_Kinematics_api.h"

namespace {

// 返回测试点生成和主界面校验共同使用的机器人机构参数。
HK_RobotParameters createDefaultRobotParameters()
{
    HK_RobotParameters parameters = {};
    parameters.L1 = 339.934;
    parameters.L2 = 177.553;
    parameters.L3 = 498.337;
    parameters.L4 = 500.0;
    parameters.L5 = 500.0;
    parameters.L6 = 51.337;
    parameters.L7 = 177.626;
    parameters.L8 = 391.747;
    parameters.L9 = 35.369;
    parameters.L10 = 195.249;
    parameters.L11 = 340.189;
    parameters.L12 = 177.509;
    parameters.L13 = 500.0;
    parameters.L14 = 0.36;
    parameters.L16 = -0.21;
    return parameters;
}

}

RobotKinematics::RobotKinematics()
    : m_context(HK_CreateContext())
{
    if (m_context == nullptr) {
        m_initializationError = QStringLiteral("无法创建机器人正解上下文");
        return;
    }

    const HK_RobotParameters parameters = createDefaultRobotParameters();
    if (HK_SetRobotParameters(m_context, &parameters) != 0) {
        m_initializationError = QStringLiteral("无法设置机器人机构参数");
        HK_DestroyContext(m_context);
        m_context = nullptr;
    }
}

RobotKinematics::~RobotKinematics()
{
    if (m_context != nullptr) {
        HK_DestroyContext(m_context);
    }
}

bool RobotKinematics::forward5Axis(
    const std::array<double, 5> &joints,
    RobotTcpPose &pose, QString &errorMessage) const
{
    pose = {};
    errorMessage.clear();
    if (m_context == nullptr) {
        errorMessage = m_initializationError.isEmpty()
            ? QStringLiteral("机器人正解上下文不可用")
            : m_initializationError;
        return false;
    }

    ForwardResult result;
    const int returnCode = HK_ForwardKinematicsResult5Axis(
        m_context, joints.data(), &result);
    if (returnCode != 0 || !result.ok || result.uiPose.size() < 5) {
        errorMessage = QStringLiteral("五轴正解失败，返回码：%1")
                           .arg(returnCode);
        return false;
    }

    pose.x = result.uiPose[0];
    pose.y = result.uiPose[1];
    pose.z = result.uiPose[2];
    pose.rx = result.uiPose[3];
    pose.ry = result.uiPose[4];
    return true;
}
