/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:36:21 by aldalmas          #+#    #+#             */
/*   Updated: 2024/07/09 14:21:19 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	count_valid_pipes(t_parse *p)
{
	int	i;
	int	s_quote_found;
	int	d_quote_found;

	i = 0;
	s_quote_found = 0;
	d_quote_found = 0;
	while (p->cmd_line[i])
	{
		if (p->cmd_line[i] == '\'')
		{
			s_quote_found++;
			if (s_quote_found == 2)
				s_quote_found = 0;
		}
		else if (p->cmd_line[i] == '\"')
		{
			d_quote_found++;
			if (d_quote_found == 2)
				d_quote_found = 0;
		}
		if (p->cmd_line[i] == '|' && d_quote_found == 0 && s_quote_found == 0)
			p->pipe_number++;
		i++;
	}
}

int	check_before_split(t_parse *p, int i)
{
	int	s_quote_found;
	int	d_quote_found;

	s_quote_found = 0;
	d_quote_found = 0;
	while (p->cmd_line[i])
	{
		if (p->cmd_line[i] == '\'')
		{
			s_quote_found++;
			s_quote_found = check_quote_found(s_quote_found);
		}
		else if (p->cmd_line[i] == '\"')
		{
			d_quote_found++;
			d_quote_found = check_quote_found(d_quote_found);
		}
		if (p->cmd_line[i] == '|' && d_quote_found == 0 && s_quote_found == 0)
		{
			p->pipe_number++;
			return (i);
		}
		i++;
	}
	return (-1);
}

void	pipe_found(t_parse *p, char next_char)
{
	p->pipe_count++;
	if (p->redir_l_count > 0 || p->redir_r_count > 0)
	{
		if (p->pipe_count == 1)
			parse_error(p, RED "syntax error near unexpected token `|'" RESET);
		else if (p->pipe_count > 1)
			parse_error(p, RED "syntax error near unexpected token `||'" RESET);
	}
	if (next_char == '\0')
		parse_error(p, RED "syntax error, no command after a pipe" RESET);
	if (next_char != '\0' && next_char != '|')
	{
		check_all_errors(p);
		p->pipe_count = 0;
	}
}

int	check_pipe_lastchar(t_parse *p, char *cmd)
{
	int	i;
	int	error;

	i = ft_strlen(cmd) - 1;
	error = 0;
	while (i >= 0 && cmd[i] == ' ')
		i--;
	if (cmd[i] == '|')
		error = 1;
	while (--i >= 0)
	{
		if (cmd[i] != '>' && cmd[i] != '<' && cmd[i] != ' ')
			break ;
		if (cmd[i] == '>' || cmd[i] == '<')
		{
			parse_error(p, RED "syntax error near unexpected token `|'" RESET);
			return (0);
		}
	}
	if (error)
	{
		parse_error(p, RED "syntax error, no command after a pipe" RESET);
		return (0);
	}
	return (1);
}
