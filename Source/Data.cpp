#include "Data.h"
#include "MyLibrary/CsvReader.h"

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
	void ReadData();

	std::map<std::string, area> areaList;
	std::map<std::string, button> buttonList;
}

void Data::Init()
{
	ReadData();
}

void Data::ReadData()
{
	CsvReader* csv = new CsvReader("data/ui.csv");
	std::string name;
	area a;
	for (int line = 1; line < csv->GetLines(); line++)
	{
		name = csv->GetString(line, AREA_DATA::NAME);
		a.leftTop.x = csv->GetInt(line, AREA_DATA::P1_X);
		a.leftTop.y = csv->GetInt(line, AREA_DATA::P1_Y);
		a.rightDown.x = csv->GetInt(line, AREA_DATA::P2_X);
		a.rightDown.y = csv->GetInt(line, AREA_DATA::P2_Y);

		areaList[name] = a;
	}
}
