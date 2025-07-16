#include "../include/ConfigProcessor.hpp"
#include "../include/ConfigGett.hpp"
#include "../../../includes/Logger.hpp"
int	main(int argv, char **argc)
{
	if (argv == 2)
	{
	    Logger::setLevel(LOG_LEVEL_DEBUG);
	    Logger::enableColors(true);
		ConfigProcessor conf((std::string(argc[1])));
		if (conf.tokenize() == 1)
			return (1);
		conf.printAllTree();
		ConfigGett getter(conf);
		const std::vector<Server> ClassServers = getter.getVectorServers();
		for (size_t i = 0; i < ClassServers.size(); ++i)
		{
			Logger::info() << ClassServers[i].getClientMaxBodySize();
			Logger::info() << ClassServers[i].getHost();
			Logger::info() << ClassServers[i].getName();
			Logger::info() << ClassServers[i].getPort();
			Logger::info() << ClassServers[i].getAutoIndex();
			Logger::info() << *(ClassServers[i].getRoot());
			Logger::info() << *(ClassServers[i].getIndex());
			std::cout << "\n\n";

		try
		{
			Location uri = ClassServers[i].getLocation("/tours");
			std::cout << uri.getName() << std::endl;
			std::cout << uri.getMethodIsAllowed("DELETE") << std::endl;
		}
		catch (...)
		{
		}
		}


	}

	return (0);
}
