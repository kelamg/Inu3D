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
		-0.5f,  0.5f, 0, // v0
		-0.5f, -0.5f, 0, // v1
		 0.5f, -0.5f, 0, // v2
		 0.5f,  0.5f, 0, // v3
	};

	vector<unsigned int> indices = {
		0, 1, 3, 
		3, 1, 2
	};

	vector<float> texture_coords = {
		0, 0, // v0
		0, 1, // v1
		1, 1, // v2
		1, 0  // v3
	};

	RawModel *model = loader.load_to_vao(vertices, texture_coords, indices);
	Texture *texture = loader.load_texture("res/textures/pepe.png");
	TexturedModel *textured_model = new TexturedModel(model, texture);
	Entity *entity = new Entity(textured_model, glm::vec3(0, 0, -1), 0.0, 0.0, 0.0, 1.0);

	while (!window.is_running())
	{
		entity->increase_position(0, 0, -0.01f);
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