## Overview of Configuration Getters and Node Navigation

This project provides **multiple ways** to explore and access configuration data. You can navigate the entire server list, search for routes inside servers, get parameters, or find specific child nodes in the configuration tree.

### How to Use These Getters and Functions

#### 1. Accessing Servers

- `getVectorOfServer()`  
  Returns a **list of all servers** in the configuration.

- `getFullMap()`  
  Returns a **map of servers indexed by port numbers**, for quick lookup by port.

- `getAllPorts()`  
  Returns a **list of all ports** configured.

- `hasPort(port)`  
  Returns `true` or `false` depending if a server with the specified port exists.

- `getServerNode(port)`  
  Returns the **server node for the given port**.

#### 2. Accessing Routes inside Servers

- `getMapOfOneServer(port)`  
  Returns a **map of URI strings to route nodes** for the specified server port.

- `getRouteNode(port, uri)`  
  Returns the **route node** (child node) inside the server identified by port for the given URI.

#### 3. Accessing Parameters (Key-Value pairs)

- `getParamOfServer(port, key)`  
  Returns the **values of a parameter key** for the specified server.

- `getParamOfRouteNode(port, uri, key)`  
  Returns the **values of a parameter key** inside a specific route of a server.

#### 4. Navigating Children Nodes directly (`Node` method)

- `Node::findChildNode(const std::string& uri) const`  
  This function searches **inside a single `Node`’s children** for a child node matching the given URI.  
  It returns a pointer to the matching child node if found, or `nullptr` if no child matches.  

  Use this when you already have a `Node` (like a server node) and want to quickly find one of its route children by URI without iterating manually.

---

### Summary

- The configuration is stored as a **tree of `Node`s**, each with parameters and children.
- Servers are identified by ports.
- Each server node can have multiple routes (children) identified by URI.
- You can use the getters to navigate:
  - List of servers  
  - Servers by port  
  - Routes inside servers  
  - Parameters inside servers or routes  
- Use `findChildNode` on a Node to find a child route directly by URI, making navigation easier and cleaner.

---

This comprehensive set of getters and helper functions allows you to explore and query the configuration data flexibly and efficiently.
