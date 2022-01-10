#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <stdlib.h>

#include "Shader.h"
#include "Sphere.h"

#define DRAW_SCENE

// #define PHONG_SHADING
// #define BLINN_PHONG_SHADING
// #define FLAT_SHADING
// #define SMOOTH_SHADING

const unsigned int SCREEN_WIDTH = 1024;
const unsigned int SCREEN_HEIGHT = 768;

const int X_SEGMENTS = 512;
const int Y_SEGMENTS = 512;

void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

int main(int argc, char *argv[])
{
  glfwInit();
  #if !defined(FLAT_SHADING) && !defined(SMOOTH_SHADING)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  #endif

  GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "HW3", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK)
  {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return -1;
  }

  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

  Sphere sphere(X_SEGMENTS, Y_SEGMENTS);

  // use Phong Shading or Blinn-Phong Shading
  #if defined(PHONG_SHADING) && !defined(BLINN_PHONG_SHADING) && !defined(FLAT_SHADING) && !defined(SMOOTH_SHADING) || defined(DRAW_SCENE)
    Shader shader("shader/phong.vert", "shader/phong.frag");
  #endif
  #if (!defined(PHONG_SHADING) && defined(BLINN_PHONG_SHADING) && !defined(FLAT_SHADING) && !defined(SMOOTH_SHADING))
    Shader shader("shader/blinn-phong.vert", "shader/blinn-phong.frag");
  #endif

  #ifdef DRAW_SCENE
    float angle1 = 0.0f;
    float angle2 = 0.0f;
    float angle3 = 0.0f;

    float radius1 = 2.0f;
    float radius2 = 15.0f;
    float radius3 = 8.0f;
  #endif

  glEnable(GL_DEPTH_TEST);

  while (!glfwWindowShouldClose(window))
  {
    processInput(window);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    #ifdef DRAW_SCENE // draw rotate scene
      Sphere sphere1(128, 128);
      Sphere sphere2(128, 128);
      Sphere sphere3(128, 128);

      shader.use();

      glm::vec3 camera_position(0.0f, 30.0f, 30.0f);
      glm::mat4 view = glm::lookAt(camera_position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

      int width, height;
      glfwGetWindowSize(window, &width, &height);
      glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 100.0f);

      shader.setMat4("view", view);
      shader.setMat4("projection", projection);

      shader.setVec3("lightPos", glm::vec3(0.0f, 20.0f, 0.0f));
      shader.setVec3("viewPos", camera_position);
      shader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

      glm::mat4 model1 = glm::mat4(1.0f);
      model1 = glm::rotate(model1, angle1, glm::vec3(0.0f, 1.0f, 0.0f));
      model1 = glm::translate(model1, glm::vec3(radius1, 0.0f, 0.0f));
      shader.setMat4("model", model1);
      shader.setVec3("objectColor", glm::vec3(0.118f, 0.565f, 1.0f));
      sphere1.draw();

      glm::mat4 model2 = glm::mat4(1.0f);
      model2 = glm::rotate(model2, angle2, glm::vec3(0.0f, 1.0f, 0.0f));
      model2 = glm::translate(model2, glm::vec3(radius2, 0.0f, 0.0f));
      shader.setMat4("model", model2);
      shader.setVec3("objectColor", glm::vec3(0.0f, 1.0f, 0.0f));
      sphere2.draw();

      glm::mat4 model3 = glm::mat4(1.0f);
      model3 = glm::rotate(model3, angle3, glm::vec3(0.0f, 1.0f, 0.0f));
      model3 = glm::translate(model3, glm::vec3(-radius3, 0.0f, 0.0f));
      shader.setMat4("model", model3);
      shader.setVec3("objectColor", glm::vec3(0.541f, 0.169f, 0.886f));
      sphere3.draw();

      angle1 += 0.01f;
      angle2 -= 0.008f;
      angle3 += 0.02f;
      if (angle1 > 360.0f)
      {
        angle1 = 0.0f;
      }
      if (angle2 < -360.0f)
      {
        angle2 = 0.0f;
      }
      if (angle3 > 360.0f)
      {
        angle3 = 0.0f;
      }
    #else // draw different shading
      /* Phong Shading or Blinn-Phong Shading */
      #if defined(PHONG_SHADING) || defined(BLINN_PHONG_SHADING) && !defined(FLAT_SHADING) && !defined(SMOOTH_SHADING)
        glm::mat4 model = glm::mat4(1.0f);
        glm::vec3 camera_position(0.0f, 0.0f, 5.0f);
        glm::mat4 view = glm::lookAt(camera_position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        int width, height;
        glfwGetWindowSize(window, &width, &height);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 100.0f);

        shader.use();
        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        shader.setVec3("lightPos", glm::vec3(-10.0f, 10.0f, 10.0f));
        shader.setVec3("viewPos", camera_position);
        shader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader.setVec3("objectColor", glm::vec3(0.118f, 0.565f, 1.0f));

        sphere.draw();
      #endif

      /* Flat Shading or Smooth Shading*/
      #if defined(FLAT_SHADING) && !defined(SMOOTH_SHADING) && !defined(PHONG_SHADING) && !defined(BLINN_PHONG_SHADING)
        glShadeModel(GL_FLAT);
      #endif
      #if !defined(FLAT_SHADING) && defined(SMOOTH_SHADING) && !defined(PHONG_SHADING) && !defined(BLINN_PHONG_SHADING)
        glShadeModel(GL_SMOOTH);
      #endif

      #if defined(FLAT_SHADING) || defined(SMOOTH_SHADING) && !defined(PHONG_SHADING) && !defined(BLINN_PHONG_SHADING)
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        gluPerspective(45.0, (double) width / (double) height, 0.1, 100.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

        GLfloat light_pos[] = {-10.0f, 10.0f, 10.0f, 0.0f};
        GLfloat light_ambient[] = {0.1f, 0.1f, 0.1f, 0.1f};
        GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
        GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

        glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

        GLfloat material_ambient[] = {0.118f, 0.565f, 1.0f, 1.0f};
        GLfloat material_diffuse[] = {0.118f, 0.565f, 1.0f, 1.0f};
        GLfloat material_specular[] = {0.118f, 0.565f, 1.0f, 1.0f};
        GLfloat material_shininess[] = {32};

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material_shininess);

        glEnable(GL_LIGHTING);      
        glEnable(GL_LIGHT0);
        glEnable(GL_COLOR_MATERIAL);

        sphere.draw_oldschool();
      #endif
    #endif

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}
