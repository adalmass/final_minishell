/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:00:32 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/11 19:20:45 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_data *dta, char **envp)
{
	int	i;

	i = 0;
	if ((ft_strncmpp(dta->read[0], "export", 6) == 0) && dta->read[0][6] == 0)
	{
		if (dta->read[1] == NULL)
		{
			while (envp[i])
			{
				printf("%s", "declare -x ");
				printf("%s\n", envp[i]);
				i++;
			}
		}
		else if (doubletab_len(dta->read) > 1)
			ft_export2(dta);
	}
}

void	ft_export2(t_data *dta)
{
	int	y;

	y = 1;
	while (dta->read[y])
	{
		if (check_export(dta, y) == 0)
			ft_export3(dta, y);
		y++;
	}
}

void	ft_export3(t_data *dta, int y)
{
	int	i;

	i = 0;
	while (dta->cpy_envp[i])
		i++;
	dta->cpy_cpy = ft_calloc(i + 2, sizeof(char *));
	i = -1;
	while (dta->cpy_envp[++i])
		dta->cpy_cpy[i] = ft_strdupp(dta->cpy_envp[i]);
	dta->cpy_cpy[i] = ft_strdupp(dta->read[y]);
	i = 0;
	while (dta->cpy_cpy[i])
		i++;
	dta->cpy_envp = ft_calloc(i + 2, sizeof(char *));
	i = -1;
	while (dta->cpy_cpy[++i])
		dta->cpy_envp[i] = ft_strdupp(dta->cpy_cpy[i]);
}

void	ft_unset(t_data *dta, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if ((ft_strncmpp(dta->read[0], "unset", 5) == 0) && dta->read[0][5] == 0)
	{
		if (dta->read[1] != NULL && dta->read[2] == NULL)
		{
			while (dta->read[1][j])
				j++;
			while (envp[i])
			{
				if (ft_strncmpp(dta->cpy_envp[i], dta->read[1], j) == 0
					&& dta->cpy_envp[i][j] == 0)
					dta->cpy_envp[i] = NULL;
				i++;
			}
		}
	}
}
