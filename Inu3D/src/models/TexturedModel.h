#pragma once

#include "RawModel.h"
#include "textures/Texture.h"

class TexturedModel
{
private:
	RawModel *m_raw_model;
	Texture *m_texture;

public:
	TexturedModel(RawModel *model, Texture *texture);
	~TexturedModel();

	inline RawModel* get_raw_model() const { return m_raw_model; }
	inline Texture* get_texture() const { return m_texture; }
};

