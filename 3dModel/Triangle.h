#pragma once
#include"math/MatrixTransform.h"
#include"math/Vector/VectorTransform.h"
#include"Novice.h"
struct Triangle {
	Vector3 vertex1;
	Vector3 vertex2;
	Vector3 vertex3;

};
//三角形の描画
void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewMatrix, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, unsigned int color);