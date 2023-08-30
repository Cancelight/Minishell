/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:47:20 by bkiziler          #+#    #+#             */
/*   Updated: 2023/08/30 13:10:24 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_data *g_data;

void	syntax_check(t_parse *parse)
{
	t_parse	*temp;

	temp = parse;
	while(temp != NULL)
	{
		if (multiple_pipes(temp))
			exit_program(-1);//değiştirilecek exit fonksiyonu yazılabilir
		else if (strmatch(temp->content, "<>"))
			pre_trim(temp->content);
		temp = temp->next;
	}
	free(temp);
}

int	multiple_pipes(t_parse *temp)
{
	if (temp->next != NULL && temp->content[0] == '|' && temp->next->content[0] == '|')
		return(1);
	else if (temp->content[0] == '|' && temp->next == NULL) // bu durum olduğunda bash komutu tamamlamanı bekliyor ben ne yapmalıyım syntax error mu sonraya mı bırakmalı
		return(1);
	else
		return (0);
}

void	pre_trim(char *find)
{
	int	i;

	i = -1;
	while(find[++i])
	{
		if (find[i] == '\'')
			i = strchar(&find[++i], '\'') + 1;
		else if (find[i] == '"')
			i = strchar(&find[++i], '"') + 1;
		else if (find[i] == '<')
			i += syntax_redirection(&find[i], '<') + 1;
		else if (find[i] == '>')
			i += syntax_redirection(&find[i], '>') + 1;
	}
}

int syntax_redirection(char *str, char symbol)
{
	int		i;
	char	rev_sym;

	i = 0;
	if (symbol == '<')
		rev_sym = '>';
	else
		rev_sym = '<';
	if (str[i] == symbol)
	{
		i++;
		if (str[i] == '\0' || str[i] == rev_sym)
			exit_program(-1);
		if (str[i] == symbol)
			i++;
		while (str[i] && str[i] == 32)
			i++;
		if (str[i] == '\0' || str[i] == symbol || str[i] == rev_sym)
			exit_program(-1);
	}
	return (i);
}
