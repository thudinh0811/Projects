#ifndef _FIREWORK_H
#define _FIREWORK_H

#include "glutil.h"

struct firework {
  float x;
  float h;
  
  int stage;
  int spokes;
  float speed;

  float a;
  float b;

  float scale;
  float rotation;

  float lifetime;

  GLuint vbuffer;
  int used_points;

  float color[3];
};

typedef struct firework firework_t;

firework_t firework_create(float x);
void firework_update(firework_t* firework);
int firework_is_done(firework_t* firework);

#endif
