/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmpp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 09:39:16 by bbousaad          #+#    #+#             */
/*   Updated: 2024/06/15 12:31:52 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmpp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	i = 0;
	s = (char *)s1;
	d = (char *)s2;
	while ((s[i] != '\0') && (d[i] != '\0') && (s[i] == d[i]) && (i < n))
		i++;
	if (((unsigned char)s[i] == (unsigned char)d[i]) || (i == n))
		return (0);
	return ((unsigned char)s[i] - (unsigned char)d[i]);
}
