#version 330 core

in vec2 pass_texture_coords;
in vec3 surface_normal;
in vec3 to_light_vector;
in vec3 to_camera_vector;
in float visibility;

out vec4 out_colour;

uniform sampler2D texture_sampler;
uniform vec3 light_colour;
uniform float shine_damper;
uniform float reflectivity;
uniform vec3 sky_colour;

void main()
{
	vec3 unit_normal = normalize(surface_normal);
	vec3 unit_light_vector = normalize(to_light_vector);

	float dot_prod = dot(unit_normal, unit_light_vector);
	float brightness = max(dot_prod, 0.2); // ambient lighting
	vec3 diffuse = brightness * light_colour;

	vec3 unit_vector_to_camera = normalize(to_camera_vector);
	vec3 light_direction = -unit_light_vector;
	vec3 reflected_light_direction = reflect(light_direction, unit_normal);
	
	float specular_factor = dot(reflected_light_direction, unit_vector_to_camera);
	specular_factor = max(specular_factor, 0.0);
	float damped_factor = pow(specular_factor, shine_damper);
	vec3 final_specular = damped_factor * reflectivity * light_colour;

	// transparency
	vec4 texture_colour = texture(texture_sampler, pass_texture_coords);
	if (texture_colour.a < 0.5)
	{
		discard;
	}

	out_colour = vec4(diffuse, 1.0) * texture_colour + vec4(final_specular, 1.0);
	out_colour = mix(vec4(sky_colour, 1.0), out_colour, visibility);
}