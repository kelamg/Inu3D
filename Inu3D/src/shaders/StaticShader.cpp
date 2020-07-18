#include "StaticShader.h"
#include "utils/maths/Maths.h"

const string VERTEX_FILE   = RES_LOC + SHA_LOC + "vertexshader.glsl";
const string FRAGMENT_FILE = RES_LOC + SHA_LOC + "fragmentshader.glsl";

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
	bind_attribute(2, "normal");
}

void StaticShader::get_all_uniform_locations()
{
	m_transformation_matrix_location = get_uniform_location("transformation_matrix");
	m_projection_matrix_location = get_uniform_location("projection_matrix");
	m_view_matrix_location = get_uniform_location("view_matrix");
	m_light_position = get_uniform_location("light_position");
	m_light_colour = get_uniform_location("light_colour");
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

void StaticShader::load_light(Light *light)
{
	set_vec3(m_light_position, light->get_position());
	set_vec3(m_light_colour, light->get_colour());
}
