#include "MasterRenderer.h"
#include "renderer/Window.h"

MasterRenderer::MasterRenderer()
{
	enable_culling();
	create_projection_matrix();
	m_shader = new StaticShader();
	m_renderer = new EntityRenderer(m_shader, m_projection_matrix);
	m_entities_map = new std::map<TexturedModel*, vector<Entity*>*>;
	m_terrain_shader = new TerrainShader();
	m_terrain_renderer = new TerrainRenderer(m_terrain_shader, m_projection_matrix);
	m_terrains = new vector<Terrain*>;
}

MasterRenderer::~MasterRenderer()
{
	delete m_entities_map;
	delete m_renderer;
	delete m_shader;
	delete m_terrain_renderer;
	delete m_terrain_shader;
}

void MasterRenderer::clean_up()
{
	m_shader->clean_up();
	m_terrain_shader->clean_up();
}

void MasterRenderer::render(Light *light, Camera *camera)
{
	m_shader->start();
	m_shader->load_light(light);
	m_shader->load_view_matrix(camera);
	m_renderer->render(m_entities_map);
	m_shader->stop();

	m_terrain_shader->start();
	m_terrain_shader->load_light(light);
	m_terrain_shader->load_view_matrix(camera);
	m_terrain_renderer->render(m_terrains);
	m_terrain_shader->stop();

	m_entities_map->clear();
	m_terrains->clear();
}

void MasterRenderer::process_entity(Entity* entity)
{
	TexturedModel *entity_model = entity->get_model();
	std::map<TexturedModel*, vector<Entity*>*>::iterator it;

	it = m_entities_map->find(entity_model);
	if (it != m_entities_map->end()) 
	{
		vector<Entity*>* batch = it->second;
		batch->push_back(entity);
	}
	else 
	{
		vector<Entity*>* new_batch = new vector<Entity*>();
		new_batch->push_back(entity);
		m_entities_map->insert(std::make_pair(entity_model, new_batch));
	}
}

void MasterRenderer::process_terrain(Terrain *terrain)
{
	m_terrains->push_back(terrain);
}

void MasterRenderer::enable_culling()
{
	//	back-face culling
	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glCullFace(GL_BACK));
}

void MasterRenderer::disable_culling()
{
	GLCall(glDisable(GL_CULL_FACE));
}


void MasterRenderer::create_projection_matrix()
{
	float aspect_ratio = window.get_aspect_ratio();;
	float y_scale = (float)((1.0f / tanf(glm::radians(FOV / 2.0f))) * aspect_ratio);
	float x_scale = y_scale / aspect_ratio;
	float frustum_length = FAR_PLANE - NEAR_PLANE;

	glm::mat4 m = glm::mat4(1.0f);
	m[0][0] = x_scale;
	m[1][1] = y_scale;
	m[2][2] = -((FAR_PLANE + NEAR_PLANE) / frustum_length);
	m[2][3] = -1;
	m[3][2] = -((2 * NEAR_PLANE * FAR_PLANE) / frustum_length);
	m[3][3] = 0;

	m_projection_matrix = m;
}
