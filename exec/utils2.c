/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 09:07:27 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/15 01:07:49 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../parsing/parsing.h"

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

void	init_struct_dta(t_data *dta, t_parse *p)
{
	dta->read = ft_splitt(dta->exec[0], ' ');
	dta->space = ft_splitt(p->cmd_line, ' ');
	// if(dta->line)
	// 	free(dta->line);
}
