#ifndef CONFIGPROCESSOR_H
#define CONFIGPROCESSOR_H


#include "../../../includes/Logger.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>   // ← necessario per std::stringstream
#include <iostream>  // ← se usi std::cout
#include <fstream>   // ← se usi std::ifstream
#include <map>   // ← se usi std::map
#include <cstdlib> // necessario per exit()
struct Validator
{
	private:
		st::map<std::string, std::function<void(std::vector<string>)>;
	public:
		void	validateIp();
		void	validateCgiPath();
		void	validateListen();
		void	validateServerName();
		void	validateErrorPage();
		void	validateClienMaxBody();
		void	validateRoot();
		void	validateIndex();
		void	validateAutoIndex();
		void	validateMethods();
		void	validateAlias();
		void	validateReturns();
		void	validateCgiExt():
}
struct	Node
{
	std::string name;
	std::vector<std::string> array;
	std::vector<Node> children;
	std::map<std::string, std::vector<std::string> > prmtrs; 
	void	pushArgInMap( void );
	void	printMap(void)const;

	void	printSubtree(const std::string &prefix, bool isLast) const;
	void	printTree() const ;
};

 
class ConfigProcessor
{
   public:
       /*♡♡♡♡♡♡♡♡♡♡♡CTOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
       ConfigProcessor(const std::string& Path);  //cannon
       ConfigProcessor(ConfigProcessor const & src);   //Cannon
 
       /*♡♡♡♡♡♡♡♡♡♡♡GETTER♡♡♡♡♡♡♡♡♡♡♡♡♡*/
	   std::string	getPath( void ) const;
	   std::string	getBuffer( void ) const;
	   void			printAllTree( void ) const;


       /*♡♡♡♡♡♡♡♡♡♡♡FT♡♡♡♡♡♡♡♡♡♡♡♡♡*/
	   void	tokenize( void );

       ConfigProcessor& operator=(ConfigProcessor const & rsh);    //Cannon
 
       /*♡♡♡♡♡♡♡♡♡♡♡DTOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
       virtual ~ConfigProcessor(); //Cannon
  private:
       ConfigProcessor();  //cannon
	   const std::string	PathFile;
	   std::string		Buffer;
	   std::vector<Node> tree;
       /*♡♡♡♡♡♡♡♡♡♡♡FT♡♡♡♡♡♡♡♡♡♡♡♡♡*/
	   std::string findRemplaceComment(std::string const& input,
			   std::string const& from, std::string const& dilimiter,
			   std::string const& to);  
	   void	RicorsiveTree(std::stringstream& sstoken, bool flags = true);
	   void	treeParser(std::stringstream& sstoken, Node& token);
       /*♡♡♡♡♡♡♡♡♡♡♡FT_MSG_ERROR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
	   void	StreamErrorFind(std::stringstream& ss) const;
       /*♡♡♡♡♡♡♡♡♡♡♡FT_VALIDATION♡♡♡♡♡♡♡♡♡♡♡♡♡*/
	   void ValidationPath( void ) const;
		void	countBracket() const;
		void	recursiveMap( void );
		void	validationParameters( void ) const;
       /*♡♡♡♡♡♡♡♡♡♡♡OPERATOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/

};
 std::ostream &operator<<(std::ostream &o, const ConfigProcessor &rhs);
#endif // CONFIGPROCESSOR_H

