/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 09:07:27 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/15 18:59:16 by bbousaad         ###   ########.fr       */
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
		while (tab[len])
			len++;
	}
	return (len);
}

int	len_read(char **tab, int i)
{
	int	len;

	len = 0;
	while (tab[i][len])
		len++;
	return (len);
}

void	init_all_struct(t_data *dta)
{
	dta->envp = NULL;
	dta->path = NULL;
	dta->line = NULL;
	dta->read = NULL;
	dta->space = NULL;
	dta->exec = NULL;
	dta->dollar = 0;
	dta->idx = 0;
	dta->exit = 0;
	dta->free_var = NULL;
	dta->free_rredi = NULL;
	dta->free_redi = NULL;
	dta->nb_pipe = 0;
	dta->cpy_envp = NULL;
	dta->cpy_cpy = NULL;
	dta->pipe_fd[0] = 0;
	dta->pipe_fd[1] = 0;
	dta->cmd1 = NULL;
	dta->str = NULL;
	dta->redi = NULL;
	dta->rredi = NULL;
	dta->file = 0;
}

int	doubletab_len(char **tab)
{
	int	y;

	y = 0;
	while (tab[y])
		y++;
	return (y);
}

int	only_space(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
