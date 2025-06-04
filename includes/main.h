/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:35:16 by rcini-ha          #+#    #+#             */
/*   Updated: 2025/06/04 16:27:05 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include "../libft/include/libft.h"
# include "define.h"
# include "struct.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/*___________________________MAIN______________________________________**/

/*___________________________HANDLERS__________________________________**/
void	handle_sigint(int a);
void	handle_sigint_heredoc(int a);

/*__________________________TOKENISATIONS______________________________**/
t_list	*parse_input_line(char *line, t_list **cmd_list);
void	free_list(t_list *cmd_list);

/*__________________________PARSING___________________________________**/

/*__________________________ENVIRONEMENT______________________________**/
t_list	*ft_envp_lst(char **envp);
char	**ft_envp_copy(char **envp);

/*__________________________BUILTINS__________________________________**/
void	ft_builtin(char *line, t_list **envp_lst);
char	*ft_get_env(char *key, t_list *envp_lst);
void	ft_export(t_list **envp_lst, char *key, char *value);
int		ft_cd(t_list **envp_lst, char *line);
void	ft_print_env(t_list *envp);
int		ft_echo(char **args);

/*__________________________UTILS__________________________________**/
int		is_whitespace(char c);
int		is_quote(char c);
int		check_unclosed_quotes(char *line);
void	trim_segment(const char *input, size_t start, size_t end, size_t *s,
			size_t *e);
int		is_unquoted_pipe(char c, int sq, int dq);
char	**split_smart_pipe(const char *input);
void	update_quote_state(char c, int *in_single, int *in_double);
int		ft_check_err(char *line);

/*__________________________DESTROY____________________________________**/
void	free_commands(char **commands);
void	free_list(t_list *cmd_list);

/*__________________________CD_UTILS____________________________________**/
char    *ft_create_path(char *pwd, char *dst);
int     ft_only_space(char *s);
int     ft_special_case(char **cmd);


char     *ft_expand_variable(char *line, t_list **env);
char     *ft_get_key(char *s);
char     *ft_get_value(char *s);
void      ft_export_var(char *line, t_list **env);
int       exec_cmd(char *line, char **envp);

/*__________________________LEXER_UTILS__________________________________**/
int     ft_error(char *msg, int code);
int     ft_put_error(char *msg, int code);



#endif
