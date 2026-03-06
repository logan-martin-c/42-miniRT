/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 17:59:52 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/04 16:43:40 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# define WIN_HEIGHT 720
# define WIN_WIDTH 1280

# define BOUNCES 5
# define SAMPLES 8
//Normalized vectors settings
# define NORM_TOLERANCE 1e-2

// Default cam settings (when not defined in the map)
// --POSITION--
# define CAM_X 0
# define CAM_Y 0
# define CAM_Z 0
// --ROTATION--
# define CAM_PITCH 0 //[0.0-1.0]
# define CAM_YAW 0 //[0.0-1.0]
# define CAM_ROLL 1 //[0.0-1.0]
// --FOV--
# define CAM_FOV 90

// Default light settings (when not defined in the map)
// --POSITION--
# define LIGHT_X 0
# define LIGHT_Y 0
# define LIGHT_Z 0
// --RATIO--
# define LIGHT_RAT 0 //[0.0-1.0]
// --COLOR--
# define LIGHT_R 255
# define LIGHT_G 255
# define LIGHT_B 200

// Default ambient light settings (when not defined in the map)
// --RATIO--
# define A_LIGHT_RAT 1 //[0.0-1.0]
// --COLOR--
# define A_LIGHT_R 255
# define A_LIGHT_G 255
# define A_LIGHT_B 255

# define RENDERING_SQUARE 24
#endif