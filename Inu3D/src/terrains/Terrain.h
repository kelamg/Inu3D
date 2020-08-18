#pragma once

#include "Common.h"
#include "models/RawModel.h"
#include "textures/ModelTexture.h"
#include "renderer/Loader.h"

class Terrain
{
private:
	static constexpr float SIZE = 800;
	static constexpr int VERTEX_COUNT = 128;

	float m_xpos;
	float m_zpos;
	RawModel *m_model;
	ModelTexture *m_texture;

	RawModel* generate_terrain(Loader *loader);

public:
	Terrain(int grid_x, int grid_y, Loader *loader, ModelTexture *texture);

	inline float get_xpos() const { return m_xpos; }
	inline float get_zpos() const { return m_zpos; }
	inline RawModel* get_model() const { return m_model; }
	inline ModelTexture* get_texture() const { return m_texture; }
};

