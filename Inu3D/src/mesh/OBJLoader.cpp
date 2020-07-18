#include "OBJLoader.h"

#include <iostream>
#include <fstream>
#include <sstream>

RawModel* OBJLoader::load_obj_model(string &filename, Loader *loader)
{
	string path = RES_LOC + OBJ_LOC + filename;
	std::ifstream infile(path);
	if (!infile)
	{
		cerr << "OBJLoader: File " << filename << " could not be opened" << endl;
		exit(1);
	}

	string line;
	vector<Vertex *> vertices;
	vector<glm::vec2> textures;
	vector<glm::vec3> normals;
	vector<unsigned int> indices;

	//	get the vertices, texture coordinates and normals from the obj file
	while (!infile.eof())
	{
		float x, y, z;
		string starting_letter;

		getline(infile, line);
		std::istringstream iss(line);

		//	lines in .obj file start with v, vn, vt, s, f etc
		iss >> starting_letter;
		if (starting_letter == "v")
		{
			iss >> x >> y >> z;
			glm::vec3 vertex(x, y, z);
			Vertex *new_vertex = new Vertex(vertices.size(), vertex);
			vertices.push_back(new_vertex);
		}
		else if (starting_letter == "vt")
		{
			iss >> x >> y >> z;
			glm::vec2 texture(x, y);
			textures.push_back(texture);
		}
		else if (starting_letter == "vn")
		{
			iss >> x >> y >> z;
			glm::vec3 normal(x, y, z);
			normals.push_back(normal);
		}
		else if (starting_letter == "f")
		{
			//	break out of the loop upon reaching the faces section of the file
			break;
		}
	}

	//	parse the faces (lines beginning with "f")
	vector<float> vertices_arr;
	vector<float> normals_arr;
	vector<float> textures_arr;
	vector<unsigned int> indices_arr;

	while (!infile.eof())
	{
		if (line == "")
			break;

		std::istringstream iss(line);
		string starting_letter;
		constexpr size_t num_val = 9; // there are 9 values to extract for each line
		unsigned int val_arr[num_val]; 

		iss >> starting_letter;
		if (starting_letter == "f")
		{
			//	f 10/1/2 20/3/4 30/5/6
			string tmp, f;
			for (int i = 0; i < 3; i++)
			{
				iss >> tmp;
				f += tmp + " ";
			}

			//	replace all '/' with space
			size_t x = f.find("/");
			while (x < string::npos)
			{
				f.replace(x, 1, " ");
				x = f.find("/", x + 1);
			}

			std::istringstream issb(f);
			for (size_t i = 0; i < num_val; i++)
			{
				issb >> val_arr[i];
				val_arr[i]--; // compensate for the indices in the .obj file which start from 1
			}

			process_vertex(val_arr[0], val_arr[1], val_arr[2], vertices, indices);
			process_vertex(val_arr[3], val_arr[4], val_arr[5], vertices, indices);
			process_vertex(val_arr[6], val_arr[7], val_arr[8], vertices, indices);
		}

		getline(infile, line);
	}

	remove_unused_vertices(vertices);
	convert_data_to_arrs(vertices, textures, normals, vertices_arr, textures_arr, normals_arr);

	for (size_t i = 0; i < indices.size(); i++) 
	{
		unsigned int idx = indices[i];
		indices_arr.push_back(idx);
	}

	//	free allocated Vertex objects
	for (size_t i = 0; i < vertices.size(); i++) 
	{
		delete vertices[i];
	}

	return loader->load_to_vao(vertices_arr, textures_arr, normals_arr, indices_arr);
}

void OBJLoader::process_vertex(
	int index, int texture_index, int normal_index, 
	vector<Vertex *> &vertices, vector<unsigned int> &indices
)
{
	Vertex *current_vertex = vertices[index];
	if (!current_vertex->is_set())
	{
		current_vertex->set_texture_index(texture_index);
		current_vertex->set_normal_index(normal_index);
		indices.push_back(index);
	}
	else
	{
		reprocess_vertex(current_vertex, texture_index, normal_index, indices, vertices);
	}
}

void OBJLoader::convert_data_to_arrs(
	vector<Vertex *> &vertices,
	vector<glm::vec2> &textures,
	vector<glm::vec3> &normals,
	vector<float> &vertices_arr,
	vector<float> &textures_arr,
	vector<float> &normals_arr
)
{
	for (size_t i = 0; i < vertices.size(); i++)
	{
		Vertex *current_vertex = vertices[i];

		glm::vec3 position = current_vertex->get_position();
		glm::vec2 texture_coord = textures[current_vertex->get_texture_index()];
		glm::vec3 normal_vector = normals[current_vertex->get_normal_index()];

		vertices_arr.push_back(position[0]);
		vertices_arr.push_back(position[1]);
		vertices_arr.push_back(position[2]);
		textures_arr.push_back(texture_coord[0]);
		
		//	1 minus because OpenGL tex_coords start from top left, blender starts from bottom left
		textures_arr.push_back(1.0f - texture_coord[1]); 
		normals_arr.push_back(normal_vector[0]);
		normals_arr.push_back(normal_vector[1]);
		normals_arr.push_back(normal_vector[2]);
	}
}

void OBJLoader::remove_unused_vertices(vector<Vertex *> &vertices)
{
	vector<Vertex *>::iterator it;
	for (it = vertices.begin(); it != vertices.end(); it++)
	{
		Vertex *vertex = *it;
		if (!vertex->is_set())
		{
			vertex->set_texture_index(0);
			vertex->set_normal_index(0);
		}
	}
}

void OBJLoader::reprocess_vertex(
	Vertex *previous_vertex, 
	int new_texture_index, 
	int new_normal_index, 
	vector<unsigned int> &indices, 
	vector<Vertex *> &vertices
)
{
	//	account for texture seams using duplicate vertices
	if (previous_vertex->has_same_texture_and_normal(new_texture_index, new_normal_index))
	{
		indices.push_back(previous_vertex->get_index());
	}
	else
	{
		Vertex *another_vertex = previous_vertex->get_duplicate_vertex();
		if (another_vertex != nullptr)
		{
			reprocess_vertex(another_vertex, new_texture_index, new_normal_index, indices, vertices);
		}
		else
		{
			Vertex *duplicate_vertex = new Vertex(vertices.size(), previous_vertex->get_position());
			duplicate_vertex->set_texture_index(new_texture_index);
			duplicate_vertex->set_normal_index(new_normal_index);
			previous_vertex->set_duplicate_vertex(duplicate_vertex);
			vertices.push_back(duplicate_vertex);
			indices.push_back(duplicate_vertex->get_index());
		}
	}
}
