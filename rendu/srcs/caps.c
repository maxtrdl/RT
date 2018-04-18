/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaspard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:24:22 by agaspard          #+#    #+#             */
/*   Updated: 2018/03/06 10:52:50 by agaspard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

float		caps2(t_env *e, t_vec *rayo, t_vec *raydir, t_form *f)
{
	t_vec	pos_lim;
	t_vec	res_prod;
	t_vec	new_pos;
	t_vec	cap1;
	t_vec	cap2;

	res_prod = prod_matr(f->high, &f->norm);
	if (e->t2 < e->t1 && e->t2 > 0.)
	{
		pos_lim = vec_add(&f->pos, &res_prod);
		res_prod = prod_matr(e->t2, raydir);
		new_pos = vec_add(&*rayo, &res_prod);
		cap2 = vec_sub(&new_pos, &pos_lim);
		if (sqrtf(dot(cap2, cap2)) <= e->rad_form)
			return (e->t2);
	}
	else if (e->t1 > 0. && f->form_id != CONE && e->t2 < e->t1)
	{
		res_prod = prod_matr(e->t1, raydir);
		new_pos = vec_add(&*rayo, &res_prod);
		cap1 = vec_sub(&new_pos, &f->pos);
		if (sqrtf(dot(cap1, cap1)) <= e->rad_form)
			return (e->t1);
	}
	return (0);
}

float		caps(t_env *e, t_vec *rayo, t_vec *raydir, t_form *f)
{
	t_vec	res_prod;
	t_vec	pos_lim;
	t_vec	new_pos;
	t_vec	cap1;

	pos_lim = vec();
	res_prod = prod_matr(f->high, &f->norm);
	if (e->t1 > 0.)
		pos_lim = vec_add(&f->pos, &res_prod);
	if ((e->t1 < e->t2 && e->t1 > 0.) && f->form_id != CONE)
	{
		res_prod = prod_matr(e->t1, raydir);
		new_pos = vec_add(&*rayo, &res_prod);
		cap1 = vec_sub(&new_pos, &f->pos);
		if (sqrtf(dot(cap1, cap1)) <= e->rad_form)
			return (e->t1);
	}
	else if (e->t2 < e->t1 && e->t2 > 0.)
		return (caps2(e, rayo, raydir, f));
	else if (e->t1 > 0. && f->form_id != CONE)
		return (caps2(e, rayo, raydir, f));
	return (0);
}

void		intersect_caps2(t_env *e, t_vec *rayo, t_vec *raydir, t_form *f)
{
	t_vec	res_prod;
	t_vec	pos_lim;

	pos_lim = vec();
	res_prod = prod_matr(f->high, &f->norm);
	if (e->t1 > 0.)
		pos_lim = vec_add(&f->pos, &res_prod);
	e->rad_form = f->rad;
	if (f->form_id == CONE)
		e->rad_form = ((f->rad * (M_PI / 180.0f)) * f->high) * 4;
	e->t1 = ((dot(f->norm, f->pos) - dot(f->norm, *rayo)) /
			dot(f->norm, *raydir));
	e->t2 = ((dot(f->norm, pos_lim) - dot(f->norm, *rayo)) /
			dot(f->norm, *raydir));
}

float		intersect_caps(t_env *e, t_vec *rayo, t_vec *raydir, t_form *f)
{
	t_vec	res_prod;
	t_vec	pos_lim;
	t_vec	new_pos;
	t_vec	cap1;
	t_vec	cap2;

	pos_lim = vec();
	res_prod = prod_matr(f->high, &f->norm);
	if (e->t1 > 0.)
	{
		pos_lim = vec_add(&f->pos, &res_prod);
		res_prod = prod_matr(e->t1, raydir);
		new_pos = vec_add(&*rayo, &res_prod);
		cap1 = vec_sub(&new_pos, &f->pos);
		cap2 = vec_sub(&new_pos, &pos_lim);
		if (dot(f->norm, cap1) > 0. && dot(f->norm, cap2) < 0.)
			return (e->t1);
	}
	intersect_caps2(e, rayo, raydir, f);
	return (caps(e, rayo, raydir, f));
}
