/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:49:27 by fmoulin           #+#    #+#             */
/*   Updated: 2025/10/30 12:17:28 by ilsedjal         ###   ########.fr       */
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
		if (tokens)
		{
			if (tokens->next)
				execute_piped_cmds(tokens, data);
			else
				execute_cmds_list(tokens, data);
		}
		// Ligne d'Ilyes a rajouter pour faire fonctionner le vrai but de minishell
		// 	i = 1;
		// 	while (tokens)
		// 	{
		// 		printf("%d cmd ->", i);
		// 		if (tokens->argv)
		// 		{
		// 			j = 0;
		// 			while (tokens->argv[j])
		// 			{
		// 				printf(" %s", tokens->argv[j]);
		// 				j++;
		// 			}
		// 		}
		// 		printf("\n");
		// 		// Parcourir les redirections liées à ce token
		// 		t_redir *redir = tokens->redir;
		// 		while (redir)
		// 		{
		// 			printf("   redir -> type=%d, file=%s\n",
		// redir->type,redir->file);
		// 			redir = redir->next;
		// 		}
		// 		tokens = tokens->next;
		// 		i++;
		// 	}
		// 	free(input);
		// }
		// 	// Ligne d'Ilyes a rajouter pour faire fonctionner le vrai but de minishell
		// 	return (0);
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	free_shell(data);
}
