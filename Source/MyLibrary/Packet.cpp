#include "Packet.h"

namespace Packet
{
	std::map<std::string, PACKET_DATA_TYPE> dataName;	// データの名前, データの種類
	std::vector<std::string> playerName;				// プレイヤーの名前
}

void Packet::Init()
{
	// 受信したデータのcharをPACKET_DATA_TYPEに変えるときに使用
	dataName["MAKE_ROOM"] = PACKET_DATA_TYPE::MAKE_ROOM;
	dataName["ENTER_ROOM"] = PACKET_DATA_TYPE::ENTER_ROOM;
	dataName["END_MAKE_ROOM"] = PACKET_DATA_TYPE::END_MAKE_ROOM;
	dataName["CHANGE_NAME"] = PACKET_DATA_TYPE::CHANGE_NAME;
	dataName["START_PLAY"] = PACKET_DATA_TYPE::START_PLAY;
	dataName["START_GAME"] = PACKET_DATA_TYPE::START_GAME;
	dataName["STOP_GAME"] = PACKET_DATA_TYPE::STOP_GAME;
	dataName["SEND_IMAGE"] = PACKET_DATA_TYPE::SEND_IMAGE;
	dataName["PLAYER_COUNT"] = PACKET_DATA_TYPE::PLAYER_COUNT;
	dataName["START_RESULT"] = PACKET_DATA_TYPE::START_RESULT;
	dataName["START_MATCHING"] = PACKET_DATA_TYPE::START_MATCHING;
}

PACKET Packet::ByteSwapMyData(PACKET data)
{
	PACKET ret;
	memcpy(ret.dataType, data.dataType, sizeof(ret.dataType));
	memcpy(ret.playerName, data.playerName, sizeof(ret.playerName));
	ret.number= htonl(data.number);
	
	return ret;
}
