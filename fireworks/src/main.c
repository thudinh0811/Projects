#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "glutil.h"
#include <GLFW/glfw3.h>
#include "ltrans.h"
#include "timedata.h"
#include "firework.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>

extern int browser_get_width(void);
extern int browser_get_height(void);

#endif

#define FIREWORK_MAX 20
void main_iter(void);

static void set_viewport_full(GLFWwindow *window) {
  int w, h;
  glfwGetWindowSize(window, &w, &h);
  glViewport(0, 0, w, h);

  //printf("asp: %.2f\n", (float)w/(float)h);
}

static void check_error(int line) {
   GLenum err = glGetError();
    if (err != GL_NO_ERROR)
      printf("err on line %d - %x\n", line, err);
}

static GLint moveLoc;
static GLint projLoc;

void mouse_move(GLFWwindow *window, double x, double y) {
  int w, h;
  glfwGetWindowSize(window, &w, &h);

  float nx = (x / w * 2) - 1;
  float ny = 1 - (y / h * 2);
  //printf("Cursor pos x: %.2f, y: %.2f\n", nx, ny);
  glUniform2f(moveLoc, nx, ny);
}

void key_callback(GLFWwindow *window, int key, int scan, int action, int mods) {
  (void)scan;
  (void)mods;
  //printf("key press %d\n | esc: %d\n", key, GLFW_KEY_ESCAPE);
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }
}

void resize_callback(GLFWwindow *window, int w, int h) {
  printf("Size w: %d, h: %d\n", w, h);
  //glfwSetWindowAspectRatio(window, 1, 1);
  set_viewport_full(window);
}

int sizei[2];
float size[2];

GLint sizeLoc;
GLint timeLoc;
GLint dimLoc;

LMMat4 proj;

GLint scaleLoc;
GLint aspectLoc;

GLuint program;
GLuint pointsProgram;

GLFWwindow* window;

firework_t fw[20];

int main(void) {
  if (!glfwInit()) {
    printf("Error glfw init\n");
    return 1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);

  window = glfwCreateWindow(1920, 1080, "Shaders", NULL, NULL);

  if (!window) {
    printf("Error window create\n");
    return 1;
  }

#ifdef __EMSCRIPTEN__
  int w = browser_get_width();
  int h = browser_get_height();
  glfwSetWindowSize(window, w, h);
  resize_callback(window, w, h);
#endif

  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);
  glfwSetWindowSizeCallback(window, resize_callback);

  gl_init();

  if (!gl_compile_shaders(&program, "assets/shaders/shader.vert",
                          "assets/shaders/shader.frag") ||
      !gl_compile_shaders(&pointsProgram, "assets/shaders/points.vert",
                          "assets/shaders/points.frag")) {
    printf("error create program shaders\n");
    return 1;
  }

  glUseProgram(program);
  check_error(__LINE__);
  
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  sizeLoc = glGetUniformLocation(program, "iSize");
  timeLoc = glGetUniformLocation(program, "iTime");
  dimLoc = glGetUniformLocation(program, "iDimension");
  moveLoc = glGetUniformLocation(program, "iCursor");
  projLoc = glGetUniformLocation(program, "iProjection");
  glUniformMatrix4fv(projLoc, 1, 0, (float*)&LMMat4_identity);
  glUniform2f(moveLoc, -1.0f, -1.0f);
  
  glfwSetCursorPosCallback(window, mouse_move);

  proj = LMMat4_identity;

  glUseProgram(pointsProgram);
  scaleLoc = glGetUniformLocation(pointsProgram, "iScale");
  aspectLoc = glGetUniformLocation(pointsProgram, "iAspect");

  time_start();
  srand(time(NULL));

  glfwGetWindowSize(window, &sizei[0], &sizei[1]);
  for (int i = 0; i < FIREWORK_MAX; i++) {
    fw[i] = firework_create((float)sizei[0] / (float)sizei[1]);
    fw[i].stage = 2;
    fw[i].lifetime = i / 2.0f;
    fw[i].x = -10000.0f;
  }

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(main_iter, 0, 1); 
  //emscripten_set_main_loop_timing(0, 0); 
#else
  while (!glfwWindowShouldClose(window)) {
    main_iter();
  }

  glfwTerminate();
  return 0;
#endif
}

void main_iter(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    time_stamp();
    TimeData td = time_get();

    glUseProgram(program);

    glUniformMatrix4fv(projLoc, 1, GL_FALSE, (float*)&LMMat4_identity);
    glfwGetWindowSize(window, sizei, sizei + 1);
    size[0] = sizei[0];
    size[1] = sizei[1];
    glUniform2fv(sizeLoc, 1, size);
    check_error(__LINE__);

    glUniform1f(timeLoc, td.time_elapsed);
    check_error(__LINE__);

    float asp = size[0] / size[1];
    LTOrthographicDescriptor desc = {
      .bottom = -1.0f,
      .top = 1.0f,
      .left = -asp,
      .right = asp,
      .near = -1.0f,
      .far = 9.0f,
    };
    proj = ltOrthographic(&desc);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, (float *)&proj);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glClear(GL_DEPTH_BUFFER_BIT);

    glUseProgram(pointsProgram);
    int vertex_stride = sizeof(float) * 7;
    
    for (int i = 0; i < FIREWORK_MAX; i++) {
      firework_update(fw + i);
    
      glUniformMatrix4fv(aspectLoc, 1, GL_FALSE, (float*)&proj);
    
      if (!firework_is_done(fw + i)) {
	glUniform1f(scaleLoc, fw[i].scale);
	glBindBuffer(GL_ARRAY_BUFFER, fw[i].vbuffer);
      
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	check_error(__LINE__);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_stride, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertex_stride, (void *)(sizeof(float) * 3));
	check_error(__LINE__);
      
	glDrawArrays(GL_POINTS, 0, fw[i].used_points);
	check_error(__LINE__);

	check_error(__LINE__);
      } else {
	fw[i] = firework_create(asp);
      }
    }


    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
}
