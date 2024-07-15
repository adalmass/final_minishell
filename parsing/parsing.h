/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldalmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:42:12 by aldalmas          #+#    #+#             */
/*   Updated: 2024/03/29 15:07:05 by aldalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <strings.h>
# include <stdarg.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../exec/minishell.h"

typedef struct s_parse
{
	int			count;
	int			error_found;
	int			space_found;
	int			echo_found;
	int			idx_start_quote;
	int			idx_end_quote;
	int			len_cmd_line;
	int			pipe_number;
	int			space_number;
	int			pipe_count;
	int			redir_l_count;
	int			cmdtab_redir_l;
	int			cmdtab_redir_r;
	int			redir_r_count;
	int			sub_start;
	int			sub_end;
	char		*cmd_line;
	char		**cmd_table;
	char		**splitted_built;
}				t_parse;

// --- main.c
int		only_space(char *s);

// --- parsing.c
int		parsing(t_parse *p);
void	create_cmds_table(t_parse *p);
void	check_cmdtable_error(t_parse *p);

// --- check_cmd.c
void	error_redirection(t_parse *p);
int		error_pipe(t_parse *p);
int		check_redir(t_parse *p, char *cmd);
void	check_all_errors(t_parse *p);
void	check_redir2(t_parse *p, char *cmd);
void	redir_last_char(t_parse *p, char *cmd);

// --- remove_quotes.c
int		check_quotes_closed(t_parse *p, char quote);
void	handle_quotes(t_parse *p, int idx_cmd);

// --- handle_pipes.c
int		check_pipe_lastchar(t_parse *p, char *cmd);
int		check_before_split(t_parse *p, int i);
void	count_valid_pipes(t_parse *p);
void	pipe_found(t_parse *p, char next_char);

// handle_space.c
void	remove_quotes(t_parse *p, int idx_cmd);

// --- redir_n_pipe.c
int		find_redir(t_parse *p, char *cmd, int echo_found);
void	redir_left_found(t_parse *p, char c);
void	redir_right_found(t_parse *p, char next_char);
void	pipe_found(t_parse *p, char next_char);
void	first_check_cmdline(t_parse *p);

// --- tools.c
void	parse_error(t_parse *p, char *error_msg);
void	init_struct(t_parse *p);
void	free_double_tab(char **tab);
char	*trim_quotes(char *splitted_built, char quote);

// --- utils.c
int		search_quote(char *s);
int		find_space(t_parse *p);
char	*trim_remake(char *s, char c);

// --- handle_quotes.c
int		check_quote_found(int quote);

//int		find_redir(t_parse *p, char *cmd, int echo_found);

// --- --- mini_libft/
int		ft_strlen(const char *s);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
char	*ft_strdup(const char *s1);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*strjoin_free(char *stock, char *temp);
char	*ft_substr(char const *s, unsigned int start, int len);
char	*ft_strchr(const char *s, int c);
char	*ft_strcpy(char *d, char *s);
char	*ft_strjoinn(const char *s1, const char *s2);
char	*ft_strtrimm(char const *s1, char const *set);

#endif