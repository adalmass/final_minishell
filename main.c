/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 10:11:25 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/12 15:53:51 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/parsing.h"
#include "exec/minishell.h"

int    g_exit_status;

void    cmdtable_to_exec(t_parse *p, t_data *dta)
{
	int	y;
	int	i;

	i = 0;
	y = 0;
	while(p->cmd_table[y])
		y++;
	dta->exec = ft_calloc(y + 1, sizeof(char *));
	while(i < y)
	{
		dta->exec[i] = ft_strdup(p->cmd_table[i]);
		i++;
	}
	dta->exec[i] = NULL;
	free_double_tab(p->cmd_table);
}

int    only_space(char *s)
{
	int    i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
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

int    main(int argc, char **argv, char **envp)
{
	t_parse	p;
	t_data	*dta;
	(void)  argc;
	(void)  argv;
	int		incpy;
	int		outcpy;
	
	incpy = dup(STDIN_FILENO);
	outcpy = dup(STDOUT_FILENO);
	dta = malloc(sizeof(t_data));
	dta->envp = envp;
	handl_env(dta, envp);
	handl_prompt();
	custom();
	using_history();
	while (1)
	{
		p.error_found = 0;
		while (p.error_found == 0)
		{
			p.cmd_line = readline("\033[0;35mMINISHELL$>\033[0;37m");
			if (!p.cmd_line)
				exit (0);
			dta->line = ft_strdup(p.cmd_line);
			if (ft_strlen(p.cmd_line) > 0)
			{
				add_history(p.cmd_line);
				if (!only_space(p.cmd_line))
				{
					if (parsing(&p))
					{
						cmdtable_to_exec(&p, dta);
						init_struct_dta(dta);
						handl_exec(dta, envp);
						if(dta->read)
							free_double_tab(dta->read);
						if(dta->exec)
							free_double_tab(dta->exec);
						if(dta->space)
							free_double_tab(dta->space);
						// if(dta->rredi)
						// 	free_double_tab(dta->rredi);
						// if(dta->redi)
						// 	free_double_tab(dta->redi);
					}
				}
			}
			handl_input_output(incpy, outcpy);
			if (p.cmd_line)
				free(p.cmd_line);
		}
	}
}
