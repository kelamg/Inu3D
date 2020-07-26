#include "Loader.h"

Loader::Loader()
{
	m_vaos = new vector<unsigned int>();
	m_vbos = new vector<unsigned int>();
	m_textures = new vector<unsigned int>();
}


Loader::~Loader()
{
	delete m_vaos;
	delete m_vbos;
	delete m_textures;
}

RawModel* Loader::load_to_vao(
	vector<float> &positions,
	vector<float> &texture_coords,
	vector<float> &normals,
	vector<unsigned int> &indices
)
{
	unsigned int vao_id = create_vao();
	bind_indices_buffer(indices);
	store_data_into_attr_list(0, 3, positions);
	store_data_into_attr_list(1, 2, texture_coords);
	store_data_into_attr_list(2, 3, normals);
	unbind_vao();
	return new RawModel(vao_id, indices.size());
}

unsigned int Loader::load_texture(string file)
{
	unsigned int texture_id;
	int texture_width, texture_height, texture_bpp;
	unsigned char *buffer;
	
	file = RES_LOC + TEX_LOC + file;

	stbi_set_flip_vertically_on_load(0);
	buffer = stbi_load(file.c_str(), &texture_width, &texture_height, &texture_bpp, 4);

	GLCall(glGenTextures(1, &texture_id));
	GLCall(glBindTexture(GL_TEXTURE_2D, texture_id));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	m_textures->push_back(texture_id);

	if (buffer)
		stbi_image_free(buffer);

	return texture_id;
}

void Loader::clean_up()
{
	vector<unsigned int>::iterator it;

	for (it = m_vaos->begin(); it != m_vaos->end(); it++)
		glDeleteVertexArrays(1, &*it);
	m_vaos->clear();

	for (it = m_vbos->begin(); it != m_vbos->end(); it++)
		glDeleteBuffers(1, &*it);
	m_vbos->clear();

	for (it = m_textures->begin(); it != m_textures->end(); it++)
		glDeleteTextures(1, &*it);
	m_textures->clear();
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

void Loader::store_data_into_attr_list(int index, int tex_coord_size, vector<float> &data)
{
	create_vbo(GL_ARRAY_BUFFER);
	GLCall(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW));
	GLCall(glVertexAttribPointer(index, tex_coord_size, GL_FLOAT, false, 0, 0)); 
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void Loader::bind_indices_buffer(vector<unsigned int> &indices)
{
	create_vbo(GL_ELEMENT_ARRAY_BUFFER);
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW));
}
