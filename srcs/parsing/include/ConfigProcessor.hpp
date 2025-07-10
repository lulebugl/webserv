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
//

//typedef void (Validator::*)(std::vector<std::string>&)
//
#define MAX_BODY_SIZE 524288000

struct Validator
{
    typedef void (Validator::*ValidateFunction)(const std::vector<std::string>&);

       /*♡♡♡♡♡♡♡♡♡♡♡CTOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
	Validator(); // ctor
   std::map<std::string, ValidateFunction> funcMap;
		void	(Validator::*_FunPTR[12])(std::vector<std::string>&);

       /*♡♡♡♡♡♡♡♡♡♡♡FT_VALIDATE♡♡♡♡♡♡♡♡♡♡♡♡♡*/
		void	validateIp(const std::vector<std::string>& prmtrs);
		void	validateCgiPath(const std::vector<std::string>& prmtrs);
		void	validateListen(const std::vector<std::string>& prmtrs);
		void	validateServerName(const std::vector<std::string>& prmtrs);
//		void	validateErrorPage(std::vector<std::string> prmtrs);
		void	validateClienMaxBody(const std::vector<std::string>& prmtrs);
		void	validatePath(const std::string& prmtrs);
		void	validateRoot(const std::vector<std::string>& prmtrs);
		void	validateAutoIndex(const std::vector<std::string>& prmtrs);
		void	validateMethods(const std::vector<std::string>& prmtrs);
		void	validateCgiExt(const std::vector<std::string>& prmtrs);

       /*♡♡♡♡♡♡♡♡♡♡♡EXCPTION♡♡♡♡♡♡♡♡♡♡♡♡♡*/
		class PortAccessDeniedException : public std::exception 
		{
			public:
				virtual const char* what() const throw();  // dichiarazione
		};
		class unknownMethods : public std::exception 
		{
			public:
				virtual const char* what() const throw();  // dichiarazione
		};
		class ToManyDoth : public std::exception 
		{
			public:
				virtual const char* what() const throw();  // dichiarazione
		};
		class OutOfRange : public std::exception 
		{
			public:
				virtual const char* what() const throw();  // dichiarazione
		};
		class InvalidCharEx: public std::exception 
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
	void	clearMap( void );
	void	pushArgInMap( void );
	void	printMap(void)const;
	void	addDefualtParm(void);

	void	printSubtree(const std::string &prefix, bool isLast) const;
	void	printTree() const ;
};

typedef void (Validator::*ValidateFunction)(const std::vector<std::string>&);
 
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
	   void		validateForbiddenParameters( void ) const;
	   void		verifyInvalidParamsInContext(const std::string& name, const Node &it) const;
	   void		validateDifferentPortServer( void ) const;
	   void		ValidationPath( void ) const;
	   void		validateCgiBin( void ) const;
	   void		heredityClientMaxBody( void );
		void	countBracket() const;
		void	recursiveMap( void );
		void	validationParameters( void );
		void	heandelError(ValidateFunction fun, std::map<std::string, std::vector<std::string> >::iterator itPrmtrs, const std::string &name);
       /*♡♡♡♡♡♡♡♡♡♡♡OPERATOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/

};
 std::ostream &operator<<(std::ostream &o, const ConfigProcessor &rhs);
#endif // CONFIGPROCESSOR_H

