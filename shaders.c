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

char *filetobuf(char *fn) {
    FILE *fp;
    char *content = NULL;
    int count=0;
 
    if (fn != NULL) {
        fp = fopen(fn,"rt");
        if (fp != NULL) {
            fseek(fp, 0, SEEK_END);
            count = ftell(fp);
            rewind(fp);
            if (count > 0) {
                content = (char *)malloc(sizeof(char) * (count+1));
                count = fread(content,sizeof(char),count,fp);
                content[count] = '\0';
            }
            fclose(fp);
        }
    }
    return content;
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
    //shader->geometrysource = filetobuf("Geometry.gs");
    shader->fragmentsource = filetobuf("Fragment.fs");
 
    shader->vertex = init_shader((const GLchar**)&shader->vertexsource, GL_VERTEX_SHADER);
    //shader->geometry = init_shader((const GLchar**)&shader->geometrysource, GL_GEOMETRY_SHADER);
    shader->fragment = init_shader((const GLchar**)&shader->fragmentsource, GL_FRAGMENT_SHADER);
 
    shader->program = glCreateProgram();
 
    /* Attach our shaders to our program */
    glAttachShader(shader->program, shader->vertex);
    //glAttachShader(shader->program, shader->geometry);
    glAttachShader(shader->program, shader->fragment);
 
    /* Attribute locations must be setup before calling glLinkProgram. */
    glBindAttribLocation(shader->program, 0, "vertex");
    glBindAttribLocation(shader->program, 1, "normal");
    glBindAttribLocation(shader->program, 2, "texCoord");
 
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

void get_matrix(shader_t *shader, const char *matrix_type, GLfloat *matrix_object) {
    GLint matrix_location = glGetUniformLocation(shader->program, matrix_type);
    glGetUniformfv(shader->program, matrix_location, matrix_object);
}

void set_matrix(shader_t *shader, const char *matrix_type, GLfloat *matrix_object) {
    GLint matrix_location = glGetUniformLocation(shader->program, matrix_type);
    glUniformMatrix4fv(matrix_location, 1, GL_FALSE, matrix_object);
}

void set_texture(shader_t *shader, GLuint texture) {
    GLint texture_location = glGetUniformLocation(shader->program, "firstTexture");
    glUniform1ui(texture_location, texture);
}

