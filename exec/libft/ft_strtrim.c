/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 15:20:28 by bbousaad          #+#    #+#             */
/*   Updated: 2024/06/15 12:45:13 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size;
	char	*cpy;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchrr(set, *s1))
		s1++;
	size = ft_strlenn(s1);
	while (size && ft_strchrr(set, s1[size]))
		size--;
	cpy = ft_substrr((char *) s1, 0, size + 1);
	return (cpy);
}
