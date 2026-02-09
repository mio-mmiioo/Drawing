#include "Data.h"
#include "MyLibrary/CsvReader.h"

namespace Data
{
	void ReadData();

	std::map<std::string, area> areaList;
}

void Data::Init()
{

}

void Data::ReadData()
{
	CsvReader* csv = new CsvReader("data/ui.csv");
	std::string name;
	for (int i = 0; i < csv->GetLines(); i++)
	{

	}
}
