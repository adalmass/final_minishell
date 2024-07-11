/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:52:31 by aldalmas          #+#    #+#             */
/*   Updated: 2024/07/10 21:29:39 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_quote_found(int quote)
{
	if (quote == 2)
		return (0);
	return (quote);
}

// A REVOIR 
int	find_quote(t_parse *p, int idx_cmd)
{
	int	i;

	i = 0;
	while (p->cmd_table[idx_cmd][i])
	{
		if (p->cmd_table[idx_cmd][i] == '\''
			|| p->cmd_table[idx_cmd][i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

void	handle_quotes(t_parse *p, int idx_cmd)
{
	int		echo_found;
	char	**temp;

	temp = ft_split(p->cmd_table[idx_cmd], ' ');
	echo_found = ft_strncmp(temp[0], "echo\0", 5);
	if (find_quote(p, idx_cmd))
	{
		if (echo_found && find_redir(p, p->cmd_table[idx_cmd], echo_found))
		{
			free_double_tab(temp);
			return ;
		}
		remove_quotes(p, idx_cmd);
	}
	free_double_tab(temp);
}

int	check_quotes_closed(t_parse *p, char quote)
{
	int	i;
	int	quote_found;

	i = 0;
	quote_found = 0;
	while (p->cmd_line[i])
	{
		if (p->cmd_line[i] == quote)
			quote_found++;
		i++;
	}
	if ((quote_found % 2 != 0) && quote == '\'')
	{
		parse_error(p, "syntax error, simple quote missing");
		return (0);
	}
	else if ((quote_found % 2 != 0) && quote == '\"')
	{
		parse_error(p, "syntax error, double quote missing");
		return (0);
	}
	return (1);
}
