/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:59:05 by aldalmas          #+#    #+#             */
/*   Updated: 2024/03/29 09:57:56 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

char	*copy(char *d, char *s, int len)
{
	int	i;

	i = 0;
	while (s[i] && (i < len))
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

size_t	check_length(char const *s, int len)
{
	int	i;

	i = 0;
	while (s[i] && (i < len))
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, int len)
{
	unsigned int	len_s;
	int				valid_length;
	char			*str;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
	{
		str = malloc(1 * sizeof(char));
		str[0] = 0;
		return (str);
	}
	valid_length = check_length(s, len);
	str = malloc((valid_length + 1) * sizeof(char));
	if (!str)
		return (NULL);
	return (copy(str, (char *)s + start, valid_length));
}
