#pragma once
#include"Matrix4x4.h"
#include<format>
#include"Vector3.h"
#include"Novice.h"
#include"math/MatrixTransform.h"
#include<numbers>
#include"math/Vector/VectorTransform.h"
struct SpherePloperty {
	Vector3 center;
	float radius;
};

void DrawSphere(const SpherePloperty& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, const Matrix4x4& viewMatrix, unsigned int color);