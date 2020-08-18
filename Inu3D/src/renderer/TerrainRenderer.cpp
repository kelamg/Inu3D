#include "TerrainRenderer.h"
#include "utils/maths/Maths.h"

TerrainRenderer::TerrainRenderer(TerrainShader *shader, glm::mat4& projection_matrix) 
	: m_shader(shader)
{
	shader->start();
	shader->load_projection_matrix(projection_matrix);
	shader->stop();
}

void TerrainRenderer::render(vector<Terrain*>* terrains)
{
	for (vector<Terrain*>::iterator it = terrains->begin(); it != terrains->end(); it++) 
	{
		Terrain* terrain = *it;
		prepare_terrain(terrain);
		load_model_matrix(terrain);
		glDrawElements(GL_TRIANGLES, terrain->get_model()->get_vertex_count(), GL_UNSIGNED_INT, 0);
		unbind_textured_model();
	}
}

void TerrainRenderer::prepare_terrain(Terrain *terrain)
{
	RawModel *raw_model = terrain->get_model();
	glBindVertexArray(raw_model->get_vao_id());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, terrain->get_texture()->get_texture_id()));
	m_shader->load_shine_vars(1, 1);
}

void TerrainRenderer::unbind_textured_model()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void TerrainRenderer::load_model_matrix(Terrain *terrain)
{
	glm::vec3 pos = glm::vec3(terrain->get_xpos(), 0.0f, terrain->get_zpos());
	glm::mat4 transformation_matrix = Maths::create_transformation_matrix(pos, 0.0f, 0.0f, 0.0f, 1.0f);

	m_shader->load_transformation_matrix(transformation_matrix);
}
