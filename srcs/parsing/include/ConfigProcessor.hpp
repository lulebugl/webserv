#ifndef CONFIGPROCESSOR_H
#define CONFIGPROCESSOR_H

#include <vector>
#include <iostream>
#include <string>
#include <sstream>   // ← necessario per std::stringstream
#include <iostream>  // ← se usi std::cout
#include <fstream>   // ← se usi std::ifstream

struct	Node
{
	std::string name;
	std::vector<std::string> array;
	std::vector<Node> children;

	void printSubtree(const std::string &prefix, bool isLast) const;
	void printTree() const ;
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
	   std::string findRemplaceComment(std::string const& input,
			   std::string const& from, std::string const& dilimiter,
			   std::string const& to);  
	   void	RicorsiveTree(std::stringstream& sstoken, bool flags = true);
	   void	treeParser(std::stringstream& sstoken, Node& token);
	   void	tokenize( void );
       /*♡♡♡♡♡♡♡♡♡♡♡OPERATOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
       ConfigProcessor& operator=(ConfigProcessor const & rsh);    //Cannon
 
       /*♡♡♡♡♡♡♡♡♡♡♡DTOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
       virtual ~ConfigProcessor(); //Cannon
  private:
       ConfigProcessor();  //cannon
	   const std::string	PathFile;
	   std::string		Buffer;
	   std::vector<Node> tree;

};
 std::ostream &operator<<(std::ostream &o, const ConfigProcessor &rhs);
#endif // CONFIGPROCESSOR_H

