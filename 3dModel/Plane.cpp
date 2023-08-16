#include"3dModel/Plane.h"

Vector3 Perpendicular(const Vector3 vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return { -vector.y, vector.x, 0.0f };
	}
	return { 0.0f,-vector.z,vector.y };
}
Vector3 Cross(const Vector3 v1, const Vector3 v2) 
{
	Vector3 result = { 0.0f,0.0f,0.0f };
	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;

	return result;
}

Vector3 Normalize(Vector3 V1) {
	Vector3 result = {};

	float length = sqrt(V1.x * V1.x + V1.y * V1.y + V1.z * V1.z);

	float newX = V1.x;
	float newY = V1.y;
	float newZ = V1.z;


	if (length != 0.0f) {
		newX = V1.x / length;
		newY = V1.y / length;
		newZ = V1.z / length;

	}

	result.x = newX;
	result.y = newY;
	result.z = newZ;


	return result;
}

void DrawPlane(const Plane plane, const Matrix4x4& viewMatrix, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, unsigned int color) {

	//1.中心点を決める
	Vector3 center = {
		plane.distance * plane.normal.x,
		plane.distance * plane.normal.y,
		plane.distance * plane.normal.z
	};

	Vector3 perpendiculars[4];
	//2.法線と垂直なベクトルを１つを決める
	perpendiculars[0] = Normalize(Perpendicular(plane.normal));
	//3.2の逆ベクトルを求める
	perpendiculars[1] = { -perpendiculars[0].x,-perpendiculars[0].y,-perpendiculars[0].z };
	//4.2と法線のクロス積を求める
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);
	//5.4の逆ベクトルを求める
	perpendiculars[3] = { -perpendiculars[2].x,-perpendiculars[2].y,-perpendiculars[2].z };



	//6.2-5のベクトルを中心点にそれぞれ定数倍して足すと4頂点が出来上がる
	//Vector3 points[4] = {};
	Vector3 extend[4] = {};
	Vector3 point[4] = {};
	//Vector3 points2[4] = {};

	Matrix4x4 worldPoints[4] = {};
	Matrix4x4 worldViewProjectionPoints[4] = {};

	Vector3 ndcPoints[4] = {};
	Vector3 screenPoints[4] = {};

	for (int32_t index = 0; index < 4; ++index) {
		extend[index] = {
			2.0f * perpendiculars[index].x,
			2.0f * perpendiculars[index].y,
			2.0f * perpendiculars[index].z
		};
		point[index] = VectorTransform::Add(center, extend[index]);



		worldPoints[index] = MatrixTransform::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, point[index]);

		////ワールドへ
		//Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		worldViewProjectionPoints[index] = MatrixTransform::Multiply(worldPoints[index], MatrixTransform::Multiply(viewMatrix, viewProjectionMatrix));


		ndcPoints[index] = Transform(point[index], worldViewProjectionPoints[index]);

		screenPoints[index] = Transform(ndcPoints[index], viewportMatrix);
	}




#pragma region 点をつなぎ合わせる

	const float offset = 0.0f;

	//WhiteToBlue
	Novice::DrawLine(
		int(screenPoints[0].x),
		int(screenPoints[0].y + offset),
		int(screenPoints[2].x),
		int(screenPoints[2].y + offset), color);

	//BlueToRed
	Novice::DrawLine(
		int(screenPoints[2].x),
		int(screenPoints[2].y + offset),
		int(screenPoints[1].x),
		int(screenPoints[1].y + offset), color);

	//RedToGreen
	Novice::DrawLine(
		int(screenPoints[1].x),
		int(screenPoints[1].y + offset),
		int(screenPoints[3].x),
		int(screenPoints[3].y + offset), color);

	//GreenWhite
	Novice::DrawLine(
		int(screenPoints[3].x),
		int(screenPoints[3].y + offset),
		int(screenPoints[0].x),
		int(screenPoints[0].y + offset), color);

#pragma endregion




}