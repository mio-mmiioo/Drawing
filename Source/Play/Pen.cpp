#include "Pen.h"
#include "DxLib.h"
#include "../MyLibrary/Color.h"
#include "../../ImGui/imgui.h"
#include <vector>

namespace Pen
{
	const area CHANGE_PEN_WIDTH = { 80, 100, 120, 340 }; // ペンの太さを変更する場所
	const point WIDTH_LINE_TOP = { 100, 120 }; // ペンの太さ変更線の上の座標
	const point WIDTH_LINE_DOWN = { 100, 320 }; // ペンの太さ変更線の下の座標
	const float WIDTH_LINE_WIDTH = 2.0f; // ペンの太さ変更線の太さ

	const area CANVAS = { 50, 50, 650, 550 }; // 絵が描ける範囲

	
	button changeColor; // 色を変更
	button changeWidth; // 線の幅を変更
	button eraser; // 消しゴム

	point pMouse; // playerのマウスの座標

	std::vector<area> drawAreaList; 
	MY_RGB penRGB; // ペンの色 RGB
	MY_HSV penHSV; // ペンの色 HSV

	// 画像
	int hColorPaletteImage; // カラーパレットの画像
}

void Pen::Init()
{
	eraser = { 800, 200, 820, 220, 0, 0, 0, 0, false };
	changeWidth = { 820, 200, 840, 220, 0, 0, 0, 0, false };
	changeColor = { 840, 200, 860, 220, 800, 300, 1000, 500, false };

	penRGB = { 0, 100, 0 };
	penHSV = Color::RGBtoHSV(penRGB);
}

void Pen::Draw()
{
	Area::DrawArea(CANVAS, Color::CANVAS);
	Area::DrawArea(changeColor.bArea, Color::B_COLOR);
	Area::DrawArea(eraser.bArea, Color::B_ERASER);
	Area::DrawArea(changeWidth.bArea, Color::B_WIDTH);

	if (changeColor.isClickArea == true)
	{
		DrawCircle(100, 500, 20, Color::CHANGE_CIRCLE, TRUE); // 確認のために描画
	}

	// 色パレットの描画 ※画像に置き換える/毎回描画すると処理が重くなる可能性があるから
	{
		int radius = (changeColor.cArea.rightDown.x - changeColor.cArea.leftTop.x) / 2;
		int centerX = changeColor.cArea.leftTop.x + radius;
		int centerY = changeColor.cArea.leftTop.y + radius;
		
		// 現在の色の表示
		DrawCircle(centerX, changeColor.cArea.leftTop.y - 20, 10.0f, Color::GetColorMYRGB(penRGB), TRUE);
		
		// 円形パレット
		for (int y = -radius; y <= radius; y++) {
			for (int x = -radius; x <= radius; x++) {
				float d = sqrt(x * x + y * y);
				if (d <= radius) {
					// 角度と距離を計算
					float h = (float)(atan2(y, x) * 180.0f / DX_PI) + 180.0f;
					float s = d / radius;
					MY_RGB c = Color::HSVtoRGB(h, s, 1.0f);
					DrawPixel(centerX + x, centerY + y, GetColor(c.red, c.green, c.blue));
				}
			}
		}

		// 輝度
		for (int i = 0; i < 200; i++) {
			int gray = (int)(i * (255.0 / 200.0));
			DrawLine(changeColor.cArea.leftTop.x + i, changeColor.cArea.rightDown.y + 20, changeColor.cArea.leftTop.x + i,
				changeColor.cArea.rightDown.y + 50, GetColor(gray, gray, gray));
		}

		// 現在の選択色からHSVを出す
		penHSV = Color::RGBtoHSV(penRGB);

		// HSVから座標を逆算 (角度hは補正分を引く)
		float h = penHSV.h - 180.0f; // 取得時に足した分を引く
		float rad = h * DX_PI_F / 180.0f;
		float s = penHSV.s;

		int cursorX = centerX + (int)(cos(rad) * s * radius);
		int cursorY = centerY + (int)(sin(rad) * s * radius);

		// 選択位置に丸を描画
		DrawCircle(cursorX, cursorY, 5, Color::BLACK, FALSE);
	}

}

