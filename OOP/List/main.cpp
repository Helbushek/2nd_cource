#include "Array.h"
#include "List.h"

int main() {
	std::vector<std::string> temp{ "asdf", "jhgf" };
	List<std::string> string(temp);
	std::cout << string << std::endl;
	List<std::string>::const_iterator iter = string.begin();
	*iter = "kek";
	std::cout << string << std::endl;
	return(0);
}