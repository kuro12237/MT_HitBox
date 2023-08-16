#include <Novice.h>
#include"3dModel/Grid.h"
#include"3dModel/Sphre.h"
#include"ImGuiManager.h"

const char kWindowTitle[] = "LE2B_14_サカキバラ_イブキ";


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

	float radius = 0.2f;
	Vector3 localCoodinate = { 0.0f,0.0f,1.0f };
	SpherePloperty sphere = { localCoodinate,radius };

	const int WINDOW_SIZE_WIDTH = 1280;
	const int WINDOW_SIZE_HEIGHT = 720;

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

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		DrawGrid(viewMatrix, projectionMatrix, viewportMatrix);


		DrawSphere(sphere, viewMatrix, viewportMatrix,BLACK);

		ImGui::Begin("Window");
		ImGui::DragFloat3("cameraTranslate", &translate.x, 0.01f);
		ImGui::DragFloat3("cameraRotate", &rotate.x, 0.01f);
		ImGui::DragFloat3("spherePos", &sphere.center.x, 0.01f);

		ImGui::DragFloat("SphereRadius", &sphere.radius, 0.01f);
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
