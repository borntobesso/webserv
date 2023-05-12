/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:41:21 by ntan              #+#    #+#             */
/*   Updated: 2022/12/19 15:25:46 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

Config::Config() : servers_count(0) {}

Config::~Config() {}

Config::Config(char const *path) : servers_count(0)
{
	servers[0] = Server();
	read_config_file(path);
	parse_server_blocks();
}

std::string	Config::getConfig()
{
	return (this->textfile);
}

void	Config::printServers()
{
	std::cout << "###############" << std::endl;
	std::cout << "example : first argument of listen in server 0, use conf.servers[0].listen[0] (here it is : [" << servers[0].listen[0] << "])" << std::endl;
	std::cout << "example : allowed_methods in server 0, use conf.servers[0].locations[0].allowed_methods[0] (here it is : [" << servers[0].locations[0].allowed_methods[0] << "])" << std::endl;
	std::cout << "###############" << std::endl;
	for (size_t i = 0; i < servers_count; i++)
	{
		std::cout << "------[ SERVER : " << i << " ]------" << std::endl;
		servers[i].print_config();
		std::cout << std::endl;
	} 
}

///////// STATIC FUNCTIONS /////////

void	print_exit(char const *error, std::string msg)
{
	std::cout << error << msg << std::endl;
	throw (std::exception());
}

void	print_exit(char const *error, size_t num)
{
	std::cout << error << num << std::endl;
	throw (std::exception());
}

///////// PRIVATE FUNCTIONS /////////

int	Config::read_config_file(char const *path)
{
	std::fstream	fs(path, std::fstream::in);
	if (!(fs.is_open()))
		print_exit("ERROR: Could not read file at ", path);
	std::string line;
	while (getline(fs, line))
	{
		line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
		if (line[0] == '#' || line.empty())
			continue;
		textfile.append(line + "\n");
	}
	return (0);
}

int	Config::parse_server_blocks()
{
	std::string keyword = "server";
	std::string open_bracket = "{";
	std::string close_bracket = "}";
	size_t pos = 0;
	size_t i = 0;
	while (pos != std::string::npos)
	{
		pos = this->textfile.find(keyword, i);
		if (pos == std::string::npos)
			break;
		size_t first = textfile.find(open_bracket, pos);
		size_t last = textfile.find(close_bracket, pos);

		// ERRORS CHECKING //
		if (first != std::string::npos && last == std::string::npos) 
			print_exit("ERROR: Missing operator: ", close_bracket);
		if (first == std::string::npos && last != std::string::npos)
			print_exit("ERROR: Missing operator: ", open_bracket);
		if (textfile[pos + keyword.size()] != open_bracket[0]) 
			print_exit("ERROR: Unrecognized : ", textfile.substr(pos, first - pos));
		if (last < first)
			print_exit("ERROR: Incorrect use of { or } at pos: ", last);
		first += 2;
		addServer(textfile.substr(first , last - first));
		i = last;
	}
	return (0);
}

void	Config::addServer(std::string server_block)
{
	if (servers_count < MAX_SERV)
	{
		this->servers[servers_count] = Server(server_block);
		servers_count++;
	}
	else
		std::cout << "MAX SERV (" << MAX_SERV << ") reached, increase in Config.hpp" << std::endl; 
}
