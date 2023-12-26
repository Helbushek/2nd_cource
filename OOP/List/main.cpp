#include "Array.h"
#include "List.h"

int main() {
	std::vector<std::string> temp{ "asdf", "jhgf" };
	List<std::string> stringCopy(temp);
	const List<std::string> string(temp);

	List<std::string>::const_iterator tempIter = string.begin();
	std::cout << *tempIter;

	return(0);
}