/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaudin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 23:07:25 by ggaudin-          #+#    #+#             */
/*   Updated: 2018/03/05 23:20:47 by jlajovec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

static void		filter(t_env *e, int x, int y, int index)
{
	if (e->sepia == 1)
		sepia(e, x, y, index);
	else if (e->bnw == 1)
		black_white(e, x, y, index);
	else
		no_filter(e, x, y, index);
}

void			put_pixel(t_env *e, int x, int xmax)
{
	int		y;
	int		index;
	int		xtmp;

	y = 0;
	xtmp = x;
	while (y < e->height)
	{
		x = xtmp;
		while (x < xmax)
		{
			index = (x * (e->bpp / 8)) + (y * e->sl);
			if (e->s->anti == 1)
				post_calc_aa(e, x, y);
			filter(e, x, y, index);
			x++;
		}
		y++;
	}
}

void			aff_img(t_env *e)
{
	if (e->lev >= 0)
	{
		mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
		mlx_put_image_to_window(e->mlx, e->win, e->dimg, 1000, 0);
		aff_dash_infos(e);
	}
	else if (e->lev == -1)
		mlx_put_image_to_window(e->mlx, e->win, e->limg, 0, 0);
	mlx_hook(e->win, 4, 1L << 2, mouse_key, e);
	mlx_hook(e->win, 6, 0, mouse_hoover, e);
	mlx_hook(e->win, 2, 0, keyhook, e);
	mlx_hook(e->win, 17, 1L << 0, (void*)closing, e);
	mlx_loop(e->mlx);
}

void			import_ressources(t_env *e)
{
	int		h;
	int		w;
	int		w1;
	int		fd;
	int		fd2;

	w = 300;
	h = 800;
	w1 = 1300;
	e->dimg = mlx_new_image(e->mlx, 300, 800);
	if ((fd = open("./ressources/Dashb.xpm", O_RDONLY)) == -1)
		ft_exit("Ressource Dashb.xpm is missing or chmod is invalid. Exiting.");
	if (mlx_xpm_file_to_image(e->mlx, "./ressources/Dashb.xpm", &w, &h) == NULL)
		ft_exit("Ressource Dashb.xpm is missing or corrupted. Exiting.");
	e->dimg = mlx_xpm_file_to_image(e->mlx, "./ressources/Dashb.xpm", &w, &h);
	e->limg = mlx_new_image(e->mlx, 1300, 800);
	if ((fd2 = open("./ressources/land.xpm", O_RDONLY)) == -1)
		ft_exit("Ressource land.xpm is missing or chmod is invalid. Exiting.");
	if (mlx_xpm_file_to_image(e->mlx, "./ressources/land.xpm", &w1, &h) == NULL)
		ft_exit("Ressource land.xpm is missing or corrupted. Exiting.");
	e->limg = mlx_xpm_file_to_image(e->mlx, "./ressources/land.xpm", &w1, &h);
	close(fd2);
	close(fd);
}

void			init_image(t_env *e)
{
	if (e->flagangle == 0)
	{
		e->factx = e->s->cam_normx;
		e->facty = e->s->cam_normy;
		e->factz = e->s->cam_normz;
		e->flagangle = -1;
	}
	if (e->inits == 0)
	{
		e->mlx = mlx_init();
		e->win = mlx_new_window(e->mlx, 1300, 800, e->s->name);
	}
	e->img = mlx_new_image(e->mlx, 1000, 800);
	e->data = mlx_get_data_addr(e->img, &e->bpp, &e->sl, &e->endn);
	import_ressources(e);
}