void Pen::SetMousePosition(point playerMouse)
{
	pMouse = playerMouse;
}

bool Pen::IsCanUse(bool* isCanUsePen)
{
	// キャンバス内にあるなら使用可能　ないなら使用不可
	if (Area::IsInArea(CANVAS, pMouse))
	{
		*isCanUsePen = true;
		return true;
	}
	return false;
}

void Pen::SetColor(int* color)
{
	*color = GetColor(penRGB.red, penRGB.green, penRGB.blue);
}

void Pen::UpdateChangePenWidth(float* lineWidth)
{
	int y = (pMouse.y - WIDTH_LINE_TOP.y);
	*lineWidth = y / 4;
}

// 色を変える処理、中身はまだ
void Pen::ChangeColor(int* color)
{
	if (Area::IsInArea(changeColor.bArea, pMouse) == true)
	{
		if (changeColor.isClickArea == true)
		{
			changeColor.isClickArea = false;
		}
		else
		{
			changeColor.isClickArea = true;
		}
	}

	if (changeColor.isClickArea == true)
	{
		// ここで色を変える処理
		int radius = (changeColor.cArea.rightDown.x - changeColor.cArea.leftTop.x) / 2;
		point center = {
			changeColor.cArea.leftTop.x + radius,
			changeColor.cArea.leftTop.y + radius
		};

		// カラーパレットとマウスの距離が一定以内の場合
		if (Area::CheckPointDistance(center, pMouse, radius) == true)
		{
			float h = (float)(atan2((pMouse.y - center.y), (pMouse.x - center.x)) * 180.0f / DX_PI) + 180.0f;
			if (h < 0)
			{
				h += 360.0f;
			}
			else if (h > 360.0f)
			{
				h -= 360.0f;
			}
			float dist = (pMouse.x - center.x) * (pMouse.x - center.x) + (pMouse.y - center.y) * (pMouse.y - center.y);
			dist = sqrtf(dist);
			float s = dist / radius;

			// 4. HSVをRGBに変換して変数に保存
			penRGB = Color::HSVtoRGB(h, s, 1.0f);
			*color = Color::GetColorMYRGB(penRGB);
		}
	}
}

// こっちに正しい処理をかく
void Pen::ChangeWidth(float* lineWidth)
{
	if (Area::IsInArea(changeWidth.bArea, pMouse) == true)
	{
		if (changeWidth.isClickArea == true)
		{
			changeWidth.isClickArea = false;
		}
		else
		{
			changeWidth.isClickArea = true;
		}

		if (changeWidth.isClickArea == true)
		{
			// 線の太さ変更の処理
			int y = (pMouse.y - WIDTH_LINE_TOP.y);
			*lineWidth = y / 4;
		}
	}
}

void Pen::Erase(int* color)
{
	if (Area::IsInArea(eraser.bArea, pMouse) == true)
	{
		if (eraser.isClickArea == true)
		{
			eraser.isClickArea = false;
			*color = GetColor(penRGB.red, penRGB.green, penRGB.blue);
		}
		else
		{
			eraser.isClickArea = true;
			*color = Color::ERASER;
		}
	}
}

void Pen::DrawChangePenWidth(float lineWidth)
{
	if (changeWidth.isClickArea == true)
	{
		point p1 = WIDTH_LINE_TOP;
		point p2 = WIDTH_LINE_DOWN;
		DrawLine(p1.x, p1.y, p2.x, p2.y, Color::WIDTH_LINE, WIDTH_LINE_WIDTH);
		DrawCircle(p1.x, p1.y + lineWidth * 4, lineWidth / 2, Color::PEN_CIRCLE, TRUE);
	}
}
