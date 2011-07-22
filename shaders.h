/*
 * =====================================================================================
 *
 *       Filename:  shaders.h
 *
 *    Description:  loads vertex- and fragment shaders
 *
 *        Version:  1.0
 *        Created:  22.07.2011 19:16:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jem
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef SHADERS_H_
#define SHADERS_H_

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>

typedef struct{
    GLchar *vertexsource, *fragmentsource;
    GLuint vertex, fragment;
    GLuint program;
} shader_t;

char* filetobuf(char *file);
shader_t *create_shaders();
void destroy_shaders(shader_t *shader);

#endif
