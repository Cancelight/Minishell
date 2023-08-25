/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:13:25 by bkiziler          #+#    #+#             */
/*   Updated: 2023/08/25 20:28:48 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_data	*data;

int	main(int argc, char **argv, char **envp)
{
	data = malloc(sizeof(t_data) * 1);
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	reading_line();
	signal_function();//şimdilik çalışmıyor projenin ana hatları bitince yazılacak
}

void	reading_line(void)
{
	t_parse *temp;

	while (1)
	{
		data->line = readline("minishell > ");
		if (data->line && *(data->line))
		{
			add_history(data->line);
			parser();
			syntax_check(data->parse);
			free(data->line);
		/*	while(data->parse != NULL) //her alınan satırdan sonra freelemek için yapılandırma gerekiyor
			{
				temp = data->parse;
				data->parse = data->parse->next;
				//free(temp->content);
				free(temp);
			}*/
		}
	}
			//system("leaks a.out");
}

void	parser(void)
{
	data->sng = 0;//single quote için
	data->dbl = 0;//double quote için
	ft_split();
	/*while (data->parse != NULL) //düzgün parse yapıp yapmama durumunu kontrol için, leake neden olan kısım bu
	{
		printf("content: %s\n", data->parse->content);
		data->parse = data->parse->next;
	}*/
}

void	ft_split(void)
{
	int	i;
	int	n;

	i = -1;
	n = 0;
	while (data->line[++i])
	{
		if (data->line[i] == '\'' && !(data->dbl % 2))//double quote açık değilse arttırılacak "bvjhwbshje'gjheuır" gibi durumlardan kaçınmak için
			data->sng++;
		else if (data->line[i] == '"' && !(data->sng % 2)) //eğer  single quoteun içinde değilse arttırılmalı
			data->dbl++;
		else if (data->line[i] == '|' && !(data->sng % 2) && !(data->dbl % 2))//quotelardan herhangi biri açık değilse pipe olarak görüyor
			addlist_substr(i, &n); //satır sınırı nedeniyle yazıldı
		if (data->line[i + 1] == 0) // stringin son kısmını yazdırıyor ve quote açık kalma durumunda quote tamamlıyor
		{
			if (data->sng % 2)
				add_back(&data->parse, \
					lstnew(substr(strjoin(data->line, "'"), n, i - n + 2)));
			else if (data->dbl % 2)
				add_back(&data->parse, \
					lstnew(substr(strjoin(data->line, "\""), n, i - n + 2)));
			else
				add_back(&data->parse, lstnew(substr(data->line, n, i - n + 1)));
		}
	}
}

void	addlist_substr(int i, int *n)
{
	add_back(&data->parse, lstnew(substr(data->line, *n, i - *n))); // "||" durumunda bu satıra girecek ama returnlerden dolayı bir şey olmayacak
	add_back(&data->parse, lstnew("|")); //pipetan sonra null gelirse ne olacak ?
	*n = i + 1;
}

void	syntax_check(t_parse *parse)
{
	while(parse != NULL)
	{
		if (multiple_pipes(parse))
			exit(0);//değiştirilecek exit fonksiyonu yazılabilir
		else if (strmatch(parse->content, "<>"))
			pre_trim(parse->content);
		parse = parse->next;
	}
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
		if (find [i] == '\'')
			i = strchar(&find[++i], '"');
		else if (find [i] == '"')
			i = strchar(&find[++i], '"');
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
			exit(-1);
		if (str[i] == symbol)
			i++;
		while (str[i] && str[i] == 32)
				i++;
		if (str[i] == '\0' || str[i] == symbol || str[i] == rev_sym)
				exit( -1);
	}
	return (i);
}



int	strchar(char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			return (i);
	}
	return (-1);
}


int	strmatch(const char *s1, const char *s2)
{
	int	i;
	int	a;

	a = -1;
	i = 0;

	while (s2[++a])
	{
		i = 0;
		while (s1[i])
		{
			if (s1[i] == s2[a])
				return (1);
			i++;
		}
	}
	return (0);
}
