#include "geometrycalculator.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <limits>

namespace {
constexpr double kPi = 3.14159265358979323846;
constexpr double kSmallValue = 1.0e-12;

struct Vector3
{
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};

Vector3 operator+(const Vector3 &left, const Vector3 &right)
{
    return {left.x + right.x, left.y + right.y, left.z + right.z};
}

Vector3 operator-(const Vector3 &left, const Vector3 &right)
{
    return {left.x - right.x, left.y - right.y, left.z - right.z};
}

Vector3 operator*(const Vector3 &value, double scale)
{
    return {value.x * scale, value.y * scale, value.z * scale};
}

double dot(const Vector3 &left, const Vector3 &right)
{
    return left.x * right.x + left.y * right.y + left.z * right.z;
}

Vector3 cross(const Vector3 &left, const Vector3 &right)
{
    return {
        left.y * right.z - left.z * right.y,
        left.z * right.x - left.x * right.z,
        left.x * right.y - left.y * right.x
    };
}

double length(const Vector3 &value)
{
    return std::sqrt(dot(value, value));
}

Vector3 normalized(const Vector3 &value)
{
    const double valueLength = length(value);
    if (valueLength <= kSmallValue) {
        return {};
    }
    return value * (1.0 / valueLength);
}

Vector3 toVector(const GeometryPoint &point)
{
    return {point.x, point.y, point.z};
}

GeometryPoint toPoint(const Vector3 &value)
{
    return {value.x, value.y, value.z};
}

double radiansToDegrees(double radians)
{
    return radians * 180.0 / kPi;
}

// Jacobi 迭代用于求三阶对称矩阵的特征值和特征向量。
void eigenDecomposition(double matrix[3][3],
                        double eigenVectors[3][3],
                        double eigenValues[3])
{
    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 3; ++column) {
            eigenVectors[row][column] = (row == column) ? 1.0 : 0.0;
        }
    }

    for (int iteration = 0; iteration < 40; ++iteration) {
        int p = 0;
        int q = 1;
        double largest = std::abs(matrix[p][q]);
        for (const auto pair : {std::array<int, 2>{0, 2},
                                std::array<int, 2>{1, 2}}) {
            const double candidate =
                std::abs(matrix[pair[0]][pair[1]]);
            if (candidate > largest) {
                largest = candidate;
                p = pair[0];
                q = pair[1];
            }
        }

        const double diagonalScale =
            std::max({1.0, std::abs(matrix[0][0]),
                      std::abs(matrix[1][1]), std::abs(matrix[2][2])});
        if (largest <= diagonalScale * 1.0e-15) {
            break;
        }

        const double angle = 0.5 * std::atan2(
            2.0 * matrix[p][q], matrix[q][q] - matrix[p][p]);
        const double cosine = std::cos(angle);
        const double sine = std::sin(angle);
        const double pp = matrix[p][p];
        const double qq = matrix[q][q];
        const double pq = matrix[p][q];

        for (int index = 0; index < 3; ++index) {
            if (index == p || index == q) {
                continue;
            }
            const double ip = matrix[index][p];
            const double iq = matrix[index][q];
            matrix[index][p] = matrix[p][index] =
                cosine * ip - sine * iq;
            matrix[index][q] = matrix[q][index] =
                sine * ip + cosine * iq;
        }

        matrix[p][p] = cosine * cosine * pp -
                       2.0 * sine * cosine * pq +
                       sine * sine * qq;
        matrix[q][q] = sine * sine * pp +
                       2.0 * sine * cosine * pq +
                       cosine * cosine * qq;
        matrix[p][q] = matrix[q][p] = 0.0;

        for (int row = 0; row < 3; ++row) {
            const double vp = eigenVectors[row][p];
            const double vq = eigenVectors[row][q];
            eigenVectors[row][p] = cosine * vp - sine * vq;
            eigenVectors[row][q] = sine * vp + cosine * vq;
        }
    }

    for (int index = 0; index < 3; ++index) {
        eigenValues[index] = matrix[index][index];
    }
}

