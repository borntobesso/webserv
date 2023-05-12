/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:04:34 by ntan              #+#    #+#             */
/*   Updated: 2022/12/29 14:56:21 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Request.hpp"

Request::Request() : request(std::string()),
	http("http", "", " "),
	method("method", "GET", ""),
	path("path", "/", ""),
	version("version", "HTTP", ""),
	host("host", "127.0.0.1:8000", ":"),
	body("body", "", ""),
	user_agent("user_agent", "", ""),
	content_disposition("Content-Disposition", "", ";"),
	content_type("Content-type", "", ";")
{}

Request::Request(std::string request) : request(request),
	http("http", "", " "),
	method("method", "GET", ""),
	path("path", "/", ""),
	version("version", "HTTP", ""),
	host("host", "127.0.0.1:8000", ":"),
	body("body", "", ""),
	user_agent("user_agent", "", ""),
	content_disposition("Content-Disposition", "", ";"),
	content_type("Content-type", "", ";")
{
	// std::cout << request << std::endl;
	parse_request();
}

/* ************************************************************************** */
/* MAIN */

void	Request::parse_request()
{
	std::string name, value;
	size_t i = 0, delim = 0, endline = 0;
	while (endline != std::string::npos)
	{
		endline = request.find("\n");
		if (request.size() == 0)
			break;
		std::string line(request.substr(0, endline));
		request = request.substr(endline + 1);
		if (i == 0)									// parse the first line
		{
			http.setValue(line);
			if (http.values.size() >= 1)
				method.setValue(http[0]);
			if (http.values.size() >= 2)
				path.setValue(http[1]);
			if (http.values.size() >= 3)
				version.setValue(http[2]);
			if (version.values[0].find("\r") != std::string::npos)
				version.values[0].erase(version.values[0].find("\r"));
		}
		else
		{
			delim = line.find(":");
			if (delim != std::string::npos) 		// if in header part
			{
				name = line.substr(0, delim);
				value = line.substr(delim + 1);
				parse_request_forest(line, name, value);
			}
			else									// if in body part (no ":" found on the line)
			{
				if (!line.empty())
				{
					while (line.find("\r") != std::string::npos)
						line.erase(line.find("\r"));
					if (line.find("WebKit") != std::string::npos)
						continue;
					body.addValue(line);
				}
				
			}
		}
		i++;
	}
}

void	Request::parse_request_forest(std::string line, std::string name, std::string value)
{
	(void)line;
	value.erase(std::remove_if(value.begin(), value.end(), isspace), value.end());
	if (name == "Host")
	{
		host.setValue(value);
		if (host.values.size() < 2 || host.values[1].empty())
			host.values.push_back("8000"); // Defaut port if not given in the request
		if (host[0] == "localhost")
			host[0] = "127.0.0.1";
	}
	else if (name == "User-Agent")
		user_agent.setValue(value);
	else if (name == "Content-Disposition")
	{
		// if (content_disposition.values.empty())
		// 	content_disposition.setValue(value);
		// else
		// 	body.addValue(line);
		content_disposition.setValue(value);
		if (content_disposition.values.size() == 3)
			body.addValue(content_disposition[2] + "&content=");
	}
	// else if (name == "Content-Type")
	// {
	// 	if (content_type.values.empty())
	// 		content_type.setValue(value);
	// 	// else
	// 	// 	body.addValue(line);
	// }
}

void	Request::add_to_body(std::string buf)
{
	std::string line;
	size_t endline = 0;
	while (endline != std::string::npos)
	{
		endline = buf.find("\n");
		if (buf.size() == 0)
			break;
		line = buf.substr(0, endline);
		buf = buf.substr(endline + 1);
		if (!line.empty())
		{
			while (line.find("\r") != std::string::npos)
				line.erase(line.find("\r"));
			if (line.find("WebKit") != std::string::npos 
				|| line.find("Content-Type") != std::string::npos)
				continue;
			if (line.find("Content-Disposition") != std::string::npos)
				line = line.substr(line.find_last_of(";") + 1) + "&content=";
			body.addValue(line);
		}
	}
}

/* ************************************************************************** */
/* DEBUG */

void	Request::print_request()
{
	std::cout << std::endl;
	std::cout << "----- [REQUEST] -----" << std::endl;
	method.print();
	path.print();
	version.print();
	// // std::cout << "name: " << version.values[0] << ";" << std::endl;
	// for (size_t i = 0; i < version.values[0].size(); i++)
	// {
	// 	std::cout << (int) version.values[0][i] << std::endl;
	// }
	host.print();
	body.print();
	user_agent.print();
	// content_disposition.print();
	// content_type.print();
}