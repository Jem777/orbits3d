/*
 * =====================================================================================
 *
 *       Filename:  textures.c
 *
 *    Description:  loads textures into opengl
 *
 *        Version:  1.0
 *        Created:  27.07.2011 22:03:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jem
 *        Company:  
 *
 * =====================================================================================
 */

#include "textures.h"

GLuint load_texture(const char *path) {
    return SOIL_load_OGL_texture (path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}

void unload_texture(GLuint image) {
    glDeleteTextures(1, &image);
}
