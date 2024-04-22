#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include <cmath>
#include <array>
#include "Vector4.h"

class Matrix4x4 {
private:
    std::array<std::array<float, 4>, 4> m;

public:
    Matrix4x4() {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                m[i][j] = (i == j) ? 1.0f : 0.0f; 
    }


    Matrix4x4 operator*(const Matrix4x4& other) const {
        Matrix4x4 result;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j) {
                result.m[i][j] = 0.0f;
                for (int k = 0; k < 4; ++k)
                    result.m[i][j] += m[i][k] * other.m[k][j];
            }
        return result;
    }

};

#endif 
