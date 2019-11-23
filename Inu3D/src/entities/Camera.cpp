#include "Camera.h"

Camera::Camera()
{
	m_position = glm::vec3(0, 0, 0);
	m_pitch = 10.0f;
	m_yaw = 0.0f;
	m_roll = 0.0f;
}


Camera::~Camera()
{
}

void Camera::move(int key)
{
	switch (key)
	{
	case GLFW_KEY_W:
		m_position.z -= 0.02f;
		break;
	case GLFW_KEY_D:
		m_position.x += 0.02f;
		break;
	case GLFW_KEY_A:
		m_position.x -= 0.02f;
		break;
	}
}
