/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:49:27 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/30 15:44:50 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec/exec_header.h"
// void	print_env_list(t_env *env) 
// {
//     while (env)
//     {
// 		printf("%s=%s\n", env->key, env->value);
//         env = env->next;
//     }
// } TEST POUR VOIR SI LA LISTE ENV_LST EST BIEN REMPLIE

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_cmd	*tokens;
	t_env	*env_list;
	int		i;
	t_shell *data = malloc(sizeof(t_shell));
	if (!data)
	return 1;
	(void)argc;
	(void)*argv;
	init_shell(data,envp);
	// print_env_list(data->envp_lst); // PRINT DE LA LISTE
	print_banner();
	rl_bind_key('\t', rl_complete);
	using_history();
	env_list = stored_env(envp);
	
	// ============ //
	// === TEST === //
	// ============ //
	
	// while (env_list)
	// {
	// 	printf("KEY : %s, VALUE : %s\n", env_list->key, env_list->value);
	// 	env_list = env_list->next;
	// }
	
	// ============ //
	// === TEST === //
	// ============ //
	
	while (1)
	{
		char *input;

		input = readline("minishell> ");
		if (!input)
			break;
		add_history(input);
		// printf("cmd = %s\n", input);
		tokens = parse_input(input);
		execute_cmds_list(tokens, data);  // Ligne d'Ilyes a rajouter pour faire fonctionner le vrai but de minishell
	// 	i = 0;
	// 	while (tokens)
	// 	{
	// 		printf("%d token ->", i);
	// 		if (tokens->argv)
	// 		{
	// 			int j = 0;
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
	// 			printf("   redir -> type=%d, file=%s\n", redir->type, redir->file);
	// 			redir = redir->next;
	// 		}

	// 		tokens = tokens->next;
	// 		i++;
	// 	}
	// 	free(input);
	}	
	free_shell(data); // Ligne d'Ilyes a rajouter pour faire fonctionner le vrai but de minishell
	return (0);
}
}
