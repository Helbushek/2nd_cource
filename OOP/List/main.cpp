#include "Array.h"
#include "List.h"

int main() {
	std::vector<std::string> temp{ "asdf", "jhgf" };
	List<std::string> stringCopy(temp);
	const List<std::string> string(temp);

	List<std::string>::Constiterator tempIter = string.begin();
	*tempIter = "a";
	std::cout << *tempIter;

	return(0);
}