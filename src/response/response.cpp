/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:46:12 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/03 04:46:27 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/response.hpp"

response::response()
{
}

response::~response()
{
}

server response::selectServer(std::vector<server> servers, std::string host, std::string port)
{
    std::vector<server>::iterator it = servers.begin();
    std::vector<server> selected;
    server elected;
    while(it != servers.end())
    {
        std::vector<int> ports = (*it).getPorts();
        if(std::find(ports.begin(), ports.end(), stoi(port)) != ports.end())
        {
            selected.push_back(*it);
        }
        it++;
    }
    it = selected.begin();
    while(it != selected.end())
    {
        std::stringstream s((*it).getServerName());
        std::string servername;
        while(std::getline(s, servername, ' '))
        {
            if (servername == host)
                elected = *it;
        }
        it++;
    }
    return elected;
}



response::response(request _req, parsing _conf)
{
    req = _req;
    conf = _conf;
    // selecting a server
    server  serv = selectServer(createServers(conf.getData(), conf), req.getReqHost(), req.getReqPort());
    // matching the path location
    _path = serv.getRootPath() + req.getReqPath();
    /*locationMatch(serv.getlocations(), req.getReqPath());*/
    
    //
}

void response::setHeaders()
{

}
void response::setBody()
{

}
void response::setStatusCode()
{

}
void response::ResponseBuilder()
{

}
void response::ClearResponse()
{

}
