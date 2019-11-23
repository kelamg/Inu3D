#include "Maths.h"

Maths::Maths()
{
}

Maths::~Maths()
{
}

glm::mat4 Maths::create_transformation_matrix(
	glm::vec3& translation, float rx, float ry, float rz, float scale
)
{
	// identity matrix
	glm::mat4 id_mat = glm::mat4(1.0f); 

	//	translation
	glm::mat4 t = glm::translate(id_mat, glm::vec3(translation[0], translation[1], translation[2]));

	//	rotation
	glm::mat4 rotx = glm::rotate(id_mat, glm::radians(rx), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 roty = glm::rotate(id_mat, glm::radians(ry), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotz = glm::rotate(id_mat, glm::radians(rz), glm::vec3(1.0f, 0.0f, 1.0f));
	glm::mat4 r = rotx * roty * rotz;

	//	scale
	glm::mat4 s = glm::scale(id_mat, glm::vec3(scale));

	glm::mat4 m = t * r * s;
	
	return m;
}

glm::mat4 Maths::create_view_matrix(Camera *camera)
{
	glm::mat4 view_matrix = glm::mat4(1.0f); // identity matrix

	//	SRT (scale, rotate, translate)
	view_matrix = glm::rotate(view_matrix, glm::radians(camera->get_pitch()), glm::vec3(1, 0, 0));
	view_matrix = glm::rotate(view_matrix, glm::radians(camera->get_yaw()), glm::vec3(0, 1, 0));

	//	move the world in opposite direction to camera
	glm::vec3 camera_position = camera->get_position();
	glm::vec3 negative_camera_position = glm::vec3(-camera_position[0], -camera_position[1], -camera_position[2]);

	view_matrix = glm::translate(view_matrix, negative_camera_position);

	return view_matrix;
}

