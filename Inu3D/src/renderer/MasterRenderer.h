#pragma once

#include "Common.h"
#include "renderer/Loader.h"
#include "renderer/Renderer.h"
#include "shaders/StaticShader.h"
#include "models/TexturedModel.h"
#include "entities/Entity.h"
#include "entities/Light.h"
#include "entities/Camera.h"

class MasterRenderer
{
private:
	StaticShader* m_shader;
	Renderer *m_renderer;
	std::map<TexturedModel*, vector<Entity*>*>* m_entities_map;

public:
	MasterRenderer();
	~MasterRenderer();

	void clean_up();
	void render(Light *light, Camera *camera);
	void process_entity(Entity *entity);
};

