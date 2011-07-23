#ifndef VECTOR_H_
#define VECTOR_H_

#include <math.h>

typedef struct{
  float x;
  float y;
  float z;
} vec3f;

typedef struct{
  double x;
  double y;
  double z;
} vec3d;

vec3f vec_create(float x, float y, float z);
void vec_fill(vec3f *v, float x, float y, float z);
vec3f vec_scale(vec3f, float);
vec3f vec_add(vec3f, vec3f);
vec3f vec_subtract(vec3f, vec3f);
vec3f vec_negate(vec3f);
float vec_dot(vec3f, vec3f);
float vec_abs(vec3f);
float vec_square(vec3f);
vec3f vec_normal(vec3f v);

#endif
