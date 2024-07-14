/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_multi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:23:21 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/14 23:08:04 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd_multi(t_data *dta, char **envp)
{
	if (check_multi_redir_happend(dta) == 0
		&& check_multi_rredir(dta) == 0)
			dta->cmd1 = ft_splitt(dta->exec[dta->idx], ' ');
	else if (check_multi_redir_happend(dta) == 1)
		dta->cmd1 = ft_splitt(dta->redi[0], ' ');
	else if (check_multi_rredir(dta) == 1)
		dta->cmd1 = ft_splitt(dta->rredi[0], ' ');
	search_path(dta, envp);
	if (access(dta->cmd1[0], X_OK) == -1)
		g_exit_status = 127;
}

void	exec_cmd(t_data *dta, char **envp, int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
		{
			g_exit_status = 2;
			exit(EXIT_FAILURE);
		}
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		if (dup2(out_fd, STDOUT_FILENO) == -1)
		{
			g_exit_status = 2;
			exit(EXIT_FAILURE);
		}
		close(out_fd);
	}
	init_cmd_multi(dta, envp);
	execute_multi(dta->cmd1, envp);
	free_double_tab(dta->cmd1);
}

void	check_multi_redir(t_data *dta)
{
	char	*temp;

	dta->redi = ft_splitt(dta->exec[dta->idx], '>');
	temp = ft_strtrim(dta->redi[1], " ");
	free (dta->redi[1]);
	dta->redi[1] = temp;
	dta->file = open(dta->redi[1], O_TRUNC | O_CREAT | O_WRONLY,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	free (temp);
}

void	check_multi_redir_happend2(t_data *dta)
{
	char	*temp;
	
	dta->redi = ft_splitt(dta->exec[dta->idx], '>');
	temp = ft_strtrim(dta->redi[1], " ");
	free (dta->redi[1]);
	dta->file = open(temp, O_WRONLY | O_CREAT |
			O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	dta->redi[1] = temp;
	free (temp);
}

int	check_multi_redir_happend(t_data *dta)
{
	int	j;

	j = 0;
	while (dta->exec[dta->idx][j])
	{
		if (dta->exec[dta->idx][j] == '>')
		{
			if (dta->exec[dta->idx][j + 1] == '>')
			{
				check_multi_redir_happend2(dta);
				return (1);
				
			}
			else if (dta->exec[dta->idx][j + 1] != '>')
			{
				check_multi_redir(dta);
				return (1);
			}
		}
		j++;
	}
	return (0);
}

int	check_multi_rredir(t_data *dta)
{
	int		j;
	int		len;
	char	*temp;

	j = 0;
	len = 0;
	while (dta->exec[dta->idx][len])
		len++;
	while (j < len)
	{
		if (dta->exec[dta->idx][j] == '<')
		{
			temp = ft_strtrim(dta->rredi[1], " ");
			free (dta->rredi[1]);
			dta->rredi[1] = temp;
			dta->file = open(dta->rredi[1], O_TRUNC | O_WRONLY,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			free (temp);
			return (1);
		}
		j++;
	}
	return (0);
}
