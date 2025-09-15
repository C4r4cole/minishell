/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:49:27 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/15 12:08:49 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	rl_bind_key('\t', rl_complete);
	using_history();
	while (1)
	{
		char *input;

		input = readline("minishell> ");
		if (!input)
			break;
		add_history(input);
		printf("hello world\n");
		free(input);
	}	
	return (0);
}