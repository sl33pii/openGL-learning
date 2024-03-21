#include "../global_state.h"
#include "render.h"
#include "render_internal.h"
#include <OpenGL/OpenGL.h>

static Render_State_Internal state = {0};

void render_init() {
    global.render.width = 800;
	global.render.height = 600;

    global.render.window = render_init_window(global.render.width, global.render.height);
   glViewport(0, 0, global.render.width, global.render.height);
    render_init_shaders(&state);
    render_init_color_texture(&state.texture_color, &state);
    render_init_quad(&state.vao_quad, &state.vbo_quad, &state.ebo_quad);
}

void render_begin() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void render_end() {
    SDL_GL_SwapWindow(global.render.window);
}

void render_quad(vec2 pos, vec2 size, vec4 color) {
    glUseProgram(state.shader_default);

    glBindVertexArray(state.vao_quad);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
