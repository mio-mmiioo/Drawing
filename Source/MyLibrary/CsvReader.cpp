#include "CsvReader.h"
#include <fstream>
#include <assert.h>

CsvReader::CsvReader(std::string filename)
{
	all.clear();
	std::ifstream ifs(filename);
	if (!ifs) return;
	unsigned char SKIP[] = { 0xEF, 0xBB, 0XBF };
	bool found = true;
	for (int i = 0; i < 3; i++)
	{
		if (ifs.get() != SKIP[i])
		{
			found = false;
			break;
		}
	}
	if (found == false)
	{
		ifs.seekg(std::ios_base::beg);
	}

	// データを読む
	std::string lineString;
	while (getline(ifs, lineString))
	{
		while (true)
		{
			int dq = 0;
			for (int i = 0; i < lineString.size(); i++)
			{
				if (lineString[i] == '"')
				{
					dq++;
				}
			}
			if (dq % 2 == 0)
			{
				break;
			}
			std::string s;
			getline(ifs, s);
			lineString += "\n" + s;
		}
		for (auto it = lineString.begin(); it != lineString.end();)
		{
			if (*it == '"')
			{
				it = lineString.erase(it);
			}
			if (it != lineString.end())
			{
				it++;
			}
		}
		// 行の中身を , で区切る
		LINEREC lineRecord;
		int top = 0;
		bool indq = false;
		for (int n = 0; n < lineString.size(); n++)
		{
			if (lineString[n] == ',')
			{
				if (indq == false)
				{
					lineRecord.record.emplace_back(lineString.substr(top, (size_t)(n - top)));
					top = n + 1;
				}
			}
			else if (lineString[n] == '"')
			{
				indq = !indq;
			}
		}
		lineRecord.record.emplace_back(lineString.substr(top, lineString.size() - top));
		all.emplace_back(lineRecord);
	}
	ifs.close();
}

CsvReader::~CsvReader()
{
	for (auto rec : all)
	{
		rec.record.clear();
	}
	all.clear();
}

int CsvReader::GetLines()
{
	return (int)all.size();
}

int CsvReader::GetColums(int line)
{
	assert(line < GetLines());
	return (int)all[line].record.size();
}

std::string CsvReader::GetString(int line, int column)
{
	assert(line < GetLines());
	if (column >= GetColums(line))
	{
		return "";
	}
	return all[line].record[column];
}

int CsvReader::GetInt(int line, int column)
{
	std::string str = GetString(line, column);
	if (str == "")
	{
		return 0;
	}
	return std::stoi(str);
}

float CsvReader::GetFloat(int line, int column)
{
	std::string str = GetString(line, column);
	if (str == "")
	{
		return 0.0f;
	}
	return std::stof(str);
}
