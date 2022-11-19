/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseUtils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:18:08 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/18 18:41:35 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSEUTILS_H
#define RESPONSEUTILS_H

#include "common.h"

namespace ResponseIUtils
{    
    typedef enum S_METHODS 
    {
        GET = 1 << 0,
        DELETE = 1 << 1,
        POST = 1 << 2,
        PUT =  1 << 3,
        UNKNOWN = 1 << 4,
        ALLOWED = GET | DELETE | POST | PUT
    } METHODS;

    typedef enum S_STATUSCODE
    {
        OK = 200,
        CREATED = 201,
        ACCEPTED = 202,
        NO_CONTENT = 204,
        PARTIAL_CONTENT = 206,
        MULTI_CHOICES = 300,
        MOVED_PERMANENTLY =  301,
        FOUND = 302,
        NOT_MODIFIED = 304,
        BAD_REQUEST = 400,
        UNAUTHORIZED = 401,
        FORBIDDEN = 403,
        NOT_FOUND =  404,
        NOT_ALLOWED = 405,
        NOT_ACCEPTABLE = 406,
        LARGE_PAYLOAD = 413,
        SERVER_ERROR = 500,
        NOT_IMPLEMENTED = 501,
        NON_SUPPORTED_HTTPVERSION = 505

    } CODES;
    
    typedef enum S_PATHMODE {
        DIR = 1 << 0,
        FILE = 1 << 1,
        // READ = 1 << 2,
        // WRITE = 1 << 3,
        // EXEC = 1 << 4,
        NONE = 1 << 5,
        D_READ = 1 << 6 ,
        D_WRITE = 1<< 7,
        D_EXEC = 1 << 8,
        D_RW = 1 << 9,
        D_RX = 1 << 10,
        D_WX = 1 << 11,
        D_ALL = 1 << 12,
        F_READ = 1 << 13,
        F_WRITE = 1 << 14,
        F_EXEC = 1 << 15,
        F_RW = 1 << 16,
        F_RX = 1 << 17,
        F_WX = 1 << 18,
        F_ALL = 1 << 19,
        ISDIR = DIR | D_ALL | D_READ | D_WRITE | D_EXEC | D_RW | D_RX | D_WX,
        ISFILE = FILE | F_EXEC | F_RW | F_RX | F_WX | F_ALL | F_ALL | F_WRITE
        
    } PATHMODE;
};

#endif