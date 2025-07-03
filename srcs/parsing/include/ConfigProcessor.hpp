#ifndef CONFIGPROCESSOR_H
#define CONFIGPROCESSOR_H
 
class ConfigProcessor
{
   public:
       /*♡♡♡♡♡♡♡♡♡♡♡CTOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
       ConfigProcessor(const std::string& Path);  //cannon
       ConfigProcessor(ConfigProcessor const & src);   //Cannon
 
       /*♡♡♡♡♡♡♡♡♡♡♡GETTER♡♡♡♡♡♡♡♡♡♡♡♡♡*/
	   std::string	getPath( void ) const;
	   std::string	getBuffer( void ) const;

 
       /*♡♡♡♡♡♡♡♡♡♡♡FT♡♡♡♡♡♡♡♡♡♡♡♡♡*/
	   void	tokinize( void );
	   std::string ConfigProcessor::findRemplaceComment(std::string const& input,
			   std::string const& from, std::string const& dilimiter,
			   std::string const& to);  
       /*♡♡♡♡♡♡♡♡♡♡♡OPERATOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
       ConfigProcessor& operator=(ConfigProcessor const & rsh);    //Cannon
 
       /*♡♡♡♡♡♡♡♡♡♡♡DTOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
       virtual ~ConfigProcessor(); //Cannon
  private:
       ConfigProcessor();  //cannon
	   const std::string	PathFile;
	   std::string		Buffer;

};
 std::ostream &operator<<(std::ostream &o, const ConfigProcessor &rhs);
#endif // CONFIGPROCESSOR_H

