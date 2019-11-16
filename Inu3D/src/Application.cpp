#include "renderer/Window.h"

int main(void)
{
	WindowProps window_props = { 800, 600, true };
	Window window(window_props);

	while (!window.is_running())
	{
		window.clear(0.1f, 0.2f, 0.3f);
		window.update();
	}

	return 0;
}