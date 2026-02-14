#include "Player.h"
#include "DxLib.h"
#include "../../ImGui/imgui.h"
#include "../MyLibrary/Time.h"
#include "../MyLibrary/Input.h"
#include "../MyLibrary/Color.h"
#include "../MyLibrary/Client.h"
#include "Theme.h"
#include "Pen.h"
#include "Area.h"
#include "../Data.h"
#include <vector>

// 一時的にこの場所に書いている
const std::string SERVER_IPADDRESS = "127.0.0.1";   // サーバーのIPアドレス
const unsigned short SERVER_PORT = 8888;            // サーバーのポート番号


namespace Player
{
	enum PHASE
	{
		THEME, // お題入力
		DRAWING, // お絵描き
		WAITE, // 待ち時間
		MAX_P_STATE
	};

	const float THEME_TIME = 5.0; // お題入力 60秒
	const float DRAWING_TIME = 30.0f; // お絵描き 180秒

	point canvasImageArea;
	point themeImageArea;

	void UpdateDrawing(); // ペンで絵を描く処理
	void DrawDrawing(); // お絵描き関連の描画
	void UpdateTheme(); // お題を入力する処理
	void DrawTheme(); // お題入力関連の描画
	void UpdateWaite(); // 待ち時間の処理 ( ここで通信処理を入れる )
	void DrawWaite(); // 待ち時間の描画
	void ImGuiInput(); 

	std::vector<std::vector<point>> drawLine; // 線の位置情報
	std::vector<int> drawLineColor; // 線の色の情報
	std::vector<float> drawLineWidth; // 線の太さの情報
	int lineCount; // 絵に描かれている線の数
	float lineWidth; // ペンの太さ
	point mouse; // マウスの座標
	bool isCanUsePen; // true → ペンが使用可能 

	PHASE phase; // 状態を管理する
	PHASE nextPhase; // 次の状態
	float timer; // 時間を管理するための変数
	int penRGB; // ペンの色

	// 画像
	int hSendImage; // 送信データ
	int hRecvImage; // 受信データ


	Client* client;

}

void Player::Init()
{
	canvasImageArea = Data::areaList["Canvas"].leftTop;
	area tmp = Data::areaList["ThemeImage"];
	themeImageArea = { tmp.leftTop.x, tmp.rightDown.y - tmp.leftTop.y };

	lineCount = 0;
	lineWidth = 10.0f;
	GetMousePoint(&mouse.x, &mouse.y);
	isCanUsePen = false;
	phase = PHASE::THEME;
	nextPhase = PHASE::WAITE;
	timer = THEME_TIME;
	penRGB = -1;
	hSendImage = -1;

	Pen::Init();
	Theme::Init();
	Pen::SetColor(&penRGB);

	client = new Client(SERVER_IPADDRESS, SERVER_PORT);
	client->Init();
}

void Player::Update()
{
	GetMousePoint(&mouse.x, &mouse.y);
	timer -= Time::DeltaTime();

	ImGuiInput();

	switch (phase)
	{
	case PHASE::THEME:
		UpdateTheme();
		break;
	case PHASE::DRAWING:
		UpdateDrawing();
		break;
	case PHASE::WAITE:
		UpdateWaite();
		timer += Time::DeltaTime();
		break;
	default:
		break;
	}

	if (timer <= 0.0f)
	{
		if (phase == PHASE::DRAWING)
		{
			Pen::MakeCanvasImage(&hSendImage); // サーバーに送るデータを作成
			timer += THEME_TIME;
			nextPhase = PHASE::THEME;
			drawLine.clear();
			drawLineColor.clear();
			drawLineWidth.clear();
			lineCount = 0;
		}
		else if (phase == PHASE::THEME)
		{
			Theme::MakeThemeImage(&hSendImage);
			timer += DRAWING_TIME;
			nextPhase = PHASE::DRAWING;
		}
		phase = WAITE;
		client->SetClient(PACKET({ hSendImage })); // サーバーに送るデータをセット
		client->SendData();
	}
}

