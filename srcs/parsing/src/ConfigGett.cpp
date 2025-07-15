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
	: tree(Parser.getVectorOfServer), allPort(Parser.getAllPorts()), MapNode(Parser.getFullMap()) 
{
	CreateServerAndLocation();
}

void	ConfigGett::CreateServerAndLocation( void )
{
	std::vector<Node>::const_iterator it = this->tree.begin();
	while (it != this->tree.end())
	{
		Server current;
		current.prmtrs = it->prmtrs;
		current.name = it->name;
		for (size_t i = 0; i < it->children.size(); ++i)
		{
			Location Lcurrent;
			Lcurrent.prmtrs = it->children[i].prmtrs;
			Lcurrent.name = it->children[i].name;
			current.locations.push_back(Lcurrent);
            current.route.insert(std::make_pair(Lcurrent.name, Lcurrent));
		}
		this->Servers.push_back(current);
		++it;
	}
}

const std::string*	ConfigGett::getErrorPage(int port, const std::string& error, const std::string& uri) const
{
	size_t	pos;

	std::map<int, Node*>::const_iterator it = Servers.find( port );
	if (it != Servers.end())
	{
		const Node *current =  it->second->findChildNode( uri );
		if (!current)
		{
			return NULL;
		}
		std::map<std::string, std::vector<std::string> >::const_iterator itChildren = current->prmtrs.begin();
		while (itChildren != current->prmtrs.end())
		{
			if ((pos = itChildren->first.find(error, 0)) !=std::string::npos)
			{
				return &(itChildren->second[0]);
			}
			++itChildren;
		}
		std::map<std::string, std::vector<std::string> >::const_iterator itMain = it->second->prmtrs.begin();
		while (itMain != it->second->prmtrs.end())
		{
			if ((pos = itMain->first.find(error, 0))  !=std::string::npos)
			{
				return &(itMain->second[0]);
			}
			itMain++;
		}
	}
	return NULL;
}

const std::string*	ConfigGett::getErrorPage(int port, const std::string& error ) const
{
	size_t	pos;
	std::map<int, Node*>::const_iterator it = Servers.find( port );
	if (it != Servers.end())
	{
		std::map<std::string, std::vector<std::string> >::const_iterator itMain = it->second->prmtrs.begin();
		while (itMain != it->second->prmtrs.end())
		{
			if ((pos = itMain->first.find(error, 0))  !=std::string::npos)
			{
				return &(itMain->second[0]);
			}
			itMain++;
		}
	}
	return NULL;
}
