#include "TexturedModel.h"

TexturedModel::TexturedModel(RawModel *model, ModelTexture *texture)
	: m_raw_model(model), m_texture(texture)
{
}


TexturedModel::~TexturedModel()
{
}
