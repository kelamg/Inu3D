#include "Terrain.h"

Terrain::Terrain(int grid_x, int grid_y, Loader* loader, ModelTexture* texture)
	: m_xpos(grid_x * SIZE), m_zpos(grid_y * SIZE), m_texture(texture), m_model(generate_terrain(loader))
{
}

RawModel* Terrain::generate_terrain(Loader* loader)
{
	int count = VERTEX_COUNT * VERTEX_COUNT;

	float *vertices = new float[count * 3];
	float *normals = new float[count * 3];
	float *texture_coords = new float[count * 3];
	unsigned int *indices = new unsigned int[6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1)];

	int vertex_pointer = 0;
	for (int i = 0; i < VERTEX_COUNT; i++) 
	{
		for (int j = 0; j < VERTEX_COUNT; j++) 
		{
			vertices[vertex_pointer * 3] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
			vertices[vertex_pointer * 3 + 1] = 0;
			vertices[vertex_pointer * 3 + 2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;

			normals[vertex_pointer * 3] = 0;
			normals[vertex_pointer * 3 + 1] = 1;
			normals[vertex_pointer * 3 + 2] = 0;

			texture_coords[vertex_pointer * 2] = (float)j / ((float)VERTEX_COUNT - 1);
			texture_coords[vertex_pointer * 2 + 1] = (float)i / ((float)VERTEX_COUNT - 1);
			vertex_pointer++;
		}
	}

	unsigned int *ptr = indices;
	for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) 
	{
		for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) 
		{
			unsigned int top_left = (gz * VERTEX_COUNT) + gx;
			unsigned int top_right = top_left + 1;
			unsigned int bottom_left = ((gz + 1) * VERTEX_COUNT) + gx;
			unsigned int bottom_right = bottom_left + 1;
			*(ptr++) = top_left;
			*(ptr++) = bottom_left;
			*(ptr++) = top_right;
			*(ptr++) = top_right;
			*(ptr++) = bottom_left;
			*(ptr++) = bottom_right;
		}
	}

	//	convert arrays to vectors
	vector<float> v(vertices, vertices + (count * 3));
	vector<float> t(texture_coords, texture_coords + (count * 3));
	vector<float> n(normals, normals + (count * 3));
	vector<unsigned int> i(indices, indices + (6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1)));
	delete[] vertices;
	delete[] texture_coords;
	delete[] normals;
	delete[] indices;
	return loader->load_to_vao(v, t, n, i);
}

