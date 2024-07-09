/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 15:19:22 by bbousaad          #+#    #+#             */
/*   Updated: 2024/06/20 17:24:43 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

char	*ft_strjoinn(const char *s1, const char *s2)
{
	int		i;
	int		n;
	char	*str;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	n = 0;
	i = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[n])
	{
		str[i + n] = s2[n];
		n++;
	}
	str[i + n] = 0;
	return (str);
}
