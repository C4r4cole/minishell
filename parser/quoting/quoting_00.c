/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_00.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:35:56 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/04 14:11:50 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	is_pipe(char c)
{
	return (c == PIPE);
}

int is_redirection_in(char c)
{
	return (c == REDIRECTION_IN);
}

int	is_redirection_out(char c)
{
	return (c == REDIRECTION_OUT);
}

int	is_space(char c)
{
	return (c == SPACE);
}

int is_tab(char c)
{
	return (c == TAB);
}
