/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:58:23 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/19 02:40:02 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CGI__HPP__
#define __CGI__HPP__
#include "common.h"
#include "request.hpp"

class cgi
{
private:
    std::map<std::string, std::string> env;
    String body;
public:
    cgi();
    cgi(String path, request req);
    ~cgi();
    void    cgiEnvInit(String path, request req);
    String  executeCgi(String script, String cgi_pass);
    char    **getEnv() const;
};

#endif  //!__CGI__H__

