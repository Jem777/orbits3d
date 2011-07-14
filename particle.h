/*
 * =====================================================================================
 *
 *       Filename:  particle.h
 *
 *    Description:  manages a particle object
 *
 *        Version:  1.0
 *        Created:  14.07.2011 03:33:00
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

#include <math.h>

#include "vertex_buffer.h"

typedef struct{
    float x,y,z;
    float vx, vy, vz;
    float r,g,b;
    float radius;
    float mass;
} particle_t;

typedef struct{
    particle_t *particles;
    unsigned long count;
    int dt;
} simulation_t;

simulation_t create_simulation();
void destroy_simulation(simulation_t simulation);
void fill_simulation(simulation_t simulation);
void draw_objects(simulation_t simulation, buffer_t buffer);
#endif
