/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:15:52 by ntan              #+#    #+#             */
/*   Updated: 2022/12/27 17:14:49 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Location.hpp"

Location::Location() : 
	// **ADD KEYS HERE, DEFAULT VALUES, DON'T LET SPACES BETWEEN VALUES
	// usage : object("object", "values seperated by delim", "delim") 
	// -> if no delimiter given, it will only consider a whole value
	path("location", "/", "<"),
	allowed_methods("allowed_methods", "GET", ","),
	rewrite("rewrite", "", ","),
	root("root", "data", ""),
	autoindex("autoindex", "on", ""),
	cgi("cgi", "off", ""),
	index("index", "", ""),
	upload_dir("upload_dir", "./data/upload", "")
	// index("index", "index", "")
{}

void	Location::print_location()
{
	path.print();
	std::cout << "\t";
	allowed_methods.print();
	std::cout << "\t";
	rewrite.print();
	std::cout << "\t";
	root.print();
	std::cout << "\t";
	autoindex.print();
	std::cout << "\t";
	cgi.print();
	std::cout << "\t";
	index.print();
	std::cout << "\t";
	upload_dir.print();
	// std::cout << "\t";
	// index.print();
}