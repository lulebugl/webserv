#include "../include/ConfigProcessor.hpp"
#include "../../../includes/Logger.hpp"
int	main(int argv, char **argc)
{
	if (argv == 2)
	{
	    Logger::setLevel(LOG_LEVEL_DEBUG);
	    Logger::enableColors(true);
		ConfigProcessor conf((std::string(argc[1])));
		conf.tokenize();
		conf.printAllTree();
	}

	return (0);
}
