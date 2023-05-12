/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserData.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:13:50 by sojung            #+#    #+#             */
/*   Updated: 2022/12/22 16:06:14 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERDATA_HPP
#define USERDATA_HPP

#include <map>
#include <string>
#include <utility> // pair

class UserData {
    public:
    UserData();
    ~UserData();
    UserData(const UserData &rhs);
    UserData &operator=(const UserData &rhs);

    std::pair<std::string, std::string> decomposer(std::string &request);
    void                                addUser(std::string &request);
    void                                deleteUser(std::string &request);
    void                                updateFile();

    private:
    std::map<std::string, std::string>  user_data;
};
#endif