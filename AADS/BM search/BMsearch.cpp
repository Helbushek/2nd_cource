#include <iostream>
#include <vector>
std::vector<int> searchByBm(std::string stringOfText, std::string stringToSearch, const char type,int startDiaposon, int endDiaposon) {
	if (type != 'all' || type != 'once') {
		std::cerr << "Incorrect type of search, use 'all' for all positions and 'once'(by default) for only first";
		return;
	}
	const int maxChar = 256;
	int lenOfText = stringOfText.length();
	int lenOfStr = stringToSearch.length();
	std::vector <int> foundedPos;
	if (endDiaposon == -1) endDiaposon = lenOfText;

	int* TAB = new int[maxChar];
	for (int i = 0; i < maxChar; i++) TAB[i] = lenOfStr;

	for (int i = 0; i < lenOfStr; i++) {
		TAB[stringToSearch[i]]=lenOfStr-i-1;
	}

	int k, j;
	for (int i = lenOfStr - 1+startDiaposon; i<endDiaposon; ) {
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
		if (j==(-1)) {
			foundedPos.push_back(k+1);
			i += lenOfStr;
			if (type == 'once') {
				return(foundedPos);
			}
		}
	}
	return(foundedPos);
}


