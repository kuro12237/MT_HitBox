#include"Grid.h"


void DrawGrid(const Matrix4x4& viewMatrix, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	//Gridの半分の幅
	const float GRID_HALF_WIDTH = 1.0f;

	//分割数
	const uint32_t SUB_DEVISION = 10;

	//一つ分の長さ
	const float GRID_EVERY = (GRID_HALF_WIDTH * 2.0f) / float(SUB_DEVISION);



	//縦

	Vector3 LocalVerticesStartColumn[11] = {};
	Vector3 LocalVerticesEndColumn[11] = {};

	Matrix4x4 WorldMatrixStartColumn[11] = {};
	Matrix4x4 WorldMatrixEndColumn[11] = {};


	Vector3 ScreenVerticesColumn = {};

	Vector3 ndcVerticesStartColumn = {};
	Vector3 ndcVerticesEndColumn = {};


	Vector3 screenVerticesStartColumn[11] = {};
	Vector3 screenVerticesEndColumn[11] = {};


	//横
	Vector3 LocalVerticesStartLine[11] = {};
	Vector3 LocalVerticesEndLine[11] = {};

	Matrix4x4 WorldMatrixStartLine[11] = {};
	Matrix4x4 WorldMatrixEndLine[11] = {};


	Vector3 ScreenVerticesLine = {};

	Vector3 ndcVerticesStartLine = {};
	Vector3 ndcVerticesEndLine = {};


	Vector3 screenVerticesStartLine[11] = {};
	Vector3 screenVerticesEndLine[11] = {};




	//奥から手前への線を順々に引いてくる(縦)
	for (int xIndex = 0; xIndex <= SUB_DEVISION; ++xIndex) {
		//上の情報を使ってワールド座標上の始点と終点を求める



		LocalVerticesStartColumn[xIndex].x = xIndex * GRID_EVERY - GRID_HALF_WIDTH;
		LocalVerticesStartColumn[xIndex].y = 0.0f;
		LocalVerticesStartColumn[xIndex].z = -GRID_HALF_WIDTH;

		LocalVerticesEndColumn[xIndex].x = xIndex * GRID_EVERY - GRID_HALF_WIDTH;
		LocalVerticesEndColumn[xIndex].y = 0.0f;
		LocalVerticesEndColumn[xIndex].z = GRID_HALF_WIDTH;






		//ローカル座標系
		//      ↓			(WorldMatrix)
		//ワールド座標系
		//      ↓			(ViewMatrix(Inverse))
		//ビュー座標系
		//      ↓			(Projection)
		//正規化デバイス座標系
		//      ↓
		//スクリーン座標系


		WorldMatrixStartColumn[xIndex] = MatrixTransform::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, LocalVerticesStartColumn[xIndex]);
		WorldMatrixEndColumn[xIndex] = MatrixTransform::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, LocalVerticesEndColumn[xIndex]);


		////ワールドへ
		Matrix4x4 worldViewProjectionMatrixStart = MatrixTransform::Multiply(WorldMatrixStartColumn[xIndex], MatrixTransform::Multiply(viewMatrix, viewProjectionMatrix));
		Matrix4x4 worldViewProjectionMatrixEnd = MatrixTransform::Multiply(WorldMatrixEndColumn[xIndex], MatrixTransform::Multiply(viewMatrix, viewProjectionMatrix));


		ndcVerticesStartColumn = Transform(LocalVerticesStartColumn[xIndex], worldViewProjectionMatrixStart);
		ndcVerticesEndColumn = Transform(LocalVerticesEndColumn[xIndex], worldViewProjectionMatrixEnd);


		screenVerticesStartColumn[xIndex] = Transform(ndcVerticesStartColumn, viewportMatrix);
		screenVerticesEndColumn[xIndex] = Transform(ndcVerticesEndColumn, viewportMatrix);



		//変換した座標を使って表示

		Novice::DrawLine(
			int(screenVerticesStartColumn[xIndex].x),
			int(screenVerticesStartColumn[xIndex].y),
			int(screenVerticesEndColumn[xIndex].x),
			int(screenVerticesEndColumn[xIndex].y),
			RED);

		Novice::DrawLine(
			int(screenVerticesStartColumn[0].x),
			int(screenVerticesStartColumn[0].y),
			int(screenVerticesEndColumn[0].x),
			int(screenVerticesEndColumn[0].y),
			BLUE);


	}
	//左から右も同じように順々に引いていく(横)
	for (uint32_t zIndex = 0; zIndex <= SUB_DEVISION; ++zIndex) {
		//奥から手前が左右に変わるだけ


		LocalVerticesStartLine[zIndex].x = -GRID_HALF_WIDTH;
		LocalVerticesStartLine[zIndex].y = 0.0f;
		LocalVerticesStartLine[zIndex].z = zIndex * GRID_EVERY - GRID_HALF_WIDTH;

		LocalVerticesEndLine[zIndex].x = GRID_HALF_WIDTH;
		LocalVerticesEndLine[zIndex].y = 0.0f;
		LocalVerticesEndLine[zIndex].z = zIndex * GRID_EVERY - GRID_HALF_WIDTH;



		WorldMatrixStartLine[zIndex] = MatrixTransform::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, LocalVerticesStartLine[zIndex]);
		WorldMatrixEndLine[zIndex] = MatrixTransform::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, LocalVerticesEndLine[zIndex]);



		////ワールドへ
		Matrix4x4 worldViewProjectionMatrixStartLine = MatrixTransform::Multiply(WorldMatrixStartLine[zIndex], MatrixTransform::Multiply(viewMatrix, viewProjectionMatrix));
		Matrix4x4 worldViewProjectionMatrixEndLine = MatrixTransform::Multiply(WorldMatrixEndLine[zIndex], MatrixTransform::Multiply(viewMatrix, viewProjectionMatrix));


		ndcVerticesStartLine = Transform(LocalVerticesStartLine[zIndex], worldViewProjectionMatrixStartLine);
		ndcVerticesEndLine = Transform(LocalVerticesEndLine[zIndex], worldViewProjectionMatrixEndLine);


		screenVerticesStartLine[zIndex] = Transform(ndcVerticesStartLine, viewportMatrix);
		screenVerticesEndLine[zIndex] = Transform(ndcVerticesEndLine, viewportMatrix);



		//変換した座標を使って表示


		Novice::DrawLine(
			int(screenVerticesStartLine[zIndex].x),
			int(screenVerticesStartLine[zIndex].y),
			int(screenVerticesEndLine[zIndex].x),
			int(screenVerticesEndLine[zIndex].y),
			RED);

		Novice::DrawLine(
			int(screenVerticesStartLine[0].x),
			int(screenVerticesStartLine[0].y),
			int(screenVerticesEndLine[0].x),
			int(screenVerticesEndLine[0].y), BLUE);
	}
}

