/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:00:32 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/14 21:29:25 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_data *dta)
{
	int	i;

	i = 0;
	if ((ft_strncmpp(dta->read[0], "export", 6) == 0) && dta->read[0][6] == 0)
	{
		if (dta->read[1] == NULL)
		{
			while (dta->cpy_envp[i])
			{
				printf("%s", "declare -x ");
				printf("%s\n", dta->cpy_envp[i]);
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
	dta->cpy_cpy = malloc((i + 2) * sizeof(char *));
	i = -1;
	while (dta->cpy_envp[++i])
		dta->cpy_cpy[i] = ft_strdupp(dta->cpy_envp[i]);
	dta->cpy_cpy[i] = ft_strdupp(dta->read[y]);
	dta->cpy_cpy[i + 1] = NULL;
	i = 0;
	while (dta->cpy_cpy[i])
		i++;
	free_double_tab(dta->cpy_envp);
	dta->cpy_envp = malloc((i + 1) * sizeof(char *));
	i = -1;
	while (dta->cpy_cpy[++i])
		dta->cpy_envp[i] = ft_strdupp(dta->cpy_cpy[i]);
	dta->cpy_envp[i] = NULL;
	free_double_tab(dta->cpy_cpy);
}

void	ft_update_export(t_data *dta, int i)
{
	int		j;
	int		y;
	char	**update_envp;

	j = 0;
	y = 0;
	update_envp = malloc(sizeof(char *) * len_cmd(dta->cpy_envp));
	while (dta->cpy_envp[j])
	{
		if (j != i)
		{
			update_envp[y] = ft_strdupp(dta->cpy_envp[j]);
			y++;
		}
		j++;
	}
	update_envp[y] = NULL;
	free_double_tab(dta->cpy_envp);
	dta->cpy_envp = update_envp;
}

void	ft_unset3(t_data *dta, int i)
{
	if (!(i + 1 == len_cmd(dta->cpy_envp)))
		ft_update_export(dta, i);
	else
	{
		free (dta->cpy_envp[i]);
		dta->cpy_envp[i] = NULL;
	}
}

void 	ft_unset2(t_data *dta, int cmd)
{
	int i;
	int j;

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
	int cmd;
	(void) envp;

	cmd = 1;
	if ((ft_strncmpp(dta->read[0], "unset", 5) == 0) && dta->read[0][5] == 0)
	{
		if (dta->read[1] != NULL)
		{
			while(dta->read[cmd])
			{
				ft_unset2(dta, cmd);
				cmd++;
			}
		}
	}
}
