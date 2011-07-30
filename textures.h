/*
 * =====================================================================================
 *
 *       Filename:  textures.h
 *
 *    Description:  loads textures into opengl
 *
 *        Version:  1.0
 *        Created:  27.07.2011 21:54:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jem
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TEXTURES_H_
#define TEXTURES_H_

#define ILUT_USE_OPENGL

#include <stdlib.h>
#include <GL/glew.h>
#include <SOIL/SOIL.h>

GLuint load_texture(const char *path);
void unload_texture(GLuint);

#endif
