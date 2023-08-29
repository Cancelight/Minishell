/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:27:58 by bkiziler          #+#    #+#             */
/*   Updated: 2023/08/29 19:22:07 by bkiziler         ###   ########.fr       */
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
int		dbl;
int		sng;
t_parse	*parse;
}				t_data;

//fonksiyonlar
void		signal_function(void);
t_parse		*lstnew(char *content);
void		parser();
t_parse		*lstlast(t_parse *lst);
void		add_back(t_parse **lst, t_parse *new);
int			ft_strlen(const char *s);
char		*strjoin(char *s1, char *s2);
char		*substr(char const *s, int start, int len);
void		ft_split();
void		reading_line(void);
void		addlist_substr(int i, int *n);
void		syntax_check(t_parse *parse);
int			multiple_pipes(t_parse *temp);
void		pre_trim(char *find);
int			syntax_redirection(char *str, char symbol);
int			strchar(char *s, int c);
int			strmatch(const char *s1, const char *s2);
void		clear_lst(t_parse **lst);
char		*put_pipe(const char *s1);
void		exit_program(int i);
void		nav_redirection(t_parse *parse);
void		heredoc_list(t_parse *parse);
int	ft_strnstr(char *haystack, char *needle, size_t len);

#endif
