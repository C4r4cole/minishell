/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:53:29 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/22 17:59:00 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redir	*ft_redirnew(char *type, char *file)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	if (ft_strncmp(type, "<", ft_strlen(type)) == 0)
	{
		new->type = REDIRECTION_IN;
		new->file = file;
	}
	if (ft_strncmp(type, ">", ft_strlen(type)) == 0)
	{
		new->type = REDIRECTION_OUT;
		new->file = file;
	}
	if (ft_strncmp(type, "<<", ft_strlen(type)) == 0)
	{
		new->type = HEREDOC;
		new->file = NULL;
	}
	if (ft_strncmp(type, ">>", ft_strlen(type)) == 0)
	{
		new->type = REDIRECTION_APPEND;
		new->file = NULL;
	}
	new->next = NULL;
	return (new);
}

t_cmd	*ft_cmdnew(char **argv, t_redir *redir)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->argv = argv;
	new->redir = redir;
	new->next = NULL;
	return (new);
}

int is_redirection(char *present_token)
{
	return (ft_strncmp(present_token, "<", ft_strlen(present_token)) == 0
			|| ft_strncmp(present_token, ">", ft_strlen(present_token)) == 0
			|| ft_strncmp(present_token, "<<", ft_strlen(present_token)) == 0
			|| ft_strncmp(present_token, ">>", ft_strlen(present_token)) == 0);
}

int	is_env(char *present_token)
{
	return (ft_strncmp(present_token, "$", ft_strlen(present_token)) == 0
			|| ft_strncmp(present_token, "~", ft_strlen(present_token)) == 0);
}

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*current_elem;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current_elem = *lst;
	while (current_elem->next != NULL)
	{
		current_elem = current_elem->next;
	}
	current_elem->next = new;
}

void	ft_rediradd_back(t_redir **lst, t_redir *new)
{
	t_redir	*current_elem;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current_elem = *lst;
	while (current_elem->next != NULL)
	{
		current_elem = current_elem->next;
	}
	current_elem->next = new;
}

// t_cmd	*parse_input(char *user_input, t_env *env);

t_cmd	*parse_input(char *user_input)
{
	char	**lexer;
	char	**tokens;
	char 	**before_pipe_tokens_tab;
	t_cmd	*cmd_list;
	t_cmd	*cmd;
	t_redir *redirection_list;
	t_redir	*redirection_sign;
	int		i;
	int		j;
	int		count;
	int		start;
	
	lexer = input_splitter(user_input);
	tokens = quotes_management(lexer);
	cmd_list = NULL;
	redirection_list = NULL;
	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (is_redirection(tokens[i]))
		{
			redirection_sign = ft_redirnew(tokens[i], tokens[i + 1]);
			ft_rediradd_back(&redirection_list, redirection_sign);
		}
		else if (is_env(tokens[i]))
		{
			ft_printf("TODO: code variables environnement");
			// TODO expand file
		}
		else if (!is_pipe(tokens[i][0]))
		{
			start = i;
			while (tokens[i] && ft_strncmp(tokens[i], "|", 1) != 0 && !is_redirection(tokens[i]))
				i++;
			count = i - start;
			before_pipe_tokens_tab = malloc(sizeof(char *) * (count + 1));
			if (!before_pipe_tokens_tab)
				return (NULL);
			while (j < count)
			{
				before_pipe_tokens_tab[j] = ft_strdup(tokens[start + j]);
				j++;
			}
			before_pipe_tokens_tab[j] = NULL;
			cmd = ft_cmdnew(before_pipe_tokens_tab, redirection_list);
			ft_cmdadd_back(&cmd_list, cmd);
			redirection_list = NULL;
		}
		i++;
	}
	return (cmd_list);
}
