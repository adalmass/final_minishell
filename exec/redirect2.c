/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:00:38 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/15 16:22:01 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_redir(char *str, char redir)
{
	int	i;
	int	redir_count;

	i = 0;
	redir_count = 0;
	while (str[i])
	{
		if (str[i] == redir)
			redir_count++;
		i++;
	}
	return (redir_count);
}

void	handl_redirect(t_data *dta, char **envp)
{
	happend_or_not(dta, envp);
}

void	handl_redirect2(t_data *dta, char **envp)
{
	if (dta->exec[1] == 0)
	{
		if (count_redir(dta->exec[0], '>') == 1)
		{
			dta->str = ft_splitt(dta->redi[1], ' ');
			if (dta->str[1] != NULL)
				regroup_cmd_args(dta);
			exec_redir(dta, envp);
			free_double_tab(dta->str);
		}
		else if (count_redir(dta->exec[0], '>') == 2)
		{
			dta->str = ft_splitt(dta->redi[1], ' ');
			if (dta->str[1] != NULL)
				regroup_cmd_args(dta);
			exec_redir2(dta, envp);
			free_double_tab(dta->str);
		}
	}
}
