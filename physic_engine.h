/*
 * =====================================================================================
 *
 *       Filename:  physic_engine.h
 *
 *    Description:  implementes the physics simulation
 *
 *        Version:  1.0
 *        Created:  20.07.2011 21:37:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jem
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef PHYSICS_H_
#define PHYSICS_H_

#include <math.h>
#include <stdio.h>

#include "vector.h"
#include "particle.h"

vec3f calc_force(particle_t *a, particle_t *b);
int check_collision(particle_t *a, particle_t *b);
void collide_particles(particle_t *array, unsigned int count);
void elastic_collision(particle_t *a, particle_t* b);
void inelastic_collision(particle_t *a, particle_t *b);
#endif
