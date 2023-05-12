/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:15:49 by ntan              #+#    #+#             */
/*   Updated: 2022/12/26 17:54:16 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "Keys.hpp"
# include <string>
# include <iostream>

class Location {

	public:
		Location();

		void	print_location();
	
		// **ADD KEYS HERE
		Keys	path;					//	request with this path will use this block
		Keys	allowed_methods;		//	allowed methods for this location
		Keys	rewrite;				//	redirection
		Keys	root;					//	directory or file where the file should be searched from
		Keys	autoindex;				//	define if directory listing in enabled
		Keys	cgi;					// 
		Keys	index;	//	default file if the request is a directory
		Keys	upload_dir;				// 	allow this location to accept upload and define a directory to store them
		// Keys	index;
};

#endif