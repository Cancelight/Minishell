/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:40:46 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/14 18:10:26 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lib.h"

t_data *g_data;

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

char	*substr(char *s, int start, int len) // genel
{
	char	*ptr;
	int		i;

	if (!s)
		return (0);
	if (ft_strlen(s) < start || len <= 0)
		return (0);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	i = 0;
	ptr = malloc((len + 1) * sizeof(char));
	ptr[len] = '\0';
	if (!ptr)
		return (NULL);
	ptr[len] = 0;
	while (i < len)
		ptr[i++] = s[start++];
	return (ptr);
}

int	strchar(char *s, int c)//genel
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

int	strmatch(const char *s1, const char *s2) //syntax control
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
