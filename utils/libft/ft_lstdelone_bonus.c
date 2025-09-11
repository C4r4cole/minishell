/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:37:43 by francoismou       #+#    #+#             */
/*   Updated: 2025/05/13 12:22:44 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	del(void *content)
// {
// 	free(content);
// }

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

// #include <stdio.h>

// int main(void)
// {
// 	t_list	*new;

// 	new = ft_lstnew(ft_strdup("ciao"));
// 	printf("%s\n", (char *)new->content);
// 	ft_lstdelone(new, del);
// 	return (0);
// }