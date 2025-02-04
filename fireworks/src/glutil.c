#include <stdio.h>
#include "glutil.h"
#include <GLFW/glfw3.h>

extern GLFWwindow* window;

#ifdef DEBUG
void APIENTRY debug_callback(GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar *message,
            const void *userParam) {
  (void)length;
  (void)userParam;
  (void)source;
  (void)type;
  (void)id;
  (void)severity;
  (void)message;
  LOG("Callback There is an error\n%s\n", message);
}
#endif

int gl_init(void) {

#ifndef __EMSCRIPTEN__
  int err = gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress);
  if (!err) {
    printf("Error starting glad\n");
    return 0;
  }
#endif

  printf("%s\n", glGetString(GL_VERSION));
  
#ifdef DEBUG
  printf("Debug build enabled\n");
  glEnable(GL_DEBUG_OUTPUT);
  //glDebugMessageCallback(debug_callback, NULL);
#endif

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  int w, h;
  glfwGetWindowSize(window, &w, &h);
  glViewport(0, 0, w, h);
  glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
  return 1;
}

long read_file(char *buffer, const char *filename, long buffer_size) {
  FILE *file = fopen(filename, "r");

  if (!file) {
    return 0;
  }

  fseek(file, 0, SEEK_END);
  long size = ftell(file);

  if (size >= buffer_size) {
    fclose(file);
    return 0;
  }

  fseek(file, 0, SEEK_SET);
  fread(buffer, 1, size, file);
  buffer[size] = 0;

  fclose(file);
  return size + 1;
}

int gl_compile_shaders(GLuint* program, const char* vfile, const char* ffile) {
  *program = 0;

  char vertex_shader[5026] = {0};
  char fragment_shader[5026] = {0};
  const char* vp = vertex_shader;
  const char* fp = fragment_shader;

  long ss = read_file(vertex_shader, vfile, 5026);
  if (ss > 5026)
    printf("Shader file is too large %s\n", vfile);
  else if (ss <= 0)
    printf("Shader not found %s\n", vfile);
  ss = read_file(fragment_shader, ffile, 5026);
  if (ss > 5026)
    printf("Shader file is too large %s\n", ffile);
  else if (ss <= 0)
    printf("Shader not found %s\n", ffile);

  printf("vert: %s\n", vertex_shader);
  printf("frag: %s\n", fragment_shader);
  
  GLint vshader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vshader, 1, &vp, NULL);
  glCompileShader(vshader);

  GLint status;
  glGetShaderiv(vshader, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE) {
    char buffer[512];
    glGetShaderInfoLog(vshader, 512, NULL, buffer);
    printf("Shader Vert compile error!\n%s\n", buffer);

    return 0;
  }

  printf("VShader compiled\n");

  GLint fshader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fshader, 1, &fp, NULL);
  glCompileShader(fshader);

  glGetShaderiv(fshader, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE) {
    char buffer[512];
    glGetShaderInfoLog(fshader, 512, NULL, buffer);
    printf("Shader Frag compile error!\n%s\n", buffer);

    return 0;
  }

  printf("FShader compiled\n");
    
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vshader);
  glAttachShader(shaderProgram, fshader);

  //glBindFragDataLocation(shaderProgram, 0, "outColor");

  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
  if (status != GL_TRUE) {
    char buffer[512];
    glGetShaderInfoLog(vshader, 512, NULL, buffer);
    printf("Shader compile error!\n%s\n", buffer);

    return 0;
  }

  printf("Program linked\n");
  
  *program = shaderProgram;
  
  glDeleteShader(fshader);
  glDeleteShader(vshader);

  return 1;
}
