#include "Renderer.h"

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::render(RawModel *model)
{
	GLCall(glBindVertexArray(model->get_vao_id()));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glDrawElements(GL_TRIANGLES, model->get_vertex_count(), GL_UNSIGNED_INT, 0));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glBindVertexArray(0));
}
