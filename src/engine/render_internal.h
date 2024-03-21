#ifndef RENDER_INTERNAL_H_INCLUDED
#define RENDER_INTERNAL_H_INCLUDED

#include <SDL2/SDL.h>

#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include "../utils.h"
#include "render.h"
#include "../global_state.h"

typedef struct render_state_internal {
  u32 vao_quad;
  u32 vbo_quad;
  u32 ebo_quad;
  u32 shader_default;
  u32 texture_color;
  vec3 fragColor;
} Render_State_Internal;

SDL_Window *render_init_window(u32 width, u32 height);
void render_init_quad(u32 *vao, u32 *vbo, u32 *ebo);
void render_init_color_texture(u32 *texture, Render_State_Internal *state);
void render_init_shaders(Render_State_Internal *state);
u32 render_shader_create(const char *path_vert, const char *path_frag);

#endif
