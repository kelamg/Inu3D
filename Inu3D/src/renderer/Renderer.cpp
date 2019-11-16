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
	GLCall(glDrawArrays(GL_TRIANGLES, 0, model->get_vertex_count()));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glBindVertexArray(0));
}
