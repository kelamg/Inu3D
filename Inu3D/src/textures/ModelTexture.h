#pragma once

#include "Common.h"

class ModelTexture
{
private:
	unsigned int m_texture_id;
	std::string m_filepath;
	unsigned char *m_buffer;
	int m_width;
	int m_height;
	int m_bpp;
	float m_shine_damper = 1;
	float m_reflectivity = 0;
	bool m_has_transparency = false;
	bool m_use_fake_lighting = false;

public: 
	ModelTexture(unsigned int texture_id);
	~ModelTexture();

	inline unsigned int get_texture_id() const { return m_texture_id; }
	inline int get_width() const { return m_width; }
	inline int get_height() const { return m_height; }
	inline int get_shine_damper() const { return m_shine_damper; }
	inline int get_reflectivity() const { return m_reflectivity; }
	inline bool get_has_transparency() const { return m_has_transparency; }
	inline bool get_use_fake_lighting() const { return m_use_fake_lighting; }
	inline void set_shine_damper(float shine_damper) { m_shine_damper = shine_damper; }
	inline void set_reflectivity(float reflectivity) { m_reflectivity = reflectivity; }
	inline void set_has_transparency(bool has_transparency) { m_has_transparency = has_transparency; }
	inline void set_use_fake_lighting(bool use_fake_lighting) { m_use_fake_lighting = use_fake_lighting; }

};

