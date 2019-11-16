#pragma once

class RawModel
{
private:
	unsigned int m_vao_id;
	unsigned int m_vertex_count;

public:
	RawModel(unsigned int vao_id, unsigned int vertex_count);
	~RawModel();

	inline unsigned int get_vao_id() { return m_vao_id; }
	inline unsigned int get_vertex_count() { return m_vertex_count;  }
};

