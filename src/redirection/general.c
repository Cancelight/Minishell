/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:11:59 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/14 17:43:43 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lib.h"

t_data *g_data;

char	**nav_redirection(char *content)
{
	int	i;
	char **return_array;
	char *temp;

	temp = ft_strdup(content);
	i = -1;
	while (temp[++i] )
	{
		if (temp[i] == '\'')
			i += strchar(&temp[i + 1], '\'') + 2;
		else if (temp[i] == '"')
			i += strchar(&temp[i + 1], '"') + 2;
		else if (temp[i] == '<')
			i = input_redirection(temp, ++i);
		else if (temp[i] == '>' && temp[i + 1] == '>')
			i = append_redirection(temp, i + 2);
		else if (temp[i] == '>' && temp[i + 1] != '>')
			i = output_redirection(temp, ++i);
	}
	if (strrchar(temp, '<') != 0 && \
		temp[strrchar(temp, '<') - 1] == '<') //tüm content döndükten sonra en sondaki '<' sembol heredocsa inputu dğeiştiriyor
		change_data_input(open("heredoc", O_RDWR | O_TRUNC, 0777));
	temp = remove_redirection(temp, 0);
	return_array = libft_split(temp, 32);
	free(temp);
	return (return_array);
}

char	*remove_redirection(char *str, char *new)
{
	int		i;
	int		n;

	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == 32)
			i++;
		if (str[i] == '<' || str[i] == '>')
		{
			while (str[i] == 32 || str[i] == '<' || str[i] == '>')
				i++;
			while (str[i] && str[i] != 32)
				i++;
		}
		else if (str[i])
		{
			n = i;
			while (str[i] && str[i] != '<' && str[i] != '>')
				i++;
			new = s2_strjoin(new, substr(str, n, i - n));
		}
	}
	free(str);
	return (new);
}
