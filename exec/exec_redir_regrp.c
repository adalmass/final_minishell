/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_regrp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:51:53 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/15 16:20:06 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	regroup_cmd_args(t_data *dta)
{
	int		i;
	char	*temp;
	char	*temp2;

	i = 0;
	temp = ft_strtrim(dta->redi[1], " ");
	temp2 = ft_strtrim(dta->redi[0], " ");
	while (temp[i] != ' ')
		i++;
	while (temp[i] == ' ')
		i++;
	if (dta->redi[1])
		free (dta->redi[1]);
	if (dta->redi[0])
		free (dta->redi[0]);
	dta->redi[1] = ft_strdupp(temp + i);
	if (temp)
		free (temp);
	temp2 = ft_strjoin_freee(temp2, " ");
	dta->redi[0] = ft_strjoin_freee(temp2, dta->redi[1]);
}

void	execute_redir(t_data *dta)
{
	dup2(dta->file, STDOUT_FILENO);
	close(dta->file);
	execute_solo(dta->cmd1, dta->envp);
	waitpid(-1, NULL, 0);
}

void	exec_redir(t_data *dta, char **envp)
{
	int	outcpy;

	if (dta->redi[1] != 0)
	{
		outcpy = dup(STDOUT_FILENO);
		dta->file = open(dta->str[0], O_TRUNC | O_WRONLY | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		dta->cmd1 = ft_splitt(dta->redi[0], ' ');
		search_path(dta, envp);
		if (access(dta->cmd1[0], X_OK) == -1)
		{
			g_exit_status = 127;
			perror(RED "Command not found " RESET);
		}
		else
		{
			execute_redir(dta);
			dup2(outcpy, STDOUT_FILENO);
			close(outcpy);
		}
		free_double_tab(dta->cmd1);
	}
	return ;
}
