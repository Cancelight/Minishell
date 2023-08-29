/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:30:38 by bkiziler          #+#    #+#             */
/*   Updated: 2023/08/29 14:48:58 by bkiziler         ###   ########.fr       */
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
			free(g_data->line);
			clear_lst(&(g_data->parse));
		}
	}
}
