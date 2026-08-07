#ifndef HK_API_H
#define HK_API_H

#ifdef _WIN32
#  ifdef HK_LIBRARY
#    define HK_API __declspec(dllexport)
#  else
#    define HK_API __declspec(dllimport)
#  endif
#  define HK_CALL __cdecl
#else
#  define HK_API __attribute__((visibility("default")))
#  define HK_CALL
#endif

#ifdef __cplusplus
#include <vector>

/**
 * @brief 正解完整输出结果。
 * @use 五轴 uiPose、movingPlatformPose、connPose 为 [x,y,z,rx,ry]。
 * @use 六轴 uiPose、movingPlatformPose、connPose 为 [x,y,z,rx,ry,rz]。
 * @use st2Pose 始终为 [x,y,z,rx,ry,rz]。
 * @use gimbal1Angles、gimbal2Angles、gimbal3Angles 为 [rx,ry,rz]，单位为度。
 */
struct ForwardResult
{
    // 正解是否成功
    bool ok = false;
    // UI端使用的末端位姿，五轴5个值，六轴6个值。
    std::vector<double> uiPose;
    // 动平台中心位姿，五轴5个值，六轴6个值。
    std::vector<double> movingPlatformPose;
    // 三个支链连接共同点位姿，五轴5个值，六轴6个值。
    std::vector<double> connPose;
    // 万向节1安装坐标系姿态，[rx,ry,rz]，单位为度
    std::vector<double> gimbal1Angles;
    // 万向节2安装坐标系姿态，[rx,ry,rz]，单位为度
    std::vector<double> gimbal2Angles;
    // 万向节3安装坐标系姿态，[rx,ry,rz]，单位为度
    std::vector<double> gimbal3Angles;
    // 支链2空间中的 pp2 位姿，[x,y,z,rx,ry,rz]
    std::vector<double> st2Pose;
};

/**
 * @brief 逆解完整输出结果。
 * @use jointValues 五轴为 [ST1,ST2,ST3,C,A]，六轴为 [ST1,ST2,ST3,C,A,B]。
 * @use movingPlatformPose、connPose 五轴5个值，六轴6个值。
 * @use st2Pose 始终为 [x,y,z,rx,ry,rz]。
 * @use solutionStatus: 0=可达，1=不可达，2=奇异，3=未计算。
 */
