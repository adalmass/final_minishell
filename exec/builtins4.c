/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:08:46 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/15 15:09:07 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset2(t_data *dta, int cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dta->read[cmd][j] && dta->read[cmd][j] != '=')
		j++;
	while (dta->cpy_envp[i])
	{
		if (ft_strncmpp(dta->cpy_envp[i], dta->read[cmd], j + 1) == 0)
		{
			if (!(i + 1 == len_cmd(dta->cpy_envp)))
				ft_update_export(dta, i);
			else
			{
				free (dta->cpy_envp[i]);
				dta->cpy_envp[i] = NULL;
			}
		}
		else if (ft_strncmpp(dta->cpy_envp[i], dta->read[cmd], j) == 0
			&& dta->cpy_envp[i][j] == '=')
			ft_unset3(dta, i);
		i++;
	}
}

void	ft_unset(t_data *dta, char **envp)
{
	int	cmd;

	(void) envp;
	cmd = 1;
	if ((ft_strncmpp(dta->read[0], "unset", 5) == 0) && dta->read[0][5] == 0)
	{
		if (dta->read[1] != NULL)
		{
			while (dta->read[cmd])
			{
				ft_unset2(dta, cmd);
				cmd++;
			}
		}
	}
}
