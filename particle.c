/*
 * =====================================================================================
 *
 *       Filename:  particle.c
 *
 *    Description:  manages the particles
 *
 *        Version:  1.0
 *        Created:  14.07.2011 16:21:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jem
 *        Company:  
 *
 * =====================================================================================
 */

#include "particle.h"

void integrate(particle_t *src, particle_t *dst, vec3f acceleration, float dt){
    // euler-cromer method
    // v' = v + a*dt    --    v, v' and a are vectors, dt is a scalar.
    dst->velocity = vec_add(src->velocity, vec_scale(acceleration, dt));
    // x' = x + v'*dt   --    x', x, v' are vectors, dt is a scalar.
    dst->position = vec_add(src->position, vec_scale(dst->velocity, dt));
}

void debug_particle(particle_t p) {
    vec3f position = p.position;
    printf("x=%f,y=%f,z=%f; r=%f,g=%f,b=%f\n", position.x, position.y, position.z, p.r, p.g, p.b);
}
