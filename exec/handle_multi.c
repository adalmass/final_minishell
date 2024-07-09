/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_multi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:23:21 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/09 20:26:56 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd_multi(t_data *dta)
{
	if (dta->redi[1] == 0 && dta->rredi[1] == 0)
		dta->cmd1 = ft_splitt(dta->exec[dta->idx], ' ');
	else if (dta->redi[1] != 0)
		dta->cmd1 = ft_splitt(dta->redi[0], ' ');
	else if (dta->rredi[1] != 0)
		dta->cmd1 = ft_splitt(dta->rredi[0], ' ');
	search_path(dta);
	if (access(dta->cmd1[0], X_OK) == -1)
	{
		g_exit_status = 1;
		perror("Command not found");
	}
}

void	check_input_output(int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		if (dup2(out_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(out_fd);
	}
}

void	exec_cmd(t_data *dta, char **envp, int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		if (dup2(out_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(out_fd);
	}
	init_cmd_multi(dta);
	execute_multi(dta->cmd1, envp);
}

int	check_multi_redir(t_data *dta)
{
	int	j;

	j = 0;
	while (dta->exec[dta->idx][j])
	{
		if (dta->exec[dta->idx][j] == '>')
		{
			dta->redi = ft_splitt(dta->exec[dta->idx], '>');
			dta->redi[1] = ft_strtrim(dta->redi[1], " ");
			dta->file = open(dta->redi[1], O_TRUNC | O_CREAT | O_WRONLY,
					(S_IRUSR | S_IWUSR));
			return (1);
		}
		j++;
	}
	return (0);
}

int	check_multi_rredir(t_data *dta)
{
	int	j;
	int	len;

	j = 0;
	len = 0;
	while (dta->exec[dta->idx][len])
		len++;
	while (j < len)
	{
		if (dta->exec[dta->idx][j] == '<')
		{
			if (dta->exec[dta->idx][j + 1] == '<')
			{
				dta->rredi = ft_splitt(dta->exec[dta->idx], '<');
				return (2);
			}
			dta->rredi[1] = ft_strtrim(dta->rredi[1], " ");
			dta->file = open(dta->rredi[1], O_TRUNC | O_WRONLY,
					(S_IRUSR | S_IWUSR));
			return (1);
		}
		j++;
	}
	return (0);
}
