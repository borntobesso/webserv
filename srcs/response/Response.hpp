/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:49:15 by ntan              #+#    #+#             */
/*   Updated: 2022/12/26 18:25:42 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "Context.hpp"
# include "Status.hpp"
# include "CgiHandler.hpp"

# include <algorithm>
# include <fstream>
# include <cstdlib>
# include <sstream>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <dirent.h>
# include <cstdio>

class Response {
	public:
		Response(Context cont);
		
	private:
		Status		status;
		Context		context;
		std::string	response;
		std::vector<unsigned char>	charvec_response;

	// Elements of the response
	public:
		Keys	version_code_message; 				// [0] = version, [1] = status_code, [2] = status_msg 
		Keys	server;
		Keys	content_length;
		Keys	content_type;
		Keys	body;

	private:
		void	check_response();
		void	set_status(std::string code);
		int		check_allowed_methods();
		int		check_version();
		int		check_max_body_size();
		int		check_file();
		int		check_rewrite();  
		int		check_access();
		
		void		make_body(std::string path);						// generate the body according to the status
		void		add_string_to_vector(std::string str);
		void		read_file(std::string path);
		int			directory_listing(std::string path);
		void	get_error_page();

		
		void	make_response();					// assemble response in http format

	public:
		void	print_response();
		const char	*get_response();
		std::vector<unsigned char> get_vector();
		
};

#endif