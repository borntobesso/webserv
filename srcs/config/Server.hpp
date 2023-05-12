/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:15:38 by ntan              #+#    #+#             */
/*   Updated: 2022/12/13 14:14:57 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Location.hpp"
# include "Keys.hpp"
# include <string>
# include <iostream>

# ifndef MAX_LOCATIONS // defined in config.hpp
# define MAX_LOCATIONS 10
# endif

class Server
{
	public:
		Server();
		Server(std::string text);
		~Server();

	public:
		std::string	getTextfile();
		void		print_config();
		void		parse_lines();
		void		parse_lines_forest(std::string name, std::string value);
		void		addLocation(std::string value);
		Location&	currentLocation();

	public:
		std::string	textfile; // Raw server block
		
		Location	locations[MAX_LOCATIONS];
		size_t		locations_count;

		// **ADD KEYS HERE
		Keys	listen;					// define ip and port of the virtual server
		Keys	server_name;			// optional name in addition of listen
		Keys	client_max_body_size;	// max size that the client can send
		Keys	error_page;				// define default error page

};

/* To add a new keyword :
1- Add the Keys object in *Server.hpp
2- Add his default configuration in the constructor in *Server.cpp
3- Add a if condition in parse_lines_forest 

note : *replace Server.#pp by Location.#pp if the new keyword will be in a location block */

#endif