/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbel-hou <hbel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:46:12 by obeaj             #+#    #+#             */
/*   Updated: 2022/12/11 11:49:56 by hbel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/response.hpp"

response::response()
{
}

response::~response()
{
}

String response::writeContent(String path, String body)
{
    std::ofstream file;
    PATHMODE mode;

    mode = checkPathMode(path);
    if (mode & ISFILE)
    {
        file.open(path.c_str(), std::ofstream::out | std::ofstream::trunc | std::ofstream::binary);
        if (file.is_open() == false)
        {
            _status_code = FORBIDDEN;
            return getErrorPage(_serv, _status_code);
        }
        file << body;
        file.close();
        _status_code = NO_CONTENT;
        return "";
    }
    else
    {
        file.open(path.c_str(), std::ofstream::out | std::ofstream::binary);
        if (file.is_open() == false)
        {
            _status_code = FORBIDDEN;
            return getErrorPage(_serv, _status_code);
        }
        file << body;
        file.close();
        _status_code = CREATED;
        return "<h1>File Uploaded successfully !</h1>";
    }
    return "";
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
            if (isMatch(it1->first, path))
            {
                if ((it1->second).find("root") != it1->second.end())
                    _rootpath = (it1->second.find("root")->second)[0];
                return it1->second;
            }
            it1++;
        }
    }
    return locations.find("/")->second;
}

String response::MethodNotAllowed(LocationMap location, String path, String body)
{
	(void)location;
	(void)path;
	(void)body;
    _status_code = NOT_ALLOWED;
    return getErrorPage(_serv, _status_code);
}

String response::MethodGet(LocationMap location, String path, String body)
{
    bool isautoindex;
    PATHMODE mode;
    std::vector<String> indexes;
    DIR *Dir;
    struct dirent *DirEntry;
    VecIterator it;
    String newpath;

    mode = checkPathMode(path);
    if (mode & ISDIR)
    {
        if (location.find("index") != location.end())
            indexes = location.find("index")->second;
        else
        {
            indexes.push_back("index.html");
            indexes.push_back("index.htm");
            indexes.push_back("index.php");
        }
        isautoindex = (location.find("autoindex") != location.end() && location.find("autoindex")->second.at(0) == "on");
        it = indexes.begin();
        if (mode & D_RD)
        {
			if (access(path.c_str(), X_OK) == 0)
				Dir = opendir(path.c_str());
			else
			{
				_status_code = FORBIDDEN;
				return getErrorPage(_serv, _status_code);
			}
			if (!Dir)
			{
                std::cout << strerror(errno);
				_status_code = SERVER_ERROR;
				return getErrorPage(_serv, _status_code);
			}
            while ((DirEntry = readdir(Dir)))
            {
                // Search for index in directory
                if ((it = std::find(indexes.begin(), indexes.end(), DirEntry->d_name)) != indexes.end())
                {
                    // if index.html or index.htm found
                    if (checkExtension(*it) == "html" || checkExtension(*it) == "htm")
                    {
                        _status_code = OK;
                        if (path[path.length() - 1] != '/')
                            path += "/";
						closedir(Dir);
                        return (readFile(path + *it));
                    }
                    else
                    {
                        _location = locationMatch(_ServerLocations, *it);
                        newpath = _rootpath + _path;
                        if (newpath[newpath.length() - 1] != '/')
                            newpath += "/";
                        closedir(Dir);
                        return (MethodCheck(_location, _reqMethod, newpath + *it, body));
                    }
                }
            }
            closedir(Dir);
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
            return getErrorPage(_serv, _status_code);
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
                return getErrorPage(_serv, _status_code);
            }
        }
        else
        {
            _status_code = OK;
            isCgiBody = true;
            cgi cgiHandler(path, __req);
            if (location.find("fastcgi_pass") != location.end())
                return (getCgiBody(cgiHandler.executeCgi(path, location.find("fastcgi_pass")->second[0])));
            else
            {
                _status_code = SERVER_ERROR;
                return getErrorPage(_serv, _status_code);
            }
        }
    }
    _status_code = NOT_FOUND;
    return getErrorPage(_serv, _status_code);
}

String response::MethodPost(LocationMap location, String path, String body)
{
    bool isautoindex;
    PATHMODE mode;
    std::vector<String> indexes;
    DIR *Dir;
    struct dirent *DirEntry;
    VecIterator it;
    String newpath;

    mode = checkPathMode(path);

    if ((location.find("upload_enable") != location.end() && location.find("upload_enable")->second[0] == "on")
        && (!__req.getReqBody().empty() || !_upload.empty()))
    {
        return (handleUpload(location));
    }
    if (!(mode & ISDIR) && !(mode & ISFILE))
    {
        _status_code = NOT_FOUND;
        return (getErrorPage(_serv, _status_code));
    }
    else if (location.find("upload_enable") != location.end() && location.find("upload_enable")->second[0] == "off")
    {
        _status_code = FORBIDDEN;
        return getErrorPage(_serv, _status_code);
    }
    if (mode & ISDIR)
    {
        if (location.find("index") != location.end())
            indexes = location.find("index")->second;
		else
        {
            indexes.push_back("index.html");
            indexes.push_back("index.htm");
            indexes.push_back("index.php");
        }
        isautoindex = (location.find("autoindex") != location.end() && location.find("autoindex")->second.at(0) == "on");
        it = indexes.begin();
        if (mode & D_RD)
        {
			if (access(path.c_str(), X_OK) == 0)
				Dir = opendir(path.c_str());
			else
			{
				_status_code = FORBIDDEN;
				return getErrorPage(_serv, _status_code);
			}
            if (!Dir)
			{
				_status_code = SERVER_ERROR;
				return getErrorPage(_serv, _status_code);
			}
            while ((DirEntry = readdir(Dir)))
            {
                // Search for index in directory
                if ((it = std::find(indexes.begin(), indexes.end(), DirEntry->d_name)) != indexes.end())
                {
                    // if index.html or index.htm found
                    if (checkExtension(*it) == "html" || checkExtension(*it) == "htm")
                    {
                        if (path[path.length() -1] != '/')
                            path += "/";
                        _status_code = OK;
                        closedir(Dir);
                        return (readFile(path + *it));
                    }
                    else
                    {
                        _location = locationMatch(_ServerLocations, *it);
                        newpath = _rootpath + _path;
                        if (newpath[newpath.length() -1] != '/')
                            newpath += "/";
                        closedir(Dir);
                        return (MethodCheck(_location, _reqMethod, newpath + *it, body));
                    }
                }
            }
            if (isautoindex)
            {
                _status_code = OK;
                // directory listing autoindex
                return dirListing(path);
            }
            closedir(Dir);
        }
        else
        {
            _status_code = FORBIDDEN;
            return getErrorPage(_serv, _status_code);
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
                return getErrorPage(_serv, _status_code);
            }
        }
        else
        {
            _status_code = OK;
            isCgiBody = true;
            cgi cgiHandler(path, __req);
            if (location.find("fastcgi_pass") != location.end())
                return (getCgiBody(cgiHandler.executeCgi(path, location.find("fastcgi_pass")->second[0])));
            else
            {
                _status_code = SERVER_ERROR;
                return getErrorPage(_serv, _status_code);
            }
        }
    }
    _status_code = NOT_FOUND;
    return (getErrorPage(_serv, _status_code));
}

String response::MethodDelete(LocationMap location, String path, String body)
{
    (void)location;
	(void)body;
    PATHMODE mode;

    mode = checkPathMode(path);
    if (mode & ISFILE || mode & ISDIR)
    {
        if (remove(path.c_str()) == 0)
            _status_code = OK;
        else
        {
            _status_code = FORBIDDEN;
            return getErrorPage(_serv, _status_code);
        }
    }
    else
    {
        _status_code = NOT_FOUND;
        return getErrorPage(_serv, _status_code);
    }
    return "<h1> File deleted successfuly !</h1>";
}

typedef String (response::*MethodCall)(LocationMap location, String path, String body);

String response::MethodCheck(LocationMap location, String method, String path, String body)
{
    std::map<String, MethodCall> methodsMap;
    std::map<String, MethodCall>::iterator it;
    std::vector<String>::iterator i;
    LocationMap::iterator it1;

    methodsMap["GET"] = &response::MethodGet;
    methodsMap["POST"] = &response::MethodPost;
    methodsMap["DELETE"] = &response::MethodDelete;
    methodsMap["NotAllowed"] = &response::MethodNotAllowed;
    it = methodsMap.begin();
    switch (_status_code)
    {
		case BAD_REQUEST:
			return (getErrorPage(_serv, _status_code));
		case LARGE_PAYLOAD:
			return (getErrorPage(_serv, _status_code));
		case NOT_IMPLEMENTED:
			return (getErrorPage(_serv, _status_code));
		case REQUEST_TIMEOUT:
			return (getErrorPage(_serv, _status_code));
		case NON_SUPPORTED_HTTPVERSION:
			return (getErrorPage(_serv, _status_code));
		default:
			break;
    }
    if ((it1 = location.find("return")) != location.end())
    {
        _status_code = static_cast<CODES>(std::stoi(it1->second[0].substr(0,3)));
        headers.insert(std::make_pair("Location", it1->second[0].substr(4)));
        return "";
    }
	if (location.find("allow_methods") != location.end())
	{
		i = std::find(location.find("allow_methods")->second.begin(), location.find("allow_methods")->second.end(), method);
		if (i == location.find("allow_methods")->second.end())
			return ((this->*methodsMap.find("NotAllowed")->second)(location, path, body));
	}
	else
		return ((this->*methodsMap.find("NotAllowed")->second)(location, path, body));
    while (it != methodsMap.end())
    {
        if (method == it->first)
            return ((this->*(it->second))(location, path, body));
        it++;
    }
    return "";
}

response::response(request req, parsing conf)
	: __conf(conf)
	, __req(req)
	, _upload(req.getFilesBody())
{
    _status_code = static_cast<CODES>(__req.getReqStatus());
    statusPhrases = setStatusPhrases();
    // selecting a server
    _serv = selectServer(createServers(conf.getData(), conf), req.getReqHost(), req.getReqPort());
    _ServerLocations = _serv.getlocations();
    _reqMethod = req.getReqMethod();
    _rootpath = _serv.getRootPath();
    _path = req.getReqPath();
	std::string _return = _serv.getReturn();
	if (_return != "")
	{
		try
		{
			_status_code = static_cast<CODES>(std::stoi(_return.substr(0,3)));
			headers.insert(std::make_pair("Location", _return.substr(4)));
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	else
	{
		_location = locationMatch(_ServerLocations, _path);
		_body = MethodCheck(_location, _reqMethod, _rootpath + _path, req.getReqBody());
	}
	setHeaders(req);
	ResponseBuilder();
}

void response::setHeaders(request req)
{
    headers.insert(std::make_pair("Server", "Webserv IHO-0.1"));
    headers.insert(std::make_pair("Date", getDate()));
    if (req.getHeaderValue("Connection") != "")
        headers.insert(std::make_pair("Connection", req.getHeaderValue("Connection") != "NoValue" ? req.getHeaderValue("Connection") : "close"));
    headers.insert(std::make_pair("Content-Length", std::to_string(_body.length())));
    if (!isCgiBody)
        headers.insert(std::make_pair("Content-Type", getContentType(req.getReqPath(), _status_code)));
    if (getContentType(req.getReqPath(), _status_code) == "application/pdf")
        headers.insert(std::make_pair("Content-Disposition", "attachment; filename=" + req.getReqPath().substr(1)));
    headers.insert(std::make_pair("Content-Location", req.getReqPath()));
}

void response::checkAndAppend(Map &map, String &str, String key)
{
    Map::iterator it;

    it = map.begin();
    while (it != map.end())
    {
        if (it->first == key)
            str.append(it->first + ": " + it->second + "\r\n");
        it++;
    }
    return;
}

String response::handleUpload(LocationMap location)
{
    // read the upload_store from location
    String upload_store;
    String body = "";
    LocationMap::iterator it1;

    Map::iterator it = _upload.begin();
    if (location.find("upload_store") != location.end())
        upload_store = location.find("upload_store")->second[0];
    else
        upload_store = "";
    // loop over the map and call writeContent function
    if (it == _upload.end() && __req.getReqBody() != "")
    {
        _status_code = UNSUPPORTEDMEDIATYPE;
        return getErrorPage(_serv, _status_code);
    }
    while (it != _upload.end())
    {
        if (checkPathMode(_rootpath + upload_store) & ISDIR)
            body = writeContent(_rootpath + upload_store + "/" + it->first, it->second);
        else
        {
            if (mkdir((_rootpath + upload_store).c_str(), 0777) == -1)
                std::cerr << RED << "Error :  " << "Couldn't create th upload location !" << std::endl;
            body = writeContent(_rootpath + upload_store + "/" + it->first, it->second);
        }
        it++;
    }
    if (_status_code == FORBIDDEN)
        return (body);
    if ((it1 = location.find("return")) != location.end())
    {
        _status_code = static_cast<CODES>(std::stoi(it1->second[0].substr(0,3)));
        headers.insert(std::make_pair("Location", it1->second[0].substr(4)));
    }
    return body;
}

void response::ResponseBuilder()
{
    _response += "HTTP/1.1 " + std::to_string(_status_code) + " " + statusPhrases[_status_code] + "\r\n";
    checkAndAppend(headers, _response, "Connection");
    checkAndAppend(headers, _response, "Date");
    checkAndAppend(headers, _response, "Content-Length");
    checkAndAppend(headers, _response, "Content-Type");
    checkAndAppend(headers, _response, "Location");
    checkAndAppend(headers, _response, "Set-Cookie");
    checkAndAppend(headers, _response, "Server");
    _response += "\r\n";
	_response.append(_body);
    _response += "\r\n";
}

void response::ClearResponse()
{
    __req.ClearRequest();
    headers.clear();
    _body.clear();
    _response.clear();
    _location.clear();
    _rootpath.clear();
    _path.clear();
    statusPhrases.clear();
    _upload.clear();
    isCgiBody = 0;    // __conf.clearConf();
    _reqMethod.clear();
    _ServerLocations.clear();
    _status_code = OK;
    //...
}

String response::getResponse()
{
    return _response;
}

String response::getCgiBody(String cgi_body)
{
    size_t found;
    size_t found1;
    String key;
    String value;
    String __headerfield;
    String line;

    if ((found1 = cgi_body.find("\r\n\r\n")) != String::npos)
        __headerfield = cgi_body.substr(0, found1 - 1);
    if (found1 == String::npos)
    {
        if ((found1 = cgi_body.find("\n\n")) != String::npos)
            __headerfield = cgi_body.substr(0, found1 - 1);
    }

    std::stringstream str(__headerfield);
    while (std::getline(str, line, '\n'))
    {
        if ((found = line.find(":")) != String::npos)
        {
			key = line.substr(0, found);
            value = line.substr(found + 1);
            headers.insert(std::make_pair(stringtrim(key), stringtrim(value)));
        }
    }
    if (headers.find("Status") != headers.end())
    {
        _status_code = static_cast<CODES>(std::stoi(headers.find("Status")->second));
        if (_status_code & SERVER_ERROR)
            return getErrorPage(_serv, _status_code);
    }
    if (found1 != String::npos)
        return (cgi_body.substr(found1 + 1));
    return "";
}

String response::dirListing(String dirname)
{
    DIR *dr;
    struct dirent *en;
    String body;
	if (access(dirname.c_str(), X_OK) == 0)
    	dr = opendir(dirname.c_str());
	else
	{
		_status_code = FORBIDDEN;
		return getErrorPage(_serv, _status_code);
	}
    if (!dr)
    {
        std::cerr << RED << "Cannot open directory : " << dirname << std::endl;
        _status_code = SERVER_ERROR;
        return getErrorPage(_serv, _status_code);
    }
    body += "<html>\n";
    body += "<head><title>Index of ";
    body += __req.getReqPath();
    body += "</title></head>\n";
    body += "<body>\n";
    body += "<h1>Index of ";
    body += __req.getReqPath();
    body += " : </h1>\n";
    body += "<hr>\n";
    body += "<pre>\n";
    if (dr)
    {
        while ((en = readdir(dr)) != NULL)
        {
            body += "<a href=\"";
            if (dirname[dirname.length() - 1] == '/')
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
        closedir(dr);
    }
    return (body);
}