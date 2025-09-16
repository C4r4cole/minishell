/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:49:27 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/16 12:36:17 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char	**input_splitted;
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
		input_splitted = input_splitter(input);
		i = 0;
		while (input_splitted[i])
		{
			printf("%d lexer -> %s\n", i, input_splitted[i]);
			i++;
		}
		free(input);
	}	
	return (0);
}