#pragma once

#include "ShaderProgram.h"
#include "entities/Light.h"
#include "entities/Camera.h"

class StaticShader : public ShaderProgram
{
private:
	int m_transformation_matrix_location;
	int m_projection_matrix_location;
	int m_view_matrix_location;
	int m_light_position;
	int m_light_colour;

public:
	StaticShader();
	~StaticShader();
	void bind_attributes();
	void get_all_uniform_locations();

	void load_transformation_matrix(const glm::mat4 &matrix);
	void load_projection_matrix(const glm::mat4 &matrix);
	void load_view_matrix(Camera *camera);
	void load_light(Light *light);

};

