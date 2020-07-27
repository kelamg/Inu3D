#pragma once

#include "Common.h"
#include "entities/Entity.h"
#include "shaders/StaticShader.h"
#include "utils/maths/Maths.h"

class Renderer
{
private:
	glm::mat4 m_projection_matrix;
	StaticShader *m_shader;

	static constexpr float FOV = 70;
	static constexpr float NEAR_PLANE = 0.1f;
	static constexpr float FAR_PLANE = 1000;

	void create_projection_matrix();

	inline glm::mat4 get_projection_matrix() const { return m_projection_matrix; }

public:
	Renderer(StaticShader *shader);
	~Renderer();

	void render(std::map<TexturedModel*, vector<Entity*>*>* entities);
	void prepare_textured_model(TexturedModel *model);
	void unbind_textured_model();
	void prepare_instance(Entity *entity);
};

