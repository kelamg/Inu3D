#include "TexturedModel.h"

TexturedModel::TexturedModel(RawModel *model, Texture *texture)
	: m_raw_model(model), m_texture(texture)
{
}


TexturedModel::~TexturedModel()
{
}
