/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:49:27 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/18 12:50:46 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char	**tokens;
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
		tokens = test_parser(input);
		i = 0;
		while (tokens[i])
		{
			printf("%d token -> %s\n", i, tokens[i]);
			i++;
		}
		free(input);
	}	
	return (0);
}