/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:50:00 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/11/12 10:38:51 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	prepare_redirection_file(int type, char **file, int *was_quoted)
{
	char	*tmp;

	*was_quoted = 0;
	if (!*file)
		return (0);
	if (type == HEREDOC && (*file)[0] == '\1')
	{
		*was_quoted = 1;
		tmp = ft_strdup((*file) + 1);
		free(*file);
		*file = tmp;
		if (!*file)
			return (0);
	}
	tmp = remove_quotes(*file);
	if (!tmp)
		return (free(*file), 0);
	*file = tmp;
	return (1);
}

int	finalize_and_push_redir(int type, char *file, int was_quoted,
		t_redir **redirection_list)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (free(file), 0);
	new_redir->type = type;
	new_redir->file = file;
	new_redir->heredoc_fd = -1;
	new_redir->next = NULL;
	if (type == HEREDOC && !was_quoted)
		new_redir->expand_heredoc = 1;
	else
		new_redir->expand_heredoc = 0;
	ft_rediradd_back(redirection_list, new_redir);
	return (1);
}

int	push_cmd_with_redirs(t_cmd **cmd_list, char **cmd_args,
		t_redir **redirection_list)
{
	t_cmd	*cmd;

	cmd = ft_cmdnew(cmd_args, *redirection_list);
	if (!cmd)
	{
		free_tab(cmd_args);
		free_redir_list(*redirection_list);
		*redirection_list = NULL;
		return (0);
	}
	ft_cmdadd_back(cmd_list, cmd);
	return (1);
}

void	cleanup_build_cmd_args(t_redir **redirection_list)
{
	free_redir_list(*redirection_list);
	*redirection_list = NULL;
}
