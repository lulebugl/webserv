/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigProcessor.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfranco <jfranco@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 19:28:53 by jfranco           #+#    #+#             */
/*   Updated: 2025/07/08 17:56:57 by jfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ConfigProcessor.hpp"

       /*♡♡♡♡♡♡♡♡♡♡♡CTOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
ConfigProcessor::ConfigProcessor(const std::string& Path)
			: PathFile(Path)
{
	std::cout << this->PathFile << "\n";
}
ConfigProcessor::ConfigProcessor()
{
    //std::cout << "Default constructor called" << std::endl;
    // ctor
}

ConfigProcessor::ConfigProcessor(ConfigProcessor const & src)
{
    //std::cout << "Copy constructor called" << std::endl;
    //*this = src;
}

       /*♡♡♡♡♡♡♡♡♡♡♡GETTER♡♡♡♡♡♡♡♡♡♡♡♡♡*/
std::string ConfigProcessor::getPath( void ) const
{
	return (this->PathFile);
}

std::string ConfigProcessor::getBuffer( void ) const
{
	return (this->Buffer);
}

void	ConfigProcessor::printAllTree( void ) const
{
	std::vector<Node>::const_iterator it = tree.begin();
	while(it != tree.end())
	{
		Logger::info() << "Schema Alberi e nodi";
		it->printTree();
		++it;
	}
	std::cout << "\n\n";
	std::vector<Node>::const_iterator it_ = tree.begin();
	while(it_ != tree.end())
	{
		std::cout << "Genitore" << "\n";
		it_->printMap();
		std::cout << "Figli" << "\n";
		  for (size_t i = 0; i < it_->children.size(); ++i)
	  	      it_->children[i].printMap();
		++it_;
	}
}
 
       /*♡♡♡♡♡♡♡♡♡♡♡FT♡♡♡♡♡♡♡♡♡♡♡♡♡*/
std::string ConfigProcessor::findRemplaceComment(std::string const& input, std::string const& from,
		std::string const& dilimiter, std::string const& to)  
{                                              
    std::string result;                        
    size_t start = 0;                          
    size_t pos, posEnd;
	if (from.empty() || dilimiter.empty())
		return input;

    while ((pos = input.find(from, start)) != std::string::npos &&
           (posEnd = input.find(dilimiter, pos)) != std::string::npos)
    {                                          
        result.append(input, start, pos - start);
        result += to;
        start = posEnd + (dilimiter.length());
    }                                          
    result.append(input, start, input.size() - start);
	pos = input.find(from, start);
	if (pos != std::string::npos)
	{
		result.append(input, start, pos - start);
	   	result += to;
	}
    return result;                             
}

void	ConfigProcessor::validationParameters()
{
	std::vector<Node>::iterator it_ = tree.begin();
	while(it_ != tree.end())
	{
		std::map<std::string, std::vector<std::string> >::iterator itPrmtrs = it_->prmtrs.begin();
		while(itPrmtrs != it_->prmtrs.end())
		{
			std::map<std::string, void(*)(std::vector<std::string>&)>::iterator itFunc = this->valval.funcMap.find(itPrmtrs->first);
			if (itFunc != this->valval.funcMap.end())	 
			{
				try
				{
					itFunc->second(itPrmtrs->second);
				}
				catch (Validator::DontValidIp &e)
				{
					Logger::warning() << "Defalt ip set";
					itPrmtrs->second[0] = "127.0.0.1";
				}
				catch (...)
				{
					Logger::error( )<< "Catch error";
				}
			}
			++itPrmtrs;

		}
		++it_;
	}
}

void	ConfigProcessor::RicorsiveTree(std::stringstream& sstoken, bool flags)
{
	std::string token;
	char c;
    if (!(sstoken >> token))
        return;
	sstoken >> std::ws;  // salta spazi bianchi (spazi, tab, newline)
	c = sstoken.peek();
	if (token == "server" && c == '{' && flags == true)
	{
		Logger::info() << "Push one tree";
		sstoken.get();
		Node root;
        root.name = token;  // salva il tipo di blocco
        treeParser(sstoken, root);  // costruisci il sottoalbero
        tree.push_back(root);       // aggiungi alla foresta
	}
//	else if (flags == false && token == "{")
//	{
//		Logger::info() << "Push new Tree";
//		Node root;
//        root.name = token;  // salva il tipo di blocco
//        treeParser(sstoken, root);  // costruisci il sottoalbero
//        tree.push_back(root);       // aggiungi alla foresta
//	}
/* ♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡
 * TODO: Vedere se togliere il blocca else if per avre server in cascata
 ♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡ */
	RicorsiveTree(sstoken);
}

