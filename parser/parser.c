/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:53:29 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/29 17:44:49 by fmoulin          ###   ########.fr       */
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
		new->type = REDIRECTION_IN, new->file = file;
	if (ft_strncmp(type, ">", ft_strlen(type)) == 0)
		new->type = REDIRECTION_OUT, new->file = file;
	if (ft_strncmp(type, "<<", ft_strlen(type)) == 0)
		new->type = HEREDOC, new->file = NULL;
	if (ft_strncmp(type, ">>", ft_strlen(type)) == 0)
		new->type = REDIRECTION_APPEND, new->file = NULL;
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
	if (!present_token)
		return (0);
	return (ft_strncmp(present_token, "<", ft_strlen(present_token)) == 0
			|| ft_strncmp(present_token, ">", ft_strlen(present_token)) == 0
			|| ft_strncmp(present_token, "<<", ft_strlen(present_token)) == 0
			|| ft_strncmp(present_token, ">>", ft_strlen(present_token)) == 0);
}

int	is_env(char *present_token)
{
	if (!present_token)
		return (0);
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


int	handle_redirection(char **tokens, int *i, t_redir **redirection_list)
{
	t_redir	*redirection_sign;
	
    if (tokens[*i + 1])
    {
		redirection_sign = ft_redirnew(tokens[*i], tokens[*i + 1]);
        ft_rediradd_back(redirection_list, redirection_sign);
        *i += 2;
        return (1);
    }
    return (0);
}

char	**create_cmd_args(char **tokens, int start, int count)
{
	char	**before_pipe_tokens_tab;
    int		j;
	
    before_pipe_tokens_tab = malloc(sizeof(char *) * (count + 1));
    if (!before_pipe_tokens_tab)
	return (NULL);
    j = 0;
    while (j < count)
    {
		before_pipe_tokens_tab[j] = ft_strdup(tokens[start + j]);
        if (!before_pipe_tokens_tab[j])
        {
			while (j > 0)
			free(before_pipe_tokens_tab[--j]);
            free(before_pipe_tokens_tab);
            return (NULL);
        }
        j++;
    }
    before_pipe_tokens_tab[j] = NULL;
    return (before_pipe_tokens_tab);
}

int	handle_command(char **tokens, int *i, t_cmd **cmd_list, t_redir **redirection_list)
{
	char	**cmd_args;
    t_cmd	*cmd;
    int		start;
    int		count;
	
    start = *i;
    while (tokens[*i] && tokens[*i][0] && !is_pipe(tokens[*i][0]) && !is_redirection(tokens[*i]))
	(*i)++;
    count = *i - start;
    if (count <= 0)
	return (1);
    cmd_args = create_cmd_args(tokens, start, count);
    if (!cmd_args)
	return (0);
    cmd = ft_cmdnew(cmd_args, *redirection_list);
    ft_cmdadd_back(cmd_list, cmd);
    *redirection_list = NULL;
    return (1);
}

t_cmd	*parse_input(char *user_input, t_env *env)
{
	char	**tokens;
    t_cmd	*cmd_list;
    t_redir	*redirection_list;
    int		i;

    if (!user_input)
        return (NULL);
    tokens = quotes_management(input_splitter(user_input), env);
    if (!tokens)
        return (NULL);
    cmd_list = NULL;
    redirection_list = NULL;
    i = 0;
    while (tokens[i])
    {
        if (!tokens[i])
            break;
        if (is_redirection(tokens[i]))
        {
            if (!handle_redirection(tokens, &i, &redirection_list))
                break;
        }
        else if (is_env(tokens[i]))
        {
            ft_printf("TODO: code variables environnement");
            i++;
        }
        else if (tokens[i][0] && !is_pipe(tokens[i][0]))
        {
            if (!handle_command(tokens, &i, &cmd_list, &redirection_list))
                return (NULL);
        }
        else
            i++;
    }
    return (cmd_list);
}