// 使用带主元的高斯消元求解三元一次方程组。
bool solveThreeByThree(const double coefficients[3][3],
                       const double values[3],
                       double result[3])
{
    double augmented[3][4]{};
    double scale = 1.0;
    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 3; ++column) {
            augmented[row][column] = coefficients[row][column];
            scale = std::max(scale, std::abs(coefficients[row][column]));
        }
        augmented[row][3] = values[row];
    }

    for (int column = 0; column < 3; ++column) {
        int pivotRow = column;
        for (int row = column + 1; row < 3; ++row) {
            if (std::abs(augmented[row][column]) >
                std::abs(augmented[pivotRow][column])) {
                pivotRow = row;
            }
        }
        if (std::abs(augmented[pivotRow][column]) <= scale * 1.0e-14) {
            return false;
        }
        if (pivotRow != column) {
            for (int index = column; index < 4; ++index) {
                std::swap(augmented[column][index],
                          augmented[pivotRow][index]);
            }
        }

        const double pivot = augmented[column][column];
        for (int index = column; index < 4; ++index) {
            augmented[column][index] /= pivot;
        }
        for (int row = 0; row < 3; ++row) {
            if (row == column) {
                continue;
            }
            const double factor = augmented[row][column];
            for (int index = column; index < 4; ++index) {
                augmented[row][index] -= factor * augmented[column][index];
            }
        }
    }

    for (int index = 0; index < 3; ++index) {
        result[index] = augmented[index][3];
    }
    return true;
}

struct Point2
{
    double x = 0.0;
    double y = 0.0;
};

// 先做代数圆拟合，再用少量 Gauss-Newton 迭代减小几何距离误差。
bool fitCircleInPlane(const std::vector<Point2> &points,
                      double &centerX, double &centerY, double &radius)
{
    double coefficients[3][3]{};
    double values[3]{};
    for (const Point2 &point : points) {
        const double row[3]{point.x, point.y, 1.0};
        const double target = -(point.x * point.x + point.y * point.y);
        for (int i = 0; i < 3; ++i) {
            values[i] += row[i] * target;
            for (int j = 0; j < 3; ++j) {
                coefficients[i][j] += row[i] * row[j];
            }
        }
    }

    double algebraic[3]{};
    if (!solveThreeByThree(coefficients, values, algebraic)) {
        return false;
    }

    centerX = -0.5 * algebraic[0];
    centerY = -0.5 * algebraic[1];
    const double radiusSquared =
        centerX * centerX + centerY * centerY - algebraic[2];
    if (radiusSquared <= kSmallValue) {
        return false;
    }
    radius = std::sqrt(radiusSquared);

    for (int iteration = 0; iteration < 12; ++iteration) {
        double normalMatrix[3][3]{};
        double rightHandSide[3]{};
        for (const Point2 &point : points) {
            const double dx = centerX - point.x;
            const double dy = centerY - point.y;
            const double distance = std::hypot(dx, dy);
            if (distance <= kSmallValue) {
                continue;
            }
            const double jacobian[3]{dx / distance, dy / distance, -1.0};
            const double residual = distance - radius;
            for (int i = 0; i < 3; ++i) {
                rightHandSide[i] -= jacobian[i] * residual;
                for (int j = 0; j < 3; ++j) {
                    normalMatrix[i][j] += jacobian[i] * jacobian[j];
                }
            }
        }

        double update[3]{};
        if (!solveThreeByThree(normalMatrix, rightHandSide, update)) {
            break;
        }
        centerX += update[0];
        centerY += update[1];
        radius += update[2];
        if (std::hypot(update[0], update[1]) < 1.0e-12 &&
            std::abs(update[2]) < 1.0e-12) {
            break;
        }
    }

    return std::isfinite(centerX) && std::isfinite(centerY) &&
           std::isfinite(radius) && radius > kSmallValue;
}
}

