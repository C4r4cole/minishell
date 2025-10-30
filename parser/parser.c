/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:53:29 by fmoulin           #+#    #+#             */
/*   Updated: 2025/10/30 17:58:50 by fmoulin          ###   ########.fr       */
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

void	cleanup_parse_error(t_cmd *cmd_list, t_redir *redirection_list, char **tokens)
{
	free_cmd_list(cmd_list);
	free_redir_list(redirection_list);
	free_tokens(tokens);
}

void	add_arg_to_cmd(t_cmd *cmd, char *arg)
{
	char	**new_argv;
	int		count;
	int		i;

	if (!cmd || !arg)
		return;

	/* 1️⃣ Compter combien d'arguments on a déjà */
	count = 0;
	if (cmd->argv)
	{
		while (cmd->argv[count])
			count++;
	}

	/* 2️⃣ Allouer un nouveau tableau de taille +2 (nouvel arg + NULL final) */
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		return;

	/* 3️⃣ Copier les anciens arguments */
	i = 0;
	while (i < count)
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}

	/* 4️⃣ Ajouter le nouvel argument */
	new_argv[i++] = ft_strdup(arg);
	new_argv[i] = NULL;

	/* 5️⃣ Libérer l'ancien tableau (mais pas les chaînes copiées) */
	if (cmd->argv)
		free(cmd->argv);

	cmd->argv = new_argv;
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
	if (!tokens)
        return (NULL);
	if (check_syntax_errors(tokens))
	{
		free_tokens(tokens);
		return (NULL);
	}
	current_cmd = NULL;
    cmd_list = NULL;
    redirection_list = NULL;
    i = 0;
	while (tokens[i])
	{
		// 1️⃣ Si on rencontre un pipe → nouvelle commande
		if (is_pipe(tokens[i][0]))
		{
			current_cmd = NULL;
			i++;
			continue;
		}
		if (is_redirection(tokens[i]))
		{
			// 🔸 Cas où il n’y a encore aucune commande en cours
			if (!current_cmd)
			{
				// Cas comme "< infile cat" → on crée un t_cmd vide juste pour stocker la redirection
				current_cmd = ft_cmdnew(NULL, NULL);
				if (!current_cmd)
					return (cleanup_parse_error(cmd_list, redirection_list, tokens), NULL);
				ft_cmdadd_back(&cmd_list, current_cmd);
			}

			// 🔸 Gérer la redirection normalement
			handle_redirection(tokens, &i, &current_cmd->redir);
			continue;
		}

		// 3️⃣ Sinon, c’est un argument ou un mot de commande normal
		if (!current_cmd)
		{
			if (!handle_command(tokens, &i, &cmd_list, &redirection_list))
				return (cleanup_parse_error(cmd_list, redirection_list, tokens), NULL);
			current_cmd = ft_lstlast(cmd_list);
			continue;
		}

		// 🔹 Ajoute l’argument directement à la commande courante
		add_arg_to_cmd(current_cmd, tokens[i]);
		i++;
	}
	if (redirection_list)
		free_redir_list(redirection_list);
	free_tokens(tokens);
    return (cmd_list);
}
