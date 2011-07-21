/*
 * =====================================================================================
 *
 *       Filename:  physic_engine.c
 *
 *    Description:  implementes the physics simulation
 *
 *        Version:  1.0
 *        Created:  20.07.2011 21:39:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jem
 *        Company:  
 *
 * =====================================================================================
 */

#include "physic_engine.h"

vec3f calc_force(particle_t *a, particle_t *b) {
    float grav_const = 0.001;
    vec3f force = vec_subtract(b->position, a->position);
    float square_r = vec_square(force);
    // Force = gamma * m1 * m2 / r^2
    // scaling: b - a / |b - a|
    return vec_scale(force, grav_const * a->mass * b->mass / (square_r * sqrt(square_r)));
}

int check_collision(particle_t *a, particle_t *b) {
    float distance = a->radius + b->radius;
    if (vec_square(vec_subtract(a->position, b->position)) <= distance*distance) {
        return 1;
    }
    return 0;
}

void collide_particles(particle_t *array, unsigned int count) {
    for (unsigned int i = 0; i < count-1; i++) {
        for (unsigned int j = i+1; j < count; j++) {
            elastic_collision(&array[i], &array[j]);
        }
    }
}

void elastic_collision(particle_t *a, particle_t *b) {
    if (!check_collision(a, b)) {
        return;
    }
    vec3f a2_v;
    vec3f b2_v;
    vec3f a_p = a->position;
    vec3f a_v = a->velocity;
    float a_m = a->mass;
    vec3f b_p = b->position;
    vec3f b_v = b->velocity;
    float b_m = b->mass;
    vec3f normal_vector = vec_subtract(b_p, a_p);
    normal_vector = vec_scale(normal_vector, 1 / vec_abs(normal_vector));
    //transform coordinates, so that b_v = 0
    a_v = vec_subtract(a_v, b_v);
    //calculate angle between a and b
    float cos_phi = fabsf(vec_dot(a_p, normal_vector)) / (vec_abs(a_p) * vec_abs(normal_vector));
    //a little trigonometry to calc v_b'
    b2_v = vec_scale(normal_vector, vec_abs(a_v) * cos_phi);
    //impulse conservation: m_a * v_a = m_a * v_a2 + m_b * v_b2
    a2_v = vec_subtract(a_v, vec_scale(b2_v, b_m / a_m));
    //back transformation
    a2_v = vec_add(a2_v, b_v);
    b2_v = vec_add(b2_v, b_v);
    a->velocity = a2_v;
    b->velocity = b2_v;
}

void inelastic_collision(particle_t *a, particle_t *b) {
    if (!check_collision(a, b)) {
        return;
    }
    float mass = a->mass + b->mass;
    // m_a * v_a + m_b * v_b = (m_a + m_b) v_r
    a->velocity = vec_scale(vec_add(vec_scale(a->velocity, a->mass), vec_scale(b->velocity, b->mass)), 1 / mass);
    // pos_a = center of mass
    a->position = vec_scale(vec_add(a->position, b->position), 0.5); // not com
    // m_r = m_a + m_b
    a->mass = mass;
}
