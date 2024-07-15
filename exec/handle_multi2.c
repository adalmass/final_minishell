/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_multi2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:24:28 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/15 16:35:23 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_multi(char **cmd, char **envp)
{
	if (execve(cmd[0], cmd, envp) == -1)
	{
		g_exit_status = 127;
		perror(RED "Command not found" RESET);
		exit(EXIT_FAILURE);
		return (1);
	}
	else
		g_exit_status = 0;
	return (0);
}

void	handl_cmd(t_data *dta, int in_fd, char **envp)
{
	close(dta->pipe_fd[0]);
	if (check_multi_redir_happend(dta) == 0
		&& check_multi_rredir(dta) == 0)
	{
		exec_cmd(dta, envp, in_fd, dta->pipe_fd[1]);
	}
	else if (check_multi_redir_happend(dta) == 1)
	{
		exec_cmd(dta, envp, in_fd, dta->file);
		close(dta->file);
	}
	else if (check_multi_rredir(dta) == 1)
	{
		exec_cmd(dta, envp, dta->file, dta->pipe_fd[1]);
		close (dta->file);
	}
}

void	handl_last_cmd(t_data *dta, int in_fd, char **envp)
{
	if (check_multi_redir_happend(dta) == 0
		&& check_multi_rredir(dta) == 0)
	{
		exec_cmd(dta, envp, in_fd, STDOUT_FILENO);
	}
	else if (check_multi_redir_happend(dta) == 1)
	{
		exec_cmd(dta, envp, in_fd, dta->file);
		close(dta->file);
	}
	else if (check_multi_rredir(dta) == 1)
	{
		exec_cmd(dta, envp, dta->file, STDOUT_FILENO);
		close (dta->file);
	}
	close(in_fd);
}

void	handl_multi_pipe(t_data *dta, char **envp, int in_fd)
{
	while (dta->exec[dta->nb_pipe])
		dta->nb_pipe++;
	while (dta->idx < dta->nb_pipe - 1)
	{
		if (pipe(dta->pipe_fd) == -1)
			perror(RED "fork" RESET);
		dta->pid = fork();
		if (dta->pid == -1)
			perror(RED "fork" RESET);
		if (dta->pid == 0)
			handl_cmd(dta, in_fd, envp);
		else
		{
			close(dta->pipe_fd[1]);
			if (in_fd != STDIN_FILENO)
				close(in_fd);
			in_fd = dta->pipe_fd[0];
		}
		dta->idx++;
	}
	dta->pid = fork();
	if (dta->pid == -1)
		perror(RED "fork" RESET);
	if (dta->pid == 0)
		handl_last_cmd(dta, in_fd, envp);
}
