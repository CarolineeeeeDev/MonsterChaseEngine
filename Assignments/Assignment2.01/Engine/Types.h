#pragma once
#include <iostream>
using namespace std;

namespace Engine
{
    class Point2D {
    public:
        int x;
        int y;

        // Constructor
        Point2D(int _x, int _y) : x(_x), y(_y) {}

        // Equality operator
        bool operator==(const Point2D& other) const {
            return x == other.x && y == other.y;
        }

        // Inequality operator
        bool operator!=(const Point2D& other) const {
            return !(*this == other);
        }

        // Addition operator
        Point2D operator+(const Point2D& other) const {
            return Point2D(x + other.x, y + other.y);
        }

        // Subtraction operator
        Point2D operator-(const Point2D& other) const {
            return Point2D(x - other.x, y - other.y);
        }

        // Multiplication by an integer
        Point2D operator*(int scalar) const {
            return Point2D(x * scalar, y * scalar);
        }

        friend Point2D operator*(int scalar, const Point2D& point) {
            return Point2D(point.x * scalar, point.y * scalar);
        }
        // Division by an integer
        Point2D operator/(int divisor) const {
            if (divisor != 0) {
                return Point2D(x / divisor, y / divisor);
            }
            else {
                // Handle division by zero
                cerr << "Division by zero!" << endl;
                return *this;
            }
        }

        // Negation operator
        Point2D operator-() const {
            return Point2D(-x, -y);
        }

        // Compound addition
        Point2D& operator+=(const Point2D& other) {
            x += other.x;
            y += other.y;
            return *this;
        }

        // Compound subtraction
        Point2D& operator-=(const Point2D& other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        // Compound multiplication by an integer
        Point2D& operator*=(int scalar) {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        // Compound division by an integer
        Point2D& operator/=(int divisor) {
            if (divisor != 0) {
                x /= divisor;
                y /= divisor;
            }
            else {
                // Handle division by zero
                cerr << "Division by zero!" << endl;
            }
            return *this;
        }
    };
}


class Monster
{
public:
    Engine::Point2D position;
    Monster(Engine::Point2D _position)
        : position(_position) { }
};

class Player
{
public:
    string name;
    Engine::Point2D position;
    bool bQuit;
    bool isGameOver;
    Engine::Point2D drivingForce2D;
    Player(string _name, Engine::Point2D _position, bool _bQuit, bool _isGameOver, Engine::Point2D _drivingForce2D)
        :name(_name), position(_position), bQuit(_bQuit), isGameOver(_isGameOver), drivingForce2D(_drivingForce2D) {}
};
