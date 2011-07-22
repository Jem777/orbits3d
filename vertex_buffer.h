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
#include <GL/gl.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_OFFSET(i) ((char *)NULL + 2 * (i))

typedef struct {
    GLfloat *vertices;
    unsigned short *indices;
    unsigned short length;
    unsigned short xrange;
    unsigned short yrange;
    GLuint vertex_vboid;
    GLuint index_vboid;
} buffer_t;

buffer_t create_vbo();
void destroy_vbo(buffer_t);
void draw_vbo(buffer_t);
void draw_vbo_raw(buffer_t buffer);
#endif
