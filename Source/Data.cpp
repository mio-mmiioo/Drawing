#include "Data.h"
#include "MyLibrary/CsvReader.h"
#include "Image.h"

namespace Data
{
	enum AREA_DATA
	{
		NAME,
		PARENT_NAME,
		P1_X,
		P1_Y,
		P2_X,
		P2_Y,
		COLOR,
		IMAGE,
		BUTTON
	};

	const std::string SERVER_IPADDRESS = "127.0.0.1";   // サーバーのIPアドレス
	const unsigned short SERVER_PORT = 8888;            // サーバーのポート番号

	void ReadData();

	std::map<std::string, area> areaList;
	std::map<std::string, button> buttonList;

	Client* client;
}

void Data::Init()
{
	ReadData();
	Packet::Init();
	client = new Client(SERVER_IPADDRESS, SERVER_PORT);
	client->Init();

	roomNumber = SERVER_PORT;
}

void Data::SendData(std::string message, int number)
{
	PACKET sendData;
	strncpy_s(sendData.dataType, sizeof(sendData.dataType), message.c_str(), _TRUNCATE);
	sendData.number = number;
	strncpy_s(sendData.playerName, sizeof(sendData.playerName), clientName.c_str(), _TRUNCATE);
	client->SetClient(sendData);
	client->SendData();
}

bool Data::isStartPlay()
{
	std::string dataType = client->GetReciveData().dataType;
	if (dataType == "START_PLAY")
	{
		return true;
	}
	return false;
}

bool Data::isStartMatching()
{
	std::string dataType = client->GetReciveData().dataType;
	if (dataType == "START_MATCHING")
	{
		clientName = client->GetReciveData().playerName;
		PACKET clientData = client->GetData();
		strncpy_s(clientData.playerName, sizeof(clientData.playerName), clientName.c_str(), _TRUNCATE);
		client->SetClient(clientData);
		return true;
	}
	return false;
}

Client* Data::GetClient()
{
	return client;
}

void Data::ReadData()
{
	CsvReader* csv = new CsvReader("data/ui.csv");
	std::string name;
	area a;
	button b;
	for (int line = 1; line < csv->GetLines(); line++)
	{
		
		name = csv->GetString(line, AREA_DATA::NAME);
		a.leftTop.x = csv->GetInt(line, AREA_DATA::P1_X);
		a.leftTop.y = csv->GetInt(line, AREA_DATA::P1_Y);
		a.rightDown.x = csv->GetInt(line, AREA_DATA::P2_X);
		a.rightDown.y = csv->GetInt(line, AREA_DATA::P2_Y);

		if (csv->GetString(line, AREA_DATA::COLOR) == "TRUE")
		{
			// 色の設定はまだ
		}

		if (csv->GetString(line, AREA_DATA::IMAGE) == "TRUE")
		{
			a.hImage = Image::hImage[name];
		}

		areaList[name] = a;

		if (csv->GetString(line, AREA_DATA::BUTTON) == "TRUE")
		{
			b.bArea = a;
			buttonList[name] = b;
		}

		a.color = -1;
		a.hImage = -1;
		a.leftTop.x = -1;
		a.leftTop.y = -1;
		a.rightDown.x = -1;
		a.rightDown.y = -1;
	}
}
