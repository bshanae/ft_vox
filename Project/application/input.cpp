//
// Created by v.belchenko on 18.07.2020.
//
#include_next "common/OpenGL.h"
#include "application/window.h"
#include "input.h"
#include <iostream>

input::input()
{
  for (int i = GLFW_KEY_SPACE; i < GLFW_KEY_LAST; i++)
	keys[i] = key_state::DEFAULT;
}


 void 				input::glfw_callback_key(GLFWwindow *window, int key, int code, int action, int mode)
{
  auto					instance = global<input>::instance();

  if (instance->keys[key] == key_state::RELEASED and action == GLFW_RELEASE)
	instance->keys[key] = key_state::DEFAULT;
  else
	instance->keys[key] = static_cast<key_state>(action);
}

void input::glfw_callback_mouse_movement(GLFWwindow *window, double x, double y)
{
  auto					instance = global<input>::instance();
  if (instance->fist_mouse_move == true)
  {
	instance->fist_mouse_move = false;
	instance->mouse_last_position = ivec2 (x, y);
  }
  instance->mouse_current_position = ivec2 (x, y);
  instance->mouse_offset = ivec2(instance->mouse_current_position.x - instance->mouse_last_position.x,
								 instance->mouse_last_position.y - instance->mouse_current_position.y);
  instance->mouse_last_position = instance->mouse_current_position;

}