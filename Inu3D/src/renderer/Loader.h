#pragma once

#include "Common.h"
#include "models/RawModel.h"

class Loader
{
private:
	vector<unsigned int> *m_vaos;
	vector<unsigned int> *m_vbos;

	unsigned int create_vao();
	unsigned int create_vbo(GLenum target);
	void unbind_vao();
	void store_data_into_attr_list(int index, vector<float> &data);
	void bind_indices_buffer(vector<unsigned int> &indices);

public:
	Loader();
	~Loader();

	RawModel* load_to_vao(
		vector<float> &positions,
		vector<unsigned int> &indices
	);

};

