/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketInfo.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsung <rsung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:13:45 by rsung             #+#    #+#             */
/*   Updated: 2022/12/23 15:29:03 by rsung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SocketInfo.hpp"
#include "UserData.hpp"

SocketInfo::SocketInfo(Config conf) : server_fds(std::vector<int>()), on(1), config(conf)
{
	// ports[0] = 8000;
	// ports[1] = 8080;
	// std::memset((char*) &address, 0, sizeof(address));
	// address.sin_family = AF_INET;
	// address.sin_addr.s_addr = htonl(INADDR_ANY);
	// address.sin_port = htons(PORT);
	end_server = FALSE;
	FD_ZERO(&master_set);
}

SocketInfo::SocketInfo(const SocketInfo &other)
{
	*this = other;
}

SocketInfo& SocketInfo::operator=(const SocketInfo &other)
{
	this->server_fds = other.server_fds;
	this->on = other.on;
	this->max_fd = other.max_fd;
	this->end_server = other.end_server;
	this->len = other.len;
	this->address = other.address;
	std::memcpy(&(this->master_set), &(other.master_set), sizeof(other.master_set));
	std::memcpy(&(this->working_set), &(other.working_set), sizeof(other.working_set));
	this->timeout = other.timeout;
//	this->buffer = other.buffer;
	return (*this);
}

struct sockaddr_in SocketInfo::set_sockaddr(struct sockaddr_in &address, int ip, int port)
{
	std::memset((char*) &address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(ip);
	address.sin_port = htons(port);
	return (address);
}

// int SocketInfo::create_socket()
// {
// 	this->server_fd = socket(AF_INET, SOCK_STREAM, 0);
// 	if (this->server_fd < 0)
// 	{
// 		std::cerr << "error: socket not created" << std::endl;
// 		return (1);
// 	}
// 	return (0);
// }

// int SocketInfo::set_socket_option()
// {
// 	int	ret = -1;

// 	ret = setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
// 	if (ret < 0)
// 	{
// 		std::cerr << "error: setsockopt() failed" << std::endl;
// 		close(this->server_fd);
// 		return (1);
// 	}
// 	return (0);
// }

// int	SocketInfo::set_non_blocking()
// {
// 	int	ret = -1;

// 	ret = fcntl(this->server_fd, F_SETFL, fcntl(this->server_fd, F_GETFL, 0) | O_NONBLOCK);
// 	if (ret < 0)
// 	{
// 		std::cerr << "error: fcntl() failed" << std::endl;
// 		close(this->server_fd);
// 		return (1);
// 	}
// 	return (0);
// }

// int SocketInfo::bind_socket(struct sockaddr_in &address)
// {
// 	int	ret = -1;

// 	ret = bind(this->server_fd, (struct sockaddr*)&address, sizeof(address));
// 	if (ret < 0)
// 	{
// 		std::cerr << "error: bind() failed" << std::endl;
// 		close(this->server_fd);
// 		return (1);
// 	}
// 	return (0);
// }

int SocketInfo::listen_socket()
{
	int ret = -1;

	for (size_t i = 0; i < this->server_fds.size(); i++)
	{
		ret = listen(server_fds[i], MAX_BACKLOG);
		if (ret < 0)
		{
			std::cerr << "error: listen() failed" << std::endl;
			close(server_fds[i]);
			return (1);
		}
	}
	return (0);
}

// void	SocketInfo::add_socket(int ip, int port)
// {
// 	struct sockaddr_in address;

// 	// set_sockaddr(address, ip, port);
// 	std::memset((char*) &address, 0, sizeof(address));
// 	address.sin_family = AF_INET;
// 	address.sin_addr.s_addr = htonl(ip);
// 	address.sin_port = htons(port);

// 	create_socket();
// 	set_socket_option();
// 	set_non_blocking();

// 	// bind_socket(address);
// 	int	ret = -1;

// 	ret = bind(this->server_fd, (struct sockaddr*)&address, sizeof(address));
// 	std::cout << "errno: " << strerror(errno) << std::endl;
// 	if (ret < 0)
// 	{
// 		std::cerr << "error: bind() failed" << std::endl;
// 		close(this->server_fd);
// 		return;
// 	}

// 	listen_socket();
// 	init_master_set();
// }


// void	SocketInfo::add_socket(int ip, int port)
// {
// 	struct sockaddr_in address;

// 	// set_sockaddr(address, ip, port);
// 	std::memset((char*) &address, 0, sizeof(address));
// 	address.sin_family = AF_INET;
// 	address.sin_addr.s_addr = htonl(ip);
// 	address.sin_port = htons(port);

// 	create_socket();
// 	set_socket_option();
// 	set_non_blocking();

// 	// bind_socket(address);
// 	int	ret = -1;

// 	ret = bind(this->server_fd, (struct sockaddr*)&address, sizeof(address));
// 	if (ret < 0)
// 	{
// 		std::cerr << "error: bind() failed" << std::endl;
// 		close(this->server_fd);
// 		return;
// 	}

// 	listen_socket();
// 	init_master_set();
// }

// void	SocketInfo::init_master_set()
// {
// 	// FD_ZERO(&(this->master_set));
// 	this->max_fd = this->server_fd;
// 	FD_SET(server_fd, &master_set);
// }

void	SocketInfo::set_timeout()
{
	
	timeout.tv_sec = 10 * 60;
	timeout.tv_usec = 0;
}

void SocketInfo::socket_master(std::vector<int> &ports)
{
	int ret = -1;

	for (size_t i = 0; i < ports.size(); i++)
	{
		int fd = socket(AF_INET, SOCK_STREAM, 0);
		if (fd < 0)
		{
			std::cerr << "error: socket not created" << std::endl;
			break;
		}

		ret = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&this->on, sizeof(this->on));
		if (ret < 0)
		{
			std::cerr << "error: setsockopt() failed" << std::endl;
			break;
		}

		ret = fcntl(fd, F_SETFL, O_NONBLOCK);
		if (ret < 0)
		{
			std::cerr << "error: fcntl() failed" << std::endl;
			close(fd);
			break;
		}
		struct sockaddr_in address;
		std::memset((char *)&address, 0, sizeof(address));
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = htonl(INADDR_ANY);
		address.sin_port = htons(ports[i]);

		// std::cout << "Actual FD : " << fd << std::endl;
		ret = bind(fd, (struct sockaddr *)&address, sizeof(address));
		if (ret < 0)
		{
			std::cerr << "error: bind() failed" << std::endl;
			close(fd);
			continue;
		}
		this->server_fds.push_back(fd);
		this->max_fd = fd;
		FD_SET(fd, &master_set);
	}
	// std::cout << "BOUND PORTS : ";
	// for (size_t i = 0; i < server_fds.size(); i++)
	// 	std::cout << server_fds[i] << " ";
	// std::cout << std::endl;
}

void	SocketInfo::server_loop()
{
	int	ret, desc_ready, new_fd, close_connec, i, wait;
	Request		request;
	UserData	data;
	ret = -1;
	desc_ready = 0;
	wait = 0;
	do
	{
		std::memcpy(&working_set, &master_set, sizeof(master_set));
		ret = select(this->max_fd + 1, &working_set, NULL, NULL, &timeout);
		if (ret < 0)
		{
			std::cerr << "error: select() failed" << std::endl;
			break ;
		}
		if (ret == 0)
		{
			std::cerr << "select() timed out. End of program" << std::endl;
			return ;
		}
		desc_ready = ret;
		for (i = 3; i <= max_fd && desc_ready > 0; ++i)
		{
			if (FD_ISSET(i, &working_set))
			{
				desc_ready -= 1;
				if (std::find(server_fds.begin(), server_fds.end(), i) != server_fds.end())
				{
					do
					{
						new_fd = accept(i, NULL, NULL);
						if (new_fd < 0)
						{
							if (errno != EWOULDBLOCK)
							{
								std::cerr << "error: accept() failed" << std::endl;
								end_server = TRUE;
							}
							break ;
						}
						FD_SET(new_fd, &master_set);
						if (new_fd > max_fd)
							max_fd = new_fd;
					} while (new_fd != -1);
				}
				else
				{
					close_connec = FALSE;
					do
					{
						std::memset(buffer, 0, sizeof(buffer));
						ret = recv(i, buffer, sizeof(buffer), MSG_DONTWAIT);
						if (ret < 0)
						{
							// if (errno != EWOULDBLOCK /*&& errno != EAGAIN*/)
							// {
							// 	std::cerr << "error: recv() failed " << strerror(errno) << std::endl;
							// }
							close_connec = TRUE;
							break ;
						}

						if (ret == 0)
						{
							close_connec = TRUE;
							break ;
						}
						// SEND HTML PAGE :

						std::string str_buf(buffer, ret);

						// std::cout << "test : " << str_buf << std::endl;
						if (str_buf.find("multipart/form-data") != std::string::npos)
						{
							request = Request(str_buf);
							wait = 1;
							break;
						}
						else if (wait != 1)
							request = Request(str_buf);
						
						if (wait == 1)
						{
							request.add_to_body(str_buf);
							wait = 0;
						}
						request.print_request();

						Context		context(config, request);
						context.print_context();
						
						Response	response(context);
						response.print_response();
						std::vector<unsigned char> vector_response = response.get_vector();
						len = ret;
						ret = send(i, vector_response.data(), vector_response.size(), 0);		
						if (ret < 0)
						{
							std::cerr << "error: send() failed" << std::endl;
							close_connec = TRUE;
							break ; 
						}
					} while (TRUE);
					if (close_connec == TRUE)
					{
						close(i);
						FD_CLR(i, &master_set);
						if (i == max_fd)
						{
							while (FD_ISSET(max_fd, &master_set) == FALSE)
								max_fd -= 1;
						}
					}
				}
			}
		}
	} while (end_server == FALSE);
	for (int j = 3; j <= max_fd; j++)
	{
		if (FD_ISSET(j, &master_set))
			close(j);
	}
}
