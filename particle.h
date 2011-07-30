/*
 * =====================================================================================
 *
 *       Filename:  particle.h
 *
 *    Description:  manages a particle object
 *
 *        Version:  1.0
 *        Created:  27.07.2011 18:58:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jem
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <stdio.h>

#include "vector.h"

typedef struct{
    vec3f position;
    vec3f velocity;
    float r,g,b;
    float radius;
    float mass;
} particle_t;

typedef struct{
    unsigned int texture;
} planet_t;

void debug_particle(particle_t particle);
void integrate(particle_t* src, particle_t* dst, vec3f acceleration, float dt);

#endif
