/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:28:36 by fmoulin           #+#    #+#             */
/*   Updated: 2025/05/05 18:02:56 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

// #include <stdio.h>

// void	test(unsigned int i, char *s)
// {
// 	s = "olleh";
// 	i = 12;
// 	printf("%d\n", i);
// 	printf("%s\n", s);
// }

// int	main(void)
// {
// 	char	s[6] = "hello";

// 	ft_striteri(s, test);
// 	return (0);
// }