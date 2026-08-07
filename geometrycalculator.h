#pragma once

#include <QString>

#include <vector>

struct GeometryPoint
{
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};

struct CircleFitResult
{
    bool success = false;
    QString errorMessage;
    GeometryPoint center;
    GeometryPoint normal;
    double angleA = 0.0;
    double angleB = 0.0;
    double angleC = 0.0;
    double radius = 0.0;
    double planeRms = 0.0;
    double circleRms = 0.0;
    double maximumResidual = 0.0;
};

class GeometryCalculator final
{
public:
    // 根据三维圆周点拟合平面和圆，并让法向朝向激光跟踪仪。
    static CircleFitResult fitCircle(
        const std::vector<GeometryPoint> &points,
        const GeometryPoint &trackerOrigin);
};
