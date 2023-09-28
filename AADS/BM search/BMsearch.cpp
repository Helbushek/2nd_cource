#include <iostream>

int* searchByBmOnce(char* stringOfText, char* stringToSearch, int startDiaposon, int endDiaposon) {
	int lenOfText = strlen(stringOfText);
	int lenOfStr = strlen(stringToSearch);
	int posForFounded=0, *foundedPos = new int[255];
	if (endDiaposon == -1) endDiaposon = lenOfText;

	int* TAB = new int[255];
	for (int i = 0; i < 255; i++) TAB[i] = lenOfStr;

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
			foundedPos[posForFounded] = k+1;
			posForFounded++;
			i += lenOfStr;
		}
	}
	foundedPos[posForFounded] = -1;
	delete[] TAB;
	return(foundedPos);
}


int searchByBmFirst(char* stringOfText, char* stringToSearch) {
	int lenOfText = strlen(stringOfText);
	int lenOfStr = strlen(stringToSearch);
	int posForFounded = 0, foundedPos;

	int* TAB = new int[255];
	for (int i = 0; i < 255; i++) TAB[i] = lenOfStr;

	for (int i = 0; i < lenOfStr; i++) {
		TAB[stringToSearch[i]] = lenOfStr - i - 1;
	}

	int k, j;
	for (int i = lenOfStr - 1; i < lenOfText; ) {
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
			return(k + 1);
		}
	}
	delete[] TAB;
	return(-1);
}