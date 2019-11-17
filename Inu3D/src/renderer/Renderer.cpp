#include "Renderer.h"

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::render(TexturedModel *textured_model)
{
	RawModel *model = textured_model->get_raw_model();
	GLCall(glBindVertexArray(model->get_vao_id()));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));
	textured_model->get_texture()->bind();
	GLCall(glDrawElements(GL_TRIANGLES, model->get_vertex_count(), GL_UNSIGNED_INT, 0));
	GLCall(glDisableVertexAttribArray(0));
	GLCall(glDisableVertexAttribArray(1));
	GLCall(glBindVertexArray(0));
}
