#ifndef _GLUTIL_H
#define _GLUTIL_H

#ifdef __EMSCRIPTEN__
#include <GLES3/gl3.h>
#include <emscripten.h>
#else
#include <glad/glad.h>
#endif

int gl_init(void);
int gl_compile_shaders(GLuint *program, const char *vfile, const char *ffile);

long read_file(char* buffer, const char* filename, long buffer_size);

#endif /* _GLUTIL_H */
