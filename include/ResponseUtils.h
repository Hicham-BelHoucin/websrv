/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseUtils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:18:08 by obeaj             #+#    #+#             */
/*   Updated: 2022/10/25 14:37:39 by obeaj            ###   ########.fr       */
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
};

#endif