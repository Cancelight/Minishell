/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:49:00 by bkiziler          #+#    #+#             */
/*   Updated: 2023/08/29 18:53:00 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_data *g_data;

void	parser(void)
{
	g_data->sng = 0;//single quote için
	g_data->dbl = 0;//double quote için
	ft_split();
/*	while (g_data->parse != NULL) //düzgün parse yapıp yapmama durumunu kontrol için, leake neden olan kısım bu
	{
		printf("content: %s\n", g_data->parse->content);
		g_data->parse = g_data->parse->next;
	}*/
}

void	ft_split(void)
{
	int	i;
	int	n;

	i = -1;
	n = 0;

	while (g_data->line[++i])
	{
		if (g_data->line[i] == '\'' && !(g_data->dbl % 2))//double quote açık değilse arttırılacak "bvjhwbshje'gjheuır" gibi durumlardan kaçınmak için
			g_data->sng++;
		else if (g_data->line[i] == '"' && !(g_data->sng % 2)) //eğer  single quoteun içinde değilse arttırılmalı
			g_data->dbl++;
		else if (g_data->line[i] == '|' && !g_data->sng % 2 && !g_data->dbl % 2)//quotelardan herhangi biri açık değilse pipe olarak görüyor
			addlist_substr(i, &n); //satır sınırı nedeniyle yazıldı
		if (g_data->line[i + 1] == 0) // stringin son kısmını yazdırıyor ve quote açık kalma durumunda quote tamamlıyor
		{
			if (g_data->sng % 2)
				add_back(&g_data->parse, \
					lstnew(substr(strjoin(g_data->line, "'"), n, i - n + 2)));
			else if (g_data->dbl % 2)
				add_back(&g_data->parse, \
					lstnew(substr(strjoin(g_data->line, "\""), n, i - n + 2)));
			else
				add_back(&g_data->parse, lstnew(substr(g_data->line, n, i - n + 1)));
		}
	}
}

void	addlist_substr(int i, int *n)
{
	add_back(&g_data->parse, lstnew(substr(g_data->line, *n, i - *n))); // "||" durumunda bu satıra girecek ama returnlerden dolayı bir şey olmayacak
	add_back(&g_data->parse, lstnew(put_pipe("|"))); //pipetan sonra null gelirse ne olacak ?
	*n = i + 1;
}
