#pragma once

#include <cmath>

namespace Engine {
    namespace Math {

        class Vector3 {
        public:
            Vector3() : m_x(0), m_y(0), m_z(0) {}
            Vector3(float i_x, float i_y, float i_z) : m_x(i_x), m_y(i_y), m_z(i_z) {}

            Vector3(const Vector3& i_other) = default;
            Vector3& operator=(const Vector3& i_other) = default;

            float x() const { return m_x; }
            float y() const { return m_y; }
            float z() const { return m_z; }

            void x(float i_x) { m_x = i_x; }
            void y(float i_y) { m_y = i_y; }
            void z(float i_z) { m_z = i_z; }

            Vector3& operator+=(const Vector3& i_rhs) {
                m_x += i_rhs.m_x;
                m_y += i_rhs.m_y;
                m_z += i_rhs.m_z;
                return *this;
            }

            Vector3& operator-=(const Vector3& i_rhs) {
                m_x -= i_rhs.m_x;
                m_y -= i_rhs.m_y;
                m_z -= i_rhs.m_z;
                return *this;
            }

            Vector3& operator*=(float i_scalar) {
                m_x *= i_scalar;
                m_y *= i_scalar;
                m_z *= i_scalar;
                return *this;
            }

            Vector3& operator/=(float i_scalar) {
                m_x /= i_scalar;
                m_y /= i_scalar;
                m_z /= i_scalar;
                return *this;
            }

            Vector3 operator-() const {
                return Vector3(-m_x, -m_y, -m_z);
            }

            void Normalize() {
                float length = Length();
                if (length != 0) {
                    *this /= length;
                }
            }

            Vector3 Normalized() const {
                Vector3 temp(*this);
                temp.Normalize();
                return temp;
            }

            float Length() const {
                return sqrt(LengthSq());
            }

            float LengthSq() const {
                return m_x * m_x + m_y * m_y + m_z * m_z;
            }

            static const Vector3 Zero;

            float m_x, m_y, m_z;
        };

        inline Vector3 operator+(const Vector3& i_lhs, const Vector3& i_rhs) {
            return Vector3(i_lhs.m_x + i_rhs.m_x, i_lhs.m_y + i_rhs.m_y, i_lhs.m_z + i_rhs.m_z);
        }

        inline Vector3 operator-(const Vector3& i_lhs, const Vector3& i_rhs) {
            return Vector3(i_lhs.m_x - i_rhs.m_x, i_lhs.m_y - i_rhs.m_y, i_lhs.m_z - i_rhs.m_z);
        }

        inline Vector3 operator*(const Vector3& i_vec, float i_scalar) {
            return Vector3(i_vec.m_x * i_scalar, i_vec.m_y * i_scalar, i_vec.m_z * i_scalar);
        }

        inline Vector3 operator*(float i_scalar, const Vector3& i_vec) {
            return Vector3(i_scalar * i_vec.m_x, i_scalar * i_vec.m_y, i_scalar * i_vec.m_z);
        }

        inline float dot(const Vector3& i_lhs, const Vector3& i_rhs) {
            return i_lhs.m_x * i_rhs.m_x + i_lhs.m_y * i_rhs.m_y + i_lhs.m_z * i_rhs.m_z;
        }

        inline Vector3 cross(const Vector3& i_lhs, const Vector3& i_rhs) {
            return Vector3(
                i_lhs.m_y * i_rhs.m_z - i_lhs.m_z * i_rhs.m_y,
                i_lhs.m_z * i_rhs.m_x - i_lhs.m_x * i_rhs.m_z,
                i_lhs.m_x * i_rhs.m_y - i_lhs.m_y * i_rhs.m_x
            );
        }

        inline bool operator==(const Vector3& i_lhs, const Vector3& i_rhs) {
            return i_lhs.m_x == i_rhs.m_x && i_lhs.m_y == i_rhs.m_y && i_lhs.m_z == i_rhs.m_z;
        }

        inline bool operator!=(const Vector3& i_lhs, const Vector3& i_rhs) {
            return !(i_lhs == i_rhs);
        }
    } 
} 
