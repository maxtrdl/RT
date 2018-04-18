/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrudel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 12:09:45 by mtrudel           #+#    #+#             */
/*   Updated: 2018/03/06 14:27:00 by agaspard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

static	void		raytracer_loop_obj_2(t_env *e)
{
	e->raydir.x = e->pcamspace.x;
	e->raydir.y = e->pcamspace.y;
	e->raydir.z = e->pcamspace.z;
	e->lenvec = 1.0 / sqrt((e->raydir.x * e->raydir.x) + (e->raydir.y * \
				e->raydir.y) + (e->raydir.z * e->raydir.z));
	e->raydir.x = e->raydir.x * e->lenvec;
	e->raydir.y = e->raydir.y * e->lenvec;
	e->raydir.z = e->raydir.z * e->lenvec;
	e->pcamspace.x = e->rayo.x + e->pcamspace.x;
	e->pcamspace.y = e->rayo.y + e->pcamspace.y;
	e->pcamspace.z = e->rayo.z + e->pcamspace.z;
	e->mint = INFINITY;
	e->form_hit = -1;
	e->t0 = INFINITY;
}

static void			raytracer_loop_obj(t_env *e, int i, int j)
{
	e->imgratio = e->width / e->height;
	e->mint = INFINITY;
	e->t0 = INFINITY;
	e->t0p = INFINITY;
	e->normal = vec();
	e->p0 = vec();
	e->pixnormx = (i + 0.500000) / e->width;
	e->pixnormy = (j + 0.500000) / e->height;
	e->pixremapx = (2.000000 * e->pixnormx - 1.000000) * e->imgratio;
	e->pixremapy = 1.000000 - 2.000000 * e->pixnormy;
	e->pixcamx = e->pixremapx * tan((30.000000 * PI / 180.000000) / 2.000000);
	e->pixcamy = e->pixremapy * tan((30.000000 * PI / 180.000000) / 2.000000);
	e->rayo = vec();
	e->rayo.x = e->s->camx + e->movex;
	e->rayo.y = e->s->camy + e->movey;
	e->rayo.z = e->s->camz + e->movez;
	e->pcamspace.x = e->pixcamx;
	e->pcamspace.y = e->pixcamy;
	e->pcamspace.z = -1;
	rothit_y(e);
	rothit_x(e);
	rothit_z(e);
	raytracer_loop_obj_2(e);
}

int					obj_select(t_env *e, int x, int y)
{
	int		hit;
	int		k;

	k = e->s->nb_lights;
	raytracer_loop_obj(e, x, y);
	while (k < e->nb_forms)
	{
		hit = intersect(e, &e->rayo, &e->raydir, e->s->forms[k]);
		if (hit && e->t0 < e->mint)
		{
			e->mint = e->t0;
			e->choice = k;
		}
		else if (hit && e->t0p < e->mint)
		{
			e->mint = e->t0p;
			e->choice = k;
		}
		k++;
	}
	return ((e->choice == -1) ? -1 : e->choice);
}

static	void		mouse_key2(int button, int x, int y, t_env *e)
{
	if (x > 1000 && x <= 1300 && y > 0 && y <= 800 && button == M_LFT
			&& e->lev > -1)
		mouse_key_dash(button, x, y, e);
	if (x > 0 && x <= 1300 && y > 0 && y <= 800)
	{
		mlx_clear_window(e->mlx, e->win);
		mlx_destroy_image(e->mlx, e->img);
		mlx_destroy_image(e->mlx, e->dimg);
		init_image(e);
		threads_launch(e);
	}
}

int					mouse_key(int button, int x, int y, t_env *e)
{
	if (x > 0 && x <= 1000 && y > 0 && y <= 800)
	{
		if (button == M_LFT && e->lev > -1)
		{
			e->lev_tmp = e->lev != 0 ? e->lev : e->lev_tmp;
			e->lev = 0;
			e->choice = obj_select(e, x, y);
		}
		else if (button == M_RGT && e->choice != -1 && e->lev > -1)
		{
			e->lev = e->lev_tmp;
			e->choice = -1;
		}
		else if ((button == M_UP || button == M_DWN) && e->choice != -1
				&& e->lev > -1)
		{
			if (button == M_DWN && e->choice != -1)
				e->s->forms[e->choice]->pos.z += 1;
			if (button == M_UP && e->choice != -1)
				e->s->forms[e->choice]->pos.z -= 1;
		}
	}
	mouse_key2(button, x, y, e);
	return (0);
}
