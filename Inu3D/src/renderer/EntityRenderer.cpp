#include "EntityRenderer.h"
#include "MasterRenderer.h"

#include <math.h>

EntityRenderer::EntityRenderer(StaticShader* shader, glm::mat4 &projection_matrix) 
	: m_shader(shader)
{
	shader->start();
	shader->load_projection_matrix(projection_matrix);
	shader->stop();
}


EntityRenderer::~EntityRenderer()
{
}

void EntityRenderer::render(std::map<TexturedModel*, vector<Entity*>*>* entities)
{
	for (std::map<TexturedModel*, vector<Entity*>*>::iterator it = entities->begin();
		it != entities->end(); it++) 
	{
		TexturedModel* model = (*it).first;

		prepare_textured_model(model);

		it = entities->find(model);
		if (it != entities->end()) 
		{
			vector<Entity*>* batch = it->second;

			for (vector<Entity*>::iterator vit = batch->begin(); vit != batch->end(); vit++) 
			{
				Entity* entity = *vit;
				prepare_instance(entity);
				GLCall(glDrawElements(GL_TRIANGLES, model->get_raw_model()->get_vertex_count(), GL_UNSIGNED_INT, 0));
			}
		}

		unbind_textured_model();
	}
}

void EntityRenderer::prepare_textured_model(TexturedModel* model)
{
	RawModel *raw_model = model->get_raw_model();
	GLCall(glBindVertexArray(raw_model->get_vao_id()));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glEnableVertexAttribArray(2));

	ModelTexture *texture = model->get_texture();
	if (texture->get_has_transparency())
	{
		MasterRenderer::disable_culling();
	}
	m_shader->load_shine_vars(texture->get_shine_damper(), texture->get_reflectivity());
	m_shader->load_fake_lighting_var(texture->get_use_fake_lighting());
	GLCall(glBindTexture(GL_TEXTURE_2D, model->get_texture()->get_texture_id()));
}

void EntityRenderer::unbind_textured_model()
{
	MasterRenderer::enable_culling();
	GLCall(glDisableVertexAttribArray(0));
	GLCall(glDisableVertexAttribArray(1));
	GLCall(glDisableVertexAttribArray(2));
	GLCall(glBindVertexArray(0));
}

void EntityRenderer::prepare_instance(Entity* entity)
{
	glm::mat4 transformation_matrix = Maths::create_transformation_matrix(
		entity->get_position(), entity->get_rotx(), entity->get_roty(), entity->get_rotz(), entity->get_scale()
	);
	m_shader->load_transformation_matrix(transformation_matrix);
}

