#pragma once

#include "Common.h"
#include "renderer/Loader.h"
#include "Vertex.h"

#include <glm/glm.hpp>

class OBJLoader
{
private:
	static void process_vertex(
		int index, int texture_index, int normal_index,
		vector<Vertex *> &vertices, vector<unsigned int> &indices
	);
	static void convert_data_to_arrs(
		vector<Vertex *> &vertices,
		vector<glm::vec2> &textures,
		vector<glm::vec3> &normals,
		vector<float> &vertices_arr,
		vector<float> &textures_arr,
		vector<float> &normals_arr
	);
	static void remove_unused_vertices(vector<Vertex *> &vertices);
	static void reprocess_vertex(
		Vertex *previous_vertex,
		int new_texture_index,
		int new_normal_index,
		vector<unsigned int> &indices,
		vector<Vertex *> &vertices
	);

public:
	static RawModel* load_obj_model(string &filename, Loader *loader);

};
