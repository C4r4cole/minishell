/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:49:39 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/06 20:08:26 by fmoulin          ###   ########.fr       */
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

void	cleanup(t_cmd *cmd_list, t_redir *redirection_list,
		char **tokens)
{
	free_cmd_list(cmd_list);
	free_redir_list(redirection_list);
	free_tokens(tokens);
}

int	pipe_and_redir_management(char **tokens, int *i, t_cmd **current_cmd,
		t_cmd **cmd_list)
{
	if (handle_pipe_case(tokens, i, current_cmd, cmd_list))
		return (1);
	if (handle_redir_case(tokens, i, current_cmd, cmd_list))
		return (1);
	return (0);
}
