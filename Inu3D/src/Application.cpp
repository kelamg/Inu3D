#include "renderer/Window.h"
#include "renderer/Loader.h"
#include "renderer/Renderer.h"

int main(void)
{
	WindowProps window_props = { 800, 600, true };
	Window window(window_props);

	Loader loader;
	Renderer renderer;

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
		renderer.render(model);
		window.update();
	}

	return 0;
}