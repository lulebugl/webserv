/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigGett.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfranco <jfranco@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:27:30 by jfranco           #+#    #+#             */
/*   Updated: 2025/07/15 18:13:10 by jfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

class Location
{
	private:
	std::string name;
	std::map<std::string, std::vector<std::string> > prmtrs; 
	public:
};
class Servers
{
	private:
	std::string name;
	std::map<std::string, Location*> route;
	std::vector<Location> location;
	std::map<std::string, std::vector<std::string> > prmtrs; 
	public:
};
class	ConfigGett
{
	public:
//		ConfigGett(const ConfigProcessor& Parser );
//		virtual ~ConfigGett();
//
//
//        // ♡ Returns a const reference to the main vector of server nodes ♡
//        const std::vector<Servers>& getVectorOfServer(void) const;
//
//        // ♡ Returns a const reference to the complete map of servers indexed by port ♡
//        const std::map<int, Servers*>& getFullMap(void) const;
//
//        // ♡ Returns a const pointer to the map of routes (uri -> Node*) for a server by its port ♡
//        // ♡ Returns nullptr if the port does not exist ♡
//        const std::map<std::string, Servers>* getMapOfOneServer(int port) const;
//
//        // ♡ Returns a const pointer to the route node specified by port and URI ♡
//        // ♡ Returns nullptr if not found .
//        const Node* getRouteNode(const std::string& port, const std::string& uri) const;
//        const Node* getRouteNode(int port, const std::string& uri) const;
//
//        // ♡ Returns a const pointer to the server node associated with the specified port ♡
//        // ♡ Returns nullptr if the port does not exist ♡
//        const Node* getServerNode(int port) const;
//
//        // ♡ Returns a const reference to the vector containing all configured server ports ♡
//        const std::vector<int>& getAllPorts() const;
//
//        // ♡ Checks whether a given port is present among the configured ports ♡
//        bool hasPort(int port);
//		bool getMethod(int port, const std::string& Methods) const;
//		bool getMethod(int port, const std::string& uri, const std::string& Methods) const;
//		bool getIsAutoIndex(int port, const std::string& uri, const std::string& Methods)const;
//		bool getIsAutoIndex(int port, const std::string& Methods)const;
//
//
//        // ♡ Returns a const pointer to the vector of strings associated with a key (parameter) for a server specified by port ♡
//        // ♡ Returns nullptr if the port or key do not exist ♡
//        const std::vector<std::string>* getParam(int port, const std::string& key) const;
//
//        // ♡♡♡ Returns a const pointer to the vector of strings associated with a key (parameter) for a route specified by port and URI ♡
//        // ♡♡♡ Returns nullptr if the port, URI, or key do not exist ♡
//        const std::vector<std::string>* getParam(int port, const std::string& uri, const std::string& key) const;
//
//		//♡♡♡ Returns the custom error page path for a given port and URI, checking location-level config first.♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡
//		//♡♡♡ Falls back to server-level config if no match is found in the location.                           ♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡
//		const std::string*	getErrorPage(int port, const std::string& error, const std::string& uri) const;
//
//		//♡♡♡ Returns the custom error page path for a given port, using only server-level configuration.♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡
//		//♡♡♡ Does not consider URI-specific location blocks.                                            ♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡
//		const std::string*	getErrorPage(int port, const std::string& error ) const;
//
//		const std::string*	ServerName(int port) const ;
//		const std::string*	ServerRoot(int port) const ;
//		const size_t		GetMaxBody(int port) const ;
//		const size_t		GetMaxBody(int port, const std::strin& uri) const ;

	private:

		   std::vector<Node>		tree;
		   std::vector<Servers>		servers;
		   std::map<int, Node*>		MapNode;
		   std::vector<int>		allPort;

};


void opokopkda
{
	const std::vector<int> port = getAllPorts();
	std::vector<int>::const_iterator it = port.begin();
	while ( )
	{
		ServerName( *it );
		S
	}
	const std::vector<Node*> Servers = getVectorOfServer();
	Servers.getName();
	for (auto it = servers.begin() ...)) {
		initialize(*it);
	}

}
