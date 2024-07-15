/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:00:35 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/15 15:11:26 by bbousaad         ###   ########.fr       */
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
	limit = len_read(dta->read, i);
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
	len = len_cmd(dta->read);
	while (i < len)
	{
		take_var(dta, i);
		take_var2(dta, i);
		i++;
	}
}

void	take_var4(t_data *dta, int i, int j)
{
	int	len;

	len = len_read(dta->cpy_envp, i);
	while (dta->cpy_envp[i][j] != '=')
		j++;
	j++;
	while (dta->cpy_envp[i][j] && j < len)
	{
		printf("%c", dta->cpy_envp[i][j]);
		j++;
	}
	printf(" ");
}

void	take_var2(t_data *dta, int z)
{
	int		i;
	int		len;
	int		j;
	char	*var;
	int		idx;

	i = 0;
	len = 0;
	j = 0;
	idx = 0;
	var = take_var(dta, z);
	while (var[len])
		len++;
	while (dta->cpy_envp[i])
	{
		idx = len_read(dta->cpy_envp, i);
		if ((idx >= len && ft_strncmpp(dta->cpy_envp[i], var, len) == 0)
			&& dta->cpy_envp[i][len] == '=')
		{
			take_var4(dta, i, j);
			break ;
		}
		i++;
	}
	free(var);
}
