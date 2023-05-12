/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Context.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 23:43:07 by ntan              #+#    #+#             */
/*   Updated: 2022/12/19 17:37:43 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_HPP
# define CONTEXT_HPP

# include "../config/Config.hpp"
# include "../client/Request.hpp"

# include <string>
# include <iostream>
# include <algorithm>

class Context {
	public:
		Context(Config conf, Request req);

	// private:
		Config	config;
		Request	request;
		void	print_context();

	private:
		void	find_server();
		void	find_location();
	
	private:
		// used for parsing
		std::vector<Server>	servers;

	public:
		// used for response
		Server				server;
		Location			location;
};

#endif