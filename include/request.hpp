/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:54:00 by obeaj             #+#    #+#             */
/*   Updated: 2022/10/19 11:33:14 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP
# include <map>
# include <vector>
# include <iostream>
# include <cstring>
# include <sstream>


class request
{
    private:
        std::map<std::string, std::vector<std::string> > req;
    public:
        request(std::string _req);
        ~request();
        void parseReqLine(std::string line);
        void parseReqMethods(std::string line);
        
};
#endif