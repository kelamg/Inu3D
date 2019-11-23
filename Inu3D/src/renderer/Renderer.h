#pragma once

#include "Common.h"
#include "entities/Entity.h"
#include "shaders/StaticShader.h"
#include "utils/maths/Maths.h"

class Renderer
{
private:
	glm::mat4 m_projection_matrix;

	static constexpr float FOV = 70;
	static constexpr float NEAR_PLANE = 0.1f;
	static constexpr float FAR_PLANE = 1000;

	void create_projection_matrix();

	inline glm::mat4 get_projection_matrix() const { return m_projection_matrix; }

public:
	Renderer(StaticShader *shader);
	~Renderer();

	void render(Entity *entity, StaticShader shader);
};

