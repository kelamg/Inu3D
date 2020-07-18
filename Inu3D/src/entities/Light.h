#pragma once

#include "Common.h"

class Light
{
private:
	glm::vec3 m_position;
	glm::vec3 m_colour;

public:
	Light(glm::vec3 position, glm::vec3 colour);
	~Light();

	inline glm::vec3 get_position() const { return m_position; }
	inline glm::vec3 get_colour() const { return m_colour; }
	inline void set_position(glm::vec3 position) { m_position = position; }
	inline void set_colour(glm::vec3 colour) { m_colour = colour; }
};

