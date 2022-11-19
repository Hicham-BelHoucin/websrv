/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imabid <imabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:46:12 by obeaj             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/19 02:54:44 by obeaj            ###   ########.fr       */
=======
/*   Updated: 2022/11/19 11:34:40 by imabid           ###   ########.fr       */
>>>>>>> 94f6ccec0a62fc1b1ce153eac49926490cabc60e
/*                                                                            */
/* ************************************************************************** */

#include "../../include/response.hpp"

response::response()
{
}

response::~response()
{
}

String	response::writeContent(String path, String body)
{
	std::ofstream	file;
    ResponseIUtils::PATHMODE mode;
    mode = checkPathMode(path);
	if (mode &  ResponseIUtils::ISFILE)
	{
		file.open(path.c_str());
		file << body;
		file.close();
		_status_code = ResponseIUtils::NO_CONTENT;
        return "";
	}
	else
	{
		file.open(_path.c_str(), std::ofstream::out | std::ofstream::trunc);
		if (file.is_open() == false)
		{
            _status_code = ResponseIUtils::FORBIDDEN;
            return readFile(ERROR403);
        }
		file << body;
		file.close();
		_status_code = ResponseIUtils::CREATED;
        return "";
	}

}

server response::selectServer(std::vector<server> servers, std::string host, std::string port)
{
    std::vector<server>::iterator it = servers.begin();
    std::vector<server> selected;
    server elected;
    while (it != servers.end())
    {
        std::vector<int> ports = (*it).getPorts();
        if (std::find(ports.begin(), ports.end(), stoi(port)) != ports.end())
        {
            selected.push_back(*it);
        }
        it++;
    }
    it = selected.begin();
    while (it != selected.end())
    {
        std::stringstream s((*it).getServerName());
        std::string servername;
        while (std::getline(s, servername, ' '))
        {
            if (servername == host)
                elected = *it;
        }
        it++;
    }
    return elected;
}

LocationMap response::locationMatch(Set locations, String path)
{
    Set::iterator it = locations.begin();
    while (it != locations.end())
    {
        if (it->first == path)
        {
            // check if location contain a root
            if ((it->second).find("root") != it->second.end())
                _rootpath = (it->second.find("root")->second)[0];
            return it->second;
        }
        it++;
    }
    if (it == locations.end())
    {
        it = locations.begin();
        while (it != locations.end())
        {
            if (((it->first).find("*") || (it->first).find("?")) && isMatch(it->first, path))
                return it->second;
            it++;
        }
    }
    return locations.find("/")->second;
}

String response::MethodNotAllowed(LocationMap location, String path, String body)
{
    _status_code = ResponseIUtils::NOT_ALLOWED;
    return readFile(ERROR405);
}


String response::MethodGet(LocationMap location, String path, String body)
{
    bool isautoindex;
    // String body = "";
    ResponseIUtils::PATHMODE mode;
    std::vector<String> indexes;
    DIR *Dir;
    struct dirent *DirEntry;
    VecIterator it;

    mode = checkPathMode(path);
    if (mode & ResponseIUtils::ISDIR)
    {
        indexes = location.find("index")->second;
        isautoindex = (location.find("autoindex") != location.end() && location.find("autoindex")->second[0] == "on");
        it = indexes.begin();
        if (mode & (ResponseIUtils::D_READ))
        {
            Dir = opendir(path.c_str());
            while ((DirEntry = readdir(Dir)))
            {
                // Search for index in directory
                if ((it = std::find(indexes.begin(), indexes.end(), DirEntry->d_name)) != indexes.end())
                {
                    // if index.html or index.htm found
                    if (checkExtension(*it) == "html" || checkExtension(*it) == "htm")
                    {
                        _status_code = ResponseIUtils::OK;
                        return (readFile(path + *it));
                    }
                    else
                    {
                        _location = locationMatch(_ServerLocations, *it);
                        return (MethodCheck(_location, _reqMethod, path + *it, body));
                    }
                }
            }
            if (isautoindex)
            {
                _status_code = ResponseIUtils::OK;
                // directory listing autoindex
                return dirListing(path);
            }
        }
        else
        {
            _status_code = ResponseIUtils::FORBIDDEN;
            return readFile(ERROR403);
        }
    }
    else if (mode & ResponseIUtils::ISFILE)
    {
        // if the file is a regulat html file
        if (checkExtension(*it) != "php" || checkExtension(*it) != "py")
        {
            if (mode & ResponseIUtils::F_READ)
            {
                _status_code = ResponseIUtils::OK;
                return (readFile(path));
            }
            else
            {
                _status_code = ResponseIUtils::FORBIDDEN;
                return readFile(ERROR403);
            }
        }
        else
        {
            headers.erase("content-type");
            isCgiBody = true;
            cgi cgiHandler(path, __req);
            return(cgiHandler.executeCgi(path, location.find("fastcgi_pass")->second[0]));
        }
    }
    _status_code = ResponseIUtils::NOT_FOUND;
    return (readFile(ERROR404));
}

