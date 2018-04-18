/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaudin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 23:45:06 by ggaudin-          #+#    #+#             */
/*   Updated: 2018/03/06 11:40:35 by agaspard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

void		norm_calc_plane(t_env *e, t_form *f, t_vec *n)
{
	e->shininess = 128 * e->r[0]->intensity;
	e->diffusecol.r = f->col.r;
	e->diffusecol.g = f->col.g;
	e->diffusecol.b = f->col.b;
	e->speculcol.r = 0.2;
	e->speculcol.g = 0.2;
	e->speculcol.b = 0.2;
	n->x = f->norm.x;
	n->y = f->norm.y;
	n->z = f->norm.z;
}

void		norm_caps(t_env *e, t_form *f, t_vec *n)
{
	t_vec	res_prod;
	t_vec	tmp;
	t_vec	tmp2;
	t_vec	pos_lim;

	res_prod = prod_matr(f->high, &f->norm);
	vec_normalize(&f->norm);
	pos_lim = vec_add(&f->pos, &res_prod);
	tmp = vec_sub(&e->p0, &f->pos);
	tmp2 = vec_sub(&e->p0, &pos_lim);
	if (dot(f->norm, tmp) >= -0.001 && dot(f->norm, tmp) <= 0.001)
		*n = prod_matr(-1.0, &f->norm);
	else if (dot(f->norm, tmp2) >= -0.001 && dot(f->norm, tmp2) <= 0.001)
		*n = f->norm;
}

void		norm_calc_cone_cylinder(t_env *e, t_form *f, t_vec *n)
{
	t_vec	v;
	float	l;
	t_vec	project;

	e->shininess = 128 * e->r[0]->intensity;
	e->diffusecol.r = e->r[0]->bdperlin == 1 ? (f->col.r + (perlin(e->i + 0.5,\
	e->j + 0.5, 10.5) * 0.5)) + 0.4 : f->col.r;
	e->diffusecol.g = e->r[0]->bdperlin == 1 ? (f->col.g + (perlin(e->i + 0.5,\
	e->j + 0.5, 10.5) * 0.5)) + 0.4 : f->col.g;
	e->diffusecol.b = e->r[0]->bdperlin == 1 ? (f->col.b + (perlin(e->i + 0.5,\
	e->j + 0.5, 10.5) * 0.5)) + 0.4 : f->col.b;
	e->speculcol.r = 1.7;
	e->speculcol.g = 1.7;
	e->speculcol.b = 1.7;
	v.x = e->p0.x - f->pos.x;
	v.y = e->p0.y - f->pos.y;
	v.z = e->p0.z - f->pos.z;
	l = dot(v, f->norm);
	project = prod_matr(l, &f->norm);
	*n = vec_sub(&v, &project);
	if (f->form_id == CONE)
		*n = prod_matr(powf(cosf(f->rad * (M_PI * 180.0f)), 2), n);
	if (f->high != 0 && f->form_id != HYPERBOL)
		norm_caps(e, f, n);
	vec_normalize(n);
}

void		norm_calc(t_env *e, t_form *f, t_vec *n)
{
	if (f->form_id == PLANE)
		norm_calc_plane(e, f, &*n);
	else if (f->form_id == SPHERE)
		norm_calc_sphere(e, f, &*n);
	else if (f->form_id == CONE || f->form_id == CYLINDER || \
	f->form_id == HYPERBOL)
		norm_calc_cone_cylinder(e, f, &*n);
}

void		norm_init(t_env *e)
{
	t_vec	tmp;

	tmp = vec();
	tmp = vec_sub(&e->lightpos, &e->p0);
	e->lightray = vec_normalize(&tmp);
	e->normal = vec();
	norm_calc(e, e->r[0]->s->forms[e->form_hit], &e->normal);
	e->normal = vec_normalize(&e->normal);
	e->ambient = vec();
	ambient_set(e->r[0]->s->forms[e->form_hit]->col, e->ambient);
}
