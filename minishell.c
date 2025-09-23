/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:49:27 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/22 17:47:17 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	t_cmd	*tokens;
	int		i;
	
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
		i = 0;
		while (tokens)
		{
			printf("%d token ->", i);
			if (tokens->argv)
			{
				int j = 0;
				while (tokens->argv[j])
				{
					printf(" %s", tokens->argv[j]);
					j++;
				}
			}
			printf("\n");

			// Parcourir les redirections liées à ce token
			t_redir *redir = tokens->redir;
			while (redir)
			{
				printf("   redir -> type=%d, file=%s\n", redir->type, redir->file);
				redir = redir->next;
			}

			tokens = tokens->next;
			i++;
		}
		free(input);
	}	
	return (0);
}