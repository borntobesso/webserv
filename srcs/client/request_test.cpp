/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_test.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:53:29 by ntan              #+#    #+#             */
/*   Updated: 2022/12/09 15:01:10 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Request.hpp"
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <string>
# include <iostream>

int	main()
{
	int fd = open("request_example", O_RDONLY);
	char buffer[30000];
	int rd = read(fd, buffer, 30000);
	std::string str(buffer, rd);

	try
	{
		Request	request(str);
		request.print_request();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}