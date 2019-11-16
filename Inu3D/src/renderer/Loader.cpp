#include "Loader.h"

Loader::Loader()
{
	m_vaos = new vector<unsigned int>();
	m_vbos = new vector<unsigned int>();
}


Loader::~Loader()
{
	delete m_vaos;
	delete m_vbos;
}

RawModel* Loader::load_to_vao(vector<float> &positions, vector<unsigned int> &indices)
{
	unsigned int vao_id = create_vao();
	bind_indices_buffer(indices);
	store_data_into_attr_list(0, positions);
	unbind_vao();
	return new RawModel(vao_id, indices.size());
}

unsigned int Loader::create_vao()
{
	unsigned int vao_id = 0;
	GLCall(glGenVertexArrays(1, &vao_id));
	m_vaos->push_back(vao_id);
	GLCall(glBindVertexArray(vao_id));
	return vao_id;
}

void Loader::unbind_vao()
{
	GLCall(glBindVertexArray(0));
}

unsigned int Loader::create_vbo(GLenum target)
{
	unsigned int vbo_id = 0;
	GLCall(glGenBuffers(1, &vbo_id));
	m_vbos->push_back(vbo_id);
	GLCall(glBindBuffer(target, vbo_id));
	return vbo_id;
}

void Loader::store_data_into_attr_list(int index, vector<float> &data)
{
	create_vbo(GL_ARRAY_BUFFER);
	GLCall(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW));
	GLCall(glVertexAttribPointer(index, 3, GL_FLOAT, false, 0, 0)); // using vertex positions for now
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void Loader::bind_indices_buffer(vector<unsigned int> &indices)
{
	create_vbo(GL_ELEMENT_ARRAY_BUFFER);
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW));
}
