/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:34:25 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/14 17:44:15 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lib.h"

t_data	*g_data;

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
