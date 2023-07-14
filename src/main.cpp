#include <iostream>
#include <SDL2/SDL.h>
#include <Screen.hpp>
#include <Triangle.hpp>
#include <cmath>
#include <array>

void handle_events(bool& run);
Vector2f project_3D_on_2D(Vector3f& to_project, float focal_length, float fov, float aspect_ratio);
Vector3f rotate_vector_3D(Vector3f& to_rotate, Vector3f u_axis, float angle);

int main() {

  constexpr const int WIDTH = 1280;
  constexpr const int HEIGHT = 720;
  constexpr const float SCALE = 1.0f;
  constexpr const float ASPECT_RATIO = (float)WIDTH/(float)HEIGHT;
  constexpr const char* TITLE = "Rotating 3D";

  constexpr const float CAMERA_Z_POS = -1.8f;
  constexpr const float FOCAL_LENGTH = 1.0f;
  constexpr const float FOV = M_PI / 2;

  constexpr const Vector3f ROTATION_AXIS(0.0f, 1.0f, 0.0f);
  // constexpr const Vector3f ROTATION_AXIS(3.0f/13.0f, 12.0f/13.0f, 4.0f/13.0f);
  constexpr const float ROTATION_ANGLE = M_PI / 128;

  Screen scr(TITLE, WIDTH, HEIGHT, SCALE);

  Mesh solid_3d_cube;
  solid_3d_cube.triangles.reserve(12);
  solid_3d_cube.triangles.emplace_back(Triangle( {-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, -1.0f}, {1.0f, -1.0f, -1.0f} ));
  solid_3d_cube.triangles.emplace_back(Triangle( {1.0f, -1.0f, -1.0f}, {-1.0f, -1.0f, -1.0f}, {-1.0f, 1.0f, -1.0f} ));

  solid_3d_cube.triangles.emplace_back(Triangle( {-1.0f, 1.0f, 1.0f}, {-1.0f, 1.0f, -1.0f}, {-1.0f, -1.0f, -1.0f} ));
  solid_3d_cube.triangles.emplace_back(Triangle( {-1.0f, -1.0f, -1.0f}, {-1.0f, -1.0f, 1.0f}, {-1.0f, 1.0f, 1.0f} ));
  
  solid_3d_cube.triangles.emplace_back(Triangle( {1.0f, 1.0f, 1.0f}, {-1.0f, 1.0f, 1.0f}, {-1.0f, -1.0f, 1.0f} ));
  solid_3d_cube.triangles.emplace_back(Triangle( {-1.0f, -1.0f, 1.0f}, {1.0f, -1.0f, 1.0f}, {1.0f, 1.0f, 1.0f} ));

  solid_3d_cube.triangles.emplace_back(Triangle( {1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, -1.0f, 1.0f} ));
  solid_3d_cube.triangles.emplace_back(Triangle( {1.0f, -1.0f, 1.0f}, {1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, -1.0f} ));

  solid_3d_cube.triangles.emplace_back(Triangle( {-1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, -1.0f} ));
  solid_3d_cube.triangles.emplace_back(Triangle( {1.0f, 1.0f, -1.0f}, {-1.0f, 1.0f, -1.0f}, {-1.0f, 1.0f, 1.0f} ));

  solid_3d_cube.triangles.emplace_back(Triangle( {-1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, 1.0f} ));
  solid_3d_cube.triangles.emplace_back(Triangle( {1.0f, -1.0f, 1.0f}, {-1.0f, -1.0f, 1.0f}, {-1.0f, -1.0f, -1.0f} ));

  bool work = true;
  while (work) {
    handle_events(work);

    scr.render_set_draw_color(0xff, 0xff, 0xff, 0xff);

    for (Triangle& t : solid_3d_cube.triangles) {
      for (Vector3f& v : t.vertices) {
        v = rotate_vector_3D(v, ROTATION_AXIS, ROTATION_ANGLE);
      }

      // Projection

      std::array<Vector2f, 3> arr;

      for (int i = 0; i < 3; i++) {
	Vector3f copy = t.vertices[i];
	copy.z -= CAMERA_Z_POS;
        arr[i] = project_3D_on_2D(copy, FOCAL_LENGTH, FOV, ASPECT_RATIO);

	arr[i].y *= -1;
	arr[i].x += 1; arr[i].y += 1;
	arr[i].x /= 2; arr[i].y /= 2;

	arr[i].x *= WIDTH;
	arr[i].y *= HEIGHT;
      }

      scr.render_draw_triangle((int)arr[0].x, (int)arr[0].y, (int)arr[1].x, (int)arr[1].y, (int)arr[2].x, (int)arr[2].y);
    }

    scr.render_set_draw_color(0x00, 0x00, 0x00, 0xff);
    scr.render_show();
    scr.render_clear();

    SDL_Delay(20);
  }
  
  return 0;
}

void handle_events(bool& run) {
  SDL_Event ev;
  while (SDL_PollEvent(&ev)) {
    if (ev.type == SDL_QUIT)
      run = false;
  }
}

Vector2f project_3D_on_2D(Vector3f& to_project, float focal_length, float fov, float aspect_ratio) {
  return Vector2f( to_project.x * focal_length / aspect_ratio / (to_project.z + focal_length) / std::tan(fov/2), to_project.y * focal_length / (to_project.z + focal_length) / std::tan(fov/2));
}

Vector3f rotate_vector_3D(Vector3f& to_rotate, Vector3f u_axis, float angle) {
  float sin_of_angle = std::sin(angle);
  float cos_of_angle = std::cos(angle);

  float u_xy = u_axis.x * u_axis.y;
  float u_xz = u_axis.x * u_axis.z;
  float u_yz = u_axis.y * u_axis.z;
  return Vector3f(
    to_rotate.x*(cos_of_angle + u_axis.x * u_axis.x * (1 - cos_of_angle))  +  to_rotate.y*(u_xy * (1 - cos_of_angle) - u_axis.z * sin_of_angle    )  +  to_rotate.z*(u_xz * (1 - cos_of_angle) + u_axis.y * sin_of_angle    )  ,
    to_rotate.x*(u_xy * (1 - cos_of_angle) + u_axis.z * sin_of_angle    )  +  to_rotate.y*(cos_of_angle + u_axis.y * u_axis.y * (1 - cos_of_angle))  +  to_rotate.z*(u_yz * (1 - cos_of_angle) - u_axis.x * sin_of_angle    )  ,
    to_rotate.x*(u_xz * (1 - cos_of_angle) - u_axis.y * sin_of_angle    )  +  to_rotate.y*(u_yz * (1 - cos_of_angle) + u_axis.x * sin_of_angle    )  +  to_rotate.z*(cos_of_angle + u_axis.z * u_axis.z * (1 - cos_of_angle))
  );
}
