/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:21:50 by bkiziler          #+#    #+#             */
/*   Updated: 2023/09/22 19:33:40 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_data *g_data;

void	reading_line(void)
{
	while (1)
	{
		g_data->line = readline("minishell > ");
		if (g_data->line && *(g_data->line))
		{
			add_history(g_data->line);
			parser();
			syntax_check(g_data->parse);
			nav_redirection(g_data->parse);
			if (!(g_data->sng % 2) && !(g_data->dbl % 2))
			{
				printf("%d %d \n",(g_data->sng % 2), (g_data->dbl % 2));
				printf("free öncesi--------------\n");
				free(g_data->line);
			}
			printf("free sonrasi--------------\n");
			/*while (g_data->parse != NULL) //düzgün parse yapıp yapmama durumunu kontrol için, leake neden olan kısım bu
			{
				printf("content: %s\n", g_data->parse->content);
				g_data->parse = g_data->parse->next;
			}*/
			clear_lst(&(g_data->parse)); // abort var
			system("leaks minishell");
		}
	}
}
