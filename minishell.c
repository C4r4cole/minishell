/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:49:27 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/03 14:03:23 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/exec_header.h"
#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*tokens;
	t_shell	*data;
	char	*input;

	data = malloc(sizeof(t_shell));
	if (!data)
		return (1);
	(void)argc;
	(void)*argv;
	init_shell(data, envp);
	rl_bind_key('\t', rl_complete);
	using_history();
	while (1)
	{
		// Installe le handler SIGINT juste avant readline
		setup_signals_main();
		signal(SIGQUIT, handle_sigquit);
		input = readline("minishell> ");
		if (!input)
			break ;
		if (g_sig == SIGINT)
		{
			data->exit_status = 130;
			g_sig = 0;
		}
		add_history(input);
		tokens = parse_input(input, data);
		free(input);
		data->current_cmd_list = tokens;
		if (tokens)
		{
			if (tokens->next)
				execute_piped_cmds(tokens, data);
			else
				execute_cmds_list(tokens, data);
			free_cmd_list(tokens);
		}
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	free_shell(data);
}
