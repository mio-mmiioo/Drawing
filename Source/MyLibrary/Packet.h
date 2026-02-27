#pragma once
#include <WinSock2.h>
#include <vector>
#include <string>
#include <map>

// 受信したデータの種類
enum PACKET_DATA_TYPE
{
    MAKE_ROOM,		// 部屋立ち上げ
    ENTER_ROOM,		// 入室
    END_MAKE_ROOM,	// 部屋作成完了
    CHANGE_NAME,	// 名前の登録
    START_PLAY,     // プレイ画面開始
    STOP_GAME,		// 回答待ち
    START_GAME,		// ゲーム再開
    SEND_IMAGE,		// 回答・お題の画像
    START_MATCHING, // マッチング画面開始
    MAX_PACKET_TYPE
};

// 受信したいデータの中身
struct PACKET
{
    char dataType[256];
    char playerName[256];
    int number;
};

namespace Packet
{
    void Init(); // 初期化 Serverと同じ

    // バイトオーダーを変換する関数
    // PACKET内を書き換えたら書き換える必要がある
    // ※本当はサイズを確認しから変換するべき
    PACKET ByteSwapMyData(PACKET data);


    extern std::map<std::string, PACKET_DATA_TYPE> dataName;	// データの名前, データの種類
    extern std::vector<std::string> playerName;					// プレイヤーの名前

}

