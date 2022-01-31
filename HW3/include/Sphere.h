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
  GLuint VAO;
  GLuint VBO;
  GLuint EBO;

  std::vector<glm::vec3> positions; // position vectors
  std::vector<glm::vec3> normals;   // normal vectors

  std::vector<float> sphere_vertices;
  std::vector<int> sphere_indices;
  
public:
  Sphere(int X_SEGMENTS, int Y_SEGMENTS); // split into X_SEGMENTS x Y_SEGMENTS pieces
  ~Sphere();
  
  void draw();  // draw sphere using opengl core profile mode
  void draw_oldschool();  // draw sphere using deprectaed glBegin() and glEnd()
};

#endif