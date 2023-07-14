#pragma once
#include <array>
#include <vector>

struct Vector2f {
  float x;
  float y;
  Vector2f(float p_x = 0, float p_y = 0) : x(p_x), y(p_y) {
  }
};

struct Vector3f {
  float x;
  float y;
  float z;

  Vector3f(float p_x = 0, float p_y = 0, float p_z = 0) : x(p_x), y(p_y), z(p_z) {
  }
};

struct Triangle {
  std::array<Vector3f, 3> vertices;
  Triangle(Vector3f p_vertex1, Vector3f p_vertex2, Vector3f p_vertex3) {
    vertices[0] = p_vertex1;
    vertices[1] = p_vertex2;
    vertices[2] = p_vertex3;
  }
};

struct Mesh {
  std::vector<Triangle> triangles;
  Mesh() {}
};
