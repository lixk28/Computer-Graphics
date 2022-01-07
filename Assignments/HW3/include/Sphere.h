#ifndef SPHERE_H
#define SPHERE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "Shader.h"

const GLfloat PI = glm::pi <GLfloat> ();

class Sphere
{
private:
  GLuint VAO = 0;
  GLuint VBO;
  GLuint EBO;

  std::vector<glm::vec3> positions;
  std::vector<glm::vec3> normals;

  std::vector<float> sphere_vertices;
  std::vector<int> sphere_indices;
  
public:
  Sphere(int stack_count, int sector_count);
  ~Sphere();
  
  void draw();
  void draw_oldschool();
};

#endif