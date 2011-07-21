#ifndef VECTOR_H_
#define VECTOR_H_

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

void vec_fill(vec3f *v, float x, float y, float z);
vec3f vec_scale(vec3f, float);
vec3f vec_add(vec3f, vec3f);
vec3f vec_subtract(vec3f, vec3f);
vec3f vec_negate(vec3f);
float vec_dot(vec3f, vec3f);
float vec_abs(vec3f);
float vec_square(vec3f);

#endif
