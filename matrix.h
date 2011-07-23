/*
 * =====================================================================================
 *
 *       Filename:  matrix.h
 *
 *    Description:  basic matrix operations
 *
 *        Version:  1.0
 *        Created:  23.07.2011 04:19:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jem
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <GL/glew.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

GLfloat *create_matrix();
void destroy_matrix(GLfloat *matrix);

void load_identity(GLfloat matrix[16]);
void multiply_matrix(GLfloat matrix[16], GLfloat matrix0[16], GLfloat matrix1[16]);
void translate(GLfloat matrix[16], GLfloat x, GLfloat y, GLfloat z);
void scale(GLfloat matrix[16], GLfloat x, GLfloat y, GLfloat z);
void rotate(GLfloat matrix[16], GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

#endif
