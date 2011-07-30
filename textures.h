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
#include <IL/il.h>

void init_textures();
GLuint load_texture(const char *path);

#endif
