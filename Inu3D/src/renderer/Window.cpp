#include "Window.h"

const char *APP_NAME = "Inu3D";

Window window;

Window::Window()
{
	m_camera = new Camera();
}

void Window::init(WindowProps &props)
{
	m_props.width = props.width;
	m_props.height = props.height;
	m_props.vsync = props.vsync;

	if (!glfwInit())
		throw runtime_error("Failed to initialize GLFW");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(props.width, props.height, APP_NAME, nullptr, nullptr);
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
	else
		glfwSwapInterval(0);
}

Window::~Window()
{
	delete m_camera;

	if (m_window)
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}
}

void Window::clear(float x, float y, float z)
{
	GLCall(glClearColor(x, y, z, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Window::update()
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

auto Window::viewport_did_resize(int width, int height) -> void
{
	GLCall(glViewport(0, 0, (GLsizei)width, (GLsizei)height));
}

auto Window::process_input(GLFWwindow *window, int key, int action) -> void
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//	Handle key input here for now
	if (action == GLFW_REPEAT)
	{
		cout << key << " pressed" << endl;
		m_camera->move(key);

	}
}
