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
	RawModel *model = OBJLoader::load_obj_model(dragon, &loader);
	//Texture *stall_texture = loader.load_texture("stall_tex.png");
	TexturedModel *textured_model = new TexturedModel(model, new ModelTexture(loader.load_texture("snow-layer.png")));
	ModelTexture *texture = textured_model->get_texture();
	texture->set_shine_damper(10);
	texture->set_reflectivity(1);

	Entity *entity = new Entity(textured_model, glm::vec3(0, -10, -30), 0.0, 0.0, 0.0, 1.0);
	Light* light = new Light(glm::vec3(0, 0, -20), glm::vec3(1, 1, 1));

	while (window.is_running())
	{
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