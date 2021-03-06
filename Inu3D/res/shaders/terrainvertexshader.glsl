#version 330 core

in vec3 position;
in vec2 texture_coords;
in vec3 normal;

out vec2 pass_texture_coords;
out vec3 surface_normal;
out vec3 to_light_vector;
out vec3 to_camera_vector;
out float visibility;

uniform mat4 transformation_matrix;
uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform vec3 light_position;

const float density = 0.007;
const float gradient = 1.5;

void main()
{
	vec4 world_position = transformation_matrix * vec4(position, 1.0);
	vec4 position_relative_to_cam = view_matrix * world_position;
	gl_Position = projection_matrix * position_relative_to_cam;
	pass_texture_coords = texture_coords * 20.0; // multi-tilling

	//	multiply the surface normal by the transformation matrix 
	//	to account handle rotated models
	surface_normal = (transformation_matrix * vec4(normal, 0.0)).xyz;
	to_light_vector = light_position - world_position.xyz;
	to_camera_vector = (inverse(view_matrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - world_position.xyz;

	float distance = length(position_relative_to_cam.xyz);
	visibility = exp(-pow((distance * density), gradient));
	visibility = clamp(visibility, 0.0, 1.0);
}