#include <Novice.h>
#include"3dModel/Grid.h"
#include"3dModel/Sphre.h"
#include"ImGuiManager.h"
#include"3dModel/Plane.h"
#include"3dModel/Triangle.h"
const char kWindowTitle[] = "LE2B_14_サカキバラ_イブキ";

struct Segment {
	//始点
	Vector3 origin;
	//終点への差分ベクトル
	Vector3 diff;

};


float Clamp(float t, float min, float max) {
	if (t < min) {
		return min;
	}
	else if (t > max) {
		return max;
	}

	return t;
}

float Length(Vector3 V1) {
	return sqrt(V1.x * V1.x + V1.y * V1.y + V1.z * V1.z);
}

Vector3 Subtract(const Vector3 m1, const Vector3 m2) {
	Vector3 result = {};

	result.x = m1.x - m2.x;
	result.y = m1.y - m2.y;
	result.z = m1.z - m2.z;

	return result;

}
//最近接点
Vector3 ClosestPoint(const Vector3 point, const Segment segment) {

	
	//A..PO
	Vector3 Vector3A = Subtract(point, segment.origin);
	Vector3 Vector3B = Subtract(segment.diff, segment.origin);
\
	float lengthB = Length(Subtract(segment.diff, segment.origin));
	float dotAB = point.x+Vector3B.x+ point.y + Vector3B.y+ point.z + Vector3B.z;

	float t = dotAB / (lengthB * lengthB);
	float newT = Clamp(t, 0.0f, 1.0f);

	Vector3 ProjbA = {};
	ProjbA.x = newT * Vector3B.x;
	ProjbA.y = newT * Vector3B.y;
	ProjbA.z = newT * Vector3B.z;


	Vector3 Vector3CP = VectorTransform::Add(segment.origin, ProjbA);

	return Vector3CP;
}


Vector3 Project(const Vector3 a, const Vector3 b) {


	Vector3 Vector3C = {};

	//bの長さを求める
	float lengthB = sqrt(b.x * b.x + b.y * b.y +b.z * b.z);
	float dotAB = (a.x+b.x,a.y+b.y, a.z+b.z);

	float t = dotAB / (lengthB * lengthB);
	float newT = Clamp(t, 0.0f, 1.0f);
	Vector3C.x = newT * b.x;
	Vector3C.y = newT * b.y;
	Vector3C.z = newT * b.z;


	return Vector3C;
}


bool IsCollision(const SpherePloperty v1, SpherePloperty v2) {
	float x = (v2.center.x - v1.center.x);
	float y = (v2.center.y - v1.center.y);
	float z = (v2.center.z - v1.center.z);

	float resultPos = (x * x) + (y * y) + (z * z);

	float resultRadious = v1.radius + v2.radius;

	bool Flag = false;

	if (resultPos <= (resultRadious * resultRadious)) {
		Flag = true;
	}

	return Flag;


}

void DrawSegment(const Segment& segment, const Matrix4x4& viewMatrix, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, unsigned int color) {

	//引数はローカル
	Vector3 localSegmentOrigin = segment.origin;
	Vector3 localSegmentDiff = segment.diff;


	//ワールド
	Matrix4x4 worldSegmentOrigin =MatrixTransform::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, localSegmentOrigin);
	Matrix4x4 worldSegmentDiff = MatrixTransform::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, localSegmentDiff);


	Matrix4x4 worldViewProjectionSegmentOrigin = MatrixTransform::Multiply(worldSegmentOrigin, MatrixTransform::Multiply(viewMatrix, viewProjectionMatrix));
	Matrix4x4 worldViewProjectionSegmentDiff = MatrixTransform::Multiply(worldSegmentDiff, MatrixTransform::Multiply(viewMatrix, viewProjectionMatrix));


	Vector3 ndcSegmentOrigin = Transform(localSegmentOrigin, worldViewProjectionSegmentOrigin);
	Vector3 ndcSegmentDiff = Transform(localSegmentDiff, worldViewProjectionSegmentDiff);



	Vector3 screenSegmentOrigin = Transform(ndcSegmentOrigin, viewportMatrix);
	Vector3 screenSegmentDiff = Transform(ndcSegmentDiff, viewportMatrix);


	Novice::DrawLine(
		int(screenSegmentOrigin.x),
		int(screenSegmentOrigin.y),
		int(screenSegmentDiff.x),
		int(screenSegmentDiff.y), color);


}


