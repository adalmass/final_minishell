/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:24:51 by aldalmas          #+#    #+#             */
/*   Updated: 2024/07/09 19:57:57 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	get_last_cmd(t_parse *p, int y, int last_pipe)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (p->cmd_line[last_pipe + i])
		i++;
	p->cmd_table[y] = malloc(sizeof(char) * i + 1);
	if (!p->cmd_table)
		return ;
	i = 0;
	while (p->cmd_line[last_pipe + i])
	{
		p->cmd_table[y][j] = p->cmd_line[last_pipe + i];
		j++;
		i++;
	}
	p->cmd_table[y][j] = '\0';
}

int	set_cmdtab_memory(t_parse *p)
{
	p->pipe_number = 0;
	count_valid_pipes(p);
	if (p->pipe_number > 0)
	{
		p->pipe_number++;
		p->cmd_table = malloc(sizeof(char *) * (p->pipe_number + 1));
		if (!p->cmd_table)
			return (0);
		p->cmd_table[p->pipe_number] = NULL;
		return (1);
	}
	else if (p->pipe_number == 0)
	{
		p->pipe_number++;
		p->cmd_table = malloc(sizeof(char *) * (p->pipe_number + 1));
		if (!p->cmd_table)
			return (0);
		p->cmd_table[0] = ft_strdup(p->cmd_line);
		p->cmd_table[1] = NULL;
		return (0);
	}
	return (1);
}

void	create_cmds_table(t_parse *p)
{
	int	i;
	int	y;
	int	idx_pipe;
	int	last_pipe;

	i = 0;
	y = 0;
	last_pipe = -1;
	if (!set_cmdtab_memory(p))
		return ;
	while (p->cmd_line[i])
	{
		idx_pipe = check_before_split(p, i);
		if (idx_pipe > -1)
		{
			p->cmd_table[y] = ft_substr(p->cmd_line, i, (idx_pipe - i));
			y++;
			i = idx_pipe;
			last_pipe = idx_pipe;
		}
		i++;
	}
	if (p->cmd_line[i] == '\0')
		get_last_cmd(p, y, last_pipe + 1);
	p->cmd_table[y + 1] = NULL;
}

void	check_cmdtable_error(t_parse *p)
{
	int		y;
	char	*temp;

	y = 0;
	temp = NULL;
	while (p->cmd_table[y])
	{
		if (only_space(p->cmd_table[y]))
		{
			parse_error(p, "syntax error with `|'");
			return ;
		}
		temp = trim_remake(p->cmd_table[y], ' ');
		if (p->cmd_table[y])
			free (p->cmd_table[y]);
		p->cmd_table[y] = ft_strdup(temp);
		free (temp);
		handle_quotes(p, y);
		if (p->error_found == 1)
			return ;
		check_redir(p, p->cmd_table[y]);
		p->space_found = 0;
		y++;
		//exit (0);
	}
}

int	parsing(t_parse *p)
{	
	init_struct(p);
	if (!check_quotes_closed(p, '\'') || !check_quotes_closed(p, '\"'))
		return (0);
	first_check_cmdline(p);
	if (p->error_found == 1)
		return (0);
	create_cmds_table(p);
	if (p->error_found == 1)
		return (0);
	check_cmdtable_error(p);
	if (p->error_found == 1)
		return (0);
	return (1);
}
