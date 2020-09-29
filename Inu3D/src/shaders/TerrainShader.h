#pragma once

#include "ShaderProgram.h"
#include "entities/Camera.h"
#include "entities/Light.h"

class TerrainShader : public ShaderProgram
{
private:
	//	locations
	int m_transformation_matrix_location;
	int m_projection_matrix_location;
	int m_view_matrix_location;
	int m_light_position;
	int m_light_colour;
	int m_shine_damper;
	int m_reflectivity;
	int m_sky_colour;

public:
	TerrainShader();
	~TerrainShader();
	void bind_attributes();
	void get_all_uniform_locations();

	void load_transformation_matrix(const glm::mat4 &matrix);
	void load_projection_matrix(const glm::mat4 &matrix);
	void load_view_matrix(Camera *camera);
	void load_light(Light *light);
	void load_shine_vars(float damper, float reflectivity);
	void load_sky_colour(float r, float g, float b);

};

