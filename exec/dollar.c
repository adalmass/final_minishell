/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:00:35 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/09 16:40:43 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*take_var(t_data *dta, int i)
{
	int		j;
	int		k;
	int		limit;
	char	*new_cmd;

	j = 1;
	k = 0;
	limit = ft_strlenn(dta->read[i]) - 1;
	new_cmd = malloc(sizeof(char) * (limit + 1));
	while (dta->read[i][j] && k <= limit)
	{
		new_cmd[k] = dta->read[i][j];
		k++;
		j++;
	}
	new_cmd[k] = '\0';
	return (new_cmd);
}

void	take_var3(t_data *dta)
{
	int	i;
	int	len;

	i = 1;
	len = 0;
	while (dta->read[len])
		len++;
	while (i < len)
	{
		take_var(dta, i);
		take_var2(dta, i);
		i++;
	}
}

void	take_var4(t_data *dta, int i, int j)
{
	while (dta->cpy_envp[i][j - 1] != '=')
		j++;
	while (dta->cpy_envp[i][j])
	{
		write(1, &dta->cpy_envp[i][j], 1);
		j++;
	}
	write(1, " ", 1);
}

void	take_var2(t_data *dta, int z)
{
	int		i;
	int		len;
	int		j;
	char	*var;

	i = 0;
	len = 0;
	j = 0;
	var = take_var(dta, z);
	while (var[len])
		len++;
	while (dta->cpy_envp[i])
	{
		if ((ft_strncmpp(dta->cpy_envp[i], var, len) == 0)
			&& dta->cpy_envp[i][len] == '=')
		{
			take_var4(dta, i, j);
		}
		i++;
	}
}
