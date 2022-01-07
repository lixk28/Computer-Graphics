#include "Sphere.h"

Sphere::Sphere(int X_SEGMENTS, int Y_SEGMENTS)
{
  // std::vector<glm::vec3> positions;
  // std::vector<glm::vec3> normals;

  for (int y = 0; y <= Y_SEGMENTS; ++y)
  {
    for (int x = 0; x <= X_SEGMENTS; ++x)
    {
      float xSegment = (float)x / (float)X_SEGMENTS;
      float ySegment = (float)y / (float)Y_SEGMENTS;
      float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
      float yPos = std::cos(ySegment * PI);
      float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

      positions.push_back(glm::vec3(xPos, yPos, zPos));
      normals.push_back(glm::vec3(xPos, yPos, zPos));
    }
  }

  bool oddRow = false;
  for (int y = 0; y < Y_SEGMENTS; ++y)
  {
    if (!oddRow)
    {
      for (int x = 0; x <= X_SEGMENTS; ++x)
      {
        sphere_indices.push_back(y * (X_SEGMENTS + 1) + x);
        sphere_indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
      }
    }
    else
    {
      for (int x = X_SEGMENTS; x >= 0; --x)
      {
        sphere_indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
        sphere_indices.push_back(y * (X_SEGMENTS + 1) + x);
      }
    }
    oddRow = !oddRow;
  }

  for (int i = 0; i < positions.size(); ++i)
  {
    sphere_vertices.push_back(positions[i].x);
    sphere_vertices.push_back(positions[i].y);
    sphere_vertices.push_back(positions[i].z);
    if (normals.size() > 0)
    {
      sphere_vertices.push_back(normals[i].x);
      sphere_vertices.push_back(normals[i].y);
      sphere_vertices.push_back(normals[i].z);
    }
  }

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sphere_vertices.size() * sizeof(float), &sphere_vertices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphere_indices.size() * sizeof(int), &sphere_indices[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
}

Sphere::~Sphere()
{
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
}

void Sphere::draw()
{
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLE_STRIP, sphere_indices.size(), GL_UNSIGNED_INT, 0);
}

void Sphere::draw_oldschool()
{
  glBegin(GL_TRIANGLE_STRIP);
  for (int i = 0; i < sphere_indices.size(); i++)
  {
    glVertex3f(positions[sphere_indices[i]].x, positions[sphere_indices[i]].y, positions[sphere_indices[i]].z);
    glNormal3f(normals[sphere_indices[i]].x, normals[sphere_indices[i]].y, normals[sphere_indices[i]].z);
  }
  glEnd();
}