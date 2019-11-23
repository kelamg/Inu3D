#include "Entity.h"

Entity::Entity(TexturedModel *model, glm::vec3 position, float rotx, float roty, float rotz, float scale)
	: m_model(model), m_position(position), m_rotx(rotx), m_roty(roty), m_rotz(rotz), m_scale(scale)
{
}

Entity::~Entity()
{
}

void Entity::increase_position(float dx, float dy, float dz)
{
	m_position.x += dx;
	m_position.y += dy;
	m_position.z += dz;
}

void Entity::increase_rotation(float dx, float dy, float dz)
{
	m_rotx += dx;
	m_roty += dy;
	m_rotz += dz;
}
