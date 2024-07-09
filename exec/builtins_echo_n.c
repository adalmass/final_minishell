/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo_n.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:46:10 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/09 16:34:13 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_echo_n(t_data *dta)
{
	int	i;
	int	len;

	i = 1;
	len = 0;
	while (dta->read[1][len])
		len++;
	if (dta->read[1][0] == '-' && dta->read[1][1] == 'n')
	{
		if (dta->read[1][2] != 0)
		{
			while (dta->read[1][i] == 'n')
				i++;
		}
		if (dta->read[1][2] != 0)
		{
			if (i < len)
				return (1);
		}
	}
	return (0);
}

void	print_echo_n(t_data *dta, int i)
{
	int	len;

	len = 0;
	while (dta->read[len])
		len++;
	while (i <= len - 1)
	{
		printf("%s", dta->read[i]);
		if (i != len - 1)
			printf(" ");
		i++;
	}
}

int	check_echo_n2(t_data *dta, int i)
{
	int	len;
	int	j;

	len = 0;
	j = 1;
	while (dta->read[i][len])
		len++;
	if (dta->read[i][0] == '-' && dta->read[i][1] == 'n')
	{
		if (dta->read[i][2] != 0)
		{
			while (dta->read[i][j] == 'n')
				j++;
		}
		if (dta->read[i][2] != 0)
		{
			if (j < len)
				return (1);
		}
	}
	return (0);
}
