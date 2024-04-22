#pragma once

#include "Vector4.h"
#include "Vector3.h"
#include <cmath>
#include <stdexcept> 

namespace Engine {
    namespace Math {

        class Matrix4 {
        public:
            Matrix4() : m_11(1), m_12(0), m_13(0), m_14(0),
                m_21(0), m_22(1), m_23(0), m_24(0),
                m_31(0), m_32(0), m_33(1), m_34(0),
                m_41(0), m_42(0), m_43(0), m_44(1) {} 

            Matrix4(float i_11, float i_12, float i_13, float i_14,
                float i_21, float i_22, float i_23, float i_24,
                float i_31, float i_32, float i_33, float i_34,
                float i_41, float i_42, float i_43, float i_44)
                : m_11(i_11), m_12(i_12), m_13(i_13), m_14(i_14),
                m_21(i_21), m_22(i_22), m_23(i_23), m_24(i_24),
                m_31(i_31), m_32(i_32), m_33(i_33), m_34(i_34),
                m_41(i_41), m_42(i_42), m_43(i_43), m_44(i_44) {}

            Matrix4(const Matrix4& i_other) = default;
            Matrix4& operator=(const Matrix4& i_other) = default;

            Matrix4 operator*(const Matrix4& i_other) const {
                return Matrix4(
                    m_11 * i_other.m_11 + m_12 * i_other.m_21 + m_13 * i_other.m_31 + m_14 * i_other.m_41,
                    m_11 * i_other.m_12 + m_12 * i_other.m_22 + m_13 * i_other.m_32 + m_14 * i_other.m_42,
                    m_11 * i_other.m_13 + m_12 * i_other.m_23 + m_13 * i_other.m_33 + m_14 * i_other.m_43,
                    m_11 * i_other.m_14 + m_12 * i_other.m_24 + m_13 * i_other.m_34 + m_14 * i_other.m_44,

                    m_21 * i_other.m_11 + m_22 * i_other.m_21 + m_23 * i_other.m_31 + m_24 * i_other.m_41,
                    m_21 * i_other.m_12 + m_22 * i_other.m_22 + m_23 * i_other.m_32 + m_24 * i_other.m_42,
                    m_21 * i_other.m_13 + m_22 * i_other.m_23 + m_23 * i_other.m_33 + m_24 * i_other.m_43,
                    m_21 * i_other.m_14 + m_22 * i_other.m_24 + m_23 * i_other.m_34 + m_24 * i_other.m_44,

                    m_31 * i_other.m_11 + m_32 * i_other.m_21 + m_33 * i_other.m_31 + m_34 * i_other.m_41,
                    m_31 * i_other.m_12 + m_32 * i_other.m_22 + m_33 * i_other.m_32 + m_34 * i_other.m_42,
                    m_31 * i_other.m_13 + m_32 * i_other.m_23 + m_33 * i_other.m_33 + m_34 * i_other.m_43,
                    m_31 * i_other.m_14 + m_32 * i_other.m_24 + m_33 * i_other.m_34 + m_34 * i_other.m_44,

                    m_41 * i_other.m_11 + m_42 * i_other.m_21 + m_43 * i_other.m_31 + m_44 * i_other.m_41,
                    m_41 * i_other.m_12 + m_42 * i_other.m_22 + m_43 * i_other.m_32 + m_44 * i_other.m_42,
                    m_41 * i_other.m_13 + m_42 * i_other.m_23 + m_43 * i_other.m_33 + m_44 * i_other.m_43,
                    m_41 * i_other.m_14 + m_42 * i_other.m_24 + m_43 * i_other.m_34 + m_44 * i_other.m_44
                );
            }


