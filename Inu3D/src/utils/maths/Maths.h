#pragma once

#include "entities/Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Maths
{
public:
	Maths();
	~Maths();

	static glm::mat4 create_transformation_matrix(
		glm::vec3& translation,
		float rx, float ry, float rz,
		float scale
	);

	static glm::mat4 create_view_matrix(Camera *camera);
};

