#pragma once

#include "Common.h"
#include "models/TexturedModel.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void render(TexturedModel *textured_model);
};

