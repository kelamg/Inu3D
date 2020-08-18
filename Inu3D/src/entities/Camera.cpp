#include "Camera.h"

Camera::Camera()
{
	m_position = glm::vec3(0, 10, 100);
	m_pitch = 0.0f;
	m_yaw = 0.0f;
	m_roll = 0.0f;
}


Camera::~Camera()
{
}

void Camera::move(int key)
{
	float camera_speed = 1.5f;
	switch (key)
	{
	case GLFW_KEY_W:
		m_position.z -= camera_speed;
		break;
	case GLFW_KEY_A:
		m_position.x -= camera_speed;
		break;
	case GLFW_KEY_S:
		m_position.z += camera_speed;
		break;
	case GLFW_KEY_D:
		m_position.x += camera_speed;
		break;
	}
}
