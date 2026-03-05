#pragma once

// 1人一つ立ち上げるので、classじゃない
namespace Player
{
	void Init();	// 初期化
	void Update();	// 更新処理
	void Draw();	// 描画処理
	void Release();	// 解放処理
}
