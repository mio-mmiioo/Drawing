#include "Packet.h"

namespace Packet
{
	std::map<std::string, PACKET_DATA_TYPE> dataName;	// データの名前, データの種類
	std::vector<std::string> playerName;				// プレイヤーの名前
}

void Packet::Init()
{
	dataName["MAKE_ROOM"] = PACKET_DATA_TYPE::MAKE_ROOM;
	dataName["ENTER_ROOM"] = PACKET_DATA_TYPE::ENTER_ROOM;
	dataName["END_MAKE_ROOM"] = PACKET_DATA_TYPE::END_MAKE_ROOM;
	dataName["REGISTER_NAME"] = PACKET_DATA_TYPE::REGISTER_NAME;
}

PACKET Packet::ByteSwapMyData(PACKET data)
{
	PACKET ret;
	memcpy(ret.dataType, data.dataType, sizeof(ret.dataType));
	memcpy(ret.playerName, data.playerName, sizeof(ret.playerName));
	ret.hImage = htonl(data.hImage);
	
	return ret;
}
