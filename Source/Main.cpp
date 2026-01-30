#include "DxLib.h"
#include "Scene.h"
#include "Screen.h"
#include "MyLibrary/Input.h"
#include "MyLibrary/Time.h"
#include "../ImGui/imgui_impl_dxlib.hpp"

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

	// ImGuiの初期化
	SetHookWinProc([](HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT /*CALLBACK*/
	{
		// DxLibとImGuiのウィンドウプロシージャを両立させる
		SetUseHookWinProcReturnValue(FALSE);
		return ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
	});

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.Fonts->AddFontFromFileTTF(u8"c:\\Windows\\Fonts\\meiryo.ttc", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());	ImGui_ImplDXlib_Init();
	
	// その他の初期化
	Input::InitActionMap();
	Time::Init();
	SceneMaster::CreateFirst(); // 最初のシーンを作成

	while (1)
	{

		// 更新処理
		Input::StateUpdate();
		Time::Update();
		ImGui_ImplDXlib_NewFrame();
		ImGui::NewFrame();
		SceneMaster::Update();

		// 描画処理
		ScreenFlip();
		ClearDrawScreen();
		SceneMaster::Draw();
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDXlib_RenderDrawData();

		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}

		if (ProcessMessage() == -1 || Input::IsKeyDown("exit")) {
			break;
		}
	}

	SceneMaster::Release();
	ImGui_ImplDXlib_Shutdown();
	ImGui::DestroyContext();

	return 0;
}