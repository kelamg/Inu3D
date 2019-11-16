#include "Window.h"

const char *APP_NAME = "Inu3D";

Window::Window(const WindowProps& props)
	: m_props(props)
{
	init();
}

void Window::init()
{
	glfwInit();
	if (!glfwInit())
		throw runtime_error("Failed to initialize GLFW");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(get_width(), get_height(), APP_NAME, nullptr, nullptr);
	if (!m_window)
	{
		glfwTerminate();
		throw runtime_error("Failed to initialize GLFW window");
	}

	glfwMakeContextCurrent(m_window);
	glfwSetWindowUserPointer(m_window, this);

	glfwSetKeyCallback(m_window, key_callback);
	glfwSetFramebufferSizeCallback(m_window, framebuffersize_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		throw runtime_error("Failed to initialize GLAD");
	}

	if (with_vsync())
		glfwSwapInterval(1);
}

Window::~Window()
{
	if (m_window)
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}
}

void Window::clear(float x, float y, float z)
{
	glClearColor(x, y, z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::update()
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

auto Window::viewport_did_resize(int width, int height) -> void
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

auto Window::process_input(GLFWwindow *window) -> void
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
