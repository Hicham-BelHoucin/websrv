/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseUtils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:18:08 by obeaj             #+#    #+#             */
/*   Updated: 2022/12/11 01:28:05 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSEUTILS_H
#define RESPONSEUTILS_H

#include "common.h"

typedef enum S_STATUSCODE
{
    OK = 200,
    CREATED = 201,
    ACCEPTED = 202,
    NO_CONTENT = 204,
    PARTIAL_CONTENT = 206,
    S_SUCCESS = OK | CREATED | ACCEPTED | NO_CONTENT | PARTIAL_CONTENT,
    MULTI_CHOICES = 300,
    MOVED_PERMANENTLY =  301,
    FOUND = 302,
    NOT_MODIFIED = 304,
    REDIRECT = MULTI_CHOICES | MOVED_PERMANENTLY | FOUND | NOT_MODIFIED,
    BAD_REQUEST = 400,
    UNAUTHORIZED = 401,
    FORBIDDEN = 403,
    NOT_FOUND =  404,
    NOT_ALLOWED = 405,
    NOT_ACCEPTABLE = 406,
    REQUEST_TIMEOUT = 408,
    LARGE_PAYLOAD = 413,
	UNSUPPORTEDMEDIATYPE = 415,
    S_ERROR = BAD_REQUEST | UNAUTHORIZED | FORBIDDEN | NOT_FOUND | NOT_ALLOWED | NOT_ACCEPTABLE | LARGE_PAYLOAD | UNSUPPORTEDMEDIATYPE,
    SERVER_ERROR = 500,
    NOT_IMPLEMENTED = 501,
    NON_SUPPORTED_HTTPVERSION = 505,
    S_SERVER_ERR = SERVER_ERROR | NOT_IMPLEMENTED | NON_SUPPORTED_HTTPVERSION

} CODES;

typedef enum S_PATHMODE {
    _DIR = 1 << 0,
    _FILE = 1 << 1,
    // READ = 1 << 2,
    // WRITE = 1 << 3,
    // EXEC = 1 << 4,
    _NONE_ = 1 << 2,
    D_READ = 1 << 3 ,
    D_WRITE = 1<< 4,
    D_EXEC = 1 << 5,
    D_RW = 1 << 6,
    D_RX = 1 << 7,
    D_WX = 1 << 8,
    D_ALL = 1 << 9,
    F_READ = 1 << 10,
    F_WRITE = 1 << 11,
    F_EXEC = 1 << 12,
    F_RW = 1 << 13,
    F_RX = 1 << 14,
    F_WX = 1 << 15,
    F_ALL = 1 << 17,
    F_RD = F_RX | F_RW | F_READ | F_ALL,
    D_RD = D_RX | D_RW | D_READ | D_ALL,
    ISDIR = _DIR | D_ALL | D_READ | D_WRITE | D_EXEC | D_RW | D_RX | D_WX,
    ISFILE = _FILE | F_EXEC | F_RW | F_RX | F_WX | F_READ | F_ALL | F_WRITE

} PATHMODE;

#endif