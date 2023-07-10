#pragma once

#include <SDL2/SDL.h>

class Screen {
public:
  Screen(const char* p_title, const int p_width, const int p_height, const float p_scale);
  ~Screen();

  void render_clear();
  void render_show();
  void render_set_draw_color(uint8_t r = 0x00, uint8_t g = 0x00, uint8_t b = 0x00, uint8_t a = 0xff);
  void render_draw_line(const int p_p1_x, const int p_p1_y, const int p_p2_x, const int p_p2_y);
  void render_draw_triangle(const int p_a_x, const int p_a_y, const int p_b_x, const int p_b_y, const int p_c_x, const int p_c_y);
private:
  SDL_Window* m_window;
  SDL_Renderer* m_renderer;
};
