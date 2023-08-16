#pragma once
#include"Novice.h"
#include"Matrix4x4.h"
#include"Vector3.h"
#include"math/Vector/VectorTransform.h"
#include"math/MatrixTransform.h"
struct Plane {
	Vector3 normal; 
	float distance; 
};
Vector3 Perpendicular(const Vector3 vector);
Vector3 Normalize(Vector3 V1);
void DrawPlane(const Plane plane, const Matrix4x4& viewMatrix, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, unsigned int color);
Vector3 Cross(const Vector3 v1, const Vector3 v2);