#include "vector.h"
#include <math.h>

void vec_fill(vec3f *v, float x, float y, float z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

vec3f vec_scale(vec3f v, float a){
  vec3f r;
  r.x = v.x * a;
  r.y = v.y * a;
  r.z = v.z * a;
  return r;
}
vec3f vec_add(vec3f v, vec3f w){
  vec3f r;
  r.x = v.x + w.x;
  r.y = v.y + w.y;
  r.z = v.z + w.z;
  return r;
}
vec3f vec_subtract(vec3f v, vec3f w){
  vec3f r;
  r.x = v.x - w.x;
  r.y = v.y - w.y;
  r.z = v.z - w.z;
  return r;
}
vec3f vec_negate(vec3f v){
  vec3f r;
  r.x = -v.x;
  r.y = -v.y;
  r.z = -v.z;
  return r;
}
float vec_dot(vec3f v, vec3f w){
  return v.x * w.x + v.y * w.y + v.z * w.z;
}
float vec_abs(vec3f v){
  return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}
float vec_square(vec3f v){
  return v.x*v.x + v.y*v.y + v.z*v.z;
}
