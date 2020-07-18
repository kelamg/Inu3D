#include "Light.h"

Light::Light(glm::vec3 position, glm::vec3 colour)
	: m_position(position), m_colour(colour)
{
}

Light::~Light()
{
}
