/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:24:47 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/04 16:54:01 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int is_redirection_in(char c)
{
	return (c == REDIRECTION_IN);
}

int	is_redirection_out(char c)
{
	return (c == REDIRECTION_OUT);
}

int is_redirection(char *present_token)
{
	if (!present_token)
		return (0);
	return (ft_strcmp(present_token, "<") == 0
			|| ft_strcmp(present_token, ">") == 0
			|| ft_strcmp(present_token, "<<") == 0
			|| ft_strcmp(present_token, ">>") == 0);
}

int	get_redir_type(char *token)
{
	if (!ft_strcmp(token, "<"))
		return (REDIRECTION_IN);
	if (!ft_strcmp(token, ">"))
		return (REDIRECTION_OUT);
	if (!ft_strcmp(token, ">>"))
		return (REDIRECTION_APPEND);
	if (!ft_strcmp(token, "<<"))
		return (HEREDOC);
	return (-1);
}
