#pragma once
#include <string>
#include <vector>

class CsvReader
{
public:
	CsvReader(std::string filename);
	~CsvReader();
	int GetLines(); // 行数を取得する
	int GetColums(int line); // 指定した行のカラム数を取得する
	std::string GetString(int line, int column); // 指定した行・列のデータを文字列で返す
	int GetInt(int line, int column); // 指定した行・列のデータをint型の数値で返す
	float GetFloat(int line, int column); // 指定した行・列のデータをfloat型の数値で返す
private:
	struct LINEREC {
		std::vector<std::string> record;
	};
	std::vector<LINEREC> all;
};


