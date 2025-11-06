/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:49:39 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/06 17:33:26 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parser.h"

int	handle_pipe_case(char **tokens, int *i, t_cmd **current_cmd,
		t_cmd **cmd_list)
{
	if (is_pipe(tokens[*i][0]))
	{
		(*i)++;
		*current_cmd = ft_cmdnew(NULL, NULL);
		if (!*current_cmd)
			return (0);
		ft_cmdadd_back(cmd_list, *current_cmd);
		return (1);
	}
	return (0);
}

int	handle_redir_case(char **tokens, int *i, t_cmd **current_cmd, t_cmd **list)
{
	if (!is_redirection(tokens[*i]))
		return (0);
	if (!*current_cmd)
	{
		*current_cmd = ft_cmdnew(NULL, NULL);
		if (!*current_cmd)
			return (0);
		ft_cmdadd_back(list, *current_cmd);
	}
	if (!handle_redirection(tokens, i, &(*current_cmd)->redir))
		return (0);
	return (1);
}
