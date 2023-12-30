#include "Array.h"
#include "List.h"

int main() {
	std::vector<std::string> temp{ "asdf", "jhgf" };
	List<std::string> string(temp), string2(temp);
	List<std::string>::_iterator tempIter= string.end(), tempIter2 = string2.begin();
	--tempIter;
	tempIter.move(tempIter2);
	string.resize();
	string2.resize();
	std::cout << string << std::endl << string2;
	return(0);
}