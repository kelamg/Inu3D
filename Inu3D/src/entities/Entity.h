#pragma once

#include "models/TexturedModel.h"

#include <glm/glm.hpp>

class Entity
{
private:
	TexturedModel *m_model;
	glm::vec3 m_position;
	float m_rotx;
	float m_roty;
	float m_rotz;
	float m_scale;

public:
	Entity(
		TexturedModel *model, glm::vec3 position, float rotx, float roty, float rotz, float scale
	);
	~Entity();
	void increase_position(float dx, float dy, float dz);
	void increase_rotation(float dx, float dy, float dz);

	inline TexturedModel* get_model() { return m_model; }
	inline glm::vec3& get_position() { return m_position; }
	inline void set_position(glm::vec3 &position) { m_position = position; }
	inline float get_rotx() const { return m_rotx; }
	inline float get_roty() const { return m_roty; }
	inline float get_rotz() const { return m_rotz; }
	inline float get_scale() const { return m_scale; }
};

