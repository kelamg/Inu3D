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

	RawModel *model = loader.load_to_vao(vertices, indices);

	while (!window.is_running())
	{
		window.clear(0.1f, 0.2f, 0.3f);
		shader.start();
		renderer.render(model);
		shader.stop();
		window.update();
	}

	return 0;
}