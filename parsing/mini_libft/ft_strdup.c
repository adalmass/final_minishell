/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:45:26 by aldalmas          #+#    #+#             */
/*   Updated: 2024/03/15 17:42:18 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

char	*ft_strdup(const char *s1)
{
	char	*d;

	d = malloc(ft_strlen(s1) + 1 * sizeof(char));
	if (!d)
		return (NULL);
	ft_memcpy(d, s1, ft_strlen(s1));
	d[ft_strlen(s1)] = '\0';
	return (d);
}
