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

#include <time.h>

#include "vertex_buffer.h"
#include "physic_engine.h"

typedef struct{
    particle_t *src_buf;
    particle_t *dst_buf;
    unsigned long count;
    float dt;
} simulation_t;

simulation_t *create_simulation();
void destroy_simulation(simulation_t *simulation);
void fill_simulation(simulation_t *simulation);
void run_simulation(simulation_t *simulation);
void draw_objects(simulation_t *simulation, buffer_t buffer);

#endif
