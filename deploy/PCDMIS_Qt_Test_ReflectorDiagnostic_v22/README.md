# PC-DMIS Qt 坐标读取测试

这是一个 Windows Qt 6 Widgets 测试程序，通过 PC-DMIS Automation COM 接口读取
激光跟踪仪坐标。界面中的“坐标来源”下拉框支持两种模式：

- “仪器坐标”：定时读取 `Machine.ProbePosition` 的 X、Y、Z。
- “当前 PC-DMIS 对齐坐标”：读取 `Machine.ProbePosition` 后，使用当前活动对齐的
  `MachineToPartMatrix` 转换为零件坐标。程序读取矩阵的 `Item(1)..Item(12)`，
  并在 Qt 内按照“各对齐轴点乘（仪器坐标减 Offset）”完成转换。

数据单位由 PC-DMIS 当前设置决定。

矩阵模式不依赖 `ReadoutExt` 实时事件、探头读数窗口设置，也不需要把
`PointData` 对象传回 PC-DMIS，适用于 PC-DMIS 2017 R1/AT403 环境。

连接到 PC-DMIS 后，程序还会监听 `Machine.ErrorMsg`。当 PC-DMIS 报告
`ERROR_TYPE_REFLECTOR_NOT_FOUND`（`ErrorType=2`）时，程序在日志中提示
“未找到反射球，当前坐标可能无效”。该诊断只记录 PC-DMIS 主动上报的错误，
不会停止坐标读取、弹出警告框或修改坐标结果。

## 圆心与法向计算

主界面的“圆心与法向计算”用于手动采集圆周点：

1. 选择仪器坐标或当前 PC-DMIS 对齐坐标。
2. 将靶球依次放到圆周上的不同位置，点击“采集当前点”。
3. 至少采集 3 点，实际建议采集 6 点以上并尽量均匀分布。
4. 点击“计算圆心与姿态”。

程序使用最小二乘方法拟合平面，将点投影到平面后拟合圆。结果表格显示圆心
XYZ、固定轴 X→Y→Z 欧拉角 ABC、半径及拟合误差。法向自动选择朝向
激光跟踪仪的一侧；当前版本不计算绕法向的旋转，因此 C 固定为 0°。

几何计算集中在 `geometrycalculator.h/.cpp`，其中包含平面特征向量计算、二维
圆拟合及 A/B 角换算，并配有关键中文注释。

## 环境要求

- Windows 10/11
- Qt 6（MSVC 64 位），包含 ActiveQt/AxContainer
- PCL 1.12.1 附带的 VTK 9.1（默认路径 `D:/PCL1.12.1`，用于测试点 STL
  可达域过滤）
- PC-DMIS 已安装并授权
- PC-DMIS 已配置激光跟踪仪，能够在软件中正常连接、回零和显示坐标

## 测试点生成

主界面的“标定工具 → 测试点生成...”会打开从 PMT 项目移植的测试点页面。
关节组合、插值、0.5 小数选项、去重、STL 可达域过滤，以及 TXT、CSV、JBR
输出方式均保持原来的生成逻辑。

测试点页面左侧增加“激光跟踪仪可见性筛选”：

1. 先在主界面连接 PC-DMIS，并在 PC-DMIS 中激活与机器人基坐标一致的对齐。
2. 打开测试点页面，点击“获取/刷新位置”。程序复用主界面的 Automation
   连接，把跟踪仪机器坐标原点转换到当前活动对齐坐标系。
   如果只想离线检查界面和筛选流程，可点击“使用测试位置”。程序始终使用
   `X=0, Y=2000, Z=-5000 mm`，不根据 STL 自动计算，加载 STL 也不会修改
   该坐标。模拟位置不会访问 PC-DMIS，不能作为实测数据。
3. 输入 J6=0° 时靶球中心相对 TCP 的 X/Y/Z 安装偏移，并根据实际安装选择
   靶球开口方向。一般径向安装可选“沿 TCP → 靶球（径向）”。
4. 设置最大入射角和 J6 整周检查步长。
5. “预览筛选”和最终筛选明细位于底部“生成设置”区域。预览按当前复选框
   状态依次执行关节范围生成、去重、扩散区域过滤和 J6 整周过滤，并显示每个
   环节移除及剩余的点数。只有点击“预览筛选”才会重新计算这些统计。
   三维视图只显示最终保留的绿色 TCP，不再显示被剔除点。橙色球为跟踪仪
   原点，蓝色线框球为覆盖当前工作模型的测量范围，红色线框球为 0.8 m
   近场排除区。
   测试时可继续点击“导出保留位姿”，把最终保留点导出为 CSV。文件包含
   J1～J6、五轴正解 TCP 的 X/Y/Z（mm）、原始 RX/RY 角度，以及从姿态矩阵
   按标准 `R=Rz·Ry·Rx` 提取的 ZYX 三个角度。CSV 不再导出弧度列。
   关节范围、靶球参数或仪器位置改变后，旧预览会失效，必须重新预览再导出。
