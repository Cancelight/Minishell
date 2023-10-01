/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:21:50 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/01 20:20:40 by bkiziler         ###   ########.fr       */
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
			heredoc_list(g_data->parse);
			// node içeriğine git include'dan bak -Alp
			//Bağlı listenin yapısı örnek commandline = "ls << a | grep a"
			//node 1 = ls << a ->next node2
			//node 2 = | ->next node 3
			//node 3 = grep a->next'i null bunu biliyorsun demi ali -Alp
			//parserdan böyle çıkıyor ve sonra heredoc filan çalışıyor
			//burdan sonra sen napiyon biliyon mu akrabam benim
			//while içinde pipe geldiğinde geçerek contenti alıp nav_redirection'a gönderirsen contenti
			//sana double array dönücek execve ye gönderebileceğin.
			//ayrıyeten her nav_redirectiondan return aldığında structta nav_redirectiona gönderilen son komut line'ın
			//input ve output dosyalarının isimleri  structtan (g_data->input_file ve g_data->output_file) alınıp işlenebilir
			//outputta append olup olmadığını belirtmek için append_flag vardır, kullanılmadığında -1,
			//append_redirection varsa 1, append redirection yoksa 0 değerlerini alır.
			//alınan dosyaları değiştirmek için dup2 fonksiyonunu şudur:

			//redirectionı kaldırılmış ve double arraye çevirilmiş halidir kullanım while örneği:
			//(parse exec kısmı bittikten sonra freeleniyor, free yazmana gerek yok).
			while (g_data->parse != NULL)
			{
				char *output;
				char *input;
				char **command_line;
				if (g_data->parse->content[0] != '|') //pipelar direkt atlanabilir
					command_line = nav_redirection(g_data->parse->content);
				output = g_data->output_file;
				input = g_data->input_file;
				g_data->parse = g_data->parse->next;
				g_data->append_flag = -1;
			}
			//buradan itibaren execten sonra çalışacak genel freeleme ve yeni komut line alma işlemi süreci başlıyor
			if (!(g_data->sng % 2) && !(g_data->dbl % 2))
				free(g_data->line);
			clear_lst(&(g_data->parse));
			system("leaks minishell");
		}
	}
}
