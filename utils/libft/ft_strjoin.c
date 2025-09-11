/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:47:50 by fmoulin           #+#    #+#             */
/*   Updated: 2025/05/02 17:11:13 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		total_len;
	int		i;
	int		j;
	char	*alloc;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	j = 0;
	alloc = malloc(sizeof(char) * (total_len + 1));
	if (!alloc)
		return (NULL);
	while (s1[i] != '\0')
	{
		alloc[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		alloc[i] = s2[j];
		i++;
		j++;
	}
	alloc[i] = '\0';
	return (alloc);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	s1[6] = "hello";
// 	char	s2[6] = "world";

// 	printf("%s\n", ft_strjoin(s1, s2));
// 	return (0);
// }