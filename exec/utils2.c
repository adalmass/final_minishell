/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 09:07:27 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/08 16:24:07 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
}
