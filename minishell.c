/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:49:27 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/23 15:22:17 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec/exec_header.h"

int main(void)
{
	t_cmd	*tokens;
	// int		i;
	t_shell *data = malloc(sizeof(t_shell));
	if (!data)
		return 1;

	init_shell(data);
	print_banner();
	rl_bind_key('\t', rl_complete);
	using_history();
	while (1)
	{
		char *input;

		input = readline("minishell> ");
		if (!input)
			break;
		add_history(input);
		// printf("cmd = %s\n", input);
		tokens = parse_input(input);
		execute_cmds_list(tokens, data);
		// i = 0;
		// while (tokens)
		// {
		// 	printf("%d token ->", i);
		// 	if (tokens->argv)
		// 	{
		// 		int j = 0;
		// 		while (tokens->argv[j])
		// 		{
		// 			printf(" %s", tokens->argv[j]);
		// 			j++;
		// 		}
		// 	}
		// 	printf("\n");

		// 	// Parcourir les redirections liées à ce token
		// 	t_redir *redir = tokens->redir;
		// 	while (redir)
		// 	{
		// 		printf("   redir -> type=%d, file=%s\n", redir->type, redir->file);
		// 		redir = redir->next;
		// 	}

		// 	tokens = tokens->next;
		// 	i++;
		// }
		
		free(input);
	}	
	free_shell(data);
	return (0);
}