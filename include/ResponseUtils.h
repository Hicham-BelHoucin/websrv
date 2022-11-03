/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseUtils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:18:08 by obeaj             #+#    #+#             */
/*   Updated: 2022/11/01 03:59:32 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSEUTILS_H
#define RESPONSEUTILS_H

namespace ResponseIUtils
{
    typedef enum S_METHODS 
    {
        GET = 1 << 0,
        DELETE = 1 << 1,
        POST = 1 << 2,
        UNKNOWN = 1 << 3,
        ALLOWED = GET | DELETE | POST
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
        SERVER_ERROR = 500,
        NOT_IMPLEMENTED = 501,
        NON_SUPPORTED_HTTPVERSION = 505

    } CODES;
};

#endif