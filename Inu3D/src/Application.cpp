#include "renderer/Window.h"
#include "renderer/Loader.h"
#include "renderer/MasterRenderer.h"
#include "shaders/StaticShader.h"
#include "entities/Entity.h"
#include "terrains/Terrain.h"
#include "mesh/OBJLoader.h"
#include "utils/random/Random.h"

int main(void)
{
	WindowProps window_props = { 800, 600, true };
	window.init(window_props); // window global

	Loader loader;
	MasterRenderer renderer;

	string dragon_model = "dragon/dragon.obj";
	string stall_model = "stall/stall.obj";
	string grass_model = "grass/grassModel.obj";
	string dragon_texture = "snow-layer.png";
	string stall_texture = "stall_tex.png";
	string grass_texture = "grassTexture.png";

	TexturedModel *dragon = new TexturedModel(
		OBJLoader::load_obj_model(dragon_model, &loader), new ModelTexture(loader.load_texture(dragon_texture)));
	dragon->get_texture()->set_shine_damper(10);
	dragon->get_texture()->set_reflectivity(1);

	TexturedModel *grass = new TexturedModel(
		OBJLoader::load_obj_model(grass_model, &loader), new ModelTexture(loader.load_texture(grass_texture)));
	grass->get_texture()->set_has_transparency(true);
	grass->get_texture()->set_use_fake_lighting(true);

	Entity *entity = new Entity(dragon, glm::vec3(0, 0, -30), 0.0, 0.0, 0.0, 1.0);
	Light* light = new Light(glm::vec3(3000, 2000, 2000), glm::vec3(1, 1, 1));

	Terrain *terrain = new Terrain(0, -1, &loader, new ModelTexture(loader.load_texture("grass.png")));
	Terrain *terrain2 = new Terrain(-1, -1, &loader, new ModelTexture(loader.load_texture("grass.png")));

	vector<Entity*> entities;
	for (int i = 0; i < 500; i++)
	{
		entities.push_back(new Entity(grass, glm::vec3(Random::Rand() * 800 - 400, 0, Random::Rand() * -600), 0, 0, 0, 1));
	}

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
		renderer.process_terrain(terrain);
		renderer.process_terrain(terrain2);
		renderer.process_entity(entity);
		for (auto entity : entities)
		{
			renderer.process_entity(entity);
		}
		renderer.render(light, window.get_camera());
		window.update();
	}

	renderer.clean_up();
	loader.clean_up();

	return 0;
}