/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:35:38 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/14 17:44:05 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lib.h"

t_data	*g_data;

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

char	*ft_strdup(const char *s1)
{
	char	*cp;
	int i = 0;
	cp = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (cp == NULL)
		return (0);
	while(s1[i]){
		cp[i] = s1[i];
		i++;
	}
	return (cp);
}
