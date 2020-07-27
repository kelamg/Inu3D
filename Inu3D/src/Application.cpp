#include "renderer/Window.h"
#include "renderer/Loader.h"
#include "renderer/MasterRenderer.h"
#include "shaders/StaticShader.h"
#include "entities/Entity.h"
#include "mesh/OBJLoader.h"

int main(void)
{
	WindowProps window_props = { 800, 600, true };
	window.init(window_props); // window global

	Loader loader;
	MasterRenderer renderer;

	string dragon = "dragon/dragon.obj";
	string stall = "stall/stall.obj";
	string dragon_texture = "snow-layer.png";
	string stall_texture = "stall_tex.png";
	RawModel *model = OBJLoader::load_obj_model(dragon, &loader);
	TexturedModel *textured_model = new TexturedModel(model, new ModelTexture(loader.load_texture(dragon_texture)));
	ModelTexture *texture = textured_model->get_texture();
	texture->set_shine_damper(10);
	texture->set_reflectivity(1);

	Entity *entity = new Entity(textured_model, glm::vec3(0, -10, -30), 0.0, 0.0, 0.0, 1.0);
	Light* light = new Light(glm::vec3(0, 0, -20), glm::vec3(1, 1, 1));

	//	performance
	double previous_time = glfwGetTime();
	int nb_frames = 0;

	while (window.is_running())
	{
		double current_time = glfwGetTime();
		nb_frames++;
		if (current_time - previous_time >= 1.0) // if previous print was more than a second ago
		{
			//	16.666ms is 60fps, 33.333 is 30fps
			cout << 1000.0 / double(nb_frames) << " ms/frame" << endl;
			nb_frames = 0;
			previous_time += 1.0;
		}

		entity->increase_rotation(0, 1, 0);
		window.clear(0.1f, 0.2f, 0.3f);
		renderer.process_entity(entity);
		renderer.render(light, window.get_camera());
		window.update();
	}

	loader.clean_up();
	renderer.clean_up();

	return 0;
}