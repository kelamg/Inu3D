#pragma once

#include "Common.h"
#include "renderer/Loader.h"
#include "renderer/EntityRenderer.h"
#include "renderer/TerrainRenderer.h"
#include "shaders/StaticShader.h"
#include "shaders/TerrainShader.h"
#include "models/TexturedModel.h"
#include "entities/Entity.h"
#include "entities/Light.h"
#include "entities/Camera.h"

class MasterRenderer
{
private:
	static constexpr float FOV = 70;
	static constexpr float NEAR_PLANE = 0.1f;
	static constexpr float FAR_PLANE = 1000;
	static constexpr float RED = 0.5f;
	static constexpr float GREEN = 0.5f;
	static constexpr float BLUE = 0.5f;

	glm::mat4 m_projection_matrix;
	StaticShader *m_shader;
	TerrainShader *m_terrain_shader;
	EntityRenderer *m_renderer;
	TerrainRenderer *m_terrain_renderer;
	std::map<TexturedModel*, vector<Entity*>*>* m_entities_map;
	vector<Terrain*>* m_terrains;

	void create_projection_matrix();

	inline glm::mat4 get_projection_matrix() const { return m_projection_matrix; }


public:
	MasterRenderer();
	~MasterRenderer();

	void prepare();
	void clean_up();
	void render(Light *light, Camera *camera);
	void process_entity(Entity *entity);
	void process_terrain(Terrain *terrain);

	static void enable_culling();
	static void disable_culling();
};

