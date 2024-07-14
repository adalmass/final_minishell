/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:37:14 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/15 01:38:51 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    happend_or_not(t_data *dta, char **envp)
{
    if (count_redir(dta->exec[0], '>') == 1)
    {
        if (dta->str[1] != NULL)
            regroup_cmd_args(dta);
        exec_redir(dta, envp);
    }
    if (count_redir(dta->exec[0], '>') == 2)
    {
        if (dta->str[1] != NULL)
            regroup_cmd_args(dta);
        exec_redir2(dta, envp);  
    }
}

void	exec_redir2(t_data *dta, char **envp)
{
	int	outcpy;

	if(dta->redi[1] != 0)
	{
		outcpy = dup(STDOUT_FILENO);
		dta->file = open(dta->str[0], O_WRONLY | O_CREAT | O_APPEND,
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
			dup2(dta->file, STDOUT_FILENO);
			close(dta->file);
			execute_solo(dta->cmd1, dta->envp);
			waitpid(-1, NULL, 0);
			dup2(outcpy, STDOUT_FILENO);
			close(outcpy);
		}
		free_double_tab(dta->cmd1);
	}
	return ;
}