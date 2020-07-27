#include "MasterRenderer.h"

MasterRenderer::MasterRenderer()
{
	m_shader = new StaticShader();
	m_renderer = new Renderer(m_shader);
	m_entities_map = new std::map<TexturedModel*, vector<Entity*>*>;
}

MasterRenderer::~MasterRenderer()
{
	delete m_entities_map;
	delete m_renderer;
	delete m_shader;
}

void MasterRenderer::clean_up()
{
	m_shader->clean_up();
}

void MasterRenderer::render(Light *light, Camera *camera)
{
	m_shader->start();
	m_shader->load_light(light);
	m_shader->load_view_matrix(camera);
	m_renderer->render(m_entities_map);
	m_shader->stop();
	m_entities_map->clear();
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
