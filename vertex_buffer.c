/*
 * =====================================================================================
 *
 *       Filename:  vertex_buffer.c
 *
 *    Description:  Vertex Buffer Object Module
 *
 *        Version:  1.0
 *        Created:  02.07.2011 16:10:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jem 
 *        Company:  
 *
 * =====================================================================================
 */

#include "vertex_buffer.h"

buffer_t *create_vbo() {
    buffer_t *buffer = malloc(sizeof(buffer_t));

    unsigned int xrange = 20;
    unsigned int yrange = 20;
    unsigned int index = 0;
    unsigned int tex_index = 0;
    unsigned int offset = xrange + 2; // length of one triangle fan
    unsigned int index_count = 2 * offset + 2 * (xrange + 1) * (yrange - 1);
    unsigned int vertex_count = xrange * yrange + 2;
    unsigned short *indices = malloc(sizeof(unsigned short) * index_count);
    GLfloat *vertices = malloc(sizeof(GLfloat) * 3 * vertex_count);
    GLfloat *normals = malloc(sizeof(GLfloat) * 3 * vertex_count);
    GLfloat *tex_coords = malloc(sizeof(GLfloat) * 2 * vertex_count);
    if (buffer == NULL || indices == NULL || vertices == NULL || tex_coords == NULL) {
        return NULL;
    }

    // vertices
    vertices[0] = 0;
    vertices[1] = 0;
    vertices[2] = 1;
    vertices[3] = 0;
    vertices[4] = 0;
    vertices[5] = -1;
    // normal vectors are the same, but without alpha
    normals[0] = 0;
    normals[1] = 0;
    normals[2] = 1;
    normals[3] = 0;
    normals[4] = 0;
    normals[5] = -1;
    // texCoord
    tex_coords[0] = 0.5;
    tex_coords[1] = 0;
    tex_coords[2] = 0.5;
    tex_coords[3] = 1;
    index = 2;
    for (unsigned int y = 0; y < yrange; y++) {
        float theta = M_PI * (float)(y+1) / (yrange+1);
        for (unsigned int x = 0; x < xrange; x++) {
            float phi = 2 * M_PI * (float)x / xrange;
            //polar coordinates
            vertices[index*3] = sin(theta) * cos(phi);
            vertices[index*3+1] = sin(theta) * sin(phi);
            vertices[index*3+2] = cos(theta);
            normals[index*3] = sin(theta) * cos(phi);
            normals[index*3+1] = sin(theta) * sin(phi);
            normals[index*3+2] = cos(theta);
            tex_coords[index*2] = (float)x / xrange;
            tex_coords[index*2+1] = (float)(y+1) / (yrange+1);
            index++;
        }
    }
    indices[0] = 0;
    indices[offset] = 1;
    index = 1;
    for (unsigned int i = 0; i < xrange; i++) {
        indices[index] = i + 2;
        indices[index + offset] = xrange + 1 - i + (yrange-1) * xrange;
        index++;
    }
    indices[index] = 2;
    indices[index + offset] = xrange + 1 + (yrange-1) * xrange;

    index = 2 * offset;
    for (unsigned int y = 0; y < (yrange - 1); y++) {
        for (unsigned int x = 0; x < xrange; x++) {
            indices[index] = (y * xrange) + x + 2;
            indices[index + 1] = ((1+y) * xrange) + x + 2;
            index += 2;
        }
        indices[index] = y * xrange + 2;
        indices[index + 1] = (y+1) * xrange + 2;
        index += 2;
    }

    buffer->indices = indices;
    buffer->vertices = vertices;
    buffer->normals = normals;
    buffer->tex_coords = tex_coords;
    buffer->xrange = xrange;
    buffer->yrange = yrange;

    glGenBuffers(1, &buffer->index_vboid);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->index_vboid);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * index_count, buffer->indices, GL_STATIC_DRAW);

    glGenBuffers(1, &buffer->vertex_vboid);
    glBindBuffer(GL_ARRAY_BUFFER, buffer->vertex_vboid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * vertex_count, &buffer->vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &buffer->normal_vboid);
    glBindBuffer(GL_ARRAY_BUFFER, buffer->normal_vboid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * vertex_count, &buffer->normals[0], GL_STATIC_DRAW);

    glGenBuffers(1, &buffer->tex_coord_vboid);
    glBindBuffer(GL_ARRAY_BUFFER, buffer->tex_coord_vboid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * vertex_count, &buffer->tex_coords[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, buffer->vertex_vboid);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, buffer->normal_vboid);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, buffer->tex_coord_vboid);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

    return buffer;
}

void draw_vbo(buffer_t *buffer) {
    unsigned int fan_length = buffer->xrange + 2;
    unsigned int strip_length = 2 * (buffer->xrange + 1);
    glBindBuffer(GL_ARRAY_BUFFER, buffer->vertex_vboid);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->index_vboid);
    glDrawElements(GL_TRIANGLE_FAN, fan_length, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
    glDrawElements(GL_TRIANGLE_FAN, fan_length, GL_UNSIGNED_SHORT, BUFFER_OFFSET(fan_length));
    for (unsigned int i = 0; i < (buffer->yrange-1); i++) {
        glDrawElements(GL_TRIANGLE_STRIP, strip_length, GL_UNSIGNED_SHORT, BUFFER_OFFSET(i * strip_length + 2 * fan_length));
    }
}

void destroy_vbo(buffer_t *buffer) {
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDeleteBuffers(1, &buffer->vertex_vboid);
    glDeleteBuffers(1, &buffer->normal_vboid);
    glDeleteBuffers(1, &buffer->tex_coord_vboid);
    glDeleteBuffers(1, &buffer->index_vboid);
    //glDeleteVertexArrays(1, &vao);
    free(buffer->vertices);
    free(buffer->normals);
    free(buffer->tex_coords);
    free(buffer->indices);
    free(buffer);
}

void draw_vbo_raw(buffer_t *buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, buffer->vertex_vboid);
    glDrawArrays(GL_POINTS, 0, buffer->xrange * buffer->yrange + 2);
}
