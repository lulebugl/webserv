
#include "../include/ConfigProcessor.hpp"
#include "../include/ConfigProcessor.hpp"
#include "../include/ConfigProcessor.hpp"
#include "../include/ConfigProcessor.hpp"
#include "../include/ConfigProcessor.hpp"

void Node::printTree() const {
    std::cout << name << "\n";
	std::vector<std::string>::const_iterator it = array.begin();

	while(it != array.end())
	{
		std::cout << *it << "\n";
		++it;
	}
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

	while(it != array.end())
	{
		std::cout << (isLast ? "   └── " : "   ├── ");
		std::cout << *it << "\n";
		++it;
	}
	

    for (size_t i = 0; i < children.size(); ++i) {
        bool childIsLast = (i == children.size() - 1);
        std::string newPrefix = prefix + (isLast ? "    " : "│   ");
        children[i].printSubtree(newPrefix, childIsLast);
    }
}

