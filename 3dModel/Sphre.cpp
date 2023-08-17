#include "Sphre.h"


void DrawSphere(const SpherePloperty& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, const Matrix4x4& viewMatrix, unsigned int color)
{
	//Cg2球
//分割数
	const uint32_t SUBDIVISION = 30;
	//lat
	const float LON_EVERY =2.0f* (float)std::numbers::pi / float(SUBDIVISION);
	//lon
	const float LAT_EVERY = (float)std::numbers::pi / float(SUBDIVISION);




	for (uint32_t latIndex = 0; latIndex < SUBDIVISION; ++latIndex) {
		float lat = -1.0f * (float)(float)std::numbers::pi / 2.0f + LAT_EVERY * latIndex;

		for (uint32_t lonIndex = 0; lonIndex < SUBDIVISION; ++lonIndex) {
			float lon = lonIndex * LON_EVERY;

			Vector3 a, b, c;

			//Local

			a = { sphere.radius * std::cosf(lat) * std::cosf(lon), sphere.radius * std::sinf(lat), sphere.radius * std::cosf(lat) * std::sinf(lon) };
			a = VectorTransform::Add(a, sphere.center);
			b = { sphere.radius * std::cosf(lat + LAT_EVERY) * std::cosf(lon), sphere.radius * std::sinf(lat + LAT_EVERY), sphere.radius * std::cosf(lat + LAT_EVERY) * std::sinf(lon) };
			b = VectorTransform::Add(b, sphere.center);
			c = { sphere.radius * std::cosf(lat) * std::cosf(lon + LON_EVERY), sphere.radius * std::sinf(lat), sphere.radius * std::cosf(lat) * std::sinf(lon + LON_EVERY) };
			c = VectorTransform::Add(c, sphere.center);

			Matrix4x4 WorldMatrixA = MatrixTransform::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, sphere.center);
			Matrix4x4 WorldMatrixB = MatrixTransform::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, sphere.center);
			Matrix4x4 WorldMatrixC = MatrixTransform::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, sphere.center);


			////world


			Matrix4x4 worldViewProjectionMatrixA = MatrixTransform::Multiply(WorldMatrixA, MatrixTransform::Multiply(viewMatrix, viewProjectionMatrix));
			Matrix4x4 worldViewProjectionMatrixB = MatrixTransform::Multiply(WorldMatrixB, MatrixTransform::Multiply(viewMatrix, viewProjectionMatrix));
			Matrix4x4 worldViewProjectionMatrixC = MatrixTransform::Multiply(WorldMatrixC, MatrixTransform::Multiply(viewMatrix, viewProjectionMatrix));
			viewMatrix;

			Vector3 ndcVerticesA = Transform(a,worldViewProjectionMatrixA);
			Vector3 ndcVerticesB = Transform(b,worldViewProjectionMatrixB);
			Vector3 ndcVerticesC = Transform(c,worldViewProjectionMatrixC);
			ndcVerticesA = Transform(ndcVerticesA, viewportMatrix);
			ndcVerticesB = Transform(ndcVerticesB, viewportMatrix);
			ndcVerticesC = Transform(ndcVerticesC, viewportMatrix);


			//ab
			Novice::DrawLine(
				int(ndcVerticesA.x),
				int(ndcVerticesA.y),
				int(ndcVerticesB.x),
				int(ndcVerticesB.y), color);

			////ac
			Novice::DrawLine(
				int(ndcVerticesC.x),
				int(ndcVerticesC.y),
				int(ndcVerticesA.x),
				int(ndcVerticesA.y), color);



		}



	}


}