CircleFitResult GeometryCalculator::fitCircle(
    const std::vector<GeometryPoint> &points,
    const GeometryPoint &trackerOrigin)
{
    CircleFitResult result;
    if (points.size() < 3) {
        result.errorMessage = QStringLiteral("至少需要采集 3 个圆周点。");
        return result;
    }

    Vector3 centroid;
    for (const GeometryPoint &point : points) {
        centroid = centroid + toVector(point);
    }
    centroid = centroid * (1.0 / static_cast<double>(points.size()));

    double covariance[3][3]{};
    for (const GeometryPoint &point : points) {
        const Vector3 delta = toVector(point) - centroid;
        const double values[3]{delta.x, delta.y, delta.z};
        for (int row = 0; row < 3; ++row) {
            for (int column = 0; column < 3; ++column) {
                covariance[row][column] +=
                    values[row] * values[column];
            }
        }
    }

    double eigenVectors[3][3]{};
    double eigenValues[3]{};
    eigenDecomposition(covariance, eigenVectors, eigenValues);

    std::array<int, 3> order{0, 1, 2};
    std::sort(order.begin(), order.end(),
              [&eigenValues](int left, int right) {
                  return eigenValues[left] < eigenValues[right];
              });
    const double largestEigenValue =
        std::max(0.0, eigenValues[order[2]]);
    const double middleEigenValue =
        std::max(0.0, eigenValues[order[1]]);
    if (largestEigenValue <= kSmallValue ||
        middleEigenValue <= largestEigenValue * 1.0e-10) {
        result.errorMessage =
            QStringLiteral("采集点几乎重合或位于同一直线上，无法拟合圆。");
        return result;
    }

    Vector3 normal = normalized({
        eigenVectors[0][order[0]],
        eigenVectors[1][order[0]],
        eigenVectors[2][order[0]]
    });

    // 特征向量有正负两个方向，这里选择指向激光跟踪仪的一侧。
    const Vector3 trackerDirection = toVector(trackerOrigin) - centroid;
    const double directionDot = dot(normal, trackerDirection);
    if (directionDot < 0.0 ||
        (std::abs(directionDot) <= kSmallValue && normal.z < 0.0)) {
        normal = normal * -1.0;
    }

    const Vector3 reference =
        (std::abs(normal.z) < 0.9) ? Vector3{0.0, 0.0, 1.0}
                                   : Vector3{1.0, 0.0, 0.0};
    const Vector3 axisU = normalized(cross(reference, normal));
    const Vector3 axisV = normalized(cross(normal, axisU));

    std::vector<Point2> projectedPoints;
    projectedPoints.reserve(points.size());
    double planeErrorSquared = 0.0;
    for (const GeometryPoint &point : points) {
        const Vector3 delta = toVector(point) - centroid;
        projectedPoints.push_back({dot(delta, axisU), dot(delta, axisV)});
        const double planeDistance = dot(delta, normal);
        planeErrorSquared += planeDistance * planeDistance;
    }

    double localCenterX = 0.0;
    double localCenterY = 0.0;
    if (!fitCircleInPlane(projectedPoints, localCenterX,
                          localCenterY, result.radius)) {
        result.errorMessage =
            QStringLiteral("圆拟合失败，请增加分布均匀的圆周采集点。");
        return result;
    }

    const Vector3 center =
        centroid + axisU * localCenterX + axisV * localCenterY;
    double circleErrorSquared = 0.0;
    for (const Point2 &point : projectedPoints) {
        const double residual =
            std::hypot(point.x - localCenterX,
                       point.y - localCenterY) - result.radius;
        circleErrorSquared += residual * residual;
        result.maximumResidual =
            std::max(result.maximumResidual, std::abs(residual));
    }

    result.center = toPoint(center);
    result.normal = toPoint(normal);
    result.planeRms =
        std::sqrt(planeErrorSquared / static_cast<double>(points.size()));
    result.circleRms =
        std::sqrt(circleErrorSquared / static_cast<double>(points.size()));

    // 固定轴 X→Y→Z 欧拉角约定；用户不需要绕法向旋转，所以 C 固定为 0。
    result.angleA = radiansToDegrees(
        std::asin(std::clamp(-normal.y, -1.0, 1.0)));
    result.angleB = radiansToDegrees(std::atan2(normal.x, normal.z));
    result.angleC = 0.0;
    result.success = true;
    return result;
}
