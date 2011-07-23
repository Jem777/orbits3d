/*
 * =====================================================================================
 *
 *       Filename:  shaders.c
 *
 *    Description:  loads vertex- and fragment shaders
 *
 *        Version:  1.0
 *        Created:  22.07.2011 19:19:23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jem
 *        Company:  
 *
 * =====================================================================================
 */

#include "shaders.h"

char* filetobuf(char *file) {
    FILE *fptr;
    long length;
    char *buf;
 
    fptr = fopen(file, "rb"); /* Open file for reading */
    if (!fptr) /* Return NULL on failure */
        return NULL;
    fseek(fptr, 0, SEEK_END); /* Seek to the end of the file */
    length = ftell(fptr); /* Find out how many bytes into the file we are */
    buf = (char*)malloc(length+1); /* Allocate a buffer for the entire length of the file and a null terminator */
    fseek(fptr, 0, SEEK_SET); /* Go back to the beginning of the file */
    fread(buf, length, 1, fptr); /* Read the contents of the file in to the buffer */
    fclose(fptr); /* Close the file */
    buf[length] = 0; /* Null terminator */
 
    return buf; /* Return the buffer */
}

GLuint init_shader(const GLchar **source, GLint shader_type) {
    char *info_log;
    int max_length;
    GLint is_compiled;
    GLuint shader;

    shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, source, 0);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
    if(is_compiled == GL_FALSE) {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);
        /* The maxLength includes the NULL character */
        info_log = (char *)malloc(max_length);
        glGetShaderInfoLog(shader, max_length, &max_length, info_log);
        /* Handle the error in an appropriate way such as displaying a message or writing to a log file. */
        if (shader_type == GL_VERTEX_SHADER) {
            printf("Compiling Vertex-Shader failed: \n%s\n", info_log);
        } else if (shader_type == GL_GEOMETRY_SHADER) {
            printf("Compiling Geometry-Shader failed: \n%s\n", info_log);
        } else if (shader_type == GL_FRAGMENT_SHADER) {
            printf("Compiling Fragment-Shader failed: \n%s\n", info_log);
        }
        free(info_log);
        exit(1);
    }
    return shader;
}

shader_t *create_shaders() {
    int IsLinked;
    int maxLength;
    char *shaderProgramInfoLog;
 
    // create a shader struct
    shader_t *shader = malloc(sizeof(shader_t));

    // Read our shaders into the appropriate buffers
    shader->vertexsource = filetobuf("Vertex.vs");
    shader->fragmentsource = filetobuf("Fragment.fs");
 
    shader->vertex = init_shader((const GLchar**)&shader->vertexsource, GL_VERTEX_SHADER);
    shader->fragment = init_shader((const GLchar**)&shader->fragmentsource, GL_FRAGMENT_SHADER);
 
    /* If we reached this point it means the vertex and fragment shaders compiled and are syntax error free. */
    /* We must link them together to make a GL shader program */
    /* GL shader programs are monolithic. It is a single piece made of 1 vertex shader and 1 fragment shader. */
    /* Assign our program handle a "name" */
    shader->program = glCreateProgram();
 
    /* Attach our shaders to our program */
    glAttachShader(shader->program, shader->vertex);
    glAttachShader(shader->program, shader->fragment);
 
    /* Bind attribute index 0 (coordinates) to in_Position and attribute index 1 (color) to in_Color */
    /* Attribute locations must be setup before calling glLinkProgram. */
    //glBindAttribLocation(shader->program, 0, "in_Position");
    //glBindAttribLocation(shader->program, 1, "in_Color");
 
    /* Link our program */
    /* At this stage, the vertex and fragment programs are inspected, optimized and a binary code is generated for the shader. */
    /* The binary code is uploaded to the GPU, if there is no error. */
    glLinkProgram(shader->program);
 
    /* Again, we must check and make sure that it linked. If it fails, it would mean either there is a mismatch between the vertex */
    /* and fragment shaders. It might be that you have surpassed your GPU's abilities. Perhaps too many ALU operations or */
    /* too many texel fetch instructions or too many interpolators or dynamic loops. */
 
    glGetProgramiv(shader->program, GL_LINK_STATUS, (int *)&IsLinked);
    if(!IsLinked) {
        /* Noticed that glGetProgramiv is used to get the length for a shader program, not glGetShaderiv. */
        glGetProgramiv(shader->program, GL_INFO_LOG_LENGTH, &maxLength);
        /* The maxLength includes the NULL character */
        shaderProgramInfoLog = (char *)malloc(maxLength);
        /* Notice that glGetProgramInfoLog, not glGetShaderInfoLog. */
        glGetProgramInfoLog(shader->program, maxLength, &maxLength, shaderProgramInfoLog);
        /* Handle the error in an appropriate way such as displaying a message or writing to a log file. */
        printf("Linking shaders failed: \n%s\n", shaderProgramInfoLog);
        free(shaderProgramInfoLog);
        exit(1);
    }
 
    /* Load the shader into the rendering pipeline */
    glUseProgram(shader->program);
    return shader;
}

void destroy_shaders(shader_t *shader) {
    /* Cleanup all the things we bound and allocated */
    glUseProgram(0);
    glDetachShader(shader->program, shader->vertex);
    glDetachShader(shader->program, shader->fragment);
    glDeleteProgram(shader->program);
    glDeleteShader(shader->vertex);
    glDeleteShader(shader->fragment);
    free(shader->vertexsource);
    free(shader->fragmentsource);
    free(shader);
}

void get_matrix(shader_t *shader, const char *matrix_type) {
    GLint matrix_location = glGetUniformLocation(shader->program, matrix_type);
    asdf;
}

void set_matrix(shader_t *shader, asdf) {
    GLint matrix_location = glGetUniformLocation(shader->program, matrix_type);
    glUniformMatrix4fv(g_modelViewLocation, 1, GL_FALSE, g_modelView);
    asdf;
}
