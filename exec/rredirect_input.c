/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rredirect_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 13:09:35 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/15 19:41:46 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	regroup_cmd_args_input(t_data *dta)
{
	int		i;
	char	*temp;
	char	*temp2;

	i = 0;
	temp = ft_strtrim(dta->rredi[1], " ");
	temp2 = ft_strtrim(dta->rredi[0], " ");
	while (temp[i] != ' ')
		i++;
	while (temp[i] == ' ')
		i++;
	if (dta->rredi[1])
		free (dta->rredi[1]);
	if (dta->rredi[0])
		free (dta->rredi[0]);
	dta->rredi[1] = ft_strdupp(temp + i);
	if (temp)
		free (temp);
	temp = ft_strjoin_freee(temp2, " ");
	dta->rredi[0] = ft_strjoin_freee(temp, dta->rredi[1]);
}

void	execute_redir_input(t_data *dta)
{
	dup2(dta->file, STDIN_FILENO);
	close(dta->file);
	execute_solo(dta->cmd1, dta->envp);
	waitpid(-1, NULL, 0);
}

void	exec_redir_input(t_data *dta, char **envp)
{
	int	incpy;

	incpy = dup(STDIN_FILENO);
	if (access(dta->str[0], F_OK) == -1)
		perror("Error file");
	else
		dta->file = open(dta->str[0], O_TRUNC | O_WRONLY,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	dta->cmd1 = ft_splitt(dta->rredi[0], ' ');
	search_path(dta, envp);
	if (access(dta->cmd1[0], X_OK) == -1)
	{
		free_double_tab(dta->cmd1);
		perror("Command not found ");
	}
	else
	{
		execute_redir_input(dta);
		dup2(incpy, STDIN_FILENO);
		close(incpy);
		free_double_tab(dta->cmd1);
	}
	return ;
}

void	handl_redirect_input2(t_data *dta, char **envp)
{
	if (count_redir(dta->exec[0], '<'))
	{
		dta->str = ft_splitt(dta->rredi[1], ' ');
		if (dta->str[1] != NULL)
			regroup_cmd_args_input(dta);
		exec_redir_input(dta, envp);
		free_double_tab(dta->str);
	}
}
