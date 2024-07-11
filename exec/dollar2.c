/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:26:26 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/11 16:28:54 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_what2(t_data *dta, int j, int len, int i)
{
	printf("%d", g_exit_status);
	while (j < len)
	{
		printf("%c", dta->read[i][j]);
		j++;
	}
	printf(" ");
}

void	dollar_what(t_data *dta)
{
	int	i;
	int	j;
	int	len;
	int cmd;

	i = 1;
	j = 2;
	cmd = len_cmd(dta->read);
	while (i < cmd)
	{
		len = len_read(dta->read, i);
		if(len >= 2 && ft_strncmpp(dta->read[i], "$?", 2) == 0)
		{
			j = 2;
			if (dta->read[i][j] == 0)
				printf("%d ", g_exit_status);
			else if (dta->read[i][j] != 0)
				dollar_what2(dta, j, len, i);	
		}
		else
			printf("%s ", dta->read[i]);
		i++;
	}
}

int	search_dollar(t_data *dta, int i)
{
	if (dta->space[i][0] == '\'' && dta->space[i][1] == '$')
		return (1);
	return (0);
}
