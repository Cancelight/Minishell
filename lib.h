/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:27:58 by bkiziler          #+#    #+#             */
/*   Updated: 2023/08/23 18:30:56 by bkiziler         ###   ########.fr       */
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


//struct
typedef struct	s_parse{
char			*content;
struct s_parse	*next;
}				t_parse;


typedef struct s_data{
int		argc;
char	**argv;
char	**envp;
char	*line;
t_parse	*parse;
}				t_data;

//fonksiyonlar
void		signal_function(void);
t_parse		*lstnew(char *content);
void		parser();
t_parse		*lstlast(t_parse *lst);
void		add_back(t_parse **lst, t_parse *new);
int		ft_strlen(const char *s);
char	*strjoin(char *s1, char *s2);
char	*substr(char const *s, unsigned int start, size_t len);
void	ft_split(char c);
void	reading_line();


#endif
