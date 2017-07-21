#include <stdio.h>
#include <stdlib.h>

/* Copyright (c) 2015-2017, ARM Limited and Contributors
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge,
 * to any person obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "loader.h"

#define BASE_ASSET_PATH    "/data/data/com.arm.developer.vrsdk.simplevr/files/"
#define SHADER_PATH(name)  BASE_ASSET_PATH name

char *read_file(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        LOGE("Failed to open file %s\n", filename);
        exit (1);
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *data = (char *)calloc(length + 1, sizeof(char));
    if (!data)
    {
        LOGE("Failed to allocate memory for file data %s\n", filename);
        exit(1);
    }
    size_t read = fread(data, sizeof(char), length, file);
    if (read != length)
    {
        LOGE("Failed to read whole file %s\n", filename);
        exit(1);
    }
    data[length] = '\0';
    fclose(file);
    return data;
}
GLuint compile_shader(const char *source, GLenum type)
{
    GLuint result = glCreateShader(type);
    glShaderSource(result, 1, (const GLchar**)&source, NULL);
    glCompileShader(result);
    GLint status;
    glGetShaderiv(result, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint length;
        glGetShaderiv(result, GL_INFO_LOG_LENGTH, &length);
        GLchar *info = new GLchar[length];
        glGetShaderInfoLog(result, length, NULL, info);
        LOGE("[COMPILE] %s\n", info);
        delete[] info;
        exit(1);
    }
    return result;
}
GLuint link_program(GLuint *shaders, int count)
{
    GLuint program = glCreateProgram();
    for (int i = 0; i < count; ++i)
        glAttachShader(program, shaders[i]);
    glLinkProgram(program);
    for (int i = 0; i < count; ++i)
        glDetachShader(program, shaders[i]);
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        GLchar *info = new GLchar[length];
        glGetProgramInfoLog(program, length, NULL, info);
        LOGE("[LINK] %s\n", info);
        delete[] info;
        exit(1);
    }
    return program;
}
void load_cube_shader(App *app)
{
    char *vs_src = read_file(SHADER_PATH("cube.vs"));
    char *fs_src = read_file(SHADER_PATH("cube.fs"));
    GLuint shaders[2];
    shaders[0] = compile_shader(vs_src, GL_VERTEX_SHADER);
    shaders[1] = compile_shader(fs_src, GL_FRAGMENT_SHADER);
    app->program_cube = link_program(shaders, 2);
    free(vs_src);
    free(fs_src);
}
void load_distort_shader(App *app)
{
    char *vs_src = read_file(SHADER_PATH("distort.vs"));
    char *fs_src = read_file(SHADER_PATH("distort.fs"));
    GLuint shaders[2];
    shaders[0] = compile_shader(vs_src, GL_VERTEX_SHADER);
    shaders[1] = compile_shader(fs_src, GL_FRAGMENT_SHADER);
    app->program_distort = link_program(shaders, 2);
    free(vs_src);
    free(fs_src);
}
void load_assets(App *app)
{
    load_distort_shader(app);
    load_cube_shader(app);
}