#version 330 core

in vec2 pass_texture_coords;
in vec3 surface_normal;
in vec3 to_light_vector;

out vec4 out_colour;

uniform sampler2D texture_sampler;
uniform vec3 light_colour;

void main()
{
	vec3 unit_normal = normalize(surface_normal);
	vec3 unit_light_vector = normalize(to_light_vector);

	float dotProd = dot(unit_normal, unit_light_vector);
	float brightness = max(dotProd, 0.0); // negative values are irrelevant
	vec3 diffuse = brightness * light_colour;

	out_colour = vec4(diffuse, 1.0) * texture(texture_sampler, pass_texture_coords);
}