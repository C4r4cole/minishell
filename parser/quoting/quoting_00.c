/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_00.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:35:56 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/18 17:27:08 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	is_pipe(char c)
{
	return (c == PIPE);
}
int	is_slash(char c)
{
	return (c == SLASH);
}

int is_backslash(char c)
{
	return (c == BACKSLASH);
}

int	is_hyphen(char c)
{
	return (c == HYPHEN);
}

int	is_underscore(char c)
{
	return (c == UNDERSCORE);
}
