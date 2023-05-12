/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Keys.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:49:18 by ntan              #+#    #+#             */
/*   Updated: 2022/12/12 16:30:11 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_HPP
# define KEYS_HPP

# include <vector>
# include <string>
# include <iostream>

class Keys
{
	public:
		Keys();
		Keys(std::string _name, std::string _value, std::string _delimiter);
		~Keys();
		
		
	public:
		std::string					name;			// name of the keyword
		std::vector<std::string>	values;			// values for this keyword, can contains multiple values
		std::string					delimiter;		// delimiter if there is multiple arguments
		// std::string					default_value;	// default value if not provided
		// bool						mandatory;		// to check if the value must be provided
		// bool						multi_args;		// to check if there is multiple value
		// bool						set;			// to check if the value was register at least once
		
	public:
		void	setValue(std::string newValue);
		void	setValue(std::string newValue, std::string delim);
		void	addValue(std::string newValue);
		void	print();

	public:
		std::string	&operator[](size_t n);
		bool 		operator==(const Keys &rhs) const;
};

#endif