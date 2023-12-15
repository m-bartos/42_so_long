/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:10:44 by mbartos           #+#    #+#             */
/*   Updated: 2023/12/12 17:40:13 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

// int pos_y = HEIGHT/2;
// int pos_x = WIDTH/2;

// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

// /**
//  * Creates a 32-bit color value (ARGB format) from individual color components.
//  * @param t The alpha value (transparency) in the range [0, 255].
//  * @param r The red color component in the range [0, 255].
//  * @param g The green color component in the range [0, 255].
//  * @param b The blue color component in the range [0, 255].
//  * @return The combined 32-bit color value in ARGB format (0xTTRRGGBB).
//  */
// int	create_trgb(int t, int r, int g, int b)
// {
// 	return (t << 24 | r << 16 | g << 8 | b);
// }

// // keycode = what is pressed
// // x, y = xy coordinates in mouse position
// int	mouse_click(int keycode, int x, int y, t_data *vars)
// {
// 	if (keycode == 1)
// 	{
// 		ft_putstr_fd("Left click\n", 1);
// 	}
// 	else if (keycode == 2)
// 	{
// 		ft_putstr_fd("Middle click\n", 1);
// 	}
// 	else if (keycode == 3)
// 	{
// 		ft_putstr_fd("Right click\n", 1);
// 	}
// 	else if (keycode == 4)
// 	{
// 		ft_putstr_fd("Scrool up\n", 1);
// 	}
// 	else if (keycode == 5)
// 	{
// 		ft_putstr_fd("Scrool down\n", 1);
// 	}
// 	return (0);
// }

// int	pressed_key(int keycode, t_data *vars)
// {
// 	int x = 10;
// 	int y = 10;
// 	int i = 0;
// 	int j = 0;

// 	ft_putnbr_fd(keycode, 1);
// 	ft_putchar_fd('\n', 1);
// 	vars->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
// 	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel, &vars->line_length, &vars->endian);
// 	while (j < WIDTH)
// 	{
// 		while (i < HEIGHT)
// 			my_mlx_pixel_put(vars, 0 + j, 0 + i++, create_trgb(0, 255-i/4, 255-j/4, 0));
// 		j++;
// 		i = 0;
// 	}
// 	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
// 	if (keycode == XK_w)
// 	{
// 		pos_y -= 50;
// 		vars->img = mlx_xpm_file_to_image(vars->mlx, "./img/Mario.xpm", &x, &y);
// 		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, pos_x, pos_y);
// 	}
// 	else if (keycode == XK_s)
// 	{
// 		pos_y += 50;
// 		vars->img = mlx_xpm_file_to_image(vars->mlx, "./img/Mario.xpm", &x, &y);
// 		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, pos_x, pos_y);
// 	}
// 	else if (keycode == XK_a)
// 	{
// 		pos_x -= 50;
// 		vars->img = mlx_xpm_file_to_image(vars->mlx, "./img/Mario.xpm", &x, &y);
// 		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, pos_x, pos_y);
// 	}
// 	else if (keycode == XK_d)
// 	{
// 		pos_x += 50;
// 		vars->img = mlx_xpm_file_to_image(vars->mlx, "./img/Mario.xpm", &x, &y);
// 		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, pos_x, pos_y);
// 	}
// 	else
// 	{
// 		vars->img = mlx_xpm_file_to_image(vars->mlx, "./img/Mario.xpm", &x, &y);
// 		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, pos_x, pos_y);
// 	}
// 	mlx_string_put(vars->mlx, vars->win, WIDTH * 0.9, HEIGHT * 0.98, create_trgb(0, 0, 255, 0), "Test string!");
// 	return (0);
// }

// int	close_win_key(int keycode, t_data *vars)
// {
// 	if (keycode == XK_Escape)
// 	{
// 		mlx_destroy_image(vars->mlx, vars->img);
// 		mlx_destroy_window(vars->mlx, vars->win);
// 		mlx_destroy_display(vars->mlx);
// 		free(vars->mlx);
// 		exit(0);
// 	}
// 	else
// 		pressed_key(keycode, vars);
// 	return (0);
// }

// int	close_win_cross(int keycode, t_data *vars)
// {
// 	mlx_destroy_image(vars->mlx, vars->img);
// 	mlx_destroy_window(vars->mlx, vars->win);
// 	mlx_destroy_display(vars->mlx);
// 	free(vars->mlx);
// 	exit(0);
// }

// int	main(int argc, char **argv)
// {
// 	t_data	img;
// 	int	i;
// 	int	j;

// 	if (argc == 2)
// 		map_check(argv[1]);
// 	img.mlx = mlx_init();
// 	if (img.mlx == NULL)
// 	{
// 		return (1);
// 	}
// 	img.win = mlx_new_window(img.mlx, WIDTH, HEIGHT, "So Long!");
// 	if (img.win == NULL)
// 	{
// 		mlx_destroy_display(img.mlx);
// 		free(img.mlx);
// 		return (1);
// 	}
// 	mlx_mouse_hide(img.mlx, img.win);
// 	img.img = mlx_new_image(img.mlx, WIDTH, HEIGHT);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
// 	i = 0;
// 	j = 0;
// 	while (j < WIDTH)
// 	{
// 		while (i < HEIGHT)
// 			my_mlx_pixel_put(&img, 0 + j, 0 + i++, create_trgb(0, 255-i/4, 255-j/4, 0));
// 		j++;
// 		i = 0;
// 	}
// 	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
// 	int x = 10;
// 	int y = 10;
// 	img.img = mlx_xpm_file_to_image(img.mlx, "./img/Mario.xpm", &x, &y);
// 	mlx_put_image_to_window(img.mlx, img.win, img.img, pos_x, pos_y);
// 	//clicking any key in the corner of window
// 	mlx_hook(img.win, 2, 1L<<0, close_win_key, &img);
// 	//clicking the CROSS in the corner of window - got segfault - WHY?
// 	mlx_hook(img.win, 17, 1L<<0, close_win_cross, &img);
// 	mlx_mouse_hook(img.win, mouse_click, &img);
// 	mlx_string_put(img.mlx, img.win, WIDTH * 0.9, HEIGHT * 0.98, create_trgb(0, 0, 255, 0), "Test string!");
// 	// keeps the proces alive with looping
// 	mlx_loop(img.mlx);
// 	return (0);
// 	}

// #include <stdio.h>
// // Exit the program as failure.
// static void ft_error(void)
// {
// 	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
// 	exit(EXIT_FAILURE);
// }

// // Print the window width and height.
// static void ft_hook(void* param)
// {
// 	const mlx_t* mlx = param;

// 	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
// }

// int32_t	main(void)
// {

// 	// MLX allows you to define its core behaviour before startup.
// 	mlx_set_setting(MLX_MAXIMIZED, true);
// 	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
// 	if (!mlx)
// 		ft_error();

// 	/* Do stuff */

// 	// Create and display the image.
// 	mlx_image_t* img = mlx_new_image(mlx, 256, 256);
// 	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
// 		ft_error();

// 	// Even after the image is being displayed, we can still modify the buffer.
// 	mlx_put_pixel(img, 0, 0, 0xFF0000FF);

// 	// Register a hook and pass mlx as an optional param.
// 	// NOTE: Do this before calling mlx_loop!
// 	mlx_loop_hook(mlx, ft_hook, mlx);
// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }


int	main (int argc, char **argv)
{
	char	**map_arr;

	if (argc == 2)
	{
		map_arr = map_check(argv[1]);
		free_array(map_arr);
	}
	return (0);
}
