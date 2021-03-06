#include <stdio.h>

#include <GL/glew.h>
#include <SDL.h>

#include "shaders.h"
#include "vertex_buffer.h"
#include "simulation.h"
#include "matrix.h"
#include "textures.h"

void setup_rendering(shader_t *shader, GLfloat camera[16], GLfloat projection[16]) {
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_CLAMP); // no clipping
    glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    glFrontFace(GL_CW);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    load_identity(projection);
    set_matrix(shader, PROJECTION_MATRIX, projection);
    load_identity(camera);
    scale(camera, 0.2, 0.2, 0.2);
    rotate(camera, 80, 1,0,0);
    glViewport(0, 0, 600, 600);
    glPolygonMode(GL_BACK,GL_LINE);
}

void change_camera(GLfloat camera[16]) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    rotate(camera, 0.5, 0,0,1);
}

int handle_events() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return 1;
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
            return 1;
        }
    }
    return 0;
}

int setup_sdl() {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) != 0){
        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }
    SDL_WM_SetCaption("Orbits 3D", "Orbits 3D");
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1); // antialiasing
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4); // antialiasing
    SDL_Surface *surface = SDL_SetVideoMode(600, 600, 24, SDL_OPENGL);
    if (surface == NULL) {
        fprintf(stderr, "Failed to initialize OpenGL: %s\n", SDL_GetError());
        return 1;
    }

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        /*  Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(err));
        return 1;
    }
    if (!GLEW_VERSION_2_0) {
        fprintf(stderr, "OpenGL 2.0 or higher is needed for this application\n");
        return 1;
    }
    return 0;
}

int main(void){
    if (setup_sdl() == 1) {
        return 1;
    }
    GLfloat camera[16];
    GLfloat projection[16];
    simulation_t *simulation = create_simulation();
    buffer_t *buffer = create_vbo();
    shader_t *shader = create_shaders();
    setup_rendering(shader, camera, projection);
    GLuint tex = load_texture("pixmaps/earthmap.jpg");
    set_texture(shader, tex);
    while(1) {
        change_camera(camera);
        draw_objects(simulation, buffer, shader, camera);
        run_simulation(simulation);
        SDL_GL_SwapBuffers();
        SDL_Delay(50);
        if(handle_events() == 1) {
            destroy_shaders(shader);
            destroy_vbo(buffer);
            destroy_simulation(simulation);
            SDL_Quit();
            exit(0);
        }
    }
}
