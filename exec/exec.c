/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:23:28 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/09 20:26:53 by bbousaad         ###   ########.fr       */
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
			g_exit_status = 1;
			perror("Command not found ");
		}
	}
}

void	take_exec(t_data *dta)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (dta->exec[len])
		len++;
	while (i <= len - 1)
	{
		dta->cmd1 = ft_splitt(dta->exec[i], ' ');
		search_path(dta);
		if (access(dta->cmd1[0], X_OK) == -1)
		{
			g_exit_status = 1;
			perror("Command not found ");
		}
		else
		{
			g_exit_status = 0;
			execute_solo(dta->cmd1, dta->envp);
		}
		waitpid(-1, NULL, 0);
		i++;
	}
}
