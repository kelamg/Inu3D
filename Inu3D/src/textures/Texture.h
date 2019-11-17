#pragma once

#include "Common.h"

class Texture
{
private:
	unsigned int m_texture_id;
	std::string m_filepath;
	unsigned char *m_buffer;
	int m_width;
	int m_height;
	int m_bpp;

public:
	Texture(const std::string &path);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;

	inline unsigned int get_texture_id() const { return m_texture_id; }
	inline int get_width() const { return m_width; }
	inline int get_height() const { return m_height; }
};

