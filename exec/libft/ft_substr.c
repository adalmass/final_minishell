/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substrr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 15:18:17 by bbousaad          #+#    #+#             */
/*   Updated: 2024/06/15 12:38:17 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substrr(const char *s, unsigned int start, size_t len)
{
	char	*dup;
	size_t	lg;

	lg = 0;
	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlenn(s) || *s == '\0')
	{
		dup = malloc(1 * sizeof(char));
		*dup = 0;
		return (dup);
	}
	else if (len > (size_t)ft_strlenn(s))
		lg = ft_strlenn(s);
	else
		while (s[lg + start] && lg < len)
			lg++;
	dup = malloc(lg + 1);
	if (!dup)
		return (NULL);
	lg = -1;
	while (++lg < len && s[lg + start])
		dup[lg] = s[start + lg];
	dup[lg] = '\0';
	return (dup);
}
