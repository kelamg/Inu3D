#pragma once

#include "Common.h"
#include "entities/Camera.h"

struct WindowProps
{
	unsigned int width;
	unsigned int height;
	bool vsync;
};

class Window
{
private:
	GLFWwindow *m_window;
	WindowProps m_props;

	//	keep the camera instance here for now
	Camera *m_camera;

	inline static auto framebuffersize_callback(GLFWwindow *gl_window, int width, int height) -> void
	{
		Window *window = static_cast<Window *>(glfwGetWindowUserPointer(gl_window));
		window->viewport_did_resize(width, height);
	}
	inline static auto key_callback(GLFWwindow *gl_window, int key, int scancode, int action, int mods) -> void
	{
		Window *window = static_cast<Window *>(glfwGetWindowUserPointer(gl_window));
		window->process_input(gl_window, key, action);
	}
	
public:
	Window();
	~Window();
	void init(WindowProps &props);
	void clear(float x, float y, float z);
	void update();

	auto viewport_did_resize(int width, int height) -> void;
	auto process_input(GLFWwindow *window, int key, int action) -> void;

	inline bool is_running() const { return !glfwWindowShouldClose(m_window); }
	inline unsigned int get_width() const { return m_props.width; }
	inline unsigned int get_height() const { return m_props.height; }
	inline unsigned int with_vsync() const { return m_props.vsync; }
	inline float get_aspect_ratio() const { return ((float)m_props.width) / m_props.height; }
	inline Camera* get_camera() const { return m_camera; }
};

extern Window window;
