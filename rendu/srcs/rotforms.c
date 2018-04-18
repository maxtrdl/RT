/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotforms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaudin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 14:06:52 by ggaudin-          #+#    #+#             */
/*   Updated: 2018/02/22 14:10:45 by ggaudin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

void		rotformz(t_form *f, int a)
{
	t_vec	tmp;
	float	angle;

	angle = a * (M_PI / 180);
	tmp.x = f->norm.x;
	tmp.y = f->norm.y;
	f->norm.x = tmp.x * cos(angle) - tmp.y * sin(angle);
	f->norm.y = tmp.x * sin(angle) + tmp.y * cos(angle);
}

void		rotformx(t_form *f, int a)
{
	t_vec	tmp;
	float	angle;

	angle = a * (M_PI / 180);
	tmp.y = f->norm.y;
	tmp.z = f->norm.z;
	f->norm.y = tmp.y * cos(angle) - tmp.z * sin(angle);
	f->norm.z = tmp.y * sin(angle) + tmp.z * cos(angle);
}

void		rotformy(t_form *f, int a)
{
	t_vec	tmp;
	float	angle;

	angle = a * (M_PI / 180);
	tmp.x = f->norm.x;
	tmp.z = f->norm.z;
	f->norm.x = tmp.x * cos(angle) + tmp.z * sin(angle);
	f->norm.z = ((tmp.x * sin(angle)) * -1) + tmp.z * cos(angle);
}
