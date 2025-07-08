/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Validator.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfranco <jfranco@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:42:00 by jfranco           #+#    #+#             */
/*   Updated: 2025/07/08 17:56:03 by jfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ConfigProcessor.hpp"
#include <functional>
Validator::Validator()
{
	funcMap["host"] = &Validator::validateIp;
	Logger::info() << "Init validation";
}

void	Validator::validateIp( std::vector<std::string>& prmtrs )
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
    for (int i = 0; i < v.size(); i++)
    {
		std::string temp = v[i];
        if (temp.size() > 1)
        {
            if (temp[0] == '0')
				throw DontValidIp();
        }
        for (int j = 0; j < temp.size(); j++)
        {
            if (std::isalpha(temp[j]))
				throw DontValidIp();
        }

        if (std::stoi(temp) > 255)
				throw DontValidIp();
    }
}
const char* Validator::ToManyDoth::what() const throw()
{
    return "Too many dots in IP address";
}

const char* Validator::clientMaxBodyOutOfRange::what() const throw()
{
    return "Client max body size out of range";
}

const char* Validator::indexMethods::what() const throw()
{
    return "Invalid index method";
}

const char* Validator::OutOfRange::what() const throw()
{
    return "IP out of valid range";
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
    return "Too many digits in IP address";
}

const char* Validator::Empty::what() const throw()
{
    return "IP address empty";
}

const char* Validator::onlyDigit::what() const throw()
{
    return "IP contains only digits";
}

