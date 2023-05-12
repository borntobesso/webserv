/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response_test.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:40:42 by ntan              #+#    #+#             */
/*   Updated: 2022/12/14 16:15:08 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Context.hpp"
# include "Response.hpp"
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <string>
# include <iostream>

int main()
{
	int fd = open("request_example", O_RDONLY);
	char buffer[30000];
	int rd = read(fd, buffer, 30000);
	std::string str(buffer, rd);

	Config 	conf("./default.conf");

	Request req(str);
	Context context(conf, req);
	
	context.config.printServers();
	context.request.print_request();
	context.print_context();

	Response response(context);
	response.print_response();
	std::cout << response.get_response() << std::endl;

	return (0);
}