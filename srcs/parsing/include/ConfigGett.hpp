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
	const size_t		getClientMaxBodySize( void )const;
	const bool			getAutoIndex( void ) const;
	const std::string*	getRoot( void ) const;
	const std::string*	getIndex( void ) const;
	const bool			getMethodIsAllowed(const std::string& method) const;
	const std::string*	getAlias() const;

};
class Server
{
	private:
	std::string name;
	std::map<std::string, Location> route;
	std::vector<Location> location;
	std::map<std::string, std::vector<std::string> > prmtrs; 
	public:
	const std::string&	getName( void ) const;
	const size_t		getHost( void )const;
	const size_t		getClientMaxBodySize( void )const;
	const bool			getAutoIndex( void ) const;
	const std::string*	getRoot( void ) const;
	const std::string*	getIndex( void ) const;
	const int			getPort( void ) const;
	const Location*		getLocation(const std::string& uri) const;
	const Location*		getCgiBin( void ) const;
	const std::string*	getErrorPageLocation(const std::string& uri, const std::string& nbrError)const;
	const std::string*	getErrorPage(const std::string& nbrError) const;
};

class	ConfigGett
{
	public:
//		ConfigGett(const ConfigProcessor& Parser );
//		virtual ~ConfigGett();
//
//
//        // ♡ Returns a const reference to the main vector of server nodes ♡
//        const std::vector<const Servers>& getVectorOfServer(void) const;
//
//
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
//		const std::string* getIndex(int port, const)
//
//
//
//		//♡♡♡ Returns the custom error page path for a given port and URI, checking location-level config first.♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡
//		//♡♡♡ Falls back to server-level config if no match is found in the location.                           ♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡
//		const std::string*	getErrorPage(int port, const std::string& error, const std::string& uri) const;
//
//		//♡♡♡ Returns the custom error page path for a given port, using only server-level configuration.♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡
//		//♡♡♡ Does not consider URI-specific location blocks.                                            ♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡
//		const std::string*	getErrorPage(int port, const std::string& error ) const;
//

	private:

		   std::vector<Node>		tree;
		   std::vector<Server>		servers;
		   std::map<int, Node*>		MapNode;
		   std::vector<int>		allPort;

};
