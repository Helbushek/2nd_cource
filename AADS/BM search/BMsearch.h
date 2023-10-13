#pragma once
#include <string>
#include <vector>
#include <iostream>

enum class BmSearchType
{
	Once,
	All
};

std::vector<int> searchByBm(std::string& stringOfText, std::string& stringToSearch, int startDiaposon = 0, int endDiaposon = -1, BmSearchType type = BmSearchType::All);