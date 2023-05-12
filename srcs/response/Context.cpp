/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Context.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 00:28:01 by ntan              #+#    #+#             */
/*   Updated: 2022/12/12 16:25:22 by ntan        	     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Context.hpp"

Context::Context(Config conf, Request req) : config(conf), request(req)
{
	find_server();

	if (!this->servers.empty())
		this->server = this->servers[0];
	else
		this->server = Server();

	this->location = Location();
	find_location();
	while (!this->location.rewrite.values.empty() 
	&& this->request.path[0].find(this->location.rewrite[0]) != std::string::npos)
	{
		this->request.path[0].replace(this->request.path[0].find(this->location.rewrite[0]), this->location.rewrite[0].size(), this->location.rewrite[1]);
		find_location();
		this->location.rewrite.delimiter = "TRUE";
	}
	this->server.locations_count = 1;
	this->server.locations[0] = this->location;
}

void	Context::find_server()
{
	// If there is no server in config file, use default server
	if (this->config.servers_count == 0)
	{
		this->servers.push_back(this->config.servers[0]);
		std::cout << "No server corresponding in config file, using default server" << std::endl;
		return ;
	}

	// Search a server with exact same ip and port
	for (size_t i = 0; i < this->config.servers_count; i++)
	{
		if ((this->config.servers[i].listen[0] == this->request.host[0])
				&& this->config.servers[i].listen[1] == this->request.host[1])
		{
			this->servers.push_back(this->config.servers[i]);
		}
	}

	// Consider server witout ip or with default ip 0.0.0.0 if no server found
	// (server without ip get 0.0.0.0 by default in server.cpp)
	if (this->servers.empty())
	{
		for (size_t i = 0; i < this->config.servers_count; i++)
		{
			if (this->config.servers[i].listen[0] == "0.0.0.0"
					&& this->config.servers[i].listen[1] == this->request.host[1])
				this->servers.push_back(this->config.servers[i]);
		}
	}

	if (this->servers.size() == 1)
		return ;

	// find the server with the same server_name
	for (size_t i = 0; i < this->servers.size(); i++)
	{
		if (this->servers[i].server_name[0] == this->request.host[0])
		{
			this->servers.insert(this->servers.begin(), this->servers[i]);
			break;
		}
	}
}

void	string_to_vector_with_delim(std::vector<std::string> &res, std::string str, std::string delim)
{
	size_t	delim_pos = 0;
	str.erase(str.begin());

	while (delim_pos != std::string::npos)
	{
		delim_pos = str.find(delim);
		if (delim_pos == 0 || str.empty())
			break;
		if (!str.substr(0, delim_pos).empty())
			res.push_back(str.substr(0, delim_pos));
		str = str.substr(delim_pos + 1);
	}
}

// prioritize exact path, then / path, then default location if no location found
void	Context::find_location()
{
	if (this->servers.empty())
		return ;

	// Search a location with exact same path
	for (size_t i = 0; i < this->server.locations_count; i++)
	{
		if (this->server.locations[i].path == this->request.path)
		{
			this->location = this->servers[0].locations[i];
			return;
		}
	}

	// Search best matching location
	std::vector<int> match_count;
	for (size_t i = 0; i < this->server.locations_count; i++)
	{
		std::vector<std::string> parsed_lpath;
		string_to_vector_with_delim(parsed_lpath, server.locations[i].path[0], "/");
		std::vector<std::string> parsed_rpath;
		string_to_vector_with_delim(parsed_rpath, request.path[0], "/");

		if (parsed_lpath.size() > parsed_rpath.size())
			match_count.push_back(0);
		else
		{
			int res = 0;
			std::vector<std::string>::iterator beg = parsed_lpath.begin();
			std::vector<std::string>::iterator end = parsed_lpath.end();
			std::vector<std::string>::iterator rbeg = parsed_rpath.begin();
			std::vector<std::string>::iterator rend = parsed_rpath.end();
			for (; beg != end && rbeg != rend; beg++, rbeg++)
			{
				if (*beg == *rbeg)
					res++;
				else
				{
					res = 0;
					break;
				}
			}
			match_count.push_back(res);
		}
	}
	if (this->server.locations_count > 0 && *std::max_element(match_count.begin(), match_count.end()) != 0)
	{
		this->location = this->server.locations[std::max_element(match_count.begin(), match_count.end()) - match_count.begin()];
		return;
	}

	// Use default / location
	for (size_t i = 0; i < this->server.locations_count; i++)
	{
		if (this->server.locations[i].path.values[0] == "/")
		{
			this->location = this->server.locations[i];
			return;
		}
	}

	// if (this->request.path[0].find(this->location.rewrite[0]) != std::string::npos)
	// {
	// 	this->request.path[0].replace(this->request.path[0].find(this->location.rewrite[0]), this->location.rewrite[0].size(), this->location.rewrite[1]);
	// 	find_location();
	// }
}

/* ************************************************************************** */
/* DEBUG */

void	Context::print_context()
{
	std::cout << "----- [CONTEXT] -----" << std::endl;
	if (this->servers.empty())
		std::cout << "No server found" << std::endl;
	else
		this->server.print_config();
}