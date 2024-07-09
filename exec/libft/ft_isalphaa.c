/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalphaa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:34:41 by bbousaad          #+#    #+#             */
/*   Updated: 2024/06/30 16:34:11 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_isalphaa(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (((str[i] >= 65) && (str[i] <= 90)) || ((str[i] >= 97) && (str[i] <= 122)))
		{
			return (1);
			break ;
		}
		i++;
	}
	return (0);
}