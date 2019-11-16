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
		// left bottom triangle
		-0.5f,  0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,

		 // right top triangle
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	RawModel *model = loader.load_to_vao(vertices);

	while (!window.is_running())
	{
		window.clear(0.1f, 0.2f, 0.3f);
		renderer.render(model);
		window.update();
	}

	return 0;
}