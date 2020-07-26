#include "Renderer.h"
#include "renderer/Window.h"

#include <math.h>

Renderer::Renderer(StaticShader *shader)
{
	create_projection_matrix();
	shader->start();
	shader->load_projection_matrix(m_projection_matrix);
	shader->stop();
}


Renderer::~Renderer()
{
}

void Renderer::render(Entity *entity, StaticShader shader)
{
	TexturedModel *model = entity->get_model();
	RawModel *raw_model = model->get_raw_model();
	GLCall(glBindVertexArray(raw_model->get_vao_id()));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glEnableVertexAttribArray(2));

	glm::mat4 transformation_matrix = Maths::create_transformation_matrix(
		entity->get_position(), entity->get_rotx(), entity->get_roty(), entity->get_rotz(), entity->get_scale()
	);
	shader.load_transformation_matrix(transformation_matrix);

	ModelTexture *texture = model->get_texture();
	shader.load_shine_vars(texture->get_shine_damper(), texture->get_reflectivity());

	GLCall(glBindTexture(GL_TEXTURE_2D, model->get_texture()->get_texture_id()));
	GLCall(glDrawElements(GL_TRIANGLES, raw_model->get_vertex_count(), GL_UNSIGNED_INT, 0));
	GLCall(glDisableVertexAttribArray(0));
	GLCall(glDisableVertexAttribArray(1));
	GLCall(glDisableVertexAttribArray(2));
	GLCall(glBindVertexArray(0));
}

void Renderer::create_projection_matrix()
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