String response::MethodPost(LocationMap location, String path, String body)
{
   bool isautoindex;
    // String body = "";
    ResponseIUtils::PATHMODE mode;
    std::vector<String> indexes;
    DIR *Dir;
    struct dirent *DirEntry;
    VecIterator it;

    mode = checkPathMode(path);
    if (mode & ResponseIUtils::ISDIR)
    {
        indexes = location.find("index")->second;
        isautoindex = (location.find("autoindex") != location.end() && location.find("autoindex")->second[0] == "on");
        it = indexes.begin();
        if (mode & (ResponseIUtils::D_READ))
        {
            Dir = opendir(path.c_str());
            while ((DirEntry = readdir(Dir)))
            {
                // Search for index in directory
                if ((it = std::find(indexes.begin(), indexes.end(), DirEntry->d_name)) != indexes.end())
                {
                    // if index.html or index.htm found
                    if (checkExtension(*it) == "html" || checkExtension(*it) == "htm")
                    {
                        _status_code = ResponseIUtils::OK;
                        return (readFile(path + *it));
                    }
                    else
                    {
                        _location = locationMatch(_ServerLocations, *it);
                        return (MethodCheck(_location, _reqMethod, path + *it, body));
                    }
                }
            }
            if (isautoindex)
            {
                _status_code = ResponseIUtils::OK;
                // directory listing autoindex
                return dirListing(path);
            }
        }
        else
        {
            _status_code = ResponseIUtils::FORBIDDEN;
            return readFile(ERROR403);
        }
    }
    else if (mode & ResponseIUtils::ISFILE)
    {
        // if the file is a regulat html file
        if (checkExtension(*it) != "php" || checkExtension(*it) != "py")
        {
            if (mode & ResponseIUtils::F_READ)
            {
                _status_code = ResponseIUtils::OK;
                return (readFile(path));
            }
            else
            {
                _status_code = ResponseIUtils::FORBIDDEN;
                return readFile(ERROR403);
            }
        }
        else
        {
            headers.erase("content-type");
            isCgiBody = true;
            cgi cgiHandler(path, __req);
            return(cgiHandler.executeCgi(path, location.find("fastcgi_pass")->second[0]));
        }
    }
    _status_code = ResponseIUtils::NOT_FOUND;
    return (readFile(ERROR404));
}

String response::MethodPut(LocationMap location, String path, String body)
{
    (void)location;
	return(writeContent(path, body));
}

String response::MethodDelete(LocationMap location, String path, String body)
{
    (void)location;
    ResponseIUtils::PATHMODE mode;

    mode = checkPathMode(path);
    if (mode & ResponseIUtils::ISFILE)
    {
        if (remove(_path.c_str()) == 0)
            _status_code = ResponseIUtils::NO_CONTENT;
        else
        {
            _status_code = ResponseIUtils::FORBIDDEN;
            return readFile(ERROR403);
        }
    }
    else
    {
        _status_code = ResponseIUtils::NOT_FOUND;
        return readFile(ERROR404);
    }
    return "";
}

