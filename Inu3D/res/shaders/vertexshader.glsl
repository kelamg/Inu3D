#version 330 core

in vec3 position;
in vec2 texture_coords;
in vec3 normal;

out vec2 pass_texture_coords;
out vec3 surface_normal;
out vec3 to_light_vector;

uniform mat4 transformation_matrix;
uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform vec3 light_position;

void main()
{
	vec4 world_position = transformation_matrix * vec4(position, 1.0);
	gl_Position = projection_matrix * view_matrix * world_position;
	pass_texture_coords = texture_coords;

	//	multiply the surface normal by the transformation matrix 
	//	to account handle rotated models
	surface_normal = (transformation_matrix * vec4(normal, 0.0)).xyz;
	to_light_vector = light_position - world_position.xyz;
}