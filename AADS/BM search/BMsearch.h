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

//std::vector<int> searchByBm(std::string stringOfText, std::string stringToSearch, BmSearchType type = BmSearchType::All, int startDiaposon = 0, int endDiaposon = -1);

std::vector<int> searchByBm(std::string stringOfText, std::string stringToSearch, BmSearchType type = BmSearchType::All, int startDiaposon = 0, int endDiaposon = -1) {
	std::vector <int> foundedPos;
	const int maxChar = 256;
	int lenOfText = stringOfText.length();
	int lenOfStr = stringToSearch.length();
	if (endDiaposon == -1) endDiaposon = lenOfText;

	std::string  TAB(maxChar, lenOfStr);
	/*for (int i = 0; i < maxChar; i++) TAB[i] = lenOfStr;*/

	for (int i = 0; i < lenOfStr; i++) {
		TAB[stringToSearch[i]] = lenOfStr - i - 1;
	}

	int k, j;
	for (int i = lenOfStr - 1 + startDiaposon; i < endDiaposon; ) {
		k = i;
		for (j = lenOfStr - 1; j >= 0; ) {
			if (stringOfText[k] == stringToSearch[j]) {
				k--;
				j--;
			}
			else {
				i += TAB[stringOfText[k]];
				break;
			}
		}
		if (j == (-1)) {
			foundedPos.push_back(k + 1);
			i += lenOfStr;
			if (type == BmSearchType::Once) {
				return(foundedPos);
			}
		}
	}

	return(foundedPos);
}


