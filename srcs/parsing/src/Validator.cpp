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
		throw ipVectorSizeToHight();
	if (prmtrs.size() < 1)
		throw ipVectorSizeToLow();
	size_t	i = 0;
	size_t	doth = 0;
	while (prmtrs[0].length() < i)
	{
		size_t pos = prmtrs[0].find('.', i);
        if (pos == std::string::npos)
            pos = prmtrs[0].length();  // se non c'è punto, segmenta fino alla fine
		else
			doth++;
		std::string sub = prmtrs[0].substr(i, pos - i);
		if (sub.length() > 3)
			throw ToManyDigitInIp();
		if (sub.empty())
			throw IpEmpty();
		size_t	y = 0;
		while (y < sub.length())
		{
			if (!std::isdigit(sub[y]))
				throw onlyDigitInIp();
			y++;
		}
		i++;
	}
	if (doth == 2)
		Logger::info() << "Ip address OK!";
	else
		throw ToManyDothInIp();
}
const char* Validator::ToManyDothInIp::what() const throw()
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

const char* Validator::ipOutOfRange::what() const throw()
{
    return "IP out of valid range";
}

const char* Validator::ipVectorSizeToHight::what() const throw()
{
    return "IP vector size too high";
}

const char* Validator::ipVectorSizeToLow::what() const throw()
{
    return "IP vector size too low";
}

const char* Validator::ToManyDigitInIp::what() const throw()
{
    return "Too many digits in IP address";
}

const char* Validator::IpEmpty::what() const throw()
{
    return "IP address empty";
}

const char* Validator::onlyDigitInIp::what() const throw()
{
    return "IP contains only digits";
}

