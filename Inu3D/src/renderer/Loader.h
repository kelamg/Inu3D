#pragma once

#include "vendor/stb_image/stb_image.h"

#include "Common.h"
#include "models/TexturedModel.h"

class Loader
{
private:
	vector<unsigned int> *m_vaos;
	vector<unsigned int> *m_vbos;
	vector<unsigned int> *m_textures;

	unsigned int create_vao();
	unsigned int create_vbo(GLenum target);
	void unbind_vao();
	void store_data_into_attr_list(int index, int tex_coord_size, vector<float> &data);
	void bind_indices_buffer(vector<unsigned int>& indices);

public:
	Loader();
	~Loader();

	RawModel* load_to_vao(
		vector<float> &positions,
		vector<float> &texture_coords,
		vector<float> &normals,
		vector<unsigned int> &indices
	);
	unsigned int load_texture(string file);
	void clean_up();

};

