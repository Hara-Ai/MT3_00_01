#include <Novice.h>
#include <cmath>

const char kWindowTitle[] = "GC2B_14_ハラ_アイ_タイトル";

struct Vector3
{
	float x, y, z;
};

//加算
Vector3 add(const Vector3& v1, const Vector3& v2)
{
	return { v1.x + v2.x,v1.y + v2.y,v1.z + v2.z };
}

//減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2)
{
	return { v1.x - v2.x,v1.y - v2.y,v1.z - v2.z };
}

//スカラー倍
Vector3 Multiply(float scalar, const Vector3& v2)
{
	return { scalar * v2.x,scalar * v2.y,scalar * v2.z };
}

float Dot(const Vector3& v1, const Vector3& v2)
{
	return { v1.x * v2.x + v1.y * v2.y + v1.z * v2.z };
}

//長さ(イルム)
float Length(const Vector3& v)
{
	return{ std::sqrt(Dot(v,v)) };
}

//正規化
Vector3 Nirmalize(const Vector3& v)
{
	float length = Length(v);
	return{ v.x / length,v.y / length,v.z / length };
}

static const int kColumnWidth = 60;
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label)
{
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	const int kWindowWidth = 1280; // ウィンドウの横幅
	const int kWindowHeight = 720; // ウィンドウの縦幅

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	Vector3 v1{ 1.0f,3.0f,-5.0f };
	Vector3 v2{ 4.0f,-1.0f,2.0f };
	float k = 4.0f;

	int kRowHeigt = 20;

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

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

		Vector3 resultadd = add(v1, v2);
		Vector3 resultSubtract = Subtract(v1, v2);
		Vector3 resultMultiply = Multiply(k, v1);
		float resultDot = Dot(v1, v2);
		float resultLength = Length(v1);
		Vector3 resultNormalize = Nirmalize(v2);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		VectorScreenPrintf(0, 0, resultadd, " : add");
		VectorScreenPrintf(0, kRowHeigt, resultSubtract, " : Subtract");
		VectorScreenPrintf(0, kRowHeigt * 2, resultMultiply, " : Multiply");
		Novice::ScreenPrintf(0, kRowHeigt * 3, "%.02f : Dot", resultDot);
		Novice::ScreenPrintf(0, kRowHeigt * 4, "%.02f : Length", resultLength);
		VectorScreenPrintf(0, kRowHeigt * 5, resultNormalize, " : Normalize");

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