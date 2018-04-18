/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaudin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 23:09:00 by ggaudin-          #+#    #+#             */
/*   Updated: 2018/03/05 15:22:04 by jlajovec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

void		fill_image_light(t_env *e, int f)
{
	e->r[0]->image[e->i][e->j].r = e->r[0]->s->forms[f]->col.r * e->ambient.x;
	e->r[0]->image[e->i][e->j].g = e->r[0]->s->forms[f]->col.g * e->ambient.y;
	e->r[0]->image[e->i][e->j].b = e->r[0]->s->forms[f]->col.b * e->ambient.z;
}

void		fill_image(t_env *e)
{
	t_vec	tmp;

	tmp = vec();
	tmp.x = e->red + e->specular.x;
	tmp.y = e->green + e->specular.y;
	tmp.z = e->blue + e->specular.z;
	e->r[0]->image[e->i][e->j].r = (e->r[0]->image[e->i][e->j].r + tmp.x);
	e->r[0]->image[e->i][e->j].g = (e->r[0]->image[e->i][e->j].g + tmp.y);
	e->r[0]->image[e->i][e->j].b = (e->r[0]->image[e->i][e->j].b + tmp.z);
}

void		light_hit(t_env *e, int f)
{
	t_vec	tmp;

	tmp = vec();
	tmp.x = e->normal.x * 1e-4f;
	tmp.y = e->normal.y * 1e-4f;
	tmp.z = e->normal.z * 1e-4f;
	tmp.x += e->p0.x;
	tmp.y += e->p0.y;
	tmp.z += e->p0.z;
	e->light_hit = intersect(e, &tmp, &e->lightray, e->r[0]->s->forms[f]);
	if (e->light_hit && e->t0 < e->mint)
	{
		e->mint = e->t0;
		e->form_light_hit = f;
	}
}

void		dark_image(t_env *e)
{
	e->r[0]->image[e->i][e->j].r = 0.2 * e->red;
	e->r[0]->image[e->i][e->j].g = 0.2 * e->green;
	e->r[0]->image[e->i][e->j].b = 0.2 * e->blue;
}

void		save_col(t_env *e)
{
	e->red = e->r[0]->image[e->i][e->j].r;
	e->green = e->r[0]->image[e->i][e->j].g;
	e->blue = e->r[0]->image[e->i][e->j].b;
}
