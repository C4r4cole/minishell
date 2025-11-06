/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:53:29 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/06 20:08:41 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_empty_input(char *user_input)
{
	int	i;

	i = 0;
	if (!user_input)
		return (1);
	while (user_input[i] && user_input[i] == ' ')
		i++;
	return (!user_input[i]);
}

char	**get_tokens(char *user_input, t_shell *shell)
{
	char	**tokens;

	tokens = input_splitter(user_input, shell);
	if (!tokens || !tokens[0])
	{
		if (tokens)
			free(tokens);
		return (NULL);
	}
	return (tokens);
}

void	add_arg_to_cmd(t_cmd *cmd, char *arg)
{
	char	**new_argv;
	int		count;
	int		i;

	if (!cmd || !arg)
		return ;
	count = 0;
	if (cmd->argv)
		while (cmd->argv[count])
			count++;
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		return ;
	i = 0;
	while (i < count)
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[i++] = ft_strdup(arg);
	new_argv[i] = NULL;
	if (cmd->argv)
		free(cmd->argv);
	cmd->argv = new_argv;
}

void	parse_input_init(t_cmd **current_cmd, t_cmd **cmd_list,
		t_redir **redirection_list, int *i)
{
	*current_cmd = NULL;
	*cmd_list = NULL;
	*redirection_list = NULL;
	*i = 0;
}

t_cmd	*parse_input(char *user_input, t_shell *shell)
{
	char	**tokens;
	t_cmd	*cmd_list;
	t_redir	*redirection_list;
	int		i;
	t_cmd	*current_cmd;

	if (is_empty_input(user_input))
		return (NULL);
	tokens = get_tokens(user_input, shell);
	if (!tokens || check_syntax_errors(tokens))
		return (free_tokens(tokens), NULL);
	parse_input_init(&current_cmd, &cmd_list, &redirection_list, &i);
	while (tokens[i])
	{
		if (pipe_and_redir_management(tokens, &i, &current_cmd, &cmd_list))
			continue ;
		if (!current_cmd && !handle_command(tokens, &i, &cmd_list,
				&redirection_list))
			return (cleanup(cmd_list, redirection_list, tokens), NULL);
		if (!current_cmd)
			current_cmd = ft_lstlast(cmd_list);
		else
			add_arg_to_cmd(current_cmd, tokens[i++]);
	}
	return (free_redir_list(redirection_list), free_tokens(tokens), cmd_list);
}
