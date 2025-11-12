/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:49:27 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/12 14:04:04 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/exec_header.h"
#include "minishell.h"

static int	main_init(t_shell **data, int argc, char **argv, char **envp)
{
	if (!*data)
		return (1);
	(void)argc;
	(void)*argv;
	init_shell(*data, envp);
	rl_bind_key('\t', rl_complete);
	using_history();
	return (0);
}

static void	handle_sigint_status(t_shell *data)
{
	if (g_sig == SIGINT)
	{
		data->exit_status = 130;
		g_sig = 0;
	}
}

static void	process_input(char *input, t_shell *data)
{
	t_cmd	*tokens;

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
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*data;
	char	*input;
	int		interactive;

	data = malloc(sizeof(t_shell));
	main_init(&data, argc, argv, envp);
	interactive = isatty(STDIN_FILENO);
	if (!isatty(STDOUT_FILENO))
		rl_outstream = stderr;
	while (1)
	{
		setup_signals_main();
		signal(SIGQUIT, handle_sigquit);
		if (interactive)
			input = readline("minishell> ");
		else
			input = readline(NULL);
		if (!input)
			break ;
		handle_sigint_status(data);
		process_input(input, data);
	}
	free_shell(data);
}
