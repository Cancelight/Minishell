/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:13:25 by bkiziler          #+#    #+#             */
/*   Updated: 2023/08/23 13:08:36 by bkiziler         ###   ########.fr       */
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
	while (1)
	{
		data->rd_line = readline("minihshell > ");
		if (data->rd_line && *(data->rd_line))
		{
			add_history(data->rd_line);
			parser();
			free(data->rd_line);
			//tüm structı freele her saturda işlenen
		}
	}


}

void	parser()
{

}

//pipe varsa ve quote açıksa devam et değilse nodea al ve pipeı da ayrı bir nodea al
char	**ft_split(char c)
{
	int	i;
	int	a;
	int	n;
	int	dbl;
	int	sng;

	a = 0;
	i = 0;
	n = 0;
	sng = 0;
	dbl = 0;
	while (data->rd_line[i])
	{
		if (data->rd_line[i] == '\'')
			sng++;
		else if (data->rd_line[i] == '"')
			dbl++;
		else if (data->rd_line[i] == c && !(sng % 2) && !(dbl % 2)) //quotelar kapalı ve pipea geldiyse
		{
			lstadd_back(&data->parse, lstnew(substr(data->rd_line, n, i - n))); // "||" durumunda bu satıra girecek ama returnlerden dolayı bir şey olmayacak
			lstadd_back(&data->parse, lstnew("|"));
			n = i + 1;
		}
		else if ()
		i++;





		n = i;
		while (s[i] != c && s[i])
			i++;
		ptr[a++] = substr(s, n, i - n);
	}
	return (ptr);
}

char	*substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	if (!s)
		return (0);
	if (ft_strlen(s) < start)
		return (0);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	i = 0;
	ptr = ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	ptr[len] = 0;
	while (i < len)
		ptr[i++] = s[start++];
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

void	lstadd_back(t_parse **lst, t_parse *new)
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
		{
			lst = lst -> next;
		}
		return (lst);
	}
	return (0);
}
