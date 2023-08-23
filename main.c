/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:13:25 by bkiziler          #+#    #+#             */
/*   Updated: 2023/08/23 18:34:09 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_data *data;

int	main(int argc, char **argv, char **envp)
{
	data = malloc(sizeof(t_data) * 1);
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	reading_line();
	parser();
	signal_function();
}

void	reading_line()
{
	t_parse *temp;

	while (1)
	{
		data->line = readline("minihshell > ");
		if (data->line && *(data->line))
		{
			add_history(data->line);
			parser();
			free(data->line);
			while(data->parse != NULL)
			{
				temp = data->parse;
				data->parse = data->parse->next;
				//free(temp->content);
				free(temp);
			}
		}
	}
			system("leaks a.out");
}

void	parser()
{
	ft_split('|');
}

void	ft_split(char c)
{
	int	i;
	int	n;
	int	dbl;
	int	sng;

	i = -1;
	n = 0;
	sng = 0;
	dbl = 0;
	while (data->line[++i])
	{
		if (data->line[i] == '\'' && !(dbl % 2))
			sng++;
		else if (data->line[i] == '"' && !(sng % 2)) //eğer quoteun içinde değilse arttıllmalı
			dbl++;
		else if (data->line[i] == c && !(sng % 2) && !(dbl % 2)) //quotelar kapalı ve pipea geldiyse
		{
			add_back(&data->parse, lstnew(substr(data->line, n, i - n))); // "||" durumunda bu satıra girecek ama returnlerden dolayı bir şey olmayacak
			add_back(&data->parse, lstnew("|")); //pipetan sonra null gelirse ne olacak ?
			n = i + 1;
		}
		if (data->line[i + 1] == 0) // string sonu ve quote açık kalma durumu son harfi almıyor
		{
			if (sng % 2)
				add_back(&data->parse, lstnew(substr(strjoin(data->line, "'"), n, i - n + 2)));
			else if (dbl % 2)
				add_back(&data->parse, lstnew(substr(strjoin(data->line, "\""), n, i - n + 2)));
			else
				add_back(&data->parse, lstnew(substr(data->line, n, i - n + 1)));
		}
	}
}

char	*substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	if (!s)
		return (0);
	if (ft_strlen(s) < start || len == 0)
		return (0);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	i = 0;
	ptr = malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ptr[len] = 0;
	while (i < len)
		ptr[i++] = s[start++];
	ptr[i] = '\0';
	return (ptr);
}

t_parse	*lstnew(char *content)
{
	t_parse	*r ;

	if (!content || !*content)
		return 0;
	r = malloc (sizeof(t_parse));
	if (r == NULL)
		return (0);
	r->content = content;
	r->next = NULL;
	return (r);
}

void	add_back(t_parse **lst, t_parse *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
		(*lst) = new;
	else
	{
		(lstlast(*lst))-> next = new;
		(lstlast(*lst))-> next = NULL;
	}
}

t_parse	*lstlast(t_parse *lst)
{
	if (lst != NULL)
	{
		while (lst -> next != NULL)
			lst = lst -> next;
		return (lst);
	}
	return (0);
}

char	*strjoin(char *s1, char *s2)
{
	char	*ptr;
	int		i;

	i = -1;
	if (!s1)
	{
		s1 = malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	ptr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (ptr == NULL)
		return (NULL);
	while (s1 && s1[++i] != '\0')
		ptr[i] = s1[i];
	while (s2 && *s2 != '\0')
		ptr[i++] = *s2++;
	ptr[i] = '\0';
	free(s1);
	return (ptr);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
