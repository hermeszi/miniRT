/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:43:25 by jngew             #+#    #+#             */
/*   Updated: 2025/06/28 17:26:05 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

t_hit	intersect_cylinder(t_ray ray, t_cylinder cylinder)
{
    t_hit	hit;
    
    (void) ray;
    (void) cylinder;
    hit.hit = 0;
    return (hit);
}
