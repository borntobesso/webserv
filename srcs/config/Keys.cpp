/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Keys.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:48:55 by ntan              #+#    #+#             */
/*   Updated: 2022/12/16 14:04:24 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Keys.hpp"

Keys::Keys() {}

Keys::Keys(std::string _name, std::string _value, std::string _delimiter)
{
	this->name = _name;
	this->delimiter = _delimiter;
	setValue(_value);
}

Keys::~Keys() {}

std::string	&Keys::operator[](size_t n)
{
	if (n > this->values.size())
		throw (std::out_of_range("Keys::operator[]: out of range"));
	return (this->values[n]);
}

bool 		Keys::operator==(const Keys &rhs) const
{
	return (this->values == rhs.values);
}

/////////////////////////

void	Keys::setValue(std::string newValue)
{
	if (!newValue.empty())
		this->values.clear();

	size_t delim_pos = 0;
	if (this->delimiter != "")
	{
		while (delim_pos != std::string::npos)
		{
			delim_pos = newValue.find(this->delimiter);
			if (delim_pos == 0 && newValue.empty())
				break;
			if (!newValue.substr(0, delim_pos).empty())
				addValue(newValue.substr(0, delim_pos));
			newValue = newValue.substr(delim_pos + 1);
		}
	}
	else
	{
		if (!newValue.empty() || this->values.empty())
			addValue(newValue);
	}
}

void	Keys::addValue(std::string newValue)
{
	this->values.push_back(newValue);
}

///// DEBUG FUNCTIONS /////

std::string	concat_vector_str(std::vector<std::string> &vec_list)
{
	typedef std::vector<std::string>::iterator	iterator;
	std::string res;
	size_t i = 0;
	for (iterator beg = vec_list.begin(); beg != vec_list.end(); ++beg, i++)
	{
		res +=  "[" + *beg + "] ";
	}
	return (res);
}

void		Keys::print()
{
	std::cout << this->name << " : " << concat_vector_str(this->values) << std::endl;
}