/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaudin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 23:37:47 by ggaudin-          #+#    #+#             */
/*   Updated: 2018/03/02 13:59:03 by agaspard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

void		specular(t_env *e)
{
	t_vec	tmp;
	t_vec	tmp2;
	float	tmpf;
	float	maxcalc;

	tmp = vec();
	tmp = vec_sub(&e->rayo, &e->p0);
	tmp2 = vec();
	tmp2 = vec_normalize(&tmp);
	maxcalc = maxdata(0.0f, dot(e->reflection, tmp2));
	tmp.x = e->speculcol.r * e->lightint.r;
	tmp.y = e->speculcol.g * e->lightint.g;
	tmp.z = e->speculcol.b * e->lightint.b;
	tmpf = (pow(maxcalc, e->shininess));
	e->specular = vec();
	if (e->r[0]->s->shine == 0)
		e->specular = prod_matr(tmpf, &tmp);
	else
		e->specular = vec();
}

void		reflection(t_env *e)
{
	float	tmp1;

	tmp1 = dot(e->lightray, e->normal);
	e->reflection = vec();
	e->reflection.x = (2 * tmp1 * e->normal.x) - e->lightray.x;
	e->reflection.y = (2 * tmp1 * e->normal.y) - e->lightray.y;
	e->reflection.z = (2 * tmp1 * e->normal.z) - e->lightray.z;
	e->reflection = vec_normalize(&e->reflection);
}

void		diffuse(t_env *e)
{
	float	tmpf;
	float	tmp2;
	t_vec	light_dist;
	t_vec	tmp;
	t_vec	n;

	tmp = prod_matr(e->t0, &e->raydir);
	light_dist = vec_add(&e->rayo, &tmp);
	n = vec_sub(&light_dist, &e->lightpos);
	n = prod_matr((sqrtf(dot(n, n))), &e->r[0]->s->forms[e->form_hit]->pos);
	e->coef = dot(n, light_dist);
	e->coef /= 15000.0f;
	tmp2 = dot(e->lightray, e->normal);
	tmpf = maxdata(0.0f, tmp2);
	e->red = (e->red + (e->diffusecol.r * e->lightint.r * tmpf));
	e->green = (e->green + (e->diffusecol.g * e->lightint.g * tmpf));
	e->blue = (e->blue + (e->diffusecol.b * e->lightint.b * tmpf));
}

void		lightset(t_env *e, int i)
{
	e->lightpos = vec();
	e->lightpos.x = e->r[0]->s->forms[i]->pos.x;
	e->lightpos.y = e->r[0]->s->forms[i]->pos.y;
	e->lightpos.z = e->r[0]->s->forms[i]->pos.z;
	e->lightint = col();
	e->lightint.r = e->r[0]->s->forms[i]->col.r;
	e->lightint.g = e->r[0]->s->forms[i]->col.g;
	e->lightint.b = e->r[0]->s->forms[i]->col.b;
	e->lightray = vec();
}

void		ambient_set(t_col c, t_vec ambient)
{
	ambient.x = c.r * 1;
	ambient.y = c.g * 1;
	ambient.z = c.b * 1;
}
