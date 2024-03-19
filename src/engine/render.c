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
    render_init_quad(&state.vao_quad, &state.vbo_quad, &state.ebo_quad);
    render_init_color_texture(&state.texture_color);
}

void render_begin() {
    glClearColor(0.08, 0.1, 0.1, 1);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void render_end() {
    SDL_GL_SwapWindow(global.render.window);
}

void render_quad(vec2 pos, vec2 size, vec4 color) {
    glUseProgram(state.shader_default);
    /* mat4 model; */
    /* f32 dest[] = {pos[0], pos[2], 0}; */
    /* glm_mat4_identity(model); */
    /* glm_translate(model, dest); */
    glBindVertexArray(state.vao_quad);

    /* glUniformMatrix4fv(glGetUniformLocation(state.shader_default, "model"), 1, GL_FALSE, &model[0][0]); */

    /* glUniform4fv(glGetUniformLocation(state.shader_default, "color"), 1, color); */



    /* glBindTexture(GL_TEXTURE_2D, state.texture_color); */
    /* glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL); */
    glDrawArrays(GL_TRIANGLES, 0 , 3);
}
