#include "Texture.h"

#include "vendor/stb_image/stb_image.h"

Texture::Texture(const string &path)
	: m_texture_id(0), m_filepath(path), m_buffer(nullptr), 
	  m_width(0), m_height(0), m_bpp(0)
{
	stbi_set_flip_vertically_on_load(0);
	m_buffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4);

	GLCall(glGenTextures(1, &m_texture_id));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_texture_id));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_buffer)
		stbi_image_free(m_buffer);
}


Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_texture_id));
}


void Texture::bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_texture_id));
}

void Texture::unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
