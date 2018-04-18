/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaudin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 22:24:27 by ggaudin-          #+#    #+#             */
/*   Updated: 2018/03/06 16:59:19 by agaspard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

void		stock_params(t_env *e, char *line, int line_nb)
{
	int		i;
	int		len;

	i = 0;
	len = ((int)ft_strlen(line) + 1);
	if ((e->map[line_nb] = (char*)malloc(sizeof(char) * (len + 1))) == 0)
		ft_exit("Second map malloc failed");
	while (line[i])
	{
		e->map[line_nb][i] = line[i];
		i++;
	}
	e->map[line_nb][i] = '\0';
}

void		parser(t_env *e, int fd)
{
	char	*line;

	e->param = 0;
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		e->param++;
		if ((int)ft_strlen(line) > 200)
			ft_exit("Please input a valid config file.");
		free(line);
	}
	if ((e->map = (char**)malloc(sizeof(char*) * e->param)) == 0)
		ft_exit("First map mallocation failed");
	e->param = 0;
	line = NULL;
	while (get_next_line(e->fd, &line) > 0)
	{
		stock_params(e, line, e->param);
		e->param++;
		free(line);
	}
}
