/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 10:11:25 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/15 19:49:59 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/parsing.h"
#include "exec/minishell.h"

int	g_exit_status;

void	cmdtable_to_exec(t_parse *p, t_data *dta)
{
	int	y;
	int	i;

	i = 0;
	y = 0;
	while (p->cmd_table[y])
		y++;
	dta->exec = ft_calloc(y + 1, sizeof(char *));
	while (i < y)
	{
		dta->exec[i] = ft_strdup(p->cmd_table[i]);
		i++;
	}
	dta->exec[i] = NULL;
	free_double_tab(p->cmd_table);
}

void	handl_input_output(int incpy, int outcpy)
{
	if (dup2(incpy, STDIN_FILENO) == -1)
	{
		perror(RED "dup2" RESET);
		exit(EXIT_FAILURE);
		close(incpy);
	}
	if (dup2(outcpy, STDOUT_FILENO) == -1)
	{
		perror(RED "dup2" RESET);
		exit(EXIT_FAILURE);
		close(outcpy);
	}
}

void	main_loop(t_parse *p, t_data *dta, char **envp)
{
	if (ft_strlen(p->cmd_line) > 0)
	{
		add_history(p->cmd_line);
		if (!only_space(p->cmd_line))
		{
			if (parsing(p))
			{
				cmdtable_to_exec(p, dta);
				dta->read = ft_splitt(dta->exec[0], ' ');
				dta->free_var = dta->read;
				dta->space = ft_splitt(p->cmd_line, ' ');
				handl_exec(dta, envp);
				if (dta->exec)
					free_double_tab(dta->exec);
				if (dta->free_var != NULL)
				{
					free_double_tab(dta->read);
					dta->free_var = NULL;
				}
				if (dta->space)
					free_double_tab(dta->space);
			}
		}
	}
}

void	initialize(t_data *dta, char **envp)
{
	using_history();
	handl_prompt();
	custom();
	init_all_struct(dta);
	handl_env(dta, envp);
	dta->envp = envp;
}

int	main(int argc, char **argv, char **envp)
{
	t_parse	p;
	t_data	*dta;
	int		incpy;
	int		outcpy;

	if (doubletab_len(envp) < 1)
		return (printf("no envp, get out of my minishell\n"), 1);
	incpy = dup(STDIN_FILENO);
	outcpy = dup(STDOUT_FILENO);
	dta = malloc(sizeof(t_data));
	initialize(dta, envp);
	while (1 || argc || argv)
	{
		p.error_found = 0;
		while (p.error_found == 0)
		{
			p.cmd_line = readline("\033[0;35mMINISHELL$>\033[0;37m");
			if (!p.cmd_line)
				exit (0);
			main_loop(&p, dta, envp);
			handl_input_output(incpy, outcpy);
			if (p.cmd_line)
				free (p.cmd_line);
		}
	}
}
