/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 22:13:53 by aldalmas          #+#    #+#             */
/*   Updated: 2024/07/10 22:30:30 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	replace_spaces(t_parse *p, int idx_cmd, char replace)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (p->cmd_table[idx_cmd][i])
	{
		if (p->cmd_table[idx_cmd][i] == '\'')
		{
			s_quote++;
			s_quote = check_quote_found(s_quote);
		}
		if (p->cmd_table[idx_cmd][i] == '\"')
		{
			d_quote++;
			d_quote = check_quote_found(d_quote);
		}
		if (p->cmd_table[idx_cmd][i] == ' ' && (d_quote > 0 || s_quote > 0))
			p->cmd_table[idx_cmd][i] = replace;
		i++;
	}
}

void	restore_spaces(t_parse *p, char replaced_char)
{
	int	x;
	int	y;

	y = 0;
	while (p->splitted_built[y])
	{
		x = 0;
		while (p->splitted_built[y][x])
		{
			if (p->splitted_built[y][x] == replaced_char)
				p->splitted_built[y][x] = ' ';
			x++;
		}
		y++;
	}
}

void	rejoin_to_cmdtable(t_parse *p, int idx_cmd)
{
	int		y;
	char	*temp;

	y = 0;
	free (p->cmd_table[idx_cmd]);
	p->cmd_table[idx_cmd] = ft_strdup("");
	while (p->splitted_built[y])
	{
		temp = ft_strjoin(p->splitted_built[y], " ");
		p->cmd_table[idx_cmd] = strjoin_free(p->cmd_table[idx_cmd], temp);
		free (temp);
		y++;
	}
}

void	modify_splitted_built(t_parse *p, int y)
{
	char	*temp;

	temp = NULL;
	if (search_quote(p->splitted_built[y]))
	{
		printf("debug: %s\n", p->splitted_built[y]);
		if (p->splitted_built[y][0] == '\'')
			temp = trim_quotes(p->splitted_built[y], '\'');
		else if (p->splitted_built[y][0] == '\"')
			temp = trim_quotes(p->splitted_built[y], '\"');
		if (temp)
		{
			p->splitted_built[y] = ft_strdup(temp);
			free (temp);
		}
	}
}

void	remove_quotes(t_parse *p, int idx_cmd)
{
	int		y;
	char	replace;

	y = 0;
	replace = -1;
	replace_spaces(p, idx_cmd, replace);
	p->splitted_built = ft_split(p->cmd_table[idx_cmd], ' ');
	restore_spaces(p, replace);
	if (find_space(p))
		return ;
	while (p->splitted_built[y])
	{
		modify_splitted_built(p, y);
		y++;
	}
	rejoin_to_cmdtable(p, idx_cmd);
	free_double_tab(p->splitted_built);
}
