/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:41:15 by ntan              #+#    #+#             */
/*   Updated: 2022/12/26 15:54:54 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "Server.hpp"
# include <iostream>
# include <fstream>
# include <string>
# include <algorithm>
# include <cstdlib>

# define MAX_SERV 10
# define MAX_LOCATIONS 10
# define CGI ".php"
# define CGI_PATH "/bin/php"

class Config
{
	public:
		Config(char const *path);
		Config();
		~Config();
		
	public:
		std::string		getConfig();
		void			printServers();

	public:
		std::string		textfile;
		size_t			servers_count;
		Server			servers[MAX_SERV];

	private:
		int		read_config_file(char const *path);
		int		parse_server_blocks();
		void	addServer(std::string server_block);
};

#endif