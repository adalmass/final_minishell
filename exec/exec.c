/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:23:28 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/12 15:57:44 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_solo(char **cmd, char **envp)
{
	pid_t	pid_;

	pid_ = fork();
	if (pid_ == 0)
	{
		if (execve(cmd[0], cmd, envp) == -1)
		{
			g_exit_status = 127;
			perror(RED "Command not found " RESET);
		}
		else
			g_exit_status = 0;
	}
}

void	take_exec(t_data *dta, char **envp)
{
	dta->cmd1 = ft_splitt(dta->exec[0], ' ');
	search_path(dta, envp);
	if (access(dta->cmd1[0], X_OK) == -1)
	{
		g_exit_status = 127;
		perror(RED "Command not found " RESET);
	}
	else
	{
		g_exit_status = 0;
		execute_solo(dta->cmd1, dta->envp);
	}
	waitpid(-1, NULL, 0);
	return ;
}
