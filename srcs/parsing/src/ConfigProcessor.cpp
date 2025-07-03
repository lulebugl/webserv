#include "../include/ConfigProcessor.hpp"

       /*♡♡♡♡♡♡♡♡♡♡♡CTOR♡♡♡♡♡♡♡♡♡♡♡♡♡*/
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
        start = posEnd + delimiter.length();
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

void ConfigProcessor::tokenize(void)
{
	std::ifstream file(this->PathFile);
	if(!file ||file.eof())
	{

	}
	std::stringstream ss;
	ss << file.rdbuf();
	this->Buffer = ss.str();
	this->Buffer = findRemplaceComment(this->Buffer, "#", "\n", "");

	/*I remove all coments from the buffer,
	  when there is a # up to the /n*/
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

