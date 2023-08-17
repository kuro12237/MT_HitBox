#include"3dModel/Cube.h"

void DrawCube(const CubePloperty& aabb, const Matrix4x4& viewMatrix, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, unsigned int  color)
 {




	 //ローカル座標
	 //手前 
	 //左上
	 Vector3 localFrontLeftTop = { aabb.min.x, aabb.max.y, aabb.min.z };
	 //右上
	 Vector3 localFrontRightTop = { aabb.max.x,aabb.max.y,aabb.min.z };
	 //左下
	 Vector3 loaclFrontLeftBottom = { aabb.min.x,aabb.min.y,aabb.min.z };
	 //右下
	 Vector3 localFrontRightBottom = { aabb.max.x,aabb.min.y,aabb.min.z };

	 //奥
	 //左上
	 Vector3 localBackLeftTop = { aabb.min.x,aabb.max.y,aabb.max.z };
	 //右上
	 Vector3 localBackRightTop = { aabb.max.x,aabb.max.y,aabb.max.z };
	 //左下
	 Vector3 loaclBackLeftBottom = { aabb.min.x,aabb.min.y,aabb.max.z };
	 //右下
	 Vector3 localBackRightBottom = { aabb.max.x,aabb.min.y,aabb.max.z };

	 //Matrix4x4 worldMatrixMax = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f },aabb.max);
	 //Matrix4x4 worldMatrixMin = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f },aabb.min);


#pragma region ワールド座標
	//FrontとBackで分けたい
	//手前から時計回り

	//手前
	//左上
	 Matrix4x4 worldFrontLeftTop = MatrixTransform::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, localFrontLeftTop);
	 //右上
	 Matrix4x4 worldFrontRightTop = MatrixTransform::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, localFrontRightTop);
	 //左下
	 Matrix4x4 worldFrontLeftBottom = MatrixTransform::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, loaclFrontLeftBottom);
	 //右下
	 Matrix4x4 worldFrontRightBottom = MatrixTransform::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, localFrontRightBottom);


	 //奥
	 //左上
	 Matrix4x4 worldBackLeftTop = MatrixTransform::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, localBackLeftTop);
	 //右上
	 Matrix4x4 worldBackRightTop = MatrixTransform::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, localBackRightTop);
	 //左下
	 Matrix4x4 worldBackLeftBottom = MatrixTransform::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, loaclBackLeftBottom);
	 //右下
	 Matrix4x4 worldBackRightBottom = MatrixTransform::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, localBackRightBottom);
#pragma endregion


#pragma region WVP

	 //手前
	 //左上
	 Matrix4x4 worldViewProjectionFrontLeftTopMatrix = MatrixTransform::Multiply(worldFrontLeftTop, MatrixTransform::Multiply(viewMatrix, viewProjectionMatrix));
	 //右上
	 Matrix4x4 worldViewProjectionFrontRightTopMatrix = MatrixTransform::Multiply(worldFrontRightTop, MatrixTransform::Multiply(viewMatrix, viewProjectionMatrix));
	 //左下
	 Matrix4x4 worldViewProjectionFrontLeftBottomMatrix = MatrixTransform::Multiply(worldFrontLeftBottom, MatrixTransform::Multiply(viewMatrix, viewProjectionMatrix));
	 //右下
	 Matrix4x4 worldViewProjectionFrontRightBottomMatrix = MatrixTransform::Multiply(worldFrontRightBottom, MatrixTransform::Multiply(viewMatrix, viewProjectionMatrix));

	 //奥
	 //左上
	 Matrix4x4 worldViewProjectionBackLeftTopMatrix = MatrixTransform::Multiply(worldBackLeftTop, MatrixTransform::Multiply(viewMatrix, viewProjectionMatrix));
	 //右上
	 Matrix4x4 worldViewProjectionBackRightTopMatrix = MatrixTransform::Multiply(worldBackRightTop, MatrixTransform::Multiply(viewMatrix, viewProjectionMatrix));
	 //左下
	 Matrix4x4 worldViewProjectionBackLeftBottomMatrix = MatrixTransform::Multiply(worldBackLeftBottom, MatrixTransform::Multiply(viewMatrix, viewProjectionMatrix));
	 //右下
	 Matrix4x4 worldViewProjectionBackRightBottomMatrix = MatrixTransform::Multiply(worldBackRightBottom, MatrixTransform::Multiply(viewMatrix, viewProjectionMatrix));


#pragma endregion


