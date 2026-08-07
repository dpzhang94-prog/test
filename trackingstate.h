#pragma once

#include <QMetaType>

// 反射球跟踪状态。
// Unknown 表示样本不足，Tracking 表示坐标正常更新，Lost 表示坐标连续冻结。
enum class TrackingState {
    Unknown,
    Tracking,
    Lost
};

Q_DECLARE_METATYPE(TrackingState)
