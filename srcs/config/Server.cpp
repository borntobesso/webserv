/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:47:35 by ntan              #+#    #+#             */
/*   Updated: 2022/12/27 13:38:58 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Server.hpp"

Server::Server() :	locations_count(0),
	listen("listen", "0.0.0.0:8000", ":"),
	server_name("server_name", "", ""),
	client_max_body_size("client_max_body_size", "100", ""),
	error_page("error_page", "", ",")
	{
		locations[0] = Location();
	}

Server::~Server() {}

Server::Server(std::string text) :	textfile(text), locations_count(0),
	// **ADD KEYS HERE, DEFAULT VALUES, DON'T LET SPACES BETWEEN VALUES
	// usage : object("object", "values seperated by delim", "delim") 
	// -> if no delimiter given, it will only consider a whole value
	listen("listen", "0.0.0.0:8000", ":"),
	server_name("server_name", "", ""),
	client_max_body_size("client_max_body_size", "100", ""),
	error_page("error_page", "", ",")							
{
	locations[0] = Location();
	parse_lines();
} 

/* ************************************************************************** */
/* STATIC */

void	remove_newline(std::string &str)
{
	while (str.find("\n") != std::string::npos)
	{
		str.erase(str.find("\n"));
	}
}

/* ************************************************************************** */
/* MAIN */

void	Server::parse_lines_forest(std::string name, std::string value)
{
	//	**ADD KEYS HERE
	if (name == "listen")
	{
		listen.setValue(value);
		if ((listen.values.size() < 2 || listen.values[1].empty()) 
				&& listen.values[0].find(".") != std::string::npos)
			listen.values.push_back("8000");
		if ((listen.values.size() < 2 || listen.values[1].empty()) 
				&& listen.values[0].find(".") == std::string::npos)
			listen.values.insert(listen.values.begin(), "0.0.0.0");
	}
	else if (name == "server_name")
		server_name.setValue(value);
	else if (name == "client_max_body_size")
		client_max_body_size.setValue(value);
	else if (name == "error_page")
		error_page.setValue(value);
	else if (name == "location")
		addLocation(value);
	else if (name == "allowed_methods")
		currentLocation().allowed_methods.setValue(value);
	else if (name == "rewrite")
		currentLocation().rewrite.setValue(value);
	else if (name == "root")
		currentLocation().root.setValue(value);
	else if (name == "autoindex")
		currentLocation().autoindex.setValue(value);
	else if (name == "cgi")
		currentLocation().cgi.setValue(value);
	else if (name == "index")
		currentLocation().index.setValue(value);
	else if (name == "upload_dir")
		currentLocation().upload_dir.setValue(value);
	// else if (name == "index")
	// 	currentLocation().index.setValue(value);
	else
		std::cout << "unrecognized instruction : " << name << ", skipping this keyword" << std::endl;
}

void	Server::parse_lines()
{
	size_t pos = 0, delim = 0;
	std::string line, name, value;
	while (pos != std::string::npos)
	{
		line = textfile.substr(pos, textfile.find("\n", pos));
		remove_newline(line);
		
		delim = line.find(":");
		if (delim != std::string::npos)
		{
			name = line.substr(0, delim);
			value = line.substr(delim + 1);
			parse_lines_forest(name, value);
		}
		
		pos = textfile.find("\n", pos);
		if (pos != std::string::npos)
			pos += 1;
	}
}

void	Server::addLocation(std::string value)
{	
	if (locations_count < MAX_LOCATIONS)
	{	
		this->locations[locations_count].path.setValue(value);
		this->locations_count++;
	}
	else
		std::cerr << "MAX LOCATIONS (" << MAX_LOCATIONS <<  ") reached, increases in Config.hpp" << std::endl;
}

// Return the last added location block
Location&	Server::currentLocation()
{
	if (locations_count > 0)
		return (this->locations[locations_count - 1]);
	else
	{
		std::cout << "Instructions before any locations block" << std::endl;
		throw (std::exception());
	}
}

/* ************************************************************************** */
/* DEBUG */

std::string	Server::getTextfile()
{
	return (this->textfile);
}

void		Server::print_config()
{
	// **ADD KEYS HERE
	listen.print();
	server_name.print();
	client_max_body_size.print();
	error_page.print();
	if (locations_count > 0)
	{
		for (size_t i = 0; i < locations_count; i++)
		{
			std::cout << "(" << i << ") ";
			locations[i].print_location();
		}
	}
	else
		locations[0].print_location();
		
}
