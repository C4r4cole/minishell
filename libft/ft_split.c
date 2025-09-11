/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:37:10 by fmoulin           #+#    #+#             */
/*   Updated: 2025/05/07 10:20:03 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_str(char const *str, char c)
{
	int	i;
	int	count;
	int	is_c;

	i = 0;
	count = 0;
	is_c = 1;
	while (str[i])
	{
		if (str[i] == c)
			is_c = 1;
		else if (str[i] != 0)
		{
			if (is_c == 1)
				count++;
			is_c = 0;
		}
		i++;
	}
	return (count);
}

static void	*free_split(char **tab, size_t i)
{
	while (i > 0)
	{
		i--;
		free(tab[i]);
	}
	free(tab);
	return (0);
}

static char	**malloc_substr(char const *s, char **tab, char c, size_t j)
{
	size_t	i;
	size_t	start;
	size_t	len;

	i = 0;
	while (s[i])
	{
		len = 0;
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c && ++i)
			len++;
		if (len > 0)
		{
			tab[j++] = ft_substr(s, start, len);
			if (!tab[j - 1])
				return (free_split(tab, j));
		}
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	char	**tab;

	count = ft_count_str(s, c);
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	tab = malloc_substr(s, tab, c, 0);
	return (tab);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char const s[33] = "King Gizzard & the Lizard Wizard";
// 	char		c;
// 	char	**tab;
// 	int	i;

// 	c = ' ';
// 	i = 0;
// 	tab = ft_split(s, c);
// 	while (tab[i] != NULL)
// 	{
// 		printf("%s\n", tab[i]);
// 		free(tab[i]);
// 		i++;
// 	}
// 	free(tab);
// 	return (0);
// }
