/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:00:38 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/15 00:50:21 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_redir(char *str, char redir)
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
	return(redir_count);
}

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

void	exec_redir(t_data *dta, char **envp)
{
	int	outcpy;

	if(dta->redi[1] != 0)
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

void	handl_redirect(t_data *dta, char **envp)
{
	happend_or_not(dta, envp);
}

void	handl_redirect2(t_data  *dta, char **envp)
{
	if (dta->exec[1] == 0)
	{
		if (count_redir(dta->exec[0], '>') == 1)
		{
			dta->str = ft_splitt(dta->redi[1], ' ');
			if(dta->str[1] != NULL)
				regroup_cmd_args(dta);
			exec_redir(dta, envp);
			free_double_tab(dta->str);
		}
		else if (count_redir(dta->exec[0], '>') == 2)
		{
			dta->str = ft_splitt(dta->redi[1], ' ');
			if(dta->str[1] != NULL)
				regroup_cmd_args(dta);
			exec_redir2(dta, envp);
			free_double_tab(dta->str);
		}
	}
}

