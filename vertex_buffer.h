/*
 * =====================================================================================
 *
 *       Filename:  vertex_buffer.h
 *
 *    Description:  header file for the vertex buffer
 *
 *        Version:  1.0
 *        Created:  02.07.2011 16:12:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jem
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef VERTEX_BUFFER_H_
#define VERTEX_BUFFER_H_

#include <GL/glew.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_OFFSET(i) ((char *)NULL + 2 * (i))

typedef struct {
    GLfloat *vertices;
    GLfloat *normals;
    GLfloat *tex_coords;
    unsigned short *indices;
    unsigned int xrange;
    unsigned int yrange;
    GLuint vertex_vboid;
    GLuint normal_vboid;
    GLuint tex_coord_vboid;
    GLuint index_vboid;
} buffer_t;

buffer_t *create_vbo();
void destroy_vbo(buffer_t *buffer);
void draw_vbo(buffer_t *buffer);
void draw_vbo_raw(buffer_t *buffer);
#endif
