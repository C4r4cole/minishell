/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:49:39 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/06 17:33:30 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parser.h"

t_redir	*ft_redirnew(char *type, char *file)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	if (ft_strcmp(type, "<") == 0)
		new->type = REDIRECTION_IN, new->file = ft_strdup(file);
	else if (ft_strcmp(type, ">") == 0)
		new->type = REDIRECTION_OUT, new->file = ft_strdup(file);
	else if (ft_strcmp(type, "<<") == 0)
		new->type = HEREDOC, new->file = ft_strdup(file);
	else if (ft_strcmp(type, ">>") == 0)
		new->type = REDIRECTION_APPEND, new->file = ft_strdup(file);
	new->next = NULL;
	return (new);
}

int	ft_rediradd_back(t_redir **lst, t_redir *new)
{
	t_redir	*current_elem;

	if (!lst || !new)
		return (0);
	if (!*lst)
	{
		*lst = new;
		return (1);
	}
	current_elem = *lst;
	while (current_elem->next != NULL)
	{
		current_elem = current_elem->next;
	}
	current_elem->next = new;
	return (1);
}
