/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:40:46 by bkiziler          #+#    #+#             */
/*   Updated: 2023/08/23 19:40:54 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lib.h"
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
