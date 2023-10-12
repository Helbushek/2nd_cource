#pragma once
#include <string>
#include <vector>
#include <iostream>
//#include "BMsearch.cpp"
enum class BmSearchType
{
	Once,
	All
};

std::vector<int> searchByBm(std::string stringOfText, std::string stringToSearch, BmSearchType type = BmSearchType::All, int startDiaposon = 0, int endDiaposon = -1);