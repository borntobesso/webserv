/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:21:29 by ntan              #+#    #+#             */
/*   Updated: 2022/12/07 19:20:17 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Config.hpp"
# include <iostream>
# include <fstream>
# include <string>

int main()
{
	try
	{
		char *str = (char *)"../../config_files/default.conf";
		Config conf(str);
		conf.printServers();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return (1);
	}
	return (0);
}