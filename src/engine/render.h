#ifndef RENDER_H
#define RENDER_H

#include "../../lib/C-Personal-Utils/types.h"
#include <SDL2/SDL.h>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <cglm/cglm.h>



typedef struct render_state {
  SDL_Window *window;
  f32 width;
  f32 height;
}Render_state;

void render_init(void);
void render_begin(void);
void render_end(void);
void render_quad(vec2 pos, vec2 size, vec4 color);

#endif
