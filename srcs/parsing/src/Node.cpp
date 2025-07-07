
#include "../include/ConfigProcessor.hpp"
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

