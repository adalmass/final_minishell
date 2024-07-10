/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:37:14 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/10 15:56:25 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    handl_redirect3(t_data *dta, int i)
{
	if (count_redir(dta->exec[i], '>') == 2)
	{
		dta->str = ft_splitt(dta->redi[1], ' ');
		if (dta->str[1] != NULL)
			regroup_cmd_args(dta);
		exec_redir2(dta);
	}
}

void	exec_redir2(t_data *dta)
{
	int	outcpy;

	if(dta->redi[1] != 0)
	{
		outcpy = dup(STDOUT_FILENO);
		dta->file = open(dta->str[0], O_WRONLY, O_CREAT ,O_APPEND,
                (S_IRUSR | S_IWUSR));
		dta->cmd1 = ft_splitt(dta->redi[0], ' ');
		search_path(dta);
		if (access(dta->cmd1[0], X_OK) == -1)
		{
			g_exit_status = 127;
			perror(RED "Command not found " RESET);
		}
		else
		{
			dup2(dta->file, STDOUT_FILENO);
			close(dta->file);
			execute_solo(dta->cmd1, dta->envp);
			waitpid(-1, NULL, 0);
			dup2(outcpy, STDOUT_FILENO);
			close(outcpy);
		}
	}
	return ;
}