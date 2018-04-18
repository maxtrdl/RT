/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaudin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 14:42:57 by ggaudin-          #+#    #+#             */
/*   Updated: 2018/03/06 14:26:50 by agaspard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

int			pos_to_percent(t_env *e, int x, int y, int re)
{
	float	percent;

	percent = 0.0;
	if (e->color_move == 1 && x >= 1010 && x <= 1290 && y >= 550 && y <= 585)
	{
		percent = ((float)x - 1010.00) / (1290.00 - 1010.00);
		if (percent < 0)
			percent = 0;
		if (percent > 1)
			percent = 1;
		colors_gradient(e, percent, 0.0);
		return (re + 1);
	}
	else
		e->color_move = 0;
	return (0);
}

int			mouse_hoover(int x, int y, void *param)
{
	t_env	*e;
	int		re;

	e = (t_env *)param;
	re = 0;
	if (x <= 1000 || y <= 0 || x >= 1300 || y >= 800 || e->choice <= -1 ||
			e->choice >= e->nb_forms)
		return (0);
	if (e->color_move == 1)
		re = pos_to_percent(e, x, y, re);
	if (re > 0)
	{
		mlx_clear_window(e->mlx, e->win);
		mlx_destroy_image(e->mlx, e->img);
		mlx_destroy_image(e->mlx, e->limg);
		init_image(e);
		threads_launch(e);
	}
	return (0);
}

void		effects_stats(t_env *e, int x, int y)
{
	if (x >= 1010 && y >= 410 && x <= 1140 && y <= 465)
		e->s->shadow = (e->s->shadow == 0) ? 1 : 0;
	if (x >= 1160 && y >= 410 && x <= 1290 && y <= 465)
		e->s->shine = (e->s->shine == 0) ? 1 : 0;
	if (x >= 1010 && y >= 490 && x <= 1140 && y <= 540)
		e->bdperlin = (e->bdperlin == 0) ? 1 : 0;
	if (x >= 1160 && y >= 490 && x <= 1290 && y <= 540)
		e->lev = (e->lev <= 1 && e->lev >= 0) ? 2 : 1;
}

void		dash_arrows(int x, int y, t_env *e)
{
	if (e->choice != -1)
	{
		if (x >= 1050 && y >= 104 && x <= 1065 && y <= 122)
			rotformx(e->s->forms[e->choice], -5);
		if (x >= 1025 && y >= 126 && x <= 1050 && y <= 141)
			rotformy(e->s->forms[e->choice], 5);
		if (x >= 1055 && y >= 140 && x <= 1065 && y <= 165)
			rotformx(e->s->forms[e->choice], 5);
		if (x >= 1066 && y >= 126 && x <= 1092 && y <= 141)
			rotformy(e->s->forms[e->choice], -5);
		if (x >= 1018 && y >= 146 && x <= 1045 && y <= 166)
			rotformz(e->s->forms[e->choice], 5);
		if (x >= 1072 && y >= 146 && x <= 1100 && y <= 166)
			rotformz(e->s->forms[e->choice], -5);
	}
}

int			mouse_key_dash(int button, int x, int y, t_env *e)
{
	if (x >= 1000 && y >= 0 && x <= 1300 && y <= 800 && button)
	{
		if (x >= 1020 && y >= 625 && x <= 1085 && y <= 685)
			add_object(e, SPHERE);
		if (x >= 1115 && y >= 625 && x <= 1190 && y <= 685)
			add_object(e, CYLINDER);
		if (x >= 1220 && y >= 625 && x <= 1285 && y <= 685)
			add_object(e, CONE);
		if (x >= 1020 && y >= 725 && x <= 1085 && y <= 785)
			e->sepia = e->sepia == 0 ? 1 : 0;
		if (x >= 1125 && y >= 710 && x <= 1175 && y <= 765)
			e->bnw = e->bnw == 0 ? 1 : 0;
		if (x >= 1225 && y >= 710 && x <= 1275 && y <= 765)
			add_object(e, PLANE);
		if (x >= 1010 && x <= 1290 && y >= 550 && y <= 585)
			e->color_move = (e->color_move == 0) ? 1 : 0;
		dash_arrows(x, y, e);
		effects_stats(e, x, y);
	}
	return (0);
}
