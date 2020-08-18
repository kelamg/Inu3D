#pragma once

#include "Common.h"
#include "shaders/TerrainShader.h";
#include "terrains/Terrain.h"

class TerrainRenderer
{
private:
	TerrainShader *m_shader;

public:
	TerrainRenderer(TerrainShader *shader, glm::mat4& projection_matrix);
	void render(vector<Terrain*>* terrains);
	void prepare_terrain(Terrain *terrain);
	void load_model_matrix(Terrain *terrain);
	void unbind_textured_model();

};

