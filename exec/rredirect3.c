/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rredirect3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:27:26 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/11 20:04:29 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_rredir(char *str, char rredir)
{
	int	i;
	int	rredir_count;

	i = 0;
	rredir_count = 0;
	while (str[i])
	{
		if (str[i] == rredir)
			rredir_count++;
		i++;
	}
	return (rredir_count);
}

void	rregroup_cmd_args(t_data *dta)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_strtrim(dta->rredi[1], " ");
	dta->rredi[0] = ft_strtrim(dta->rredi[0], " ");
	while (temp[i] != ' ')
		i++;
	while (temp[i] == ' ')
		i++;
	if (dta->rredi[1])
		free (dta->rredi[1]);
	dta->rredi[1] = ft_strdupp(temp + i);
	if (temp)
		free (temp);
	dta->rredi[0] = ft_strjoin_freee(dta->rredi[0], " ");
	dta->rredi[0] = ft_strjoin_freee(dta->rredi[0], dta->rredi[1]);
}

void	handl_rredirect(t_data *dta)
{
	if (count_rredir(dta->exec[0], '<'))
	{
		dta->str = ft_splitt(dta->rredi[1], ' ');
		if (dta->str[1] != NULL)
			rregroup_cmd_args(dta);
		prompt_redirect4(dta);
	}
}

void	exec_rredirect3(t_data *dta, char **envp)
{
	dta->cmd1 = ft_splitt(dta->rredi[0], ' ');
	search_path(dta, envp);
	execute_solo(dta->cmd1, dta->envp);
	waitpid(-1, NULL, 0);
}
