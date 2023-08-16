#pragma once

#include"Matrix4x4.h"
#include<format>
#include"Vector3.h"
#include"Novice.h"
#include"math/MatrixTransform.h"

void DrawGrid(const Matrix4x4& viewMatrix, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);