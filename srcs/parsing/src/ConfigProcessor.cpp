/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigProcessor.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfranco <jfranco@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 19:28:53 by jfranco           #+#    #+#             */
/*   Updated: 2025/07/10 19:20:10 by jfranco          ###   ########.fr       */
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
    *this = src;
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

const Node* ConfigProcessor::getRouteNode(int port, const std::string& uri)const
{
	std::map<int, Node*>::const_iterator it = Servers.find(port);
    if (it != Servers.end())
        return it->second->findChildNode(uri);
    else
        return NULL;
}

const Node* ConfigProcessor::getRouteNode(const std::string& port, const std::string& uri)const
{
    std::vector<Node>::const_iterator it = tree.begin();
    while(it != tree.end())
    {
        std::map<std::string, std::vector<std::string> >::const_iterator listen = it->prmtrs.find("listen");
		if (listen != it->prmtrs.end() && !listen->second.empty() && listen->second[0] == port)
		{
			return it->findChildNode( uri );
		}
         ++it;
    }  
     return NULL;    
}
const std::vector<Node>& ConfigProcessor::getVectorOfServer( void ) const
{
	return this->tree;
}


const std::map<std::string, Node*> * ConfigProcessor::getMapOfOneServer( int port ) const
{
	std::map<int, Node*>::const_iterator it = Servers.find( port );
	if (it != Servers.end())
		return &(it->second->route);
	else
		return NULL;
}

const Node* ConfigProcessor::getServerNode( int port ) const
{
	std::map<int, Node*>::const_iterator it = Servers.find( port );
	if (it != Servers.end())
		return it->second;
	else
		return NULL;
}

bool ConfigProcessor::hasPort ( int port )
{
	std::vector<int>::const_iterator it = std::find( allPort.begin(), allPort.end(), port );
	if (it != this->allPort.end())
		return true;
	else
		return false;
}
const std::map<int, Node*>& ConfigProcessor::getFullMap( void ) const
{
	return this->Servers;
}

const std::vector<int>& ConfigProcessor::getAllPorts( void ) const
{
	return this->allPort;
}

const std::vector<std::string>* ConfigProcessor::getParamOfServer(int port, const std::string& key) const
{
	std::map<int, Node*>::const_iterator it = Servers.find( port );
	if (it != Servers.end())
	{
		std::map<std::string, std::vector<std::string> >::const_iterator itKey= it->second->prmtrs.find( key );
		if (itKey != it->second->prmtrs.end())
		{
			return &(itKey->second);
		}
		else
			return NULL;
	}
	else
		return NULL;

}

const std::vector<std::string>* ConfigProcessor::getParamOfRouteNode(int port, const std::string& uri, const std::string& key) const
{
	std::map<int, Node*>::const_iterator it = Servers.find( port );
	if (it != Servers.end())
	{
		const Node *current = it->second->findChildNode( uri );
		if (!current)
			return NULL;
		else
		{
			std::map<std::string, std::vector<std::string> >::const_iterator itKey = current->prmtrs.find( key );
			if ( itKey != current->prmtrs.end())
			{
				return &(itKey->second);
			}
			else
				return NULL;
		}

	}
	else
		return NULL;

}
    /*♡♡♡♡♡♡♡♡♡♡♡UTILS♡♡♡♡♡♡♡♡♡♡♡♡♡*/
void	ConfigProcessor::prepareForCore( void )
{

	std::vector<Node>::iterator it = tree.begin();
	while(it != tree.end())
	{
		for (size_t i = 0; i < it->children.size(); ++i)
		{
			it->route.insert(std::make_pair(it->children[i].name, &it->children[i]));
		}
		++it;
	}
	it = tree.begin();
	while(it != tree.end())
	{

        std::map<std::string, std::vector<std::string> >::const_iterator listen = it->prmtrs.find("listen");
		if (listen != it->prmtrs.end() && !listen->second.empty())
		{
			int port;
			std::stringstream ss(listen->second[0]);
			ss >> port;
			this->allPort.push_back(port);
			this->Servers.insert(std::make_pair(port, &(*it)));
		}
		++it;
	}
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
		  {
	  	      it_->children[i].printMap();
		  }
		++it_;
	}
}
 
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
       /*♡♡♡♡♡♡♡♡♡♡♡VALIDATE♡♡♡♡♡♡♡♡♡♡♡♡♡*/
typedef void (Validator::*ValidateFunction)(const std::vector<std::string>&);
void	ConfigProcessor::heandelError(ValidateFunction fun, std::map<std::string, std::vector<std::string> >::iterator itPrmtrs, const std::string &name)
{
		try
		{
			Logger::info() << "Try validate: " << itPrmtrs->first << " in " << name;
			(this->valval.*fun)(itPrmtrs->second);
		}
		catch (Validator::DontValidIp &e)
		{
			Logger::error() << e.what() <<  " " << itPrmtrs->first; ;
			Logger::warning() << "Defalt ip set";
			itPrmtrs->second[0] = "127.0.0.1";
		}
		catch (Validator::PortAccessDeniedException &e)
		{
			Logger::error() << e.what() <<  " " << itPrmtrs->first; ;
			Logger::warning() << "Defalt port setting";
			itPrmtrs->second[0] = "8080";
		}
		catch (std::exception& e)
		{
			Logger::error() << e.what() <<  " " << itPrmtrs->first; ;
			exit(1);
		}
}

