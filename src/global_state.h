#ifndef GLOBAL_STATE_H
#define GLOBAL_STATE_H

#include "engine/render.h"

typedef struct global {
  Render_state render;
} Global;

extern Global global;

#endif