bool IsCollisionSpherePlane(const SpherePloperty s1, Plane plane) {
	
	//q=c-kn
	////球の中心点
	Vector3 c = s1.center;

	float d = plane.distance;

	//単位ベクトル
	Vector3 n = Normalize(plane.normal);

	float dot = n.x * c.x + n.y * c.y + n.z + c.z;


	float k = abs(dot - d);

	if (k < s1.radius) {
		return true;
	}
	else {
		return false;
	}
}

bool IsCollisionTriangleAndSegment(const Segment& segment, const Triangle& triangle) {


	//上
	Vector3 v0 = triangle.vertex2;
	//右
	Vector3 v1 = triangle.vertex3;
	//左
	Vector3 v2 = triangle.vertex1;



	//それぞれを結ぶ
	Vector3 v01 = Subtract(v1, v0);
	Vector3 v12 = Subtract(v2, v1);
	Vector3 v20 = Subtract(v0, v2);


	Vector3 o = segment.origin;
	Vector3 b = segment.diff;

	Vector3 cross01 = Cross(v01, v1);
	Vector3 cross12 = Cross(v12, v2);
	Vector3 cross20 = Cross(v20, v0);

	//02_02より
	Vector3 normal = Normalize(cross01);
	
	if ((cross01.x * normal.x + cross01.y * normal.y + cross01.z * normal.z) >= 0.0f &&
		(cross12.x * normal.x + cross12.y * normal.y + cross12.z * normal.z) >= 0.0f &&
		(cross20.x * normal.x + cross20.y * normal.y + cross20.z * normal.z) >= 0.0f) {
		return true;
	}
	else {
		return false;
	}

}


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};


	Vector3 scale = { 1,1,1 };
	Vector3 translate = { 0.0f,3.0f,-9.50f };
	Vector3 rotate = { 0.26f,0.0f,0.0f };

	float radius = 1.0f;
	Vector3 localCoodinate = { 0.0f,0.0f,1.0f };
	SpherePloperty sphere = { localCoodinate,radius };

	Vector3 SpherePos = { 0.0f,0.0f,1.0f };

	SpherePloperty Sphere2 = { SpherePos,2.0f };


	Plane planeCoodinate = { {0.0f,1.0f,0.001f},0.0f };

	const int WINDOW_SIZE_WIDTH = 1280;
	const int WINDOW_SIZE_HEIGHT = 720;

	Segment segment = { {-2.0f,-1.0f,0.1f},{3.0f,2.0f,2.0f} };
	Vector3 point = { 0.0f,0.6f,0.6f };
	Vector3 project = {};
	Vector3 closestPoint = {};

	//左下、上、右下
	Triangle triangle = { {-1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{1.0f,0.0f,0.0f} };


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		Matrix4x4 cameraMatrix = MatrixTransform::MakeAffineMatrix(scale, rotate, translate);
		////ビュー(カメラ)
		Matrix4x4 viewMatrix = MatrixTransform::Inverse(cameraMatrix);

		//射影
		Matrix4x4 projectionMatrix = MatrixTransform::MakePerspectiveFovMatrix(0.45f, float(WINDOW_SIZE_WIDTH) / float(WINDOW_SIZE_HEIGHT), 0.1f, 100.0f);


		//ビューポート
		Matrix4x4 viewportMatrix = MatrixTransform::MakeViewportMatrix(0, 0, float(WINDOW_SIZE_WIDTH), float(WINDOW_SIZE_HEIGHT), 0.0f, 1.0f);

		unsigned int color = WHITE;

		if (IsCollisionTriangleAndSegment(segment, triangle)) {
			color = RED;
		}
		else {
			color = WHITE;
		}

		///
		/// ↑更新処理ここまで
		///

		DrawGrid(viewMatrix, projectionMatrix, viewportMatrix);


		DrawTriangle(triangle, viewMatrix, projectionMatrix, viewportMatrix, color);

		DrawSegment(segment, viewMatrix, projectionMatrix, viewportMatrix, color);

		///
		/// ↓描画処理ここから
		///

		ImGui::Begin("camera");
		ImGui::DragFloat3("cameraTranslate", &translate.x, 0.01f);
		ImGui::DragFloat3("cameraRotate", &rotate.x, 0.01f);
	
		ImGui::End();


		ImGui::Begin("Segment");
		ImGui::DragFloat3("Origin", &segment.origin.x, 0.01f);
		ImGui::DragFloat3("Diff", &segment.diff.x, 0.01f);
		ImGui::End();

		ImGui::Begin("Triangle");
		ImGui::DragFloat3("v1", &triangle.vertex1.x, 0.01f);
		ImGui::DragFloat3("v2", &triangle.vertex2.x, 0.01f);
		ImGui::DragFloat3("v3", &triangle.vertex3.x, 0.01f);

		ImGui::End();

	
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
