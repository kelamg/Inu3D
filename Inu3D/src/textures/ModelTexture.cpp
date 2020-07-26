#include "ModelTexture.h"

ModelTexture::ModelTexture(unsigned int texture_id) 
	: m_texture_id(texture_id), m_buffer(nullptr), m_width(0), m_height(0), m_bpp(0)
{
}

ModelTexture::~ModelTexture()
{
}
