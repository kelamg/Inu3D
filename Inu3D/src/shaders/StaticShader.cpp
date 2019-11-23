#include "StaticShader.h"

const string VERTEX_FILE   = "res/shaders/vertexshader.glsl";
const string FRAGMENT_FILE = "res/shaders/fragmentshader.glsl";

StaticShader::StaticShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
	bind_attributes();
	link_program();
	get_all_uniform_locations();
}


StaticShader::~StaticShader()
{
}

void StaticShader::bind_attributes()
{
	bind_attribute(0, "position");
	bind_attribute(1, "texture_coords");
}

void StaticShader::get_all_uniform_locations()
{
	m_transformation_matrix_location = get_uniform_location("transformation_matrix");
	m_projection_matrix_location = get_uniform_location("projection_matrix");
	m_view_matrix_location = get_uniform_location("view_matrix");
}

void StaticShader::load_transformation_matrix(const glm::mat4 &matrix)
{
	set_mat4(m_transformation_matrix_location, matrix);
}

void StaticShader::load_projection_matrix(const glm::mat4 &matrix)
{
	set_mat4(m_projection_matrix_location, matrix);
}

void StaticShader::load_view_matrix(Camera *camera)
{
	glm::mat4 view_matrix = Maths::create_view_matrix(camera);
	set_mat4(m_view_matrix_location, view_matrix);
}