void	ConfigProcessor::treeParser(std::stringstream& sstoken, Node& current)
{
	std::string token;
	std::string rest;

        while (sstoken >> token)
		{
            if (token == "location")
			{
				//std::getline(sstoken >> std::ws, rest);
				while (sstoken >> token && token != "{")
					rest = rest + token;
				//rest.erase(rest.find_last_not_of(" \t\r\n") + 1);
				if (token == "{")
				{
					 Node child;
					 child.name = rest;
					 rest.clear(); 
	               	 treeParser(sstoken, child);
	               	 current.children.push_back(child);
					 Logger::info() << "Push Node: " << child.name;
				}
				else
				{
					Logger::error() << "Bracket don't open corretly";
					return;
					// TODO: Da gestire corretamente;
				}
            }
//			else if (token == "server")   // TODO:Vedere se togliere questo blocco
//				RicorsiveTree(sstoken, false);
			else
			{
				if (token == "}")
					return ;
            	current.array.push_back(token);
            }
        }
        return;
}

void	ConfigProcessor::StreamErrorFind(std::stringstream& ss) const
{
	if (ss.fail())
	{
	    std::cerr << "Errore di formato o estrazione fallita (failbit set)" << std::endl;
	    if (ss.eof())
	        std::cerr << "Si è raggiunta la fine dello stream (eofbit set)" << std::endl;
	    if (ss.bad())
	        std::cerr << "Errore grave di stream (badbit set)" << std::endl;
	}
	else
		Logger::info() << "Stream OK!";
}
#include <iostream>
#include <sys/stat.h>
void	ConfigProcessor::ValidationPath() const
{
	const std::string exte = ".conf";
	size_t	posDoth = PathFile.rfind(exte);
	struct stat sb;
	if (posDoth != std::string::npos)
	{
        if (posDoth == (PathFile.length() - exte.length())){
					Logger::info() << "Valid extension, try open file";
					if (stat(PathFile.c_str(), &sb) == 0 && (sb.st_mode & S_IFDIR)){
						Logger::error() << "the configuration must be a file";
						exit(-1);
					}
		}
		else
			exit (-1);

	}
	else
	{
			exit (-1);
	}
}

void	ConfigProcessor::countBracket() const
{
	int bracket = 0;
	for (size_t i = 0; i < Buffer.length(); ++i) {
		if (this->Buffer[i] == '{')
			bracket++;
		if (this->Buffer[i] == '}')
			bracket--;
	}
	if (bracket != 0)
	{
		Logger::error() << "Brackets don't close properly";
		exit(-1);
	}
	return ;
}

void	ConfigProcessor::recursiveMap( void )
{

	std::vector<Node>::iterator it = tree.begin();
	while(it != tree.end())
	{
		it->pushArgInMap();
		  for (size_t i = 0; i < it->children.size(); ++i)
	  	      it->children[i].pushArgInMap();
		++it;
	}
}

void ConfigProcessor::tokenize( void )
{
	ValidationPath();
	std::ifstream file(this->PathFile.c_str());
	if(!file ||file.eof())
	{
		// TODO:(e.g., log or throw an exception) ♡♡♡♡♡♡
		Logger::error() << "Error stream";
		return ;
	}
/* ♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡
	// Use a stringstream to read the entire file content into memory ♡♡♡♡♡♡
 ♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡ */
	std::stringstream ss;
	StreamErrorFind(ss);
	ss << file.rdbuf();
	file.close();
	this->Buffer = ss.str();
/* ♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡
     * Remove all comments from the buffer:
     * Look for each '#' character (start of comment)
     * and remove everything up to the newline character '\n'.
     * The `findRemplaceComment` function performs this operation. 
 ♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡ */
	this->Buffer = findRemplaceComment(this->Buffer, "#", "\n", "\n");
	countBracket();
/* ♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡
 * Create a stringstream from the cleaned buffer, allowing tokenization using >>.
 * Then pass it to treeParser for building the configuration tree structure.
 ♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡ */

    std::stringstream tokenStream(this->Buffer);
	StreamErrorFind(tokenStream);	
	RicorsiveTree(tokenStream);
	recursiveMap();
	validationParameters();
}
 
       /*♡♡♡♡♡♡♡♡♡♡♡OPERATOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
ConfigProcessor &ConfigProcessor::operator=( ConfigProcessor const &rhs)
{
    //std::cout << "Copy assignment operator called" << std::endl;
    if (this != &rhs)
    {
        // this->_n = rhs.getValue();
    }
    return *this;
}

       /*♡♡♡♡♡♡♡♡♡♡♡DTOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
ConfigProcessor::~ConfigProcessor()
{
    //std::cout << "Destructor called" << std::endl;
    // dtor
}

 std::ostream &operator<<(std::ostream &o, const ConfigProcessor &rhs)
{
   o << "File Conf: " << rhs.getPath() << "\n" << "Buffer: " << rhs.getBuffer();
   return o;
}

