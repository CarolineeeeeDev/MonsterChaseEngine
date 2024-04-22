#pragma once
#include <iostream>
#include <GLib.h>

using namespace std;

namespace Engine
{
    class Point2D {
    public:
        float x;
        float y;
        Point2D(float _x, float _y) : x(_x), y(_y) {}
        bool operator==(const Point2D& other) const {
            return x == other.x && y == other.y;
        }
        bool operator!=(const Point2D& other) const {
            return !(*this == other);
        }
        Point2D operator+(const Point2D& other) const {
            return Point2D(x + other.x, y + other.y);
        }
        Point2D operator-(const Point2D& other) const {
            return Point2D(x - other.x, y - other.y);
        }
        Point2D operator*(int scalar) const {
            return Point2D(x * scalar, y * scalar);
        }

        friend Point2D operator*(int scalar, const Point2D& point) {
            return Point2D(point.x * scalar, point.y * scalar);
        }
        Point2D operator/(int divisor) const {
            if (divisor != 0) {
                return Point2D(x / divisor, y / divisor);
            }
            else {
                cerr << "Division by zero!" << endl;
                return *this;
            }
        }
        Point2D operator-() const {
            return Point2D(-x, -y);
        }
        Point2D& operator+=(const Point2D& other) {
            x += other.x;
            y += other.y;
            return *this;
        }
        Point2D& operator-=(const Point2D& other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }
        Point2D& operator*=(int scalar) {
            x *= scalar;
            y *= scalar;
            return *this;
        }
        Point2D& operator/=(int divisor) {
            if (divisor != 0) {
                x /= divisor;
                y /= divisor;
            }
            else {
                cerr << "Division by zero!" << endl;
            }
            return *this;
        }
    };
}
