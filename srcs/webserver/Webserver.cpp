/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserver.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:18:15 by ntan              #+#    #+#             */
/*   Updated: 2022/12/29 16:16:37 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Webserver.hpp"

Webserver::Webserver(const char *path_to_config) : config(path_to_config)
{
	config.printServers();
	std::cout << "----- [CONFIG OK] -----" << std::endl;
}

int	Webserver::start()
{
	SocketInfo	test(this->config);
	
	// int port[2];
	// port[0] = 8000;
	// port[1] = 8002;
	// // for (int i = 0; i < 2; i++)
	// 	test.add_socket(INADDR_ANY, port[0]);
	// 	test.add_socket(INADDR_ANY, port[1]);
	
	// // test.init_master_set();
	// test.set_timeout();
	// test.server_loop();

	std::vector<int> ports;
	int port;

	for (size_t i = 0; i < config.servers_count; i++)
	{
		port = atoi(config.servers[i].listen.values[1].c_str());
		if (std::find(ports.begin(), ports.end(), port) == ports.end())
			ports.push_back(port);
		else
		{
			std::cout << "Same ports detected in the configuration file" << std::endl;
			return (1);
		}
	}
	test.socket_master(ports);
	test.listen_socket();
	test.set_timeout();
	test.server_loop();

	return (0);
}
