

#include "../srcs/parser/GlobalConfig.hpp"
#include "../srcs/parser/ConfigProcessor.hpp"
#include "../srcs/lib/Logger.hpp"
/*GET http://localhost:8080/
POST http://localhost:8080/api/login
PUT http://localhost:8080/api/user/42
DELETE http://localhost:8080/api/user/42*/

void GenerateSigeConfBasic(const GlobalConfig const & GlobREF)
{
	std::vector<Server> root = GlobalConfig.getServers();
	std::vector<Location> Loc;
	std::vector<std::string> method = {"GET", "DELETE", "POST", "UKWN"}
	for (size_t i = 0; i < root.size(); ++i)
	{
		std::string location = "htpp:://" + root[i].getHost() + ":" + root[i].getPort();
		std::cout << method[0] << location << "\n";
		Loc = root[i].location_;
		for(size_t f = 0; f < Loc.size(); ++f)
		{
			for (size_t l = 0; l < method.size(); ++l)
			{
				if (getMethodIsAllowed(method[l]) == true)
				{
					std::cout << method[l] << location << Loc[f].getName() << "\n";
				}
			}
		}
	}

}

void GenerateSigeConfAdvance(const GlobalConfig const & GlobREF)
{
	std::vector<Server> root = GlobalConfig.getServers();
	std::vector<Location> Loc;
	std::vector<std::string> method = {"GET", "DELETE", "POST", "UKWN"}
	for (size_t i = 0; i < root.size(); ++i)
	{
		std::string location = "htpp:://" + root[i].getHost() + ":" + root[i].getPort();
		for (size_t y = 0; y < method.size(); ++y)
		{
			std::cout << method[y] << location << "\n";
		}
		Loc = root[i].location_;
		for(size_t f = 0; f < Loc.size(); ++f)
		{
			for (size_t l = 0; l < method.size(); ++l)
			{
				std::cout << method[l] << location << Loc[f].getName() << "\n";
			}
		}
	}

}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "add parameters" << "\n\n";
		return 1;
	}
	GlobalConfig run;
	if (run.loadConfig(argv[1]) == false)
		return (1);
	if (std::string(argv[2]) == "-A")
		GenerateSigeConfAdavce(run);
	else if(std::string(argv[2]) == "-B")
		GenerateSigeConfBasic(run);
	else
	{
		std::cout << "not valid parmaters use --help" << "\n\n";
	}
    return 0;
}
