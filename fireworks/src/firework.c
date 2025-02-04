#include "firework.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "ltrans.h"
#include "timedata.h"

#define SPOKE_MAX 32

static float get_rand(float min, float max) {
  return (((float)rand() / (float)RAND_MAX) * (max - min)) + min;
}

static LMVec3 color_options[8] = {
  {0.1f, 0.6f, 0.1f},
  {0.3f, 0.1f, 0.2f},
  {0.5f, 0.6f, 0.2f},
  {0.1f, 0.4f, 0.8f},
  {0.1f, 0.7f, 0.6f},
  {0.5f, 0.2f, 0.8f},
  {0.3f, 0.2f, 0.1f},
  {0.5f, 0.2f, 0.3f},
};

firework_t firework_create(float x) {
  float a = get_rand(0.3f, 0.8f);
  float b = get_rand(0.3f, 0.8f);

  float x10 = x / 5.0f;;
  float rx = get_rand(-x + x10, x - x10);
  float rh = get_rand(-1.0f + 0.66f, 1.0f - 0.33f);

  float scale = get_rand(0.5f, 1.2f);
  float rotation = get_rand(0.0f, M_PI * 2.0f);
  float speed = get_rand(0.5f, 0.7f);

  int spokes = 12 + (rand() % (SPOKE_MAX - 12));
  int color = rand() % 8;

  firework_t firework = {
    .a = a,
    .b = b,
    .scale = scale,
    .rotation = rotation,
    .stage = 1,
    .x = rx,
    .h = rh,
    .lifetime = 1.0f,
    .speed = speed,
    .spokes = spokes,
    .vbuffer = 0,
    .used_points = 0,
    .color = {color_options[color].x, color_options[color].y, color_options[color].z},
  };

  glGenBuffers(1, &firework.vbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, firework.vbuffer);
  glBufferData(GL_ARRAY_BUFFER, SPOKE_MAX * 7 * 4 * sizeof(float), NULL, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  return firework;
}

void firework_update(firework_t *firework) {
  TimeData td = time_get();
  float pos[SPOKE_MAX * (3 + 4) * 4] = {0};
  firework->used_points = 0;
  
  if (firework->stage == 1) {
    for (int i = 0; i < 4; i++) {
      int idx = i * 7;
      float trail_delay = (1.0f - firework->lifetime) - (i * 0.05f);
      trail_delay = min(1.0f, trail_delay);
      pos[idx + 0] = firework->x;
      pos[idx + 1] = lmLerp(-1.0f, firework->h, trail_delay);
      pos[idx + 2] = firework->h;

      pos[idx + 3] = firework->color[0];
      pos[idx + 4] = firework->color[1];
      pos[idx + 5] = firework->color[2];
      pos[idx + 6] = 1.0f - (i * 0.2f);

      if (trail_delay > 0.9f) {
	pos[idx + 6] = min(pos[idx + 6], lmLerp(pos[idx + 6], 0.0f, 10.0f * (trail_delay - 0.9f)));
      }
    }

    firework->used_points = 4;
  }

  if (firework->stage == 2) {
    for (int s = 0; s < firework->spokes; s++) {
      LMMat4 rot = ltRotateZ(firework->rotation);
      double rad = (double)s / (double)firework->spokes * M_PI * 2;
      LMVec4 start = {firework->x, firework->h, firework->h, 1.0f};
      LMVec4 end = {
          .x = firework->a * cos(rad),
          .y = firework->b * sin(rad),
          .z = start.z,
          .w = 1.0f,
      };
      end = lmVec4Add(start, lmVec4MatMult(end, rot));

      for (int i = 0; i < 4; i++) {
	int idx = (s * 28) + (i * 7);
	float trail_delay = (1.0f - firework->lifetime) - (i * 0.05f);
	trail_delay = min(1.0f, trail_delay);
        LMVec4 loc = lmVec4Lerp(start, end, trail_delay);
        pos[idx + 0] = loc.x;
	pos[idx + 1] = loc.y;
	pos[idx + 2] = loc.z;

	pos[idx + 3] = firework->color[0];
	pos[idx + 4] = firework->color[1];
	pos[idx + 5] = firework->color[2];
	pos[idx + 6] = 1.0f - (i * 0.2f);

	if (trail_delay > 0.9f) {
	  pos[idx + 6] = min(pos[idx + 6], lmLerp(pos[idx + 6], 0.0f, 10.0f * (trail_delay - 0.9f)));
        } else if (trail_delay < 0.1f) {
	  pos[idx + 6] = 0.0f;
	}
      }
    }

    firework->used_points = firework->spokes * 4;
  }

  firework->lifetime -= td.delta_time * firework->speed;
  if (firework->lifetime < -0.2f && firework->stage == 1) {
    firework->stage = 2;
    firework->scale /= 2.0f;
    firework->speed *= 1.25f;
    firework->lifetime = 1.0f;
  }

  if (firework->used_points > 0) {
    glBindBuffer(GL_ARRAY_BUFFER, firework->vbuffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, firework->used_points * 7 * sizeof(float), pos);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
}

int firework_is_done(firework_t *firework) {
  return firework->lifetime < -0.2f && firework->stage == 2;
}
