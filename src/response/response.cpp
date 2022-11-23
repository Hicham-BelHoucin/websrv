/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:46:12 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/23 21:57:36 by obeaj            ###   ########.fr       */
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
    PATHMODE mode;
    mode = checkPathMode(path);
	if (mode &  ISFILE)
	{
		file.open(path.c_str());
		file << body;
		file.close();
		_status_code = NO_CONTENT;
        return "";
	}
	else
	{
		file.open(_path.c_str(), std::ofstream::out | std::ofstream::trunc);
		if (file.is_open() == false)
		{
            _status_code = FORBIDDEN;
            return readFile(ERROR403);
        }
		file << body;
		file.close();
		_status_code = CREATED;
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
        // return locations.find("*.py")->second;
        Set::iterator it1 = locations.begin();
        while (it1 != locations.end())
        {
            if (isMatch(it1->first, path))
                return it1->second;
            it1++;
        }
    }
    return locations.find("/")->second;
}

String response::MethodNotAllowed(LocationMap location, String path, String body)
{
    _status_code = NOT_ALLOWED;
    return readFile(ERROR405);
}


String response::MethodGet(LocationMap location, String path, String body)
{
    bool isautoindex;
    PATHMODE mode;
    std::vector<String> indexes;
    DIR *Dir;
    struct dirent *DirEntry;
    VecIterator it;

    mode = checkPathMode(path);
    if (mode & ISDIR)
    {
        if (location.find("index") != location.end())
            indexes = location.find("index")->second;
        isautoindex = (location.find("autoindex") != location.end() && location.find("autoindex")->second.at(0) == "on");
        it = indexes.begin();
        if (mode & (D_RD))
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
                        _status_code = OK;
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
                _status_code = OK;
                // directory listing autoindex
                return dirListing(path);
            }
        }
        else
        {
            _status_code = FORBIDDEN;
            return readFile(ERROR403);
        }
    }
    else if (mode & ISFILE)
    {
        // if the file is a regular html file
        if (checkExtension(path) != "php" && checkExtension(path) != "py" && checkExtension(path) != "cgi")
        {
            if (mode & F_RD)
            {
                _status_code = OK;
                return (readFile(path));
            }
            else
            {
                _status_code = FORBIDDEN;
                return readFile(ERROR403);
            }
        }
        else
        {
            _status_code = OK;
            isCgiBody = true;
            cgi cgiHandler(path, __req);
            if (location.find("fastcgi_pass") != location.end())
                return(cgiHandler.executeCgi(path, location.find("fastcgi_pass")->second[0]));
        }
    }
    _status_code = NOT_FOUND;
    return (readFile(ERROR404));
}

String response::MethodPost(LocationMap location, String path, String body)
{
    bool isautoindex;
    PATHMODE mode;
    std::vector<String> indexes;
    DIR *Dir;
    struct dirent *DirEntry;
    VecIterator it;

    mode = checkPathMode(path);
    if (mode & ISDIR)
    {
        if (location.find("index") != location.end())
            indexes = location.find("index")->second;
        isautoindex = (location.find("autoindex") != location.end() && location.find("autoindex")->second.at(0) == "on");
        it = indexes.begin();
        if (mode & (D_RD))
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
                        _status_code = OK;
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
                _status_code = OK;
                // directory listing autoindex
                return dirListing(path);
            }
        }
        else
        {
            _status_code = FORBIDDEN;
            return readFile(ERROR403);
        }
    }
    else if (mode & ISFILE)
    {
        // if the file is a regular html file
        if (checkExtension(path) != "php" && checkExtension(path) != "py" && checkExtension(path) != "cgi")
        {
            if (mode & F_RD)
            {
                _status_code = OK;
                return (readFile(path));
            }
            else
            {
                _status_code = FORBIDDEN;
                return readFile(ERROR403);
            }
        }
        else
        {
            _status_code = OK;
            isCgiBody = true;
            cgi cgiHandler(path, __req);
            if (location.find("fastcgi_pass") != location.end())
                return(getCgiBody(cgiHandler.executeCgi(path, location.find("fastcgi_pass")->second[0])));
        }
    }
    _status_code = NOT_FOUND;
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
    PATHMODE mode;

    mode = checkPathMode(path);
    if (mode & ISFILE)
    {
        if (remove(_path.c_str()) == 0)
            _status_code = NO_CONTENT;
        else
        {
            _status_code = FORBIDDEN;
            return readFile(ERROR403);
        }
    }
    else
    {
        _status_code = NOT_FOUND;
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
    //    _status_code = LARGE_PAYLOAD;
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

response::response(request req, parsing conf): __req(req), __conf(conf), _status_code(req.getReqStatus())
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
    // if (headers.find("Content-Type") != headers.end())
    checkAndAppend(headers,_response,"Content-Type");
    // checkAndAppend(headers,_response,"last-modified");
    checkAndAppend(headers,_response,"Server");
    _response += "\r\n";
    _response.append(_body);
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

String      response::getCgiBody(String cgi_body)
{
    int found;
    int found1;
    String tmp;
    String __headerfield;
     
    if ((found = cgi_body.find("\r\n\r\n")) != String::npos)
        __headerfield = cgi_body.substr(0, found - 1);
    while ((found = __headerfield.find("\r\n")) != String::npos)
    {
        tmp = __headerfield.substr(found + 1);
        if ((found1 = tmp.find(":")) != String::npos)
        {}
    }
    return(cgi_body.substr(cgi_body.find_last_of("\r\n") + 1));
}

String response::dirListing(String dirname)
{
	DIR *dr;
	struct dirent *en;
	String body;
	dr = opendir(dirname.c_str()); //open all directory
    body += "<html>\n";
    body += "<head><title>Index of ";
    body += __req.getReqPath();
    body += "</title></head>\n";
	body += "<body>\n";
    body += "<h1>Index of ";
    body+= __req.getReqPath();
    body+= " : </h1>\n";
	body += "<hr>\n";
	body += "<pre>\n";
	if (dr)
	{
		while ((en = readdir (dr)) != NULL)
		{
			body += "<a href=\"";
			if(dirname[dirname.length() - 1] == '/')
				body += (__req.getReqPath() + en->d_name);
			else
			    body += (__req.getReqPath() + "/" + en->d_name);
			body += "\">";
			body += en->d_name;
			body += "</a>\n";
            body += "<br>\n";
		}
		body += "</pre>\n";
		body += "<hr>\n";
		body += "</body>\n";
		body += "</html>\n";
		closedir(dr); //close all directory
	}
	return(body);
}