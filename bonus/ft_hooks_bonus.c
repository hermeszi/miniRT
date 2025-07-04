/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:21:07 by myuen             #+#    #+#             */
/*   Updated: 2025/07/04 19:48:51 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt_bonus.h"

int	key_hook(int keycode, t_main *app)
{
	if (keycode == ESC_KEY)
	{
		close_hook(app);
	}
	return (0);
}

int	mouse_hook(int button, int x, int y, t_main *app)
{
	(void)x;
	(void)y;
	(void)app;
	if (button == 4)
		printf("Mouse scroll up - this does nothing.\n");
	else if (button == 5)
		printf("Mouse scroll down - this does nothing.\n");
	else if (button == 1)
		printf("Left click - this does nothing.\n");
	return (0);
}

int	close_hook(t_main *app)
{
	free_all(app);
	exit(EXIT_SUCCESS);
}

void	init_hooks(t_main *app)
{
	mlx_key_hook(app->display->win_ptr, key_hook, app);
	mlx_mouse_hook(app->display->win_ptr, mouse_hook, app);
	mlx_hook(app->display->win_ptr, 17, 0, close_hook, app);
	printf("event hooks set\n");
}
