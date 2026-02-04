#include "Theme.h"
#include "DxLib.h"
#include <string>
#include "Area.h"
#include "../Image.h"

namespace Theme
{
	const area IMAGE_AREA = { 50, 600, 800, 620 }; // お題入力として切り取る範囲
	const int MAX_LENGTH = 200; // 入力できる最大文字数(半角文字単位)

	std::string writingTheme;
	int keyInput; // 入力データ文字列が欲しいキー入力のハンドル
}

void Theme::Init()
{
	writingTheme.clear();
	Theme::keyInput = MakeKeyInput(MAX_LENGTH, FALSE, FALSE, FALSE);
}

void Theme::Draw()
{
	DrawKeyInputString(IMAGE_AREA.leftTop.x, IMAGE_AREA.leftTop.y, Theme::keyInput);
	//DrawKeyInputModeString(x, y); // ひらがな、とか入力のやつを表示したい場合
}

void Theme::InputTheme()
{
	SetActiveKeyInput(Theme::keyInput);

	if (CheckKeyInput(Theme::keyInput) == 1)
	{
		char buf[256] = { 0 }; // バッファを初期化
		GetKeyInputString(buf, Theme::keyInput); // bufに文字列を代入 0が返ってきてるなら成功
		std::string str(buf); // bufからstringを生成
		writingTheme = str; // 代入

	}
}

void Theme::MakeThemeImage(int* hImage)
{
	Image::MakeImage(IMAGE_AREA, hImage);

	// ついでにお掃除をする
	DeleteKeyInput(keyInput);
	Theme::keyInput = MakeKeyInput(MAX_LENGTH, FALSE, FALSE, FALSE);
}
