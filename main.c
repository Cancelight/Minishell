/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:13:25 by bkiziler          #+#    #+#             */
/*   Updated: 2023/08/23 20:06:40 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_data	*data;

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

void	reading_line(void)
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
		/*	while(data->parse != NULL)
			{
				temp = data->parse;
				data->parse = data->parse->next;
				//free(temp->content);
				free(temp);
			}*/
		}
	}
			//system("leaks a.out");
}

void	parser(void)
{
	data->sng = 0;
	data->dbl = 0;
	ft_split();
	while (data->parse != NULL)
	{
		printf("content: %s\n", data->parse->content);
		data->parse = data->parse->next;
	}
}

void	addlist_substr(int i, int *n)
{
	add_back(&data->parse, lstnew(substr(data->line, *n, i - *n))); // "||" durumunda bu satıra girecek ama returnlerden dolayı bir şey olmayacak
	add_back(&data->parse, lstnew("|")); //pipetan sonra null gelirse ne olacak ?
	*n = i + 1;
}

void	ft_split(void)
{
	int	i;
	int	n;

	i = -1;
	n = 0;
	while (data->line[++i])
	{
		if (data->line[i] == '\'' && !(data->dbl % 2))
			data->sng++;
		else if (data->line[i] == '"' && !(data->sng % 2)) //eğer quoteun içinde değilse arttıllmalı
			data->dbl++;
		else if (data->line[i] == '|' && !(data->sng % 2) && !(data->dbl % 2))
			addlist_substr(i, &n);
		if (data->line[i + 1] == 0) // string sonu ve quote açık kalma durumu son harfi almıyor
		{
			if (data->sng % 2)
				add_back(&data->parse, \
					lstnew(substr(strjoin(data->line, "'"), n, i - n + 2)));
			else if (data->dbl % 2)
				add_back(&data->parse, \
					lstnew(substr(strjoin(data->line, "\""), n, i - n + 2)));
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
	if (ft_strlen(s) < start || len <= 0)
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
