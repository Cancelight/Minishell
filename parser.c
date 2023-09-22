/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:49:00 by bkiziler          #+#    #+#             */
/*   Updated: 2023/09/22 19:37:13 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_data *g_data;

void	parser(void)
{
	g_data->sng = 0;//single quote için
	g_data->dbl = 0;//double quote için
	ft_split(0, -1);
/*	while (g_data->parse != NULL) //düzgün parse yapıp yapmama durumunu kontrol için, leake neden olan kısım bu
	{
		printf("content: %s\n", g_data->parse->content);
		g_data->parse = g_data->parse->next;
	}*/
}

void	ft_split(int n, int i)
{
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
					lstnew(v2_substr(strjoin(g_data->line, "'"), n, i - n + 2)));
			else if (g_data->dbl % 2)
				add_back(&g_data->parse, \
					lstnew(v2_substr(strjoin(g_data->line, "\""), n, i - n + 2)));//freeleme konusunda sıkıntı olabilir
			else
				add_back(&g_data->parse, lstnew(substr(g_data->line, n, i - n + 1)));
			break;
		}
	}
}

void	addlist_substr(int i, int *n)
{
	add_back(&g_data->parse, lstnew(substr(g_data->line, *n, i - *n)));
	add_back(&g_data->parse, lstnew(str_dup("|")));
	*n = i + 1;
}
