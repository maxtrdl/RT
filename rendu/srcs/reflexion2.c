/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflexion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaspard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 12:02:04 by agaspard          #+#    #+#             */
/*   Updated: 2018/03/06 14:22:57 by agaspard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

void		norm_caps_ref(t_env *e, t_form *f, t_vec *n)
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

void		norm_n(t_env *e, t_vec *n, int i)
{
	n->x = e->r[0]->s->forms[i]->norm.x;
	n->y = e->r[0]->s->forms[i]->norm.y;
	n->z = e->r[0]->s->forms[i]->norm.z;
}

t_vec		getnorm(t_env *e, t_vec newstart, int i, t_vec *p0)
{
	t_vec	n;
	t_vec	v;
	t_vec	project;

	if (e->r[0]->s->forms[i]->form_id == SPHERE)
		n = vec_sub(&newstart, &e->r[0]->s->forms[i]->pos);
	else if (e->r[0]->s->forms[i]->form_id == PLANE)
		norm_n(e, &n, i);
	else
	{
		v = vec_sub(p0, &e->r[0]->s->forms[i]->pos);
		project = prod_matr(dot(v, e->r[0]->s->forms[i]->norm), \
				&e->r[0]->s->forms[i]->norm);
		n = vec_sub(&v, &project);
		if (e->r[0]->s->forms[i]->form_id == CONE)
			n = prod_matr(powf(cosf(e->r[0]->s->forms[i]->rad \
				* (M_PI * 180.0f)), 2), &n);
		if (e->r[0]->s->forms[i]->high != 0)
			norm_caps_ref(e, e->r[0]->s->forms[i], &n);
		vec_normalize(&n);
	}
	return (n);
}

void		round_num(t_vec *v)
{
	int		tmp;

	tmp = (int)(v->x * 1000);
	v->x = tmp / 1000.000;
	tmp = (int)(v->y * 1000);
	v->y = tmp / 1000.000;
	tmp = (int)(v->z * 1000);
	v->z = tmp / 1000.000;
}
