/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:01:03 by bbousaad          #+#    #+#             */
/*   Updated: 2024/07/15 19:40:36 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"

# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <limits.h>
# include <termios.h>
# include <sys/stat.h>
# include <string.h>
# include <strings.h>
# include <stdint.h>
# include "../parsing/parsing.h"

typedef struct s_data
{
	char	**envp;
	char	**path;
	char	*line;
	char	**read;
	pid_t	pid;
	char	**space;
	char	**exec;
	void	*free_var;
	void	*free_rredi;
	void	*free_redi;
	int		dollar;
	int		idx;
	int		exit;
	int		nb_pipe;
	char	**cpy_envp;
	char	**cpy_cpy;
	int		pipe_fd[2];
	char	**cmd1;
	char	**str;
	char	**redi;
	char	**rredi;
	int		file;
}	t_data;

extern int	g_exit_status;

// BUILTINS :
void	print_env(t_data *dta, char **envp);
int		check_echo_n(t_data *dta);
int		check_echo_n2(t_data *dta, int i);
void	print_echo(t_data *dta);
void	print_echo2(t_data *dta);
void	print_echo3(t_data *dta);
void	print_echo_n(t_data *dta, int i);
void	print_pwd(t_data *dta);
void	ft_exit(t_data *dta);
void	ft_exit2(t_data *dta);
int		ft_cd(t_data *dta);
void	ft_export(t_data *dta);
void	ft_export2(t_data *dta);
void	ft_export3(t_data *dta, int y);
void	ft_update_export(t_data *dta, int i);
int		check_export(t_data *dta, int y);
void	ft_unset(t_data *dta, char **envp);
void	ft_unset2(t_data *dta, int cmd);
void	ft_unset3(t_data *dta, int i);

// SIGNAUX :
void	handl_signals(int signum);
void	handl_prompt(void);
// GESTION DE PATH COMMANDE :
void	handl_env(t_data *dta, char **envp);
void	search_path(t_data *dta, char **envp);
// EXEC COMMANDE :
void	take_exec(t_data *dta, char **envp);
void	execute_solo(char **cmd, char **envp);
// GESTION DE RPOMPT :
void	custom(void);
void	handl_prompt(void);
// MULTI PIPE ;
void	multi_pipe(t_data *dta, char **envp);
void	handl_multi_pipe(t_data *dta, char **envp, int in_fd);
void	exec_cmd(t_data *dta, char **envp, int in_fd, int out_fd);
int		execute_multi(char **cmd, char **envp);
int		check_multi_redir_happend(t_data *dta);
void	init_cmd_multi(t_data *dta, char **envp);
void	check_multi_redir(t_data *dta);
int		check_multi_rredir(t_data *dta);
void	handl_last_cmd(t_data *dta, int in_fd, char **envp);
void	init_cmd_multi(t_data *dta, char **envp);
void	exec_cmd(t_data *dta, char **envp, int in_fd, int out_fd);
void	check_multi_redir(t_data *dta);
void	check_multi_redir_happend2(t_data *dta);
int		check_multi_redir_happend(t_data *dta);
void	handl_cmd(t_data *dta, int in_fd, char **envp);
// UTILS :
void	handl_input_output(int incpy, int outcpy);
int		check_file(t_data *dta);
void	init_all_struct(t_data *dta);
char	*ft_strjoin_freee(char *stock, char *temp);
char	*ft_strjoin_space(const char *s1, const char *s2);
char	**ft_splitt(char const *s, char c);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t count, size_t size);
int		ft_strncmpp(const char*s1, const char *s2, size_t n);
size_t	ft_strlenn(const char *str);
int		len_read(char **tab, int i);
int		len_cmd(char **tab);
char	*ft_strchrr(const char *s, int c);
char	*ft_strdupp(const char *s1);
int		ft_atoi(const char *str);
char	*ft_substrr(const char *s, unsigned int start, size_t len);
int		ft_isalphaa(char *str);
int		doubletab_len(char **tab);
int		only_space(char *s);

//PRINT_EXIT_STATUS
void	handl_dollar(t_data *dta, int i, int len);
void	dollar_what(t_data *dta);
void	dollar_what2(t_data *dta, int j, int len, int i);
// GESTION DE VARIABLE :
char	*take_var(t_data *dta, int i);
int		search_dollar(t_data *dta, int i);
void	take_var3(t_data *dta);
void	take_var4(t_data *dta, int i, int j);
void	take_var2(t_data *dta, int z);
// GESTION DE REDIRECTION :
void	check_redirect(t_data *dta);
void	check_redirect2(t_data *dta);
void	check_redirect3(t_data *dta);
void	execute_redir(t_data *dta);
void	handl_redirect(t_data *dta, char **envp);
void	handl_redirect2(t_data *dta, char **envp);
void	init_struct_redi3(t_data *dta);
void	init_struct_redi2(t_data *dta, char **envp);
void	init_struct_redi(t_data *dta, char **envp);
void	regroup_cmd_args(t_data *dta);
int		count_redir(char *str, char redir);
void	happend_or_not(t_data *dta, char **envp);
void	exec_redir2(t_data *dta, char **envp);
void	exec_redir(t_data *dta, char **envp);
// GESTION DE REVERSE REDIRECTION :
void	check_reverse_redirect(t_data *dta, char **envp);
void	handl_redirect_input2(t_data *dta, char **envp);
void	execute_redir_input(t_data *dta);
void	exec_redir_input(t_data *dta, char **envp);
void	regroup_cmd_args_input(t_data *dta);
void	handl_rredirect(t_data *dta, char **envp);
void	prompt_rredirect(t_data *dta);
void	prompt_redirect4(t_data *dta, char **envp);
void	reverse_redirect(t_data *dta);
void	exec_rredirect3(t_data *dta, char **envp);
void	rregroup_cmd_args(t_data *dta);
// GESTION DU SHELL :
void	handl_exec(t_data *dta, char **envp);
void	handl_exec2(t_data *dta, char **envp);
void	handl_exec3(t_data *dta, char **envp);
void	handl_exec4(t_data *dta, char **envp);

#endif