/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 09:07:27 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/11 16:55:18 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_cmd(char **tab)
{
	int	len;

	len = 0;
	if (tab)
	{
		while(tab[len])
			len++;
	}
	return (len);
}

int len_read(char **tab, int i)
{
	int len;

	len = 0;
	while (tab[i][len])
		len++;
	return (len);
}

int	doubletab_len(char **tab)
{
	int	y;

	y = 0;
	while (tab[y])
		y++;
	return (y);
}

void	init_struct_dta(t_data *dta)
{
	dta->read = ft_splitt(dta->exec[0], ' ');
	dta->space = ft_splitt(dta->line, ' ');
	if(dta->line)
		free(dta->line);
}
