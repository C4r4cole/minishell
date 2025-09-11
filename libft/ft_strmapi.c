/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:07:43 by fmoulin           #+#    #+#             */
/*   Updated: 2025/05/05 16:59:30 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*tab;

	tab = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		tab[i] = f(i, s[i]);
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

// #include <stdio.h>

// char	test(unsigned int i, char c)
// {
// 	c = c + 1;
// 	printf("%d", i);
// 	return (c);
// }

// int	main(void)
// {
// 	char	s[6] = "hello";

// 	printf("%s\n", ft_strmapi(s, test));
// 	return (0);
// }