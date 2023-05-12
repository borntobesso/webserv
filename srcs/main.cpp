/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soyoungjung <soyoungjung@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 14:57:05 by ntan              #+#    #+#             */
/*   Updated: 2022/12/26 00:20:06 by soyoungjung      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config/Config.hpp"
#include "client/Request.hpp"
#include "webserver/Webserver.hpp"

#include <unistd.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include "netinet/in.h"
#include <poll.h>
#include <sys/epoll.h>

// #define PORT 8000

int main(int argc, char *argv[])
{
	std::string path;

	if (argc > 2)
	{
		std::cerr << "one configuration file needed" << std::endl;
		return (1);
	}
	else if (argc == 2)
	{
		path = argv[1];
		struct stat s;

		if (path.find_last_of(".") == std::string::npos || path.substr(path.find_last_of("."), path.size()) != ".conf" || path.size() <= 5)
		{
			std::cerr << ".conf file name error" << std::endl;
			return (1);
		}
		if (stat(path.c_str(), &s) == -1 || !(s.st_mode & S_IFREG))
		{
			std::cout << "please check the configuration file" << std::endl;
			return (1);
		}
	}
	else
		path = "./config_files/default.conf";
	try
	{
		Webserver webserver(path.c_str());
		webserver.start();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}
