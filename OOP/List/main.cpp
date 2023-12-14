#include "Array.h"
#include "List.h"

int main() {
	std::vector<std::string> temp{ "asdf", "jhgf" };
	List<std::string> string(temp), stringCopy(temp);

	string = stringCopy;
	assert(string == stringCopy);

	std::cout << string;

	return(0);
}