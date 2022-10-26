/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServ.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:06:18 by obeaj             #+#    #+#             */
/*   Updated: 2022/10/26 14:39:09 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP  
#define WEBSERV_HPP

#include "common.h"
#include "createSocket.hpp"
#include "parsing.hpp"
#include "server.hpp"

class webserv
{
    public:
        webserv();
        ~webserv();
};
#endif