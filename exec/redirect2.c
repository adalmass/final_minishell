/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:00:38 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/10 15:45:07 by bbousaad         ###   ########.fr       */
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

	i = 0;
	temp = ft_strtrim(dta->redi[1], " ");
	dta->redi[0] = ft_strtrim(dta->redi[0], " ");
	while (temp[i] != ' ')
		i++;
	while (temp[i] == ' ')
		i++;
	if (dta->redi[1])
		free (dta->redi[1]);
	dta->redi[1] = ft_strdupp(temp + i);
	if (temp)
		free (temp);
	dta->redi[0] = ft_strjoin_freee(dta->redi[0], " ");
	dta->redi[0] = ft_strjoin_freee(dta->redi[0], dta->redi[1]);
}

void	exec_redir(t_data *dta)
{
	int	outcpy;

	if(dta->redi[1] != 0)
	{
		outcpy = dup(STDOUT_FILENO);
		dta->file = open(dta->str[0], O_TRUNC | O_CREAT | O_WRONLY,
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

void	handl_redirect(t_data *dta)
{
	
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (dta->exec[len])
		len++;
	if (dta->exec[1] != 0)
	{
		while (i < len)
		{
			if (count_redir(dta->exec[i], '>') == 1)
			{
				if (dta->str[1] != NULL)
					regroup_cmd_args(dta);
				exec_redir(dta);
			}
			i++;
		}
	}
}

void	handl_redirect2(t_data  *dta)
{
	if (dta->exec[1] == 0)
	{
		if (count_redir(dta->exec[0], '>') == 1)
		{
			dta->redi = ft_splitt(dta->exec[0], '>');
			dta->str = ft_splitt(dta->redi[1], ' ');
			if(dta->str[1] != NULL)
				regroup_cmd_args(dta);
			exec_redir(dta);
		}
		if (count_redir(dta->exec[0], '>') == 2)
		{
			dta->redi = ft_splitt(dta->exec[0], '>');
			dta->str = ft_splitt(dta->redi[1], ' ');
			if(dta->str[1] != NULL)
				regroup_cmd_args(dta);
			exec_redir2(dta);
		}
	}
}

