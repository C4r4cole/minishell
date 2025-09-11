/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:44:22 by fmoulin           #+#    #+#             */
/*   Updated: 2025/05/13 14:02:06 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	*f(void *content)
// {
// 	int		i;
// 	char	*str;

// 	str = content;
// 	i = 0;
// 	while (str[i])
// 	{
// 		str[i] = str[i] + 13;
// 		i++;
// 	}
// 	return (str);
// }

// void	del(void *content)
// {
// 	free(content);
// }

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*resulted_list;
	t_list	*new_node;
	char	*str;

	resulted_list = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		str = f(lst->content);
		new_node = ft_lstnew(str);
		if (!str || !new_node)
		{
			if (!new_node)
				del(str);
			ft_lstclear(&resulted_list, del);
			return (NULL);
		}
		ft_lstadd_back(&resulted_list, new_node);
		lst = lst->next;
	}
	return (resulted_list);
}

// #include <stdio.h>

// int main(void)
// {
//     t_list *node1 = ft_lstnew(ft_strdup("nihao"));
// 	t_list *node2 = ft_lstnew(ft_strdup("ciao"));
// 	t_list *chain = NULL;
// 	t_list	*resulted_chain;

// 	ft_lstadd_back(&chain, node1);
// 	ft_lstadd_back(&chain, node2);
// 	resulted_chain = ft_lstmap(chain, f, del);
// 	printf("%s\n", (char *)resulted_chain->content);
//     return (0);
// }