void Player::Draw()
{
	// フェーズによって描画内容を変更する
	switch (phase)
	{
	case PHASE::THEME:
		DrawTheme();
		break;
	case PHASE::DRAWING:		
		DrawDrawing();
		break;
	case PHASE::WAITE:
		DrawWaite();
		break;
	default:
		break;
	}
}

void Player::Release()
{
	drawLine.clear();
}

void Player::UpdateDrawing()
{
	isCanUsePen = false;
	Pen::SetMousePosition(mouse);
	Pen::IsCanUse(&isCanUsePen);

	// 1つ戻る
	if (Input::IsKeyDown("back") && drawLine.size() > 0)
	{
		drawLine.pop_back();
		lineCount -= 1;
	}
	// 色を変更する
	if (Input::IsKeyDown("changeColor"))
	{
		Pen::ChangeColor(&penRGB);
	}
	// 消しゴム
	if (Input::IsKeyDown("eraser"))
	{
		Pen::Erase(&penRGB);
	}
	// 線の太さを変更する 機能の実装はまだ
	if (Input::IsKeyDown("changeWidth"))
	{
		Pen::ChangeWidth(&lineWidth);
	}

	// 線を描く
	if (isCanUsePen == true)
	{
		if (Input::IsKeyDown("drawing"))
		{
			std::vector<point> tmp;
			tmp.push_back(mouse);
			drawLine.push_back(tmp);
			drawLineColor.push_back(penRGB);
			drawLineWidth.push_back(lineWidth);
		}
		else if (Input::IsKeyKeepDown("drawing"))
		{
			drawLine[lineCount].push_back(mouse);
		}
		else if (Input::IsKeyUp("drawing"))
		{
			lineCount += 1;
		}
	}
}

void Player::DrawDrawing()
{
	DrawGraph(themeImageArea.x, themeImageArea.y, hSendImage, TRUE); // マジックナンバー使用中
	Pen::Draw();
	Pen::DrawChangePenWidth(lineWidth);
	// これまでに描いた線を描画
	{
		int x;
		int y;
		int nextX;
		int nextY;
		int c;
		float lineW;

		for (int l = 0; l < drawLine.size(); l++)
		{
			c = drawLineColor[l];
			lineW = drawLineWidth[l];
			for (int p = 0; p < drawLine[l].size() - 1; p++)
			{
				x = drawLine[l][p].x;
				y = drawLine[l][p].y;
				nextX = drawLine[l][p + 1].x;
				nextY = drawLine[l][p + 1].y;

				// 線or丸のみだと、不自然な描画になってしまうため、どちらも描画
				DrawLine(x, y, nextX, nextY, c, lineW);
				DrawCircle(x, y, lineW / 2, c, TRUE);
			}
		}
	}
}

void Player::UpdateTheme()
{
	Theme::InputTheme();
}

void Player::DrawTheme()
{
	DrawGraph(canvasImageArea.x, canvasImageArea.y, hSendImage, TRUE);
	Theme::Draw();
}

void Player::UpdateWaite()
{
	// ここで通信待ちの処理、データの受け取りなどする
	client->ReceiveData();
	hRecvImage = client->GetClient().hImage;
	if (hRecvImage > 0)
	{
		phase = nextPhase;
	}
}

void Player::DrawWaite()
{
}

void Player::ImGuiInput()
{
	ImGui::Begin("Player");
	switch (phase)
	{
	case PHASE::THEME:
		ImGui::Text("THEME");
		break;
	case PHASE::DRAWING:
		ImGui::Text("DRAWING");
		break;
	case PHASE::WAITE:
		ImGui::Text("WAITE");
		break;
	default:
		ImGui::Text("NO_STATE");
		break;
	}

	ImGui::Text("timer : %f", timer);
	ImGui::Text("pen width : %f", lineWidth);
	ImGui::End();
}

