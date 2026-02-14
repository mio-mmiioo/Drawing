#pragma once
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <vector>
#include <string>
#include "Packet.h" // 作成したデータ型を読み込む

#pragma comment(lib, "ws2_32.lib")

struct CLIENT_DATA
{
	PACKET client;				// クライアント自身のデータ
	PACKET tmp;					// 送受信する際の一時的にデータを保存するための変数
	std::vector<PACKET> recv;	// サーバーからのデータを受け取る際に使用
};

/// <summary>
/// 自身で作成したstruct構造を送受信したい場合、
/// Packet.hのPACKETの中身を変更してください
/// </summary>
class Client
{
public:
	Client(std::string serverIPAddress, int portNumber); // (サーバーのIPアドレス, ポート番号)
	~Client();		// デストラクタ
	int Init();		// 初期化処理

	void SetClient(PACKET client) { data_.client = client; }	// クライアント自身に情報をセットする
	PACKET GetClient() { return data_.client; }					// クライアント自身の情報の取得
	std::vector<PACKET> GetReciveData() { return data_.recv; }	// サーバーから受け取ったデータの取得

	void SendData();	// データの送信
	void ReceiveData();	// データの受信

private:
	SOCKET sock_;					// 自身のソケット
	std::string serverIPAddress_;	// サーバーのIPアドレス
	int portNumber_;				// ポート番号

	CLIENT_DATA data_; // 作成したデータ型で作られるデータ
};
