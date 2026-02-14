#include "Client.h"
#include "DxLib.h"
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <vector>

#include "Packet.h"
#include "../../ImGui/imgui.h"


#pragma comment(lib, "ws2_32.lib")
using namespace std;

Client::Client(std::string serverIPAddress, int portNumber)
{
	serverIPAddress_ = serverIPAddress;
	portNumber_ = portNumber;
	data_.client = INIT;
}

Client::~Client()
{
	// ソケット破棄
	closesocket(sock_);
	WSACleanup();
}

int Client::Init()
{
	// WinSock2.2 初期化
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return -1;
	}

	// ソケット作成
	sock_ = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_ == INVALID_SOCKET)
	{
		return -1;
	}

	// ノンブロッキングモード設定
	unsigned long arg = 0x01;
	ioctlsocket(sock_, FIONBIO, &arg);

	// サーバアドレス設定
	SOCKADDR_IN serverSockAddress;
	memset(&serverSockAddress, 0, sizeof(serverSockAddress));
	serverSockAddress.sin_family = AF_INET;
	serverSockAddress.sin_port = htons(portNumber_);
	inet_pton(AF_INET, serverIPAddress_.c_str(), &serverSockAddress.sin_addr.s_addr);

	if (connect(sock_, (SOCKADDR*)&serverSockAddress, sizeof(serverSockAddress)) == SOCKET_ERROR)
	{
		// 非同期なので、いったん無視で続行　( selectで待機などは未実装 )
	}
	return 1;
}

void Client::SendData()
{
	// サーバに送信する構造体をネットワークバイトオーダーで作成
	data_.tmp = ByteSwapMyData(data_.client);
	send(sock_, (char*)&data_.tmp, sizeof(data_.tmp), 0); // サーバーにデータを送信
}

void Client::ReceiveData()
{
	data_.recv.clear(); // 前回のデータを削除
	while (true)
	{
		int ret = recv(sock_, (char*)&(data_.tmp), sizeof(data_.tmp), 0);
		if (ret > 0)
		{
			data_.recv.push_back(ByteSwapMyData(data_.tmp)); // データがある場合、受け取ったデータとして配列に追加する
		}
		else
		{
			// データがない場合ループを抜ける
			// エラー処理を追加したい場合ここ
			break;
		}
	}
}