void	ConfigProcessor::validateForbiddenParameters( void ) const
{
	std::vector<Node>::const_iterator it_ = tree.begin();
	while(it_ != tree.end())
	{
		for (size_t i = 0; i < it_->children.size(); ++i)
		{
			verifyInvalidParamsInContext(it_->children[i].name, it_->children[i]);
			if (it_->children[i].name == "cgi-bin")
			{
				if (it_->children[i].prmtrs.count("cgi_ext") < 1)
				{

					Logger::error() << "missing cgi_ext in: " << it_->children[i].name; 
					exit (1);
				}
				if (it_->children[i].prmtrs.count("cgi_path") < 1)
				{
					Logger::error() << "missing cgi_path in: " << it_->children[i].name; 
					exit (1);
				}
				if (it_->children[i].prmtrs.count("root") < 1)
				{
					Logger::error() << "missing root in: " << it_->children[i].name; 
					exit (1);
				}
			}
		}
		++it_;
	}
}

void	ConfigProcessor::verifyInvalidParamsInContext(const std::string& name, const Node &it ) const
{
	std::vector<std::string> vecNoAll;
	vecNoAll.push_back("listen");
	vecNoAll.push_back("host");
	vecNoAll.push_back("server_name");
	vecNoAll.push_back("error_page");
	if (name == "cgi-bin")
	{
	    vecNoAll.push_back("allow_methods");
	    vecNoAll.push_back("autoindex");
	    vecNoAll.push_back("alias");
	    vecNoAll.push_back("return");
	}

	for (size_t i = 0; i < vecNoAll.size(); i++)
	{
		std::map<std::string, std::vector<std::string> >::const_iterator itPrmtrs = it.prmtrs.find(vecNoAll[i]);
		if (itPrmtrs != it.prmtrs.end())
		{
			Logger::error() << "prmtrs non alloewd here: " << name << " " << itPrmtrs->first;
			exit(1);
		}
	}
	vecNoAll.clear();
}

void	ConfigProcessor::validateCgiBin( void ) const
{
	size_t count = 0;
	std::vector<Node>::const_iterator it_ = tree.begin();
	while(it_ != tree.end())
	{
		count = 0;
		for (size_t i = 0; i < it_->children.size(); ++i)
		{
			if (it_->children[i].name == "cgi-bin")
				count++;
		}
		if ( count < 1 )
		{
			Logger::error() << "Cgi-bin, is mandatory parameter";
			exit(1);
		}
		++it_;
	}
}

void	ConfigProcessor::heredityClientMaxBody( void )
{
	std::vector<Node>::iterator it_ = tree.begin();
	while(it_ != tree.end())
	{
		std::map<std::string, std::vector<std::string> >::const_iterator param = it_->prmtrs.find("client_max_body_size");
		if (param != it_->prmtrs.end())
		{
			for (size_t i = 0; i < it_->children.size(); ++i)
			{

				if (param != it_->prmtrs.end() && it_->children[i].name != "cgi-bin")
				{
				    it_->children[i].prmtrs.insert(*param);
				}

			}
		}
		++it_;
	}

}

void	ConfigProcessor::validateDifferentPortServer( void ) const
{
	std::vector<Node>::const_iterator it_ = tree.begin();
	while(it_ != tree.end())
	{
		std::map<std::string, std::vector<std::string> >::const_iterator listen = it_->prmtrs.find("listen");
		if (listen != it_->prmtrs.end())
		{
			size_t i = 0;
			while (i < tree.size())
			{
				size_t idx = std::distance(tree.begin(), it_);
				if ( idx == i)
					break ;
				std::map<std::string, std::vector<std::string> >::const_iterator compare = tree[i].prmtrs.find("listen");
				if (compare != tree[i].prmtrs.end())
				{
					if (compare->second[0] == listen->second[0])
					{
						Logger::error() << "Servers must have different listening to each other the port is: " << compare->second[0];
						exit(1);
					}
				}
				i++;
			}
		}
		++it_;
	}
}

void	ConfigProcessor::validationParameters( void )
{
	validateCgiBin();
	validateForbiddenParameters();
	heredityClientMaxBody();
	std::vector<Node>::iterator it_ = tree.begin();
	while(it_ != tree.end())
	{
		std::map<std::string, std::vector<std::string> >::iterator itPrmtrs = it_->prmtrs.begin();
		if (it_->prmtrs.count("listen")  < 1)
		{
			Logger::error() << "listening port, is mandatory parameter";
			exit(1);
		}
		while(itPrmtrs != it_->prmtrs.end())
		{
			std::map<std::string, ValidateFunction>::iterator itFunc = this->valval.funcMap.find(itPrmtrs->first);
			if (itFunc != this->valval.funcMap.end())	 
			{
				ValidateFunction func =itFunc->second;
				heandelError(func, itPrmtrs, it_->name);
			}
			++itPrmtrs;

		}
		std::vector<Node>::iterator itChild = it_->children.begin();
		while (itChild != it_->children.end())
		{
			std::map<std::string, std::vector<std::string> >::iterator itPrmtrs = itChild->prmtrs.begin();
			while(itPrmtrs != itChild->prmtrs.end())
			{
				std::map<std::string, ValidateFunction>::iterator itFunc = this->valval.funcMap.find(itPrmtrs->first);
				if (itFunc != this->valval.funcMap.end())	 
				{
					ValidateFunction func =itFunc->second;
					heandelError(func, itPrmtrs, itChild->name);
				}
				++itPrmtrs;

			}
			itChild++;
		}
		++it_;
	}
	validateDifferentPortServer();
	//TODO: Validare che tutti i server abbiano un listen diverso OK! aggiungere giusto il controllo se é empty
	//TODO: Ovveride client_max_body_size
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
	prepareForCore();
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

