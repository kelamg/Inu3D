#pragma once

#include "RawModel.h"
#include "textures/ModelTexture.h"

class TexturedModel
{
private:
	RawModel *m_raw_model;
	ModelTexture *m_texture;

public:
	TexturedModel(RawModel *model, ModelTexture *texture);
	~TexturedModel();

	inline RawModel* get_raw_model() const { return m_raw_model; }
	inline ModelTexture* get_texture() const { return m_texture; }
};

