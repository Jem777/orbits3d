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
void integrate(particle_t* src, particle_t* dst, vec3f acceleration, float dt);

simulation_t *create_simulation() {
    simulation_t *simulation = malloc(sizeof(simulation_t));
    simulation->count = 10;
    simulation->src_buf = malloc(sizeof(particle_t) * simulation->count);
    simulation->dst_buf = malloc(sizeof(particle_t) * simulation->count);
    simulation->dt = 0.01;
    fill_simulation(simulation);
    return simulation;
}

void destroy_simulation(simulation_t *simulation) {
    free(simulation->src_buf);
    free(simulation->dst_buf);
}

float get_random(int max) {
    float number = (float)rand() / RAND_MAX;
    number *= (float)max;
    return number;
}

void fill_simulation(simulation_t *simulation) {
    srand(time(NULL));
    for (unsigned int i = 0; i < simulation->count; i++) {
        particle_t p;
        vec_fill(&p.position, get_random(8)-4, get_random(8)-4, get_random(8)-4);
        vec_fill(&p.velocity, 0, 0, 0);
        p.r = 1;
        p.g = 0;
        p.b = i / (float)simulation->count;
        p.mass = get_random(100) + 10;
        p.radius = 0.004*p.mass;
        simulation->src_buf[i] = p;
        simulation->dst_buf[i] = p;
    }
}

void run_simulation(simulation_t *simulation) {
    collide_particles(simulation->src_buf, simulation->count);
    // iterate through each particle and addup all forces
    for (unsigned int i = 0; i < simulation->count; i++) {
        particle_t *a = &simulation->src_buf[i];
        particle_t *a2 = &simulation->dst_buf[i];
        vec3f forces;
        forces.x = forces.y = forces.z = 0;
        for (unsigned int j = 0; j < simulation->count; j++) {
            if (i != j) {
                particle_t *b = &simulation->src_buf[j];
                forces = vec_add(forces, calc_force(a, b));
            }
        }
        // a = F / m
        vec3f acc = vec_scale(forces, 1 / a->mass);
        integrate(a, a2, acc, simulation->dt);
    }

    // swap buffers
    particle_t *tmp = simulation->src_buf;
    simulation->src_buf = simulation->dst_buf;
    simulation->dst_buf = tmp;
}

void integrate(particle_t *src, particle_t *dst, vec3f acceleration, float dt){
    // euler-cromer method
    // v' = v + a*dt    --    v, v' and a are vectors, dt is a scalar.
    dst->velocity = vec_add(src->velocity, vec_scale(acceleration, dt));
    // x' = x + v'*dt   --    x', x, v' are vectors, dt is a scalar.
    dst->position = vec_add(src->position, vec_scale(dst->velocity, dt));
}

void draw_objects(simulation_t *simulation, buffer_t buffer) {
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (unsigned int i = 0; i < simulation->count; i++) {
        particle_t particle = simulation->src_buf[i];
        vec3f p = particle.position;
        glLoadIdentity();
        glTranslatef(p.x, p.y, p.z);
        glScalef(particle.radius/2, particle.radius/2, particle.radius/2);
        glColor3f(particle.r, particle.g, particle.b);
        draw_vbo(buffer);
    }
}

void debug_particle(particle_t p) {
    vec3f position = p.position;
    printf("x=%f,y=%f,z=%f; r=%f,g=%f,b=%f\n", position.x, position.y, position.z, p.r, p.g, p.b);
}