#pragma region 正規化

	 //手前
	 //左上
	 Vector3 ndcFrontLeftTop = Transform(localFrontLeftTop, worldViewProjectionFrontLeftTopMatrix);
	 //右上
	 Vector3 ndcFrontRightTop = Transform(localFrontRightTop, worldViewProjectionFrontRightTopMatrix);
	 //左下
	 Vector3 ndcFrontLeftBottom = Transform(loaclFrontLeftBottom, worldViewProjectionFrontLeftBottomMatrix);
	 //右下
	 Vector3 ndcFrontRightBottom = Transform(localFrontRightBottom, worldViewProjectionFrontRightBottomMatrix);

	 //奥
	 //左上
	 Vector3 ndcBackLeftTop = Transform(localBackLeftTop, worldViewProjectionBackLeftTopMatrix);
	 //右上
	 Vector3 ndcBackRightTop = Transform(localBackRightTop, worldViewProjectionBackRightTopMatrix);
	 //左下
	 Vector3 ndcBackLeftBottom = Transform(loaclBackLeftBottom, worldViewProjectionBackLeftBottomMatrix);
	 //右下
	 Vector3 ndcBackRightBottom = Transform(localBackRightBottom, worldViewProjectionBackRightBottomMatrix);


#pragma endregion




#pragma region スクリーン

	 //手前
	 //左上
	 Vector3 screenFrontLeftTop = Transform(ndcFrontLeftTop, viewportMatrix);
	 //右上
	 Vector3 screenFrontRightTop = Transform(ndcFrontRightTop, viewportMatrix);
	 //左下
	 Vector3 screenFrontLeftBottom = Transform(ndcFrontLeftBottom, viewportMatrix);
	 //右下
	 Vector3 screenFrontRightBottom = Transform(ndcFrontRightBottom, viewportMatrix);

	 //奥
	 //左上
	 Vector3 screenBackLeftTop = Transform(ndcBackLeftTop, viewportMatrix);
	 //右上
	 Vector3 screenBackRightTop = Transform(ndcBackRightTop, viewportMatrix);
	 //左下
	 Vector3 screenBackLeftBottom = Transform(ndcBackLeftBottom, viewportMatrix);
	 //右下
	 Vector3 screenBackRightBottom = Transform(ndcBackRightBottom, viewportMatrix);
#pragma endregion

	 //上
	 Novice::DrawLine(int(screenFrontLeftTop.x), int(screenFrontLeftTop.y), int(screenFrontRightTop.x), int(screenFrontRightTop.y), color);
	 //右
	 Novice::DrawLine(int(screenFrontRightTop.x), int(screenFrontRightTop.y), int(screenFrontRightBottom.x), int(screenFrontRightBottom.y), color);
	 //下
	 Novice::DrawLine(int(screenFrontRightBottom.x), int(screenFrontRightBottom.y), int(screenFrontLeftBottom.x), int(screenFrontLeftBottom.y), color);
	 //左
	 Novice::DrawLine(int(screenFrontLeftBottom.x), int(screenFrontLeftBottom.y), int(screenFrontLeftTop.x), int(screenFrontLeftTop.y), color);


	 //上
	 Novice::DrawLine(int(screenFrontRightTop.x), int(screenFrontRightTop.y), int(screenBackRightTop.x), int(screenBackRightTop.y), color);
	 //下
	 Novice::DrawLine(int(screenFrontRightBottom.x), int(screenFrontRightBottom.y), int(screenBackRightBottom.x), int(screenBackRightBottom.y), color);


	 //奥
	 //上
	 Novice::DrawLine(int(screenBackLeftTop.x), int(screenBackLeftTop.y), int(screenBackRightTop.x), int(screenBackRightTop.y), color);
	 //右
	 Novice::DrawLine(int(screenBackRightTop.x), int(screenBackRightTop.y), int(screenBackRightBottom.x), int(screenBackRightBottom.y), color);
	 //下
	 Novice::DrawLine(int(screenBackRightBottom.x), int(screenBackRightBottom.y), int(screenBackLeftBottom.x), int(screenBackLeftBottom.y), color);
	 //左
	 Novice::DrawLine(int(screenBackLeftBottom.x), int(screenBackLeftBottom.y), int(screenBackLeftTop.x), int(screenBackLeftTop.y), color);

	 //上
	 Novice::DrawLine(int(screenFrontLeftTop.x), int(screenFrontLeftTop.y), int(screenBackLeftTop.x), int(screenBackLeftTop.y), color);
	 //下
	 Novice::DrawLine(int(screenFrontLeftBottom.x), int(screenFrontLeftBottom.y), int(screenBackLeftBottom.x), int(screenBackLeftBottom.y), color);



}