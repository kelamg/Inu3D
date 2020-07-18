#include "renderer/Window.h"
#include "renderer/Loader.h"
#include "renderer/Renderer.h"
#include "shaders/StaticShader.h"
#include "entities/Entity.h"
#include "mesh/OBJLoader.h"

int main(void)
{
	WindowProps window_props = { 800, 600, true };
	window.init(window_props); // window global

	Loader loader;
	StaticShader shader;
	Renderer renderer(&shader);

	string model_file = "dragon/dragon.obj";
	RawModel *model = OBJLoader::load_obj_model(model_file, &loader);
	Texture *stall_texture = loader.load_texture("stall_tex.png");
	Texture *dragon_texture = loader.load_texture("snow-layer.png");
	TexturedModel *textured_model = new TexturedModel(model, dragon_texture);

	Entity *entity = new Entity(textured_model, glm::vec3(0, -10, -30), 0.0, 0.0, 0.0, 1.0);
	Light* light = new Light(glm::vec3(0, 0, -20), glm::vec3(1, 1, 1));

	while (window.is_running())
	{
		entity->increase_rotation(0, 1, 0);
		window.clear(0.1f, 0.2f, 0.3f);
		shader.start();
		shader.load_light(light);
		shader.load_view_matrix(window.get_camera());
		renderer.render(entity, shader);
		shader.stop();
		window.update();
	}

	shader.clean_up();

	return 0;
}