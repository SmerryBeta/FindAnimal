#pragma once
#include <map>
#include <vector>
#include <string>


class Repository
{
public:
	Repository();
	~Repository();
	virtual std::map<std::wstring, std::vector<std::wstring>> getMap() = 0;
};

