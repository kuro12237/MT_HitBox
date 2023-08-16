#include "Sphre.h"


void DrawSphere(const SpherePloperty& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, unsigned int color)
{
	//Cg2球

	const uint32_t kSubDivision = 30;
	const float kLonEvery = 2.0f * (float)std::numbers::pi / float(kSubDivision);
	const float kLatEvery = (float)std::numbers::pi / float(kSubDivision);

	for (uint32_t latIndex = 0; latIndex < kSubDivision; ++latIndex) {
		float lat = -1.0f * (float)std::numbers::pi / 2.0f + kLatEvery * latIndex;

		for (uint32_t lonIndex = 0; lonIndex < kSubDivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;

			Vector3 v1, v2, v3;
		
			v1 = { sphere.radius * std::cosf(lat) * std::cosf(lon), sphere.radius * std::sinf(lat), sphere.radius * std::cosf(lat) * std::sinf(lon) };
			v1 = VectorTransform::Add(v1, sphere.center);
			v2 = { sphere.radius * std::cosf(lat + kLatEvery) * std::cosf(lon), sphere.radius * std::sinf(lat + kLatEvery), sphere.radius * std::cosf(lat + kLatEvery) * std::sinf(lon) };
			v2 = VectorTransform::Add(v2, sphere.center);
			v3 = { sphere.radius * std::cosf(lat) * std::cosf(lon + kLonEvery), sphere.radius * std::sinf(lat), sphere.radius * std::cosf(lat) * std::sinf(lon + kLonEvery) };
			v3 = VectorTransform::Add(v3, sphere.center);

			v1 = Transform(v1, viewProjectionMatrix);
			v1 = Transform(v1, viewportMatrix);
			v2 = Transform(v2, viewProjectionMatrix);
			v2 = Transform(v2, viewportMatrix);
			v3 = Transform(v3, viewProjectionMatrix);
			v3 = Transform(v3, viewportMatrix);


			Novice::DrawLine(
				int(v1.x), int(v1.y),
				int(v2.x), int(v2.y),
				color
			);

			Novice::DrawLine(
				int(v1.x), int(v1.y),
				int(v3.x), int(v3.y),
				color
			);

		}
	}



}
