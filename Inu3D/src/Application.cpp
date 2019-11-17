#include "renderer/Window.h"
#include "renderer/Loader.h"
#include "renderer/Renderer.h"
#include "shaders/StaticShader.h"

int main(void)
{
	WindowProps window_props = { 800, 600, true };
	Window window(window_props);

	Loader loader;
	Renderer renderer;
	StaticShader shader;

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
	TexturedModel *texturedModel = new TexturedModel(model, texture);

	while (!window.is_running())
	{
		window.clear(0.1f, 0.2f, 0.3f);
		shader.start();
		renderer.render(texturedModel);
		shader.stop();
		window.update();
	}

	return 0;
}