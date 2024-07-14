/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:00:43 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/14 23:50:55 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void search_path2(t_data *dta, char **envp)
{
	int	i;

	i = 0;
    while (envp[i])
    {
        if (ft_strncmpp(envp[i], "PATH=", 5) == 0)
            dta->path = ft_splitt(envp[i] + 5, ':');
		i++;
    }	
}

void	search_path(t_data *dta, char **envp)
{
    int     i;
    char    *path;
    char    *temp_path;

    i = 0;
    path = NULL;
	search_path2(dta, envp);
    if (access(dta->cmd1[0], X_OK) == 0)
        return ;
    while (dta->path[i])
    {
        temp_path = ft_strjoin(dta->path[i], "/");
		if (path)
			free (path);
        path = ft_strjoin_freee(temp_path, dta->cmd1[0]);
        if (access(path, X_OK) == 0)
            break ;
		i++;
    }
    free(dta->cmd1[0]);
    dta->cmd1[0] = ft_strdupp(path);
    free(path);
    free_double_tab(dta->path);
}

// void	search_path(t_data *dta, char **envp)
// {
// 	int		i;
// 	char	*path;

// 	i = 0;
// 	path = NULL;
// 	while (envp[i])
// 	{
// 		if (ft_strncmpp(dta->envp[i], "PATH=", 5) == 0)
// 			dta->path = ft_splitt(dta->envp[i] + 5, ':');
// 		i++;
// 	}
// 	i = 0;
// 	if (access(dta->cmd1[0], X_OK) == 0)
// 		return ;
// 	while (dta->path[i])
// 	{
// 		path = ft_strjoin(dta->path[i], "/");
// 		path = ft_strjoin_freee(path, dta->cmd1[0]);
// 		if (access(path, X_OK) == 0)
// 			break ;
// 		i++;
// 	}
// 	free(dta->cmd1[0]);
// 	dta->cmd1[0] = ft_strdupp(path);
// }
