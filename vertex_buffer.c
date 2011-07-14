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

buffer_t create_vbo() {
    buffer_t buffer;
    unsigned short indices[26] = {
        2,0,8,4,10,1,
        3,11,7,9,2,0,
        5,2,8,10,3,7,2,
        6,0,9,11,1,4,0
    };
    float phi = 0.5 * (1 + sqrt(5));
    GLfloat vertices[36] = {
        0, 1, phi, 
        0, 1, -phi,
        0, -1, phi,
        0, -1, -phi,
        1, phi, 0,
        1, -phi, 0,
        -1, phi, 0,
        -1, -phi, 0,
        phi, 0, 1,
        -phi, 0, 1,
        phi, 0, -1,
        -phi, 0, -1
    };
    buffer.indices = indices;
    buffer.vertices = vertices;

    glGenBuffers(1, &buffer.vertex_vboid);
    glBindBuffer(GL_ARRAY_BUFFER, buffer.vertex_vboid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12 * 3, &buffer.vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &buffer.index_vboid);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.index_vboid);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * 26, buffer.indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, buffer.vertex_vboid);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, 0);   //The starting point of the VBO, for the vertices

    return buffer;
}

void draw_vbo(buffer_t buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, buffer.vertex_vboid);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.index_vboid);
    glDrawElements(GL_TRIANGLE_STRIP, 12, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
    glDrawElements(GL_TRIANGLE_FAN, 7, GL_UNSIGNED_SHORT, BUFFER_OFFSET(12 * 2));
    glDrawElements(GL_TRIANGLE_FAN, 7, GL_UNSIGNED_SHORT, BUFFER_OFFSET(19 * 2));
}

void destroy_vbo(buffer_t buffer) {
    glDeleteBuffers(1, &buffer.vertex_vboid);
    glDeleteBuffers(1, &buffer.index_vboid);
}

void draw_vbo_raw(buffer_t buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, buffer.vertex_vboid);
    glDrawArrays(GL_POINTS, 0, 12);
}
