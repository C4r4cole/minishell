/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:57:56 by francoismou       #+#    #+#             */
/*   Updated: 2025/05/13 11:57:46 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

// #include <stdio.h>

// int main(void)
// {
//     t_list	*node1 = ft_lstnew(ft_strdup("nihao"));
// 	t_list	*node2 = ft_lstnew(ft_strdup("ciao"));
// 	t_list	*chain = NULL;
// 	t_list	*result;

// 	ft_lstadd_back(&chain, node1);
// 	ft_lstadd_back(&chain, node2);
// 	result = ft_lstlast(chain);
// 	printf("%s\n", (char *)result->content);
//     return (0);
// }