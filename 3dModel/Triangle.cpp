#include"3dModel/Triangle.h"

void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewMatrix, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, unsigned int color)
{

	Vector3 localv1 = triangle.vertex1;
	Vector3 localv2 = triangle.vertex2;
	Vector3 localv3 = triangle.vertex3;

	//ワールド
	Matrix4x4 worldv1 = MatrixTransform::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, localv1);
	Matrix4x4 worldv2 = MatrixTransform::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, localv2);
	Matrix4x4 worldv3 = MatrixTransform::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, localv3);




	Matrix4x4 worldViewProjectionv1 = MatrixTransform::Multiply(worldv1, MatrixTransform::Multiply(viewMatrix, viewProjectionMatrix));
	Matrix4x4 worldViewProjectionv2 = MatrixTransform::Multiply(worldv2, MatrixTransform::Multiply(viewMatrix, viewProjectionMatrix));
	Matrix4x4 worldViewProjectionv3 = MatrixTransform::Multiply(worldv3, MatrixTransform::Multiply(viewMatrix, viewProjectionMatrix));




	Vector3 ndcv1 = Transform(localv1, worldViewProjectionv1);
	Vector3 ndcv2 = Transform(localv2, worldViewProjectionv2);
	Vector3 ndcv3 = Transform(localv3, worldViewProjectionv3);



	Vector3 screenv1 = Transform(ndcv1, viewportMatrix);
	Vector3 screenv2 = Transform(ndcv2, viewportMatrix);
	Vector3 screenv3 = Transform(ndcv3, viewportMatrix);


	Novice::DrawTriangle(
		int(screenv1.x),
		int(screenv1.y),
		int(screenv2.x),
		int(screenv2.y),
		int(screenv3.x),
		int(screenv3.y), color, kFillModeWireFrame);


}