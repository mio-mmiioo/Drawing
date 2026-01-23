#include "DxLib.h"
#include "Scene.h"
#include "Screen.h"
#include "MyLibrary/Input.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 初期化処理
	// 画面・DxLibの初期化
	SetGraphMode(Screen::WIDTH, Screen::HEIGHT, 32);
	SetOutApplicationLogValidFlag(FALSE); // ログを出さない
	ChangeWindowMode(Screen::WINDOW_MODE); // Windowモードの場合
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);
	//SetAlwaysRunFlag(TRUE);
	//SetUseZBuffer3D(TRUE);
	//SetWriteZBuffer3D(TRUE);
	
	// その他の初期化
	Input::InitActionMap();
	SceneMaster::CreateFirst(); // 最初のシーンを作成

	while (1)
	{
		// 更新処理
		Input::StateUpdate();
		SceneMaster::Update();

		// 描画処理
		ScreenFlip();
		ClearDrawScreen();
		SceneMaster::Draw();

		if (ProcessMessage() == -1 || Input::IsKeyDown("exit")) {
			break;
		}
	}

	return 0;
}