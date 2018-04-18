/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaudin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 23:41:56 by ggaudin-          #+#    #+#             */
/*   Updated: 2018/03/06 19:40:00 by jlajovec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

void		closing(t_env *e)
{
	free(e);
	exit(0);
}

void		ft_exit(char *s)
{
	ft_putendl(s);
	exit(EXIT_FAILURE);
}

void		rt(t_env *e)
{
	int		i;

	e->lev = e->s->shine == 0 ? 2 : 1;
	e->width = 1000;
	e->height = 800;
	e->choice = -1;
	e->inits = 0;
	e->lev = -1;
	e->flagangle = 0;
	e->sepia = 0;
	e->bnw = 0;
	e->reflexion = 0;
	e->s->anti = 0;
	e->bdperlin = 0;
	e->reflet = 0.5;
	init_image(e);
	init_main(e);
	i = -1;
	if (!(e->image = (t_col**)malloc(sizeof(t_col*) * (e->width))))
		ft_exit("Error while allocating image memory.");
	while (++i < e->width)
		if (!(e->image[i] = (t_col*)ft_memalloc(sizeof(t_col) * e->height)))
			ft_exit("Error while allocating image memory.");
	e = init_struct(e);
	threads_launch(e);
}

int			main(int ac, char **av)
{
	t_env	*e;
	int		fd;

	if (ac == 2)
	{
		if ((fd = open(av[1], O_DIRECTORY)) < 0)
		{
			if (!(e = (t_env*)malloc(sizeof(t_env))))
				ft_exit("Error while allocating env struct memory.");
			if ((e->fd = open(av[1], O_RDONLY)) == -1)
				ft_exit("File is missing.");
			fd = open(av[1], O_RDONLY);
			if (!(e->s = (t_sce*)malloc(sizeof(t_sce))))
				ft_exit("Error while allocating sce struct memory. ");
			e->s->tmp = NULL;
			parser(e, fd);
			close(e->fd);
			close(fd);
			check_params(e, e->s, e->param);
			rt(e);
		}
	}
	else
		ft_exit("Usage: ./rt [Scene file].");
	return (0);
}
