#include "MyStrProcessor.h"

MyStrProcessor::MyStrProcessor(string str):m_str(str)
{
}

vector<string> MyStrProcessor::split(char flag)
{
	vector<string> outPutStrArr;
	string str;
	for (auto it : m_str) {
		if (it == '\0')
			return outPutStrArr;
		if (it != flag)
		{
			str.push_back(it);
			continue;
		}
		outPutStrArr.push_back(str);
		str.erase();
	}
	return outPutStrArr;
}
