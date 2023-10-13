#include "BMsearch.h"

std::vector<int> searchByBm(std::string& stringOfText, std::string& stringToSearch, int startDiaposon, int endDiaposon, BmSearchType type) {
	std::vector <int> foundedPos;
	const int maxChar = 256;
	int lenOfText = stringOfText.length();
	int lenOfStr = stringToSearch.length();
	if (endDiaposon == -1) endDiaposon = lenOfText;

	std::vector <int> TAB(maxChar, lenOfStr);

	for (int i = 0; i < lenOfStr; i++) {
		TAB[(unsigned int) stringToSearch[i]] = lenOfStr - i - 1;
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


