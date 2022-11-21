/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:46:12 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/21 20:41:49 by obeaj            ###   ########.fr       */
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
            _filetype = "text/html";
            _status_code = ResponseIUtils::FORBIDDEN;
            return readFile(ERROR403);
        }
		file << body;
		file.close();
		_status_code = ResponseIUtils::CREATED;
        return "";
	}

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
        Set::iterator it1 = locations.begin();
        while (it1 != locations.end())
        {
            if (((it1->first).find("*") || (it1->first).find("?")) && isMatch(it1->first, path))
                return it1->second;
            it1++;
        }
    }
    return locations.find("/")->second;
}

String response::MethodNotAllowed(LocationMap location, String path, String body)
{
    _filetype = "text/html";
    _status_code = ResponseIUtils::NOT_ALLOWED;
    return readFile(ERROR405);
}


String response::MethodGet(LocationMap location, String path, String body)
{
    bool isautoindex;
    ResponseIUtils::PATHMODE mode;
    std::vector<String> indexes;
    DIR *Dir;
    struct dirent *DirEntry;
    VecIterator it;

    mode = checkPathMode(path);
    if (mode & ResponseIUtils::ISDIR)
    {
                std::cout << "heloooooooooooooooo\n";
        indexes = location.find("index")->second;
        isautoindex = (location.find("autoindex") != location.end() && location.find("autoindex")->second.at(0) == "on");
        it = indexes.begin();
        if (mode & (ResponseIUtils::D_RD))
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
                        _filetype = "text/html";
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
        if (checkExtension(path) != "php" || checkExtension(path) != "py" || checkExtension(path) != ".cgi")
        {
            if (mode & ResponseIUtils::F_RD)
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
        if (mode & (ResponseIUtils::D_RD))
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
        if (checkExtension(path) != "php" || checkExtension(path) != "py")
        {
            if (mode & ResponseIUtils::F_RD)
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
    // if ( location.find("max_body_size") !=location.end() && std::stoi(location.find("max_body_size")->second[0]) < body.size())
    // {
    //    _status_code = ResponseIUtils::LARGE_PAYLOAD;
    //    return(readFile(ERROR413));
    // }
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

response::response(request req, parsing conf): __req(req)
{
    statusPhrases = setStatusPhrases();
    // selecting a server
    // std::cout << req.getReqHost() << "\t" << req.getReqPort()<< "\n";
    _serv = selectServer(createServers(conf.getData(), conf), req.getReqHost(), req.getReqPort());
    // matching the path location
    _ServerLocations = _serv.getlocations();
    _reqMethod = req.getReqMethod();
    // _reqMethod = "GET";
    _rootpath = _serv.getRootPath();
    // _rootpath = "/home/obeaj";
    _path = req.getReqPath();
    // _path = "/index.html";
    _location = locationMatch(_ServerLocations, _path);
    // _location = _ServerLocations.find("/")->second;
    _body = MethodCheck(_location, _reqMethod, _rootpath + _path, req.getReqBody());
    // _body = "hell yeah";
    setHeaders(req);
    ResponseBuilder();
}

void response::setHeaders(request req)
{
    headers.insert(std::make_pair("Server", "Webserv IHO-0.1"));
    headers.insert(std::make_pair("Date", getDate()));
    // headers["Last-Modified"] = getLastModified();
    if (req.getHeaderValue("Connection") != "")
        headers.insert(std::make_pair("Connection", "Keep-Alive"));
    if (headers.find("Connection")->second == "Keep-Alive")
        headers.insert(std::make_pair("Keep-Alive", "timeout=5, max=1000"));
    headers.insert(std::make_pair("Content-Length", std::to_string(_body.length())));
    headers.insert(std::make_pair("Content-Type", getContentType(req.getReqPath(), _status_code)));
    headers.insert(std::make_pair("Content-Location", req.getReqPath()));
}

void    response::checkAndAppend(Map &map, String &str, String key)
{
    Map::iterator it;

    it  = map.find(key);
    if (it == map.end())
        return;
	if (map.find(key) != map.end())
		str.append(it->first + ": " + it->second + "\r\n");
}

void response::ResponseBuilder()
{
    _response += "HTTP/1.1 " + std::to_string(_status_code) + " " + statusPhrases[_status_code] + "\r\n";
    checkAndAppend(headers, _response, "Connection");
    checkAndAppend(headers,_response,"Keep-Alive");
    checkAndAppend(headers,_response,"Date");
    checkAndAppend(headers,_response,"Content-Location");
    checkAndAppend(headers,_response,"Content-Length");
    checkAndAppend(headers,_response,"Content-Type");
    // checkAndAppend(headers,_response,"last-modified");
    checkAndAppend(headers,_response,"Server");
    if (!isCgiBody)
        _response += "\r\n";
    _response.append(_body);
    _response += "\r\n";
}

void response::ClearResponse()
{   
    __req.ClearRequest();
    headers.clear();
    _body = "";
    _response = "";
    _location.clear();
    _rootpath = "";
    _path = "";
    statusPhrases.clear();
    isCgiBody = 0;
    
    //...
}

String      response::getResponse()
{
    return _response;
}