            Vector4 operator*(const Vector4& i_vector) const {
                return Vector4(
                    m_11 * i_vector.x() + m_12 * i_vector.y() + m_13 * i_vector.z() + m_14 * i_vector.w(),
                    m_21 * i_vector.x() + m_22 * i_vector.y() + m_23 * i_vector.z() + m_24 * i_vector.w(),
                    m_31 * i_vector.x() + m_32 * i_vector.y() + m_33 * i_vector.z() + m_34 * i_vector.w(),
                    m_41 * i_vector.x() + m_42 * i_vector.y() + m_43 * i_vector.z() + m_44 * i_vector.w()
                );
            }

            static Matrix4 CreateIdentity() {
                return Matrix4();
            }

            static Matrix4 CreateScale(float i_scaleX, float i_scaleY, float i_scaleZ) {
                return Matrix4(
                    i_scaleX, 0, 0, 0,
                    0, i_scaleY, 0, 0,
                    0, 0, i_scaleZ, 0,
                    0, 0, 0, 1
                );
            }

            static Matrix4 CreateTranslation(float i_transX, float i_transY, float i_transZ) {
                return Matrix4(
                    1, 0, 0, i_transX,
                    0, 1, 0, i_transY,
                    0, 0, 1, i_transZ,
                    0, 0, 0, 1
                );
            }

            static Matrix4 CreateRotationX(float i_angleRadians) {
                float c = std::cos(i_angleRadians);
                float s = std::sin(i_angleRadians);
                return Matrix4(
                    1, 0, 0, 0,
                    0, c, -s, 0,
                    0, s, c, 0,
                    0, 0, 0, 1
                );
            }

            static Matrix4 CreateRotationY(float i_angleRadians) {
                float c = std::cos(i_angleRadians);
                float s = std::sin(i_angleRadians);
                return Matrix4(
                    c, 0, s, 0,
                    0, 1, 0, 0,
                    -s, 0, c, 0,
                    0, 0, 0, 1
                );
            }

            static Matrix4 CreateRotationZ(float i_angleRadians) {
                float c = std::cos(i_angleRadians);
                float s = std::sin(i_angleRadians);
                return Matrix4(
                    c, -s, 0, 0,
                    s, c, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1
                );
            }

            Vector3 TransformPoint(const Vector3& point) const {
                float x = m_11 * point.x() + m_12 * point.y() + m_13 * point.z() + m_14;
                float y = m_21 * point.x() + m_22 * point.y() + m_23 * point.z() + m_24;
                float z = m_31 * point.x() + m_32 * point.y() + m_33 * point.z() + m_34;
                return Vector3(x, y, z);
            }


            void Invert() {

                Transpose(); 
            }

            Matrix4 GetInverse() const {
                Matrix4 result(*this);
                result.Invert();
                return result;
            }

            void Transpose() {
                std::swap(m_12, m_21);
                std::swap(m_13, m_31);
                std::swap(m_14, m_41);
                std::swap(m_23, m_32);
                std::swap(m_24, m_42);
                std::swap(m_34, m_43);
            }

            Matrix4 GetTranspose() const {
                Matrix4 result(*this);
                result.Transpose();
                return result;
            }

            Vector4 Row(size_t i_row) const {
                switch (i_row) {
                case 0: return Vector4(m_11, m_12, m_13, m_14);
                case 1: return Vector4(m_21, m_22, m_23, m_24);
                case 2: return Vector4(m_31, m_32, m_33, m_34);
                case 3: return Vector4(m_41, m_42, m_43, m_44);
                default: throw std::out_of_range("Row index out of range");
                }
            }

            Vector4 Col(size_t i_col) const {
                switch (i_col) {
                case 0: return Vector4(m_11, m_21, m_31, m_41);
                case 1: return Vector4(m_12, m_22, m_32, m_42);
                case 2: return Vector4(m_13, m_23, m_33, m_43);
                case 3: return Vector4(m_14, m_24, m_34, m_44);
                default: throw std::out_of_range("Column index out of range");
                }
            }

        private:
            float m_11, m_12, m_13, m_14;
            float m_21, m_22, m_23, m_24;
            float m_31, m_32, m_33, m_34;
            float m_41, m_42, m_43, m_44;
        };
    } 
}
