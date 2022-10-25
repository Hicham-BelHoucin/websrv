/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcuts.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:30:50 by obeaj             #+#    #+#             */
/*   Updated: 2022/10/25 15:11:06 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHORTCUTS_H
# define SHORTCUTS_H

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <cstring>
#include <fstream>
#include <sstream>
#define	WHITESPACES " \t\n\v\f\r"

typedef	std::vector <std::string >								Methods;
typedef std::pair<std::string, std::string>						Pair;
typedef	std::multimap<std::string , std::string>				Map;
typedef	std::map<std::string , Methods>							LMap;
typedef std::map<std::string, LMap>								Set;
typedef	std::map<std::string , std::string >::iterator			Iter;

#endif