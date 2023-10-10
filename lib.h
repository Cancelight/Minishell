/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:27:58 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/10 19:52:57 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LIB_H
#define LIB_H

//kütüphaneler
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <signal.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <string.h>

//struct parselamak için
typedef struct	s_parse{
char			*content;
struct			s_parse	*next;
}				t_parse;

//genel verilerin tutulması için
typedef struct s_data{
int		argc;
char	**argv;
char	**envp;
char	*line;
int		input_file;
int		output_file;
int		heredoc_cnt;
int		syntax_flag;
int		dbl;
int		sng;
t_parse	*parse;
}		t_data;

//fonksiyonlar
void	signal_function(void);
t_parse	*lstnew(char *content);
void	parser();
t_parse	*lstlast(t_parse *lst);
void	add_back(t_parse **lst, t_parse *new);
int		ft_strlen(const char *s);
char	*strjoin(char *s1, char *s2);
char	*substr(char *s, int start, int len);
void	ft_split(int n, int i);
void	reading_line();
void	addlist_substr(int i, int *n);
void	syntax_check(t_parse *parse);
int		multiple_pipes(t_parse *temp);
void	pre_trim(char *find);
int		syntax_redirection(char *str, char symbol);
int		strchar(char *s, int c);
int		strmatch(const char *s1, const char *s2);
void	clear_lst(t_parse **lst);
char	*str_dup(const char *s1);
void	exit_program(char *str, int i);
char	**nav_redirection(char *content);
void	heredoc_list(t_parse *parse);
void	heredoc_str(char *str);
int		search(char *detect, char *found);
int		heredoc_file(char *str, int i);
int		ft_strcmp(char *s1, char *s2);
void	ft_putstr_fd(char *s, int fd);
void	change_data_input(int file);
void	ft_putendl_fd(char *s, int fd);
int		input_redirection(char *str, int i);
int		strrchar(char *s, int c);
int		append_redirection(char *str, int i);
void	change_data_output(int file, int append_flag);
int		output_redirection(char *str, int i);
char	*remove_redirection(char *str, char *new);
char	*s2_strjoin(char *s1, char *s2);
char	*v2_substr(char *s, int start, int len);
char	*trim_quote(char *str, int i);
void	duplication(int fd_in, int fd_out);
char	**libft_split(char *s, char c);
char	*ft_substr(char *s, int start, int len);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);

#endif
