/*
 * =====================================================================================
 *
 *       Filename:  matrix.c
 *
 *    Description:  basic matrix operations
 *
 *        Version:  1.0
 *        Created:  23.07.2011 04:17:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "matrix.h"

GLfloat *create_matrix() {
    GLfloat *return_value = malloc(sizeof(GLfloat) * 16);
    GLfloat identity[] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    memcpy(return_value, identity, sizeof(GLfloat) * 16);
    return return_value;
}

void destroy_matrix(GLfloat *matrix) {
    //you have to free your mind, neo
    free(matrix);
}

void load_identity(GLfloat matrix[16]) {
	matrix[0] = 1.0f;
	matrix[1] = 0.0f;
	matrix[2] = 0.0f;
	matrix[3] = 0.0f;

	matrix[4] = 0.0f;
	matrix[5] = 1.0f;
	matrix[6] = 0.0f;
	matrix[7] = 0.0f;

	matrix[8] = 0.0f;
	matrix[9] = 0.0f;
	matrix[10] = 1.0f;
	matrix[11] = 0.0f;

	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;
}

void multiply_matrix(GLfloat matrix[16], GLfloat matrix0[16], GLfloat matrix1[16]) {
    GLuint i;
    GLuint k;

    GLfloat temp[16];

    for (i = 0; i < 16; i++) {
        temp[i] = 0.0f;
        for (k = 0; k < 4; k++) {
            //			  		row   column   		   row column
            temp[i] += matrix0[(i % 4) + (k * 4)] * matrix1[(k) + ((i / 4) * 4)];
        }
    }

    for (i = 0; i < 16; i++) {
        matrix[i] = temp[i];
    }
}

void translate(GLfloat matrix[16], GLfloat x, GLfloat y, GLfloat z) {
    GLfloat temp[16];
    load_identity(temp);

    temp[12] += x;
    temp[13] += y;
    temp[14] += z;
    multiply_matrix(matrix, matrix, temp);
}

void scale(GLfloat *matrix, GLfloat x, GLfloat y, GLfloat z) {
    GLfloat temp[16];

    load_identity(temp);

    temp[0] = x;
    temp[5] = y;
    temp[10] = z;

    multiply_matrix(matrix, matrix, temp);
}

void rotate(GLfloat *matrix, GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
	GLfloat temp[16];

	GLfloat s = sinf(2.0f * (float)M_PI * angle / 360.0f);
	GLfloat c = cosf(2.0f * (float)M_PI * angle / 360.0f);

    vec3f vector = vec_create(x, y, z);
    vec_normal(vector);

	x = vector.x;
	y = vector.y;
	z = vector.z;

	load_identity(temp);

	temp[0] = x * x * (1 - c) + c;
	temp[1] = x * y * (1 - c) + z * s;
	temp[2] = x * z * (1 - c) - y * s;

	temp[4] = x * y * (1 - c) - z * s;
	temp[5] = y * y * (1 - c) + c;
	temp[6] = y * z * (1 - c) + x * s;

	temp[8] = x * z * (1 - c) + y * s;
	temp[9] = y * z * (1 - c) - x * s;
	temp[10] = z * z * (1 - c) + c;

	multiply_matrix(matrix, matrix, temp);
}

