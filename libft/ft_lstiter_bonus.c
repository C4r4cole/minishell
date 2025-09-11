/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:45:18 by fmoulin           #+#    #+#             */
/*   Updated: 2025/05/13 11:49:31 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	f(void *content)
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
// }

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// #include <stdio.h>

// int	main(void)
// {
// 	t_list	*base;
// 	t_list	first;
// 	t_list	second;
// 	t_list	third;

// 	base = &first;
// 	first.content = ft_strdup("hello");
// 	first.next = &second;
// 	second.content = ft_strdup("world");
// 	second.next = &third;
// 	third.content = ft_strdup("!");
// 	third.next = NULL;

// 	ft_lstiter(base, f);
// 	while (base)
// 	{
// 		printf("%s\n", (char *)base->content);
// 		base = base->next;
// 	}
// 	return (0);
// }