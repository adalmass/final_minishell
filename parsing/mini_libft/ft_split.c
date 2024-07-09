/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:47:20 by aldalmas          #+#    #+#             */
/*   Updated: 2024/03/15 17:42:18 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

size_t	w_count(char const *s, char sep)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == sep)
			i++;
		if (s[i] && s[i] != sep)
			j++;
		while (s[i] && s[i] != sep)
			i++;
	}
	return (j);
}

char	*copy_word(char const *s, size_t j, size_t ij)
{
	size_t	x;
	char	*word;

	x = 0;
	word = malloc((j + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (j > 0)
	{
		word[x] = s[ij + x];
		x++;
		j--;
	}
	word[x] = '\0';
	return (word);
}

size_t	condition_before_copy(char const *s, char sep, size_t i, size_t j)
{
	while (s[i] && (s[i] != sep))
	{
		j++;
		i++;
	}
	return (j);
}

char	**search_word(char const *s, char **words, char sep, size_t i)
{
	size_t	y;
	size_t	j;

	j = 0;
	y = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == sep))
			i++;
		j = condition_before_copy((char *)s, sep, i, j);
		i = i + j;
		if (j > 0)
		{
			words[y] = copy_word((char *)s, j, i - j);
			y++;
		}
		j = 0;
	}
	words[y] = NULL;
	return (words);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**words;

	if (!s)
		return (NULL);
	i = 0;
	words = malloc((w_count((char *)s, c) + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	return (search_word((char *)s, words, c, i));
}
