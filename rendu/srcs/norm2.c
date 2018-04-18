/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaudin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 23:29:20 by ggaudin-          #+#    #+#             */
/*   Updated: 2018/03/06 11:40:55 by agaspard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

void		norm_calc_sphere(t_env *e, t_form *f, t_vec *n)
{
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
	n->x = e->p0.x - f->pos.x;
	n->y = e->p0.y - f->pos.y;
	n->z = e->p0.z - f->pos.z;
}
