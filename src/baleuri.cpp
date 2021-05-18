// Simple Hello World program

#include <string>
#include <regex>

int main(int argc, char **argv) {
	printf("Hello World\n");

	std::basic_regex test("/w*");
	std::smatch matches;

	return 0;

}
