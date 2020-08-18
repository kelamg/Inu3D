#pragma once

#include "Common.h"
#include "entities/Entity.h"
#include "shaders/StaticShader.h"
#include "utils/maths/Maths.h"

class EntityRenderer
{
private:
	StaticShader *m_shader;

public:
	EntityRenderer(StaticShader *shader, glm::mat4 &projection_matrix);
	~EntityRenderer();

	void render(std::map<TexturedModel*, vector<Entity*>*>* entities);
	void prepare_textured_model(TexturedModel *model);
	void unbind_textured_model();
	void prepare_instance(Entity *entity);
};

