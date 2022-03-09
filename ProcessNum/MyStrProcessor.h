#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;
class MyStrProcessor
{
public:
	MyStrProcessor(string str);
	vector<string> split(char flag);
private:
	string m_str;
};

