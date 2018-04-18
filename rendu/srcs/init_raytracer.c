/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raytracer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaudin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 23:18:50 by ggaudin-          #+#    #+#             */
/*   Updated: 2018/02/22 12:10:39 by ggaudin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

static	void		raytracer_loop2(t_env *e)
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
	e->t0 = 0.0f;
}

void				raytracer_loop(t_env *e, int i, int j)
{
	e->pixnormx = (i + 0.500000) / e->r[0]->width;
	e->pixnormy = (j + 0.500000) / e->r[0]->height;
	e->pixremapx = (2.000000 * e->pixnormx - 1.000000) * e->imgratio;
	e->pixremapy = 1.000000 - 2.000000 * e->pixnormy;
	e->pixcamx = e->pixremapx * tan((30.000000 * PI / 180.000000) / 2.000000);
	e->pixcamy = e->pixremapy * tan((30.000000 * PI / 180.000000) / 2.000000);
	e->rayo = vec();
	e->rayo.x = e->r[0]->s->camx + e->r[0]->movex;
	e->rayo.y = e->r[0]->s->camy + e->r[0]->movey;
	e->rayo.z = e->r[0]->s->camz + e->r[0]->movez;
	e->pcamspace.x = e->pixcamx;
	e->pcamspace.y = e->pixcamy;
	e->pcamspace.z = -1;
	rot_y(e);
	rot_x(e);
	rot_z(e);
	raytracer_loop2(e);
}

void				init_raytracer(t_env *e)
{
	e->imgratio = e->r[0]->width / e->r[0]->height;
	e->mint = INFINITY;
	e->t0 = 0.0f;
	e->normal = vec();
	e->diffusecol = col();
	e->speculcol = col();
	e->p0 = vec();
}
