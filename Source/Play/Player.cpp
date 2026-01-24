#include "Player.h"
#include "DxLib.h"
#include "../MyLibrary/Input.h"
#include "../MyLibrary/Color.h"
#include <vector>

namespace Player
{
	struct point
	{
		int x;
		int y;
	};
	std::vector<std::vector<point>> drawLine;
	int lineCount;
	float lineHalfWidth; // ペンの太さ
	int mouseX; // マウスのx座標
	int mouseY; // マウスのy座標
}

void Player::Init()
{
	lineCount = 0;
	lineHalfWidth = 5.0f;
	GetMousePoint(&mouseX, &mouseY);

}

void Player::Update()
{
	GetMousePoint(&mouseX, &mouseY);
	point current = { mouseX, mouseY };
	if (Input::IsKeyDown("drawing"))
	{
		std::vector<point> tmp;
		tmp.push_back(current);
		drawLine.push_back(tmp);
	}
	else if (Input::IsKeyKeepDown("drawing"))
	{
		drawLine[lineCount].push_back(current);
	}
	else if (Input::IsKeyUp("drawing"))
	{
		lineCount += 1;
	}
}

void Player::Draw()
{
	// これまでに描いた線を描画
	{
		int x;
		int y;
		int nextX;
		int nextY;

		for (int lineCounter = 0; lineCounter < drawLine.size(); lineCounter++)
		{
			for (int pointCounter = 0; pointCounter < drawLine[lineCounter].size() - 1; pointCounter++)
			{
				x = drawLine[lineCounter][pointCounter].x;
				y = drawLine[lineCounter][pointCounter].y;
				nextX = drawLine[lineCounter][pointCounter + 1].x;
				nextY = drawLine[lineCounter][pointCounter + 1].y;
				DrawLine(x, y, nextX, nextY, Color::RED, lineHalfWidth);
			}
		}
	}
}

void Player::Release()
{
	drawLine.clear();
}

