/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 08:58:23 by aldalmas          #+#    #+#             */
/*   Updated: 2024/06/21 09:12:27 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

size_t	end_idx_set(char const *s1, char const *set)
{
	size_t	i;

	i = ft_strlen(s1);
	while (i > 0)
	{
		if (ft_strchr(set, s1[i]))
			i--;
		else
			return (i + 1);
	}
	return (0);
}

size_t	start_idx_set(char const *s1, char const *set, size_t end_idx)
{
	size_t	i;

	i = 0;
	while (i < end_idx)
	{
		if (ft_strchr(set, s1[i]))
			i++;
		else
			return (i);
	}
	return (0);
}

char	*ft_strtrimm(char const *s1, char const *set)
{
	size_t	j;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	j = end_idx_set(s1, set);
	i = start_idx_set(s1, set, j);
	return (ft_substr(s1, i, j - i));
}
