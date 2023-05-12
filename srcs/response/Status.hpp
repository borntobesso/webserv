/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Status.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:06:44 by ntan              #+#    #+#             */
/*   Updated: 2022/12/14 14:14:26 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef STATUS_HPP
# define STATUS_HPP

# include <string>
# include <map>

class Status {

	public:
		Status();

	private:
		std::map<std::string, std::string>	codes_map;

	public:
		std::string get_message(std::string code);
};

#endif