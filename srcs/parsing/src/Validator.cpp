/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Validator.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfranco <jfranco@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:42:00 by jfranco           #+#    #+#             */
/*   Updated: 2025/07/09 16:06:17 by jfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ConfigProcessor.hpp"
#include <functional>
Validator::Validator()
{
	//funcMap["host"] = &Validator::validateIp;
	//funcMap.emplace("host", &Validator::validateIp);
	this->funcMap.insert(std::make_pair("host", &Validator::validateIp));
	this->funcMap.insert(std::make_pair("server_name", &Validator::validateServerName));
	this->funcMap.insert(std::make_pair("client_max_body_size", &Validator::validateClienMaxBody));
	this->funcMap.insert(std::make_pair("autoindex", &Validator::validateAutoIndex));
	this->funcMap.insert(std::make_pair("allow_methods", &Validator::validateMethods));
	return ;
}

void	Validator::validateAutoIndex(const std::vector<std::string>& prmtrs)
{
	if (prmtrs.size() > 1)
		throw VectorSizeToHight();
	if (prmtrs.size() < 1)
		throw VectorSizeToLow();
	if (prmtrs[0].size() < 1)
		throw Empty();
	if (prmtrs[0] != "on" || prmtrs[0] != "off")
		throw unknownMethods();
	Logger::valide() << "autoIndex";
}

void	Validator::validateMethods(const std::vector<std::string>& prmtrs)
{
	if (prmtrs.size() < 1)
		throw VectorSizeToLow();
	for (size_t i = 0; i < prmtrs.size(); i++)
	{
		if (prmtrs[i].size() < 1)
			throw Empty();
		if (prmtrs[i] != "GET" && prmtrs[i] != "POST" && prmtrs[i] != "DELETE" )
			throw unknownMethods();
	}
	Logger::valide() << "allow_methods";
}
void	Validator::validateClienMaxBody(const std::vector<std::string>& prmtrs)
{
	if (prmtrs.size() > 1)
		throw VectorSizeToHight();
	if (prmtrs.size() < 1)
		throw VectorSizeToLow();
	if (prmtrs[0].size() < 1)
		throw Empty();
	for (size_t i = 0; prmtrs[0][i]; i++){
		if (!std::isdigit(prmtrs[0][i]))
		{
			throw InvalidCharEx();
		}
	}
	std::stringstream ss(prmtrs[0]);
	long long nbr;
	ss >> nbr;
	if(nbr > MAX_BODY_SIZE)
		throw clientMaxBodyOutOfRange();
	Logger::valide() << "Client_Max_Body";
}

void	Validator::validateIp(const std::vector<std::string>& prmtrs )
{
	if (prmtrs.size() > 1)
		throw VectorSizeToHight();
	if (prmtrs.size() < 1)
		throw VectorSizeToLow();
	std::string s = prmtrs[0];
	std::vector<std::string> v;
	 std::stringstream ss(s);
    while (ss.good())
    {
		std::string substr;
       	std::getline(ss, substr, '.');
		v.push_back(substr);
    }
    if (v.size() != 4)
			throw DontValidIp();
    for (size_t i = 0; i < v.size(); i++)
    {
		std::string temp = v[i];
        if (temp.size() > 1)
        {
            if (temp[0] == '0')
				throw DontValidIp();
        }
        for (size_t j = 0; j < temp.size(); j++)
        {
            if (std::isalpha(temp[j]))
				throw DontValidIp();
        }

        if (std::atoi(temp.c_str()) > 255)
				throw DontValidIp();
    }
	Logger::valide() << "host";
}

static	bool InvalidChar(char c)
{
	if (c == '%' || c == '!' || c == '@' || c == '#' || c == '$' || c == '^' ||
    c == '&' || c == '*' || c == '(' || c == ')' || c == '+' || c == '=' ||
    c == '{' || c == '}' || c == '[' || c == ']' || c == '|' || c == '\\' ||
    c == ':' || c == ';' || c == '"' || c == '\'' || c == '<' || c == '>' ||
    c == ',' || c == '/' || c == '?' || c == '~' || c == '`' || c == ' ' ||
    c == '_' )
		return true;
	return false;
}


void	Validator::validateServerName(const std::vector<std::string>& prmtrs)
{
	for (size_t i = 0; i < prmtrs.size(); i++)
	{
		if (prmtrs[i].size() < 1)
			throw Empty();
		for (size_t y = 0; y < prmtrs[i].length(); y++)
		{
			if (InvalidChar(prmtrs[i][y]) == true)
			{
				throw InvalidCharEx();
			}
		}

	}
	Logger::valide() << "Server_name";
}

const char* Validator::unknownMethods::what() const throw()
{
    return "methods dont allowed";
}
const char* Validator::ToManyDoth::what() const throw()
{
    return "Too many dots in IP address";
}

const char* Validator::clientMaxBodyOutOfRange::what() const throw()
{
    return "Client max body size out of range";
}

const char* Validator::InvalidCharEx::what() const throw()
{
    return "Invalid char in: ";
}

const char* Validator::VectorSizeToHight::what() const throw()
{
    return "IP vector size too high";
}

const char* Validator::VectorSizeToLow::what() const throw()
{
    return "IP vector size too low";
}

const char* Validator::DontValidIp::what() const throw()
{
    return "IP address is non valid";
}

const char* Validator::Empty::what() const throw()
{
    return "Value is empty";
}

const char* Validator::onlyDigit::what() const throw()
{
    return "IP contains only digits";
}

