#pragma once
#include"Matrix4x4.h"
#include<format>
#include"Vector3.h"
#include"Novice.h"
#include"math/MatrixTransform.h"
#include<numbers>
#include"math/Vector/VectorTransform.h"
struct CubePloperty {
	Vector3 min;
	Vector3 max;
};


void DrawCube(const CubePloperty& aabb, const Matrix4x4& viewMatrix, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, unsigned int  color);