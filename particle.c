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

void debug_particle(particle_t particle);

simulation_t create_simulation() {
    simulation_t simulation;
    simulation.count = 4;
    simulation.particles = malloc(sizeof(particle_t) * simulation.count);
    simulation.dt = 0;
    fill_simulation(simulation);
    return simulation;
}

void destroy_simulation(simulation_t simulation) {
    free(simulation.particles);
}

void fill_simulation(simulation_t simulation) {
    for (unsigned int i = 0; i < simulation.count; i++) {
        particle_t p;
        p.x = 0;
        p.y = 0;
        p.z = i;
        p.vx = 0;
        p.vy = 0;
        p.vz = 0;
        p.r = 1;
        p.g = 0;
        p.b = i / (float)simulation.count;
        p.radius = 0.1*i + 0.1;
        p.mass = 1000;
        simulation.particles[i] = p;
    }
}

void draw_objects(simulation_t simulation, buffer_t buffer) {
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (unsigned int i = 0; i < simulation.count; i++) {
        particle_t p = simulation.particles[i];
        glLoadIdentity();
        glTranslatef(p.x, p.y, p.z);
        glScalef(p.radius/2, p.radius/2, p.radius/2);
        glColor3f(p.r, p.g, p.b);
        draw_vbo(buffer);
    }
}

void debug_particle(particle_t p) {
    printf("x=%f,y=%f,z=%f; r=%f,g=%f,b=%f\n", p.x, p.y, p.z, p.r, p.g, p.b);
}
