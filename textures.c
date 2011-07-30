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

void init_textures() {
    ilInit();
}

GLuint load_texture(const char *path) {
    ILuint texid;
    ILboolean success;
    GLuint image;
    ilGenImages(1, &texid);
    ilBindImage(texid);
    success = ilLoadImage((const ILstring)path);
    if (!success) {
        printf("Couldn't load texture at %s\n", path);
        exit(1);
    }
    success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
    if (!success) {
        printf("Couldn't convert texture at %s to RGB, uByte\n", path);
        exit(1);
    }
    glGenTextures(1, &image);
    glBindTexture(GL_TEXTURE_2D, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
            ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), 
            GL_UNSIGNED_BYTE, ilGetData());
    ilDeleteImages(1, &texid);
    return image;
}

void unload_texture(GLuint image) {
    glDeleteTextures(1, &image);
}