typedef String (response::*MethodCall)(LocationMap location, String path, String body);

String response::MethodCheck(LocationMap location, String method, String path, String body)
{
    std::map<String, MethodCall> methodsMap;
    std::map<String, MethodCall>::iterator it;
    std::vector<String>::iterator i;
    methodsMap["GET"] = &response::MethodGet;
    methodsMap["POST"] = &response::MethodPost;
    methodsMap["DELETE"] = &response::MethodDelete;
    methodsMap["PUT"] = &response::MethodPut;
    methodsMap["NotAllowed"] = &response::MethodNotAllowed;
    it = methodsMap.begin();
    
    // TODO: Add checking for the body size;
    if (std::stoi(location.find("max_body_size")->second[0]) < body.size())
    {
       _status_code = ResponseIUtils::LARGE_PAYLOAD;
       return(readFile(ERROR413));
    }
    
    while (it != methodsMap.end())
    {
        if (method == it->first)
            return ((this->*(it->second))(location, path, body));
        it++;
    }
    i = std::find(location.find("allow_methods")->second.begin(), location.find("allow_methods")->second.end(), method);
    if (i == location.find("allow_methods")->second.end())
        return ((this->*methodsMap.find("NotAllowed")->second)(location, path, body));
    return "";
}

response::response(request req, parsing conf):__req(req)
{

    statusPhrases = setStatusPhrases();
    // selecting a server
    _serv = selectServer(createServers(conf.getData(), conf), req.getReqHost(), req.getReqPort());
    // matching the path location
    _ServerLocations = _serv.getlocations();
    _reqMethod = req.getReqMethod();
    _rootpath = _serv.getRootPath();
    _path = req.getReqPath();
    _location = locationMatch(_ServerLocations, _path);
    _body = MethodCheck(_location, _reqMethod, _rootpath + _path, req.getReqBody());
    setHeaders(req);
    ResponseBuilder();
}

void response::setHeaders(request req)
{
    headers.insert(std::make_pair("server", "Webserv IHO-0.1"));
    headers.insert(std::make_pair("date", getDate() + "\r\n"));
    // headers["last-modified"] = getLastModified();
    if (req.getHeaderValue("Connection") != "")
        headers.insert(std::make_pair("connection", req.getHeaderValue("Connection") + "\r\n"));
    if (headers.find("connection")->second == "Keep-Alive")
        headers.insert(std::make_pair("keep-alive", "timeout=5, max=1000\r\n"));
    headers.insert(std::make_pair("content-length", std::to_string(_body.length()) + "\r\n"));
    headers.insert(std::make_pair("content-type", getContentType(_body)));
    headers.insert(std::make_pair("content-location", req.getReqPath()));
}

void    response::checkAndAppend(Map &map, String &str, String key)
{
	if (map.find(key) != map.end())
		str.append(map.find(key)->first + ": " + map.find(key)->second + "\r\n");
}

void response::ResponseBuilder()
{
    _response.append("HTTP/1.1 " + std::to_string(_status_code) + statusPhrases[_status_code] + "\r\n");
    checkAndAppend(headers, _response, "connection");
    _response.append(headers.find("connection")->first + ": " + headers.find("connection")->second);
    checkAndAppend(headers,_response,"content-length");
    checkAndAppend(headers,_response,"content-location");
    checkAndAppend(headers,_response,"content-type");
    checkAndAppend(headers,_response,"date");
    checkAndAppend(headers,_response,"keep-alive");
    checkAndAppend(headers,_response,"last-modified");
    checkAndAppend(headers,_response,"server");
    checkAndAppend(headers,_response,"content-location");
    if (!isCgiBody)
        _response.append("\r\n");
    _response.append(_body);
}

void response::ClearResponse()
{
    headers.clear();
    _body = "";
    _response = "";
    _location.clear();
    //...
}
