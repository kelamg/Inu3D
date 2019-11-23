#include "renderer/Window.h"
#include "renderer/Loader.h"
#include "renderer/Renderer.h"
#include "shaders/StaticShader.h"
#include "entities/Entity.h"

int main(void)
{
	WindowProps window_props = { 800, 600, true };
	window.init(window_props); // window global

	Loader loader;
	StaticShader shader;
	Renderer renderer(&shader);

	vector<float> vertices = {
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f
	};

	vector<unsigned int> indices = {
		 0,  1,  3,
		 3,  1,  2,
		 4,  5,  7,
		 7,  5,  6,
		 8,  9, 11,
		11,  9, 10,
		12, 13, 15,
		15, 13, 14,
		16, 17, 19,
		19, 17, 18,
		20, 21, 23,
		23, 21, 22
	};

	vector<float> texture_coords = {
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0
	};

	RawModel *model = loader.load_to_vao(vertices, texture_coords, indices);
	Texture *texture = loader.load_texture("res/textures/pepe.png");
	TexturedModel *textured_model = new TexturedModel(model, texture);
	Entity *entity = new Entity(textured_model, glm::vec3(0, 0, -5), 0.0, 0.0, 0.0, 1.0);

	while (!window.is_running())
	{
		entity->increase_rotation(1, 1, 0);
		window.clear(0.1f, 0.2f, 0.3f);
		shader.start();
		shader.load_view_matrix(window.get_camera());
		renderer.render(entity, shader);
		shader.stop();
		window.update();
	}

	shader.clean_up();

	return 0;
}