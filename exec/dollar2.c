/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:26:26 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/15 00:15:49 by aldalmas         ###   ########.fr       */
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
			{
				if(dta->exit == 127)
					printf("%d ", dta->exit);
				else
					printf("%d ", g_exit_status);
			}
			
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
