#include <SDL2/SDL.h>

#include "SDL2/SDL_video.h"
#include "render.h"
#include "render_internal.h"

SDL_Window *render_init_window(u32 width, u32 height) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        ERROR_EXIT("Could not init SDL: %s\n", SDL_GetError());
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window *window = SDL_CreateWindow(
        "MyGame",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_OPENGL
    );

    if (!window) {
        ERROR_EXIT("Failed to init window: %s\n", SDL_GetError());
    }

    SDL_GL_CreateContext(window);


    puts("OpenGL Loaded");
    printf("Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version:  %s\n", glGetString(GL_VERSION));

    return window;
}


void render_init_shaders(Render_State_Internal *state) {
    state->shader_default = render_shader_create("./shaders/FragColor.vert", "./shaders/FragColor.frag");

    glUseProgram(state->shader_default);
}

void render_init_color_texture(u32 *texture) {
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);
    u8 solid_white[4] = {255, 255, 255, 255};
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, solid_white);

    glBindTexture(GL_TEXTURE_2D, 0);
}


void render_init_quad(u32 *vao, u32 *vbo, u32 *ebo) {
    //     x,    y, z, u, v
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    }; 

    glGenVertexArrays(1, vao);
    glGenBuffers(1, vbo);

    glBindVertexArray(*vao);

    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
	// x, y, z
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void*) 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



    glBindVertexArray(0);
}