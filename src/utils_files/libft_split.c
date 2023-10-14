/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:27:00 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/14 18:10:18 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lib.h"

t_data *g_data;

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
	ptr[count] = 0;
	while (a < count)
	{
		while (s[i] == c && s[i])
			i++;
		n = i;
		while (s[i] != c && s[i])
			i++;
		ptr[a++] = ft_substr(s, n, i - n);
	}
	return (ptr);
}

char	*ft_substr(char *s, int start, int len)
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
	if (!ptr)
		return (NULL);
	ptr[len] = 0;
	while (i < len)
		ptr[i++] = s[start++];
	return (ptr);
}
