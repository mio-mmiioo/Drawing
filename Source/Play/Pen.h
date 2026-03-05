#pragma once
#include "../MyLibrary/Area.h"

namespace Pen
{
	void Init(); // 初期化
	void Draw(); // 描画処理
	void SetMousePosition(point playerMouse); // マウスの位置をセットする
	bool IsCanUse(bool* isCanUsePen); // ペンを使用できるか否か
	void MakeCanvasImage(int* hImage); // 引数に、キャンバスに書かれている絵を画像として保存する
	void SetColor(int* color); // 色の指定

	void ChangeColor(int* color);		// ペンの色を変更する
	void ChangeWidth(float* lineWidth); // ペンの太さを変更する
	void Erase(int* color);				// 消しゴムを使用する(ペンの色をキャンバスの色に変更する)

	void DrawChangePenWidth(float lineWidth);
}
