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
	Validator(); // ctor
   std::map<std::string, void(*)(std::vector<std::string>& )> funcMap;
		void	(Validator::*_FunPTR[12])(std::vector<std::string>&);
       /*♡♡♡♡♡♡♡♡♡♡♡FT_VALIDATE♡♡♡♡♡♡♡♡♡♡♡♡♡*/
		static void	validateIp(std::vector<std::string>& prmtrs);
//		void	validateCgiPath(std::vector<std::string> prmtrs);
//		void	validateListen(std::vector<std::string> prmtrs);
//		void	validateServerName(std::vector<std::string> prmtrs);
//		void	validateErrorPage(std::vector<std::string> prmtrs);
//		void	validateClienMaxBody(std::vector<std::string> prmtrs);
//		void	validateRoot(std::vector<std::string> prmtrs);
//		void	validateIndex(std::vector<std::string> prmtrs);
//		void	validateAutoIndex(std::vector<std::string> prmtrs);
//		void	validateMethods(std::vector<std::string> prmtrs);
//		void	validateAlias(std::vector<std::string> prmtrs);
//		void	validateReturns(std::vector<std::string> prmtrs);
//		void	validateCgiExt(std::vector<std::string> prmtrs):
       /*♡♡♡♡♡♡♡♡♡♡♡EXCPTION♡♡♡♡♡♡♡♡♡♡♡♡♡*/
		class ToManyDoth : public std::exception 
		{
			public:
				virtual const char* what() const throw();  // dichiarazione
		};
		class clientMaxBodyOutOfRange : public std::exception 
		{
			public:
				virtual const char* what() const throw();  // dichiarazione
		};
		class indexMethods : public std::exception 
		{
			public:
				virtual const char* what() const throw();  // dichiarazione
		};
		class OutOfRange: public std::exception 
		{
			public:
				virtual const char* what() const throw();  // dichiarazione
		};
		class VectorSizeToHight : public std::exception 
		{
			public:
				virtual const char* what() const throw();  // dichiarazione
		};
		class VectorSizeToLow : public std::exception 
		{
			public:
				virtual const char* what() const throw();  // dichiarazione
		};
		class  DontValidIp : public std::exception 
		{
			public:
				virtual const char* what() const throw();  // dichiarazione
		};
		
		class  Empty: public std::exception 
		{
			public:
				virtual const char* what() const throw();  // dichiarazione
		};

		class  onlyDigit: public std::exception 
		{
			public:
				virtual const char* what() const throw();  // dichiarazione
		};
};

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
	   struct Validator valval;
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
		void	validationParameters( void );
       /*♡♡♡♡♡♡♡♡♡♡♡OPERATOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/

};
 std::ostream &operator<<(std::ostream &o, const ConfigProcessor &rhs);
#endif // CONFIGPROCESSOR_H