6. 勾选“生成时启用 J6 整周可见性筛选”后再生成文件。程序使用 J1～J5
   正解得到主轴中心 TCP 和姿态，不修改任何一个定位关节；随后将独立主轴
   J6 均匀模拟旋转 360°。靶球中心偏移和开口法向随 J6 一起绕 TCP 局部
   +Z 轴旋转，每个检查位置都满足 0.8～160 m 测距和反射球入射角限制时，
   才保留该关节点。

可见性计算使用五轴正解返回的 `[x,y,z,rx,ry]`，其中 `rx/ry` 按运动学 DLL
的实际输出使用弧度。TCP 按主轴中心处理，靶球中心由界面安装偏移计算；姿态
矩阵按 `R=Rx·Ry` 构造，再右乘绕 TCP 局部 +Z 轴的 J6 旋转。

相关代码按功能和第三方依赖分开存放：

- `features/testpoints/`：测试点页面、生成及文件输出逻辑。
- `thirdparty/kinematics/`：运动学头文件、导入库、运行时 DLL 和 qmake `.pri`。
- `thirdparty/vtk/vtk.pri`：qmake 使用的最小 VTK 依赖。

qmake 会通过 `thirdparty/kinematics/kinematics.pri` 导入运动学库，并在链接后
把 `HK_Kinematics.dll` 复制到程序输出目录。CMake 使用对应的 imported target
完成相同操作。

## 使用 Qt Creator（推荐使用 qmake，避开本机 CMake 异常）

1. 关闭 Qt Creator 中原来打开的 CMake 项目。
2. 用 Qt Creator 打开本目录的 `PCDMIS_Qt_Test.pro`。
3. 选择 `Desktop Qt 6.5.3 MSVC2019 64bit` Kit。
4. 在左下角构建配置中选择 `Release` 或 `Debug`。
5. 构建并运行。
6. 在 PC-DMIS 中配置并连接仪器。
7. 在本程序中点击“连接 PC-DMIS”。
8. 在“坐标来源”中选择仪器坐标或当前 PC-DMIS 对齐坐标。
9. 点击“读取一次”或“开始连续读取”。矩阵模式下，日志应显示已取得
   `Commands.CurrentAlignment` 和 `MachineToPartMatrix`。

本机的 Qt CMake 3.30.5 在重复配置 Visual Studio 构建目录时可能异常退出，
因此这个项目同时提供了 qmake 的 `.pro` 文件。程序源码和功能不受影响。

## 使用 CMake（可选）

如果使用 CMake，请先为每个配置准备一个全新的构建目录，不要把 Qt Creator 的
Ninja 构建和 Visual Studio 构建放进同一个目录：

1. 用 Qt Creator 打开本目录的 `CMakeLists.txt`。
2. 选择 `Desktop Qt 6.5.3 MSVC2019 64bit` Kit。
3. 在“项目 → 构建设置”中把 Release 构建目录改为一个新的目录，例如
   `build-PCDMIS_Qt_Test-Release`。
4. 如果 PCL 不在默认目录，为 CMake 增加配置参数，例如
   `-DPCL_ROOT=D:/your/path/PCL1.12.1`。

## 命令行构建

在 PowerShell 中执行（本机 Qt 自带的 CMake 路径如下）：

```powershell
& D:/Qt6.5.3/Tools/CMake_64/bin/cmake.exe -S . -B build-qt `
  -G "Visual Studio 17 2022" -A x64 `
  -DCMAKE_PREFIX_PATH=D:/Qt6.5.3/6.5.3/msvc2019_64
& D:/Qt6.5.3/Tools/CMake_64/bin/cmake.exe --build build-qt --config Debug
```

## 说明

- 程序连接的是 `PCDLRN.Application`，不是串口。
- 本程序不会直接控制 Leica 跟踪仪，也不需要 Leica 硬件 SDK。
- 程序不显示或查询激光跟踪仪底层驱动状态；是否可用以
  `ProbePosition` 能否持续返回有效坐标为准。
- 下拉框切换不会断开或重新创建 PC-DMIS COM 连接。
- 对齐坐标模式每隔约十次采样重新读取一次当前活动对齐矩阵，因此在 PC-DMIS
  中切换活动坐标系后无需重新连接。
- 如果 COM 对象创建失败，请优先检查 PC-DMIS 是否完整安装、许可证是否有效，
  以及程序位数是否与 PC-DMIS/Automation 组件兼容。
