#include "Array.h"
#include "List.h"

int main() {
	std::vector<std::string> temp{ "asdf", "jhgf" };
	List<std::string> stringCopy(temp);
	const List<std::string> string(temp);

	for (List<std::string>::Constiterator iter = string.begin(); iter != string.end(); iter++) {
		std::cout << *iter << ' ';
	}

	return(0);
}