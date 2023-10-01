/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:40:46 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/01 20:30:28 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
//liste fonksiyonları libftden alınıp struct yapısına uygun revize edildi
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

char	*strjoin(char *s1, char *s2)//s1 freelendi
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

char	*s2_strjoin(char *s1, char *s2)
{
	char	*ptr;
	int		i;
	int		a;

	a = 0;
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
	while (s2 && s2[a] != '\0')
		ptr[i++] = s2[a++];
	ptr[i] = '\0';
	free(s1);
	free(s2);
	return (ptr);
}

int	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*substr(char const *s, int start, int len)
{
	char	*ptr;
	int	i;

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

char	*v2_substr(char *s, int start, int len)
{
	char	*ptr;
	int	i;

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
	free(s);
	return (ptr);
}

void	clear_lst(t_parse **lst)
{
	t_parse *cnext;

	cnext = (*lst);
	while (cnext != (NULL))
	{
		cnext = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		(*lst) = cnext;
	}
}

int	strchar(char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			return (i);
	}
	return (-1);
}

int	strmatch(const char *s1, const char *s2)
{
	int	i;
	int	a;

	a = -1;
	i = 0;

	while (s2[++a])
	{
		i = 0;
		while (s1[i])
		{
			if (s1[i] == s2[a])
				return (1);
			i++;
		}
	}
	return (0);
}

char	*str_dup(const char *s1)
{
	char	*cp;
	int	i;

	i = -1;
	cp = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (cp == NULL)
		return (0);
	while (s1[++i])
		cp[i] = s1[i];
	cp[i] = '\0';
	return(cp);
}

void	exit_program(char *str, int i)
{
	printf("%s\n", str);
	exit(i);
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	if (ft_strlen(s1) == 0 && ft_strlen(s2) == 0)
		return (0);
	if (!s1 || !*s1)
		return (1);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	while ( s2[i] && s1[i] && s1[i] == s2[i])
		i++;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	return (1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

int	search(char *detect, char *found)
{
	int	i;
	int	a;

	i = -1;
	while (detect[++i])
	{
		a = 0;
		while (detect[i] && found[a] && detect[i] == found[a])
		{
			i++;
			a++;
		}
		if (found[a] == '\0')
			return (1);
	}
	return(0);
}

int	strrchar(char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == (char)c)
			return (len);
		len--;
	}
	return (-1);
}

static int	countc(char const *a, char b)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (a[i])
	{
		if ((a[i] == b && ((a[i + 1] != '\0') && a[i + 1] != b)))
			count++;
		i++;
	}
	if (a[0] != b)
		count ++;
	return (count);
}

static char	**protect(void)
{
	char	**rtn;

	rtn = malloc(1 * sizeof(char *));
	rtn[0] = NULL;
	return (rtn);
}

char	**libft_split(char *s, char c)
{
	int		i;
	int		a;
	int		count;
	int		n;
	char	**ptr;

	a = 0;
	i = 0;
	n = 0;
	if (!s || s[0] == 0)
		return (protect());
	count = countc(s, c);
	ptr = malloc((count + 1) * sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	while (a < count)
	{
		while (s[i] == c)
			i++;
		n = i;
		while (s[i] != c && s[i])
			i++;
		ptr[a++] = substr(s, n, i - n);
	}
	return (ptr);
}