struct InverseResult
{
    bool ok = false;
    int solutionStatus = 0;
    std::vector<double> jointValues;
    std::vector<double> movingPlatformPose;
    std::vector<double> connPose;
    std::vector<double> gimbal1Angles;
    std::vector<double> gimbal2Angles;
    std::vector<double> gimbal3Angles;
    std::vector<double> st2Pose;
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 机器人结构参数。
 * @use 参数 L1-L19 的顺序与 Component::accroding_L_setParameters 一致。
 */
typedef struct HK_RobotParameters
{
    double L1;
    double L2;
    double L3;
    double L4;
    double L5;
    double L6;
    double L7;
    double L8;
    double L9;
    double L10;
    double L11;
    double L12;
    double L13;
    double L14;
    double L15;
    double L16;
    double L17;
    double L18;
    double L19;
} HK_RobotParameters;

/**
 * @brief 独立计算上下文。
 * @use 不同线程可以同时使用不同的 HK_Context 对象进行并行计算。
 */
typedef struct HK_Context HK_Context;

/**
 * @brief 创建独立计算上下文。
 * @use 每个线程可以创建自己的上下文用于并行计算。
 * @return 成功返回上下文指针，失败返回 nullptr。
 */
HK_API HK_Context* HK_CALL HK_CreateContext(void);

/**
 * @brief 销毁独立计算上下文。
 * @param context HK_CreateContext 返回的上下文指针。
 */
HK_API void HK_CALL HK_DestroyContext(HK_Context* context);

/**
 * @brief 获取独立上下文中的机器人参数。
 * @param context HK_CreateContext 返回的上下文指针，不能为空。
 * @param params 输出机器人参数结构体，不能为空。
 * @return 0-成功，-1-失败。
 */
HK_API int HK_CALL HK_GetRobotParameters(
    HK_Context* context, HK_RobotParameters* params);

/**
 * @brief 设置独立上下文中的机器人参数。
 * @param context HK_CreateContext 返回的上下文指针，不能为空。
 * @param params 机器人参数结构体，不能为空。
 * @return 0-成功，-1-失败。
 */
HK_API int HK_CALL HK_SetRobotParameters(
    HK_Context* context, const HK_RobotParameters* params);

/**
 * @brief 按数值设置独立上下文中的机器人参数。
 * @param context HK_CreateContext 返回的上下文指针，不能为空。
 * @use 参数顺序与 Component::accroding_L_setParameters 一致。
 * @return 0-成功，-1-失败。
 */
HK_API int HK_CALL HK_SetRobotParametersByValues(
    HK_Context* context,
    double L1, double L2, double L3, double L4, double L5,
    double L6, double L7, double L8, double L9, double L10,
    double L11, double L12, double L13, double L14, double L15,
    double L16, double L17, double L18, double L19);

/**
 * @brief 使用独立上下文计算五轴机器人正解。
 * @param context HK_CreateContext 返回的上下文指针，不能为空。
 * @param joint_values 输入关节值数组，必须为5个值: [ST1,ST2,ST3,C,A]。
 * @param pose 输出末端位姿数组，必须预留5个值: [x,y,z,rx,ry]。
 * @return 0-成功，-1-失败。
 */
HK_API int HK_CALL HK_ForwardKinematics5Axis(
    HK_Context* context, const double joint_values[5], double pose[5]);

/**
 * @brief 使用独立上下文计算六轴机器人正解。
 * @param context HK_CreateContext 返回的上下文指针，不能为空。
 * @param joint_values 输入关节值数组，必须为6个值: [ST1,ST2,ST3,C,A,B]。
 * @param pose 输出末端位姿数组，必须预留6个值: [x,y,z,rx,ry,rz]。
 * @return 0-成功，-1-失败。
 */
HK_API int HK_CALL HK_ForwardKinematics6Axis(
    HK_Context* context, const double joint_values[6], double pose[6]);

/**
 * @brief 使用独立上下文计算机器人正解。
 * @param context HK_CreateContext 返回的上下文指针，不能为空。
 * @param axis_count 轴数，只支持5或6。
 * @param joint_values 输入关节值数组。axis_count=5时必须为5个值，axis_count=6时必须为6个值。
 * @param pose 输出末端位姿数组。axis_count=5时必须预留5个值，axis_count=6时必须预留6个值。
 * @return 0-成功，-1-失败。
 */
HK_API int HK_CALL HK_ForwardKinematics(
    HK_Context* context, int axis_count, const double* joint_values, double* pose);

/**
 * @brief 使用独立上下文计算五轴机器人逆解。
 * @param context HK_CreateContext 返回的上下文指针，不能为空。
 * @param pose 输入末端位姿数组，必须为5个值: [x,y,z,rx,ry]。
 * @param joint_values 输出关节值数组，必须预留5个值: [ST1,ST2,ST3,C,A]。
 * @return 0-成功，-1-失败。
 */
HK_API int HK_CALL HK_InverseKinematics5Axis(
    HK_Context* context, const double pose[5], double joint_values[5]);

/**
 * @brief 使用独立上下文计算六轴机器人逆解。
 * @param context HK_CreateContext 返回的上下文指针，不能为空。
 * @param pose 输入末端位姿数组，必须为6个值: [x,y,z,rx,ry,rz]。
 * @param joint_values 输出关节值数组，必须预留6个值: [ST1,ST2,ST3,C,A,B]。
 * @return 0-成功，-1-失败。
 */
HK_API int HK_CALL HK_InverseKinematics6Axis(
    HK_Context* context, const double pose[6], double joint_values[6]);

/**
 * @brief 使用独立上下文计算机器人逆解。
 * @param context HK_CreateContext 返回的上下文指针，不能为空。
 * @param axis_count 轴数，只支持5或6。
 * @param pose 输入末端位姿数组。axis_count=5时必须为5个值，axis_count=6时必须为6个值。
 * @param joint_values 输出关节值数组。axis_count=5时必须预留5个值，axis_count=6时必须预留6个值。
 * @return 0-成功，-1-失败。
 */
HK_API int HK_CALL HK_InverseKinematics(
    HK_Context* context, int axis_count, const double* pose, double* joint_values);

/**
 * @brief 获取独立上下文中上一次逆解状态。
 * @param context HK_CreateContext 返回的上下文指针，不能为空。
 * @param status 输出状态值，不能为空。
 * @return 0-成功，-1-失败。
 */
HK_API int HK_CALL HK_GetLastSolutionStatus(
    HK_Context* context, int* status);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/**
 * @brief 使用独立上下文计算五轴机器人完整正解结果。
 * @param context HK_CreateContext 返回的上下文指针，不能为空。
 * @param joint_values 输入关节值数组，必须为5个值: [ST1,ST2,ST3,C,A]。
 * @param result 输出完整正解结果，不能为空。
 * @use result 使用本头文件中的 ForwardResult 结构。
 * @use uiPose、movingPlatformPose、connPose 为 [x,y,z,rx,ry]。
 * @use st2Pose 为 [x,y,z,rx,ry,rz]。
 * @return 0-成功，-1-失败。
 */
HK_API int HK_CALL HK_ForwardKinematicsResult5Axis(
    HK_Context* context, const double joint_values[5], ForwardResult* result);

/**
 * @brief 使用独立上下文计算六轴机器人完整正解结果。
 * @param context HK_CreateContext 返回的上下文指针，不能为空。
 * @param joint_values 输入关节值数组，必须为6个值: [ST1,ST2,ST3,C,A,B]。
 * @param result 输出完整正解结果，不能为空。
 * @use result 使用本头文件中的 ForwardResult 结构。
 * @use uiPose、movingPlatformPose、connPose、st2Pose 为 [x,y,z,rx,ry,rz]。
 * @return 0-成功，-1-失败。
 */
HK_API int HK_CALL HK_ForwardKinematicsResult6Axis(
    HK_Context* context, const double joint_values[6], ForwardResult* result);

/**
 * @brief 使用独立上下文计算机器人完整正解结果。
 * @param context HK_CreateContext 返回的上下文指针，不能为空。
 * @param axis_count 轴数，只支持5或6。
 * @param joint_values 输入关节值数组。axis_count=5时必须为5个值，axis_count=6时必须为6个值。
 * @param result 输出完整正解结果，不能为空。
 * @use result 使用本头文件中的 ForwardResult 结构。
 * @use 五轴 uiPose、movingPlatformPose、connPose 为5个值；六轴为6个值。st2Pose 始终为6个值。
 * @return 0-成功，-1-失败。
 */
HK_API int HK_CALL HK_ForwardKinematicsResult(
    HK_Context* context, int axis_count, const double* joint_values, ForwardResult* result);

/**
 * @brief 使用独立上下文计算五轴机器人完整逆解结果。
 * @param context HK_CreateContext 返回的上下文指针，不能为空。
 * @param pose 输入末端位姿数组，必须为5个值: [x,y,z,rx,ry]。
 * @param result 输出完整逆解结果，不能为空。
 * @use result->jointValues 为 [ST1,ST2,ST3,C,A]。
 */
HK_API int HK_CALL HK_InverseKinematicsResult5Axis(
    HK_Context* context, const double pose[5], InverseResult* result);

/**
 * @brief 使用独立上下文计算六轴机器人完整逆解结果。
 * @param context HK_CreateContext 返回的上下文指针，不能为空。
 * @param pose 输入末端位姿数组，必须为6个值: [x,y,z,rx,ry,rz]。
 * @param result 输出完整逆解结果，不能为空。
 * @use result->jointValues 为 [ST1,ST2,ST3,C,A,B]。
 */
HK_API int HK_CALL HK_InverseKinematicsResult6Axis(
    HK_Context* context, const double pose[6], InverseResult* result);

/**
 * @brief 使用独立上下文计算机器人完整逆解结果。
 * @param context HK_CreateContext 返回的上下文指针，不能为空。
 * @param axis_count 轴数，只支持5或6。
 * @param pose 输入末端位姿数组。axis_count=5时必须为5个值，axis_count=6时必须为6个值。
 * @param result 输出完整逆解结果，不能为空。
 */
HK_API int HK_CALL HK_InverseKinematicsResult(
    HK_Context* context, int axis_count, const double* pose, InverseResult* result);

#endif

#endif // HK_API_H
