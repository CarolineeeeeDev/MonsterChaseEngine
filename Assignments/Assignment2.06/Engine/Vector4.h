#pragma once
#include "Vector3.h" 
#include <cmath>     

namespace Engine {
    namespace Math {

        class Vector4 {
        public:
            Vector4() : m_x(0), m_y(0), m_z(0), m_w(0) {}
            Vector4(float i_x, float i_y, float i_z, float i_w) : m_x(i_x), m_y(i_y), m_z(i_z), m_w(i_w) {}
            Vector4(const Vector3& i_other, float i_w = 1.0f) : m_x(i_other.x()), m_y(i_other.y()), m_z(i_other.z()), m_w(i_w) {}

            Vector4(const Vector4& i_other) = default;
            Vector4& operator=(const Vector4& i_other) = default;

            float x() const { return m_x; }
            float y() const { return m_y; }
            float z() const { return m_z; }
            float w() const { return m_w; }

            void x(float i_x) { m_x = i_x; }
            void y(float i_y) { m_y = i_y; }
            void z(float i_z) { m_z = i_z; }
            void w(float i_w) { m_w = i_w; }

            Vector4& operator+=(const Vector4& rhs) {
                m_x += rhs.m_x;
                m_y += rhs.m_y;
                m_z += rhs.m_z;
                m_w += rhs.m_w;
                return *this;
            }

            Vector4& operator-=(const Vector4& rhs) {
                m_x -= rhs.m_x;
                m_y -= rhs.m_y;
                m_z -= rhs.m_z;
                m_w -= rhs.m_w;
                return *this;
            }

            Vector4& operator*=(float scalar) {
                m_x *= scalar;
                m_y *= scalar;
                m_z *= scalar;
                m_w *= scalar;
                return *this;
            }

            Vector4& operator/=(float scalar) {
                m_x /= scalar;
                m_y /= scalar;
                m_z /= scalar;
                m_w /= scalar;
                return *this;
            }

            Vector4 operator-() const {
                return Vector4(-m_x, -m_y, -m_z, -m_w);
            }

            void Normalize() {
                float len = Length();
                if (len != 0) {
                    *this /= len;
                }
            }

            Vector4 Normalized() const {
                Vector4 result(*this);
                result.Normalize();
                return result;
            }

            float Length() const {
                return std::sqrt(LengthSq());
            }

            float LengthSq() const {
                return m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w;
            }

            static const Vector4 Zero;

            float m_x, m_y, m_z, m_w;
        };

        inline Vector4 operator+(const Vector4& lhs, const Vector4& rhs) {
            return Vector4(lhs.m_x + rhs.m_x, lhs.m_y + rhs.m_y, lhs.m_z + rhs.m_z, lhs.m_w + rhs.m_w);
        }

        inline Vector4 operator-(const Vector4& lhs, const Vector4& rhs) {
            return Vector4(lhs.m_x - rhs.m_x, lhs.m_y - rhs.m_y, lhs.m_z - rhs.m_z, lhs.m_w - rhs.m_w);
        }

        inline Vector4 operator*(const Vector4& vec, float scalar) {
            return Vector4(vec.m_x * scalar, vec.m_y * scalar, vec.m_z * scalar, vec.m_w * scalar);
        }

        inline Vector4 operator*(float scalar, const Vector4& vec) {
            return Vector4(scalar * vec.m_x, scalar * vec.m_y, scalar * vec.m_z, scalar * vec.m_w);
        }

        inline bool operator==(const Vector4& lhs, const Vector4& rhs) {
            return lhs.m_x == rhs.m_x && lhs.m_y == rhs.m_y && lhs.m_z == rhs.m_z && lhs.m_w == rhs.m_w;
        }

        inline bool operator!=(const Vector4& lhs, const Vector4& rhs) {
            return !(lhs == rhs);
        }
    } 
} 


namespace Engine {
    namespace Math {
        const Vector4 Vector4::Zero(0.0f, 0.0f, 0.0f, 0.0f);
    }
}
