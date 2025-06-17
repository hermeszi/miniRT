/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:13:00 by myuen             #+#    #+#             */
/*   Updated: 2025/06/17 16:24:29 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

t_mat3	mat3_from_vectors(t_vec3 right, t_vec3 up, t_vec3 forward)
{
	t_mat3	m;
	m.col[0] = right;
	m.col[1] = up;
	m.col[2] = forward;
	return (m);
}
t_vec3	mat3_multiply_vec3(t_mat3 m, t_vec3 v)
{
	t_vec3	res;

	res.x = m.col[0].x * v.x + m.col[1].x * v.y + m.col[2].x * v.z;
	res.y = m.col[0].y * v.x + m.col[1].y * v.y + m.col[2].y * v.z;
	res.z = m.col[0].z * v.x + m.col[1].z * v.y + m.col[2].z * v.z;
	return (res);
}
