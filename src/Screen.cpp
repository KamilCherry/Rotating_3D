#include <iostream>
#include <Screen.hpp>
#include <SDL2/SDL.h>

Screen::Screen(const char* p_title, const int p_width, const int p_height, const float p_scale) : m_window(nullptr), m_renderer(nullptr) {

  if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0) std::cerr << "Couldn't initialize EVENTS. Error: " << SDL_GetError() << std::endl;
  if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) std::cerr << "Couldn't initialize VIDEO. Error: " << SDL_GetError() << std::endl;

  m_window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_width * p_scale, p_height * p_scale, SDL_WINDOW_SHOWN);
  if (m_window == NULL) std::cerr << "Couldn't create a window. Error: " << SDL_GetError() << std::endl;

  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
  if (m_renderer == NULL) std::cerr << "Couldn't create a renderer. Error: " << SDL_GetError() << std::endl;
}

Screen::~Screen() {
  SDL_QuitSubSystem(SDL_INIT_EVENTS);
  SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void Screen::render_clear() {
  SDL_RenderClear(m_renderer);
}

void Screen::render_show() {
  SDL_RenderPresent(m_renderer);
}

void Screen::render_set_draw_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
}

void Screen::render_draw_line(const int p_p1_x, const int p_p1_y, const int p_p2_x, const int p_p2_y) {
  SDL_RenderDrawLine(m_renderer, p_p1_x, p_p1_y, p_p2_x, p_p2_y);
}

void Screen::render_draw_triangle(const int p_a_x, const int p_a_y, const int p_b_x, const int p_b_y, const int p_c_x, const int p_c_y) {
  SDL_RenderDrawLine(m_renderer, p_a_x, p_a_y, p_b_x, p_b_y);
  SDL_RenderDrawLine(m_renderer, p_b_x, p_b_y, p_c_x, p_c_y);
  SDL_RenderDrawLine(m_renderer, p_a_x, p_a_y, p_c_x, p_c_y);
}
