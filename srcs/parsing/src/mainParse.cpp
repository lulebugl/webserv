#include "../include/ConfigProcessor.hpp"
int	main(int argv, char **argc)
{
	std::cout <<"test"<< "\n";
	ConfigProcessor conf((std::string(argc[1])));
	conf.tokenize();
	conf.printAllTree();

	return (0);
}
