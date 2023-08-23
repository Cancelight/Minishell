/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:13:25 by bkiziler          #+#    #+#             */
/*   Updated: 2023/08/23 14:54:39 by bkiziler         ###   ########.fr       */
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
		data->line = readline("minihshell > ");
		if (data->line && *(data->line))
		{
			add_history(data->line);
			parser();
			free(data->line);
			//tüm structı freele her saturda işlenen
		}
	}


}

void	parser()
{
	ft_split('|');
	while(data->parse != NULL)
	{
		printf("content: %s\n", data->parse->content);
		data->parse = data->parse->next;
	}

}

//pipe varsa ve quote açıksa devam et değilse nodea al ve pipeı da ayrı bir nodea al
void	ft_split(char c)
{
	int	i;
	int	n;
	int	dbl;
	int	sng;

	i = 0;
	n = 0;
	sng = 0;
	dbl = 0;
	while (data->line[i])
	{
		if (data->line[i] == '\'' && !(dbl % 2))
			sng++;
		else if (data->line[i] == '"' && !(sng % 2)) //eğer quoteun içinde değilse arttıllmalı
			dbl++;
		else if (data->line[i] == c && !(sng % 2) && !(dbl % 2)) //quotelar kapalı ve pipea geldiyse
		{
			lstadd_back(&data->parse, lstnew(substr(data->line, n, i - n))); // "||" durumunda bu satıra girecek ama returnlerden dolayı bir şey olmayacak
			lstadd_back(&data->parse, lstnew("|")); //pipetan sonra null gelirse ne olacak ?
			n = i + 1;
		}
		if (data->line[i + 1] == 0) // string sonu ve quote açık kalma durumu son harfi almıyor
		{
			if (sng % 2)
				lstadd_back(&data->parse, lstnew(substr(ft_strjoin(data->line, "'"), n, i - n + 2)));
			else if (dbl % 2)
				lstadd_back(&data->parse, lstnew(substr(ft_strjoin(data->line, "\""), n, i - n + 2)));
			else
				lstadd_back(&data->parse, lstnew(substr(data->line, n, i - n + 1)));
		}
		i++;
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;

	if (!s1 || !s2)
		return (0);
	ptr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, ft_strlen(s1) + 1);
	ft_strlcat(ptr, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (ptr);
}


size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!dst && !dstsize)
		return (0);
	i = ft_strlen(dst);
	if (i >= dstsize)
		return (ft_strlen(src) + dstsize);
	ft_strlcpy((dst + i), src, dstsize - i);
	return (i + ft_strlen(src));
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int		s1;
	size_t	i;

	i = 0;
	s1 = ft_strlen(src);
	if (!dstsize)
		return (s1);
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (s1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (0);
	ft_memset(ptr, 0, (size * count));
	return (ptr);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	u;
	size_t			i;

	u = c;
	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = u;
		i++;
	}
	return (b);
}
