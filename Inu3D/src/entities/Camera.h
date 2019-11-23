#pragma once

#include "Common.h"

#include <glm/glm.hpp>

class Camera
{
private:
	glm::vec3 m_position;
	float m_pitch;
	float m_yaw;
	float m_roll;

public:
	Camera();
	~Camera();

	void move(int key);

	inline glm::vec3& get_position() { return m_position; }
	inline float get_pitch() const { return m_pitch; }
	inline float get_yaw() const { return m_yaw; }
	inline float get_roll() const { return m_roll; }
};

