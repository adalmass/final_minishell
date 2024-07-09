/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 08:28:27 by aldalmas          #+#    #+#             */
/*   Updated: 2024/07/09 14:01:47 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	find_space(t_parse *p)
{
	int	x;

	x = 0;
	while (p->splitted_built[0][x])
	{
		if (p->splitted_built[0][x] == ' ')
		{
			p->space_found = 1;
			parse_error(p, "Command not found");
			return (1);
		}
		x++;
	}
	return (0);
}

int	search_quote(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

char	*trim_remake(char *s, char c)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	end = 0;
	if (!s[i])
		return (NULL);
	while (s[i] == c)
		i++;
	start = i;
	i = ft_strlen(s) - 1;
	while (i > 0 && s[i] == c)
		i--;
	if (s[i] != c)
		end = i + 1;
	return (ft_substr((const char *)s, start, end - start));
}
