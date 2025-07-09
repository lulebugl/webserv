
#include "../include/ConfigProcessor.hpp"
void Node::clearMap( void )
{
	std::map<std::string, std::vector<std::string> >::iterator it = prmtrs.begin();

for (; it != prmtrs.end(); ++it)
	{
        std::vector<std::string>& vec = it->second;
        if (!vec.empty()) 
		{
            std::string& sub = vec.back();
            sub.erase(sub.find_last_not_of(";") + 1);
		}
	}
}

void Node::addDefualtParm( void )
{
	if (this->name == "server")
	{
		std::vector<std::string> vec;
		vec.push_back("1048576");
		prmtrs.insert(std::make_pair("client_max_body_size", vec));
		std::vector<std::string> vecIp;
		vecIp.push_back("127.0.0.1");
		prmtrs.insert(std::make_pair("host", vecIp));

	}
	std::vector<std::string> vecAuto;
	vecAuto.push_back("off");
	prmtrs.insert(std::make_pair("autoindex", vecAuto));
	std::vector<std::string> vecMetho;
	vecMetho.push_back("GET");
	prmtrs.insert(std::make_pair("allow_methods", vecMetho));
	std::vector<std::string> vecIndex;
	vecIndex.push_back("index.html");
	prmtrs.insert(std::make_pair("index", vecIndex));
}
void Node::pushArgInMap( void )
{
	std::vector<std::string>::iterator it = array.begin();
    std::string key;
    while (it != array.end())
    {
        if (!it->empty() && (*it)[it->size() - 1] != ';')
			key = *it;
		if (key == "error_page" && it + 1 != array.end())
			key = key + " " + *(it + 1);
        ++it;
        std::vector<std::string>::iterator start = it;
        std::vector<std::string>::iterator end = it;
        while (it != array.end())
        {
            end = it;
            if (!it->empty() && (*it)[it->size() - 1] == ';')
            {
                ++it;
                break;
            }
            ++it;
        }
		if (!key.empty())
			prmtrs.insert(std::make_pair(key, std::vector<std::string>(start, end + 1)));
		key.clear();
    }
	clearMap();
	addDefualtParm();
}

void	Node::printMap( void ) const
{
	Logger::info() << "Istruzzioni all'interno del nodo: " << name;
	std::map<std::string, std::vector<std::string> >::const_iterator stamp = prmtrs.begin();
	while (stamp != prmtrs.end())
	{
		std::string key = stamp->first;
		std::vector<std::string> value = stamp->second;
		std::cout << "La chiave: " << key << std::endl;
		std::cout << "I valori :";
		std::vector<std::string>::const_iterator val = value.begin();
		while(val != value.end())
		{
			std::cout << " " << *val;
			val++;
		}
		std::cout << "\n\n";
		stamp++;
	}
}

void Node::printTree( void ) const 
{
    std::cout << name << "\n";
	std::vector<std::string>::const_iterator it = array.begin();
	(void)it;
    for (size_t i = 0; i < children.size(); ++i) {
        bool isLast = (i == children.size() - 1);
        children[i].printSubtree("", isLast);
    }
}

void Node::printSubtree(const std::string& prefix, bool isLast) const {
    std::cout << prefix;
    std::cout << (isLast ? "└── " : "├── ");
    std::cout << name << "\n";
	std::vector<std::string>::const_iterator it = array.begin();

	(void)it;
//	while(it != array.end())
//	{
//		std::cout << (isLast ? "   └── " : "   ├── ");
//		std::cout << *it << "\n";
//		++it;
//	}
	

    for (size_t i = 0; i < children.size(); ++i) {
        bool childIsLast = (i == children.size() - 1);
        std::string newPrefix = prefix + (isLast ? "    " : "│   ");
        children[i].printSubtree(newPrefix, childIsLast);
    }
}

