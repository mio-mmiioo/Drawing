#pragma once
#include "DxLib.h"

// 受信したいデータの中身
static struct PACKET
{
    int hImage;
};

// バイトオーダーを変換する関数
// PACKET内を書き換えたら書き換える必要がある
// ※本当はサイズを確認しから変換するべき
static PACKET ByteSwapMyData(PACKET data)
{
    PACKET ret;
    ret.hImage = htonl(data.hImage);

    return ret;
}

static PACKET INIT = { -1 }; // 初期データ
