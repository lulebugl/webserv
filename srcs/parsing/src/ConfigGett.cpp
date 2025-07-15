/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigGett.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfranco <jfranco@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:03:31 by jfranco           #+#    #+#             */
/*   Updated: 2025/07/15 18:47:55 by jfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

ConfigGett::ConfigGett( const ConfigProcessor &Parser)
	: tree(Parser.getVectorOfServer), allPort(Parser.getAllPorts()), :
{
}
