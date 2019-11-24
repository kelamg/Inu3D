#pragma once

#include "Common.h"

#include <glm/glm.hpp>

class Vertex
{
private:
	static constexpr int NO_INDEX = -1;

	glm::vec3 m_position;
	int m_index;
	int m_texture_index = NO_INDEX;
	int m_normal_index = NO_INDEX;
	Vertex *m_duplicate_vertex = nullptr;

public:
	Vertex(int index, glm::vec3 position);
	~Vertex();

	inline int get_index() const { return m_index; }
	inline int get_texture_index() const { return m_texture_index; }
	inline void set_texture_index(int texture_index) { m_texture_index = texture_index; }
	inline void set_normal_index(int normal_index) { m_normal_index = normal_index; }
	inline int get_normal_index() const { return m_normal_index; }
	inline Vertex* get_duplicate_vertex() const { return m_duplicate_vertex; }
	inline void set_duplicate_vertex(Vertex *duplicate_vertex) { m_duplicate_vertex = duplicate_vertex; }
	inline glm::vec3 get_position() const { return m_position; }
	inline bool is_set() { return m_texture_index != NO_INDEX && m_normal_index != NO_INDEX; }
	inline bool has_same_texture_and_normal(int other_texture_index, int other_normal_index)
	{
		return other_texture_index == m_texture_index && other_normal_index == m_normal_index;
	}

